
#include <stdio.h>
static FILE uartout = {0} ;

// create a output function
// This works because Serial.write, although of
// type virtual, already exists.
//// static int uart_putchar (char c, FILE *stream)
int uart_putchar (char c, FILE *stream)
{
    Serial.write(c) ;
    return 0 ;
}

int input[6] = {A0,A1,A2,A3,A4,A5};
void setup() 
{
  Serial.begin(115200); // remember to set baud
  for(int i =0;i<6;i++)
  {
    pinMode(input[i],INPUT_PULLUP);
  }
}
int32_t lastoutput = 0;
int32_t lastinput[6] = {0};
byte lastPINC = 0;
void loop() {
 int count[6] = {0};
  while(millis() - lastoutput <60000){ // per minute
  if(PINC !=0B111111){
    for(int i = 0;i<6;i++){
      if(bitRead(PINC,i)!=1){
        if(millis() - lastinput[i]>1){
          if(bitRead(lastPINC,i) != 0){
            count[i]+=1;
            lastinput[i] = millis();
          }
        }
      }
    }
  }
  lastPINC = PINC;
  }
  lastoutput = millis();
  for(int i = 0;i<6;i++){
    Serial.print(" |");Serial.print(count[i]);Serial.print(" ");
   }
   Serial.println("");
 
}

  
