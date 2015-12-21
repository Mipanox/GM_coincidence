#include <EnableInterrupt.h>

int count[5]={}; // 5 tubes
int tempc[5]={};
int dt;
unsigned long pre_t=0;

void setup() 
{
    Serial.begin(9600);
    
    enableInterrupt(A0, &counter, RISING);
    enableInterrupt(A1, &counter, RISING);
    enableInterrupt(A2, &counter, RISING);
    enableInterrupt(A3, &counter, RISING);
    enableInterrupt(A4, &counter, RISING);
}

void loop() 
{
    /*
    if (count[0]/2!=tempc[0] ||
        count[1]/2!=tempc[1] ||
        count[2]/2!=tempc[2] ||
        count[3]/2!=tempc[3] ||
        count[4]/2!=tempc[4] ) 
    {
        Serial.print(dt);
        Serial.print(' ');
        Serial.print(count[dt]/2);
        Serial.print(' ');
        Serial.println(micros()); // time stamp for later analysis, us

        tempc[dt]=count[dt]/2;
    }
    */
    enableInterrupt(A0, &counter, RISING);
    enableInterrupt(A1, &counter, RISING);
    enableInterrupt(A2, &counter, RISING);
    enableInterrupt(A3, &counter, RISING);
    enableInterrupt(A4, &counter, RISING);

    // delay(50); // take data once per 0.05 s
}

void counter() {
    unsigned long now_t = micros();
    if (now_t - pre_t > 500)
    {
        dt = PINC-1;
        count[dt]++;
        pre_t = now_t;
    }
    Serial.print(dt);
    Serial.print(' ');
    Serial.print(count[dt]/2);
    Serial.print(' ');
    Serial.println(micros()); // time stamp, in us
}

