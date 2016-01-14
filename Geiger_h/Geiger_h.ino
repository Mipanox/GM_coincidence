#include <stdio.h>
#define debug 
static FILE uartout = {0} ;

int uart_putchar (char c, FILE *stream)
{
    Serial.write(c) ;
    return 0 ;
}

int  input[6]   = {A0,A1,A2,A3,A4,A5};
byte output[10] = {3, 6,12,24,  7, 14, 28,  15,  30,   31};
//                12,23,34,45,123,234,345,1234,2345,12345

void setup() {
  Serial.begin(9600);
  for (int i=0; i<6; i++)
  {
    pinMode(input[i],INPUT_PULLUP);
  }
  
  #ifdef debug
  Serial.println("Counter Started, the format is:");

  for (int i=0; i<10; i++)
  {
      Serial.print(output[i],BIN);
      Serial.print(" ");
  }
  Serial.println("");
  #endif
}
int32_t lastoutput = 0;
byte    lastPINC   = 0;

void loop() 
{
  uint16_t count[32]      = {0};
  uint16_t dataoutput[10] = {0};
  
  while (millis() - lastoutput < 1000)
  {
    byte data = PINC;
    if(data != 0B111111)
    {
      byte alert = 0;
      uint32_t startCatch = micros();
      
      while (micros() - startCatch < 500)
      { // which pins have been hit cumulatively in this 500 us
        data |= PINC;
      }
      for (int i=0; i<5; i++)
      {
        alert += bitRead(data,i);
      }
      if (alert >= 2)
      {
        if (lastPINC != data)
        {
          count[data] +=1;
        }   
      }
    }
    lastPINC = data;
  }
  lastoutput = millis();

  for (int i=0; i<10; i++)
  {
    dataoutput[i] = count[output[i]];
  }
  
  #ifdef debug
  for(int i=0; i<10; i++)
  {
    Serial.print(dataoutput[i]);
    Serial.print(" ");
  }
  Serial.println("");
  #endif
  
  printf("XDATA=%0100X\r", dataoutput);
}
