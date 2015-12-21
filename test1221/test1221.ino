#include <EnableInterrupt.h>
// #include <PinChangeInt.h>

int count=0;
int pf=0;
int tp=0;

void setup() {
    Serial.begin(9600);
    enableInterrupt(A0, &counter, RISING);
    // PCintPort::attachInterrupt(A0, &counter, RISING);
}

void loop() {
    //disableInterrupt(A0);
    // PCintPort::detachInterrupt(A0);
    if (count/2 != tp) {
      Serial.print(count/2);
      Serial.print(' ');
      enableInterrupt(A0, &counter, RISING);
      Serial.println(micros());
      // PCintPort::attachInterrupt(A0, &counter, RISING);
      delay(100);

      tp = count/2;
    }
    /*
    int pin = digitalRead(A0);
    if (pin==HIGH){
      pf++;
      Serial.println(pf);
      delay(500);
    }
    */
}

void counter() {
    count++;
}

//////////////////////////

