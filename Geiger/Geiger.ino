#include <stdio.h>
static FILE uartout = {0};

/** static int uart_putchar (char c, FILE *stream)
 -- above not working in OSX, so removed static in below: **/
int uart_putchar (char c, FILE *stream)
{
  Serial.write(c);
  return 0;
}

int input[6] = {A0,A1,A2,A3,A4,A5};
void setup() 
{
  Serial.begin(115200); // remember to set baud in monitor
  for (int i=0; i<6; i++)
  {
    pinMode(input[i],INPUT_PULLUP);
  }
}

/* print count */
void single_tube(int cnt[])
{
  for (int i=0; i<6; i++)
  {
    Serial.print(cnt[i]);
    Serial.print(" ");
  }
   Serial.println("");
}

void coincidence(int cn[])
{
  for (int i=0; i<64; i++)
  {
    Serial.print(cn[i]);
    Serial.print(" ");
  }
  Serial.println("");
}

/////////////////////////////////////////
int32_t lastoutput = 0;
int32_t lastcoin   = 0;
int32_t lastinput[6] = {0};
byte lastPINC = 0;

void loop() 
{
  int count[6]     = {0};
  int lastcount[6] = {0};
  int coin[64]     = {0}; // 2^6
  
  while (millis() - lastoutput < 1000) // output per min
  {
    byte pinchange = 0;
    int  pinchc    = 0;

    for (int i=0; i<6; i++) lastcount[i] = count[i];
    while (micros() - lastcoin < 500) // coincidence interval = 500 us
    {
      //// record hit in each tube ////
      if (PINC != 0B111111)
      {  
        for (int i=0; i<6; i++)
        {
          if (bitRead(PINC,i)!=1) // get lowering edges
          {
            if (millis() - lastinput[i] > 1) // debouncing for 1 ms
            {
              if (bitRead(lastPINC,i) != 0)
              {
                count[i] += 1;
                lastinput[i] = millis();
              }
            }
          }
        }
      }
    lastPINC = PINC;
    }
    lastcoin = micros();

    //// check which tubes have been hit
    for (int i=0; i<6; i++)
    {
      if (count[i] != lastcount[i])
      {
        bitWrite(pinchange,i,1);
        pinchc += 1;
      }
    }
    //// count coincidence 
    if (pinchc >= 2) // if coincidence happens
    {
      int whichpins = int(pinchange);
      coin[whichpins] += 1;
    }
  }
  lastoutput = millis();
  
  /* select to print single tube countings or multi-tube coincidence */
  single_tube(count);
  // coincidence(coin);
}
  
