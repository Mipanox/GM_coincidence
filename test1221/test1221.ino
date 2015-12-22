#include <EnableInterrupt.h> // please load this

int count[5]={}; // 5 tubes
int tempc[5]={};
int dt; // tube number = PIC - 1
unsigned long pre_t=0;

void setup() 
{
    Serial.begin(9600);
    // interrupt
    enableInterrupt(A0, &counter, RISING);
    enableInterrupt(A1, &counter, RISING);
    enableInterrupt(A2, &counter, RISING);
    enableInterrupt(A3, &counter, RISING);
    enableInterrupt(A4, &counter, RISING);
}

void loop() 
{
    enableInterrupt(A0, &counter, RISING);
    enableInterrupt(A1, &counter, RISING);
    enableInterrupt(A2, &counter, RISING);
    enableInterrupt(A3, &counter, RISING);
    enableInterrupt(A4, &counter, RISING);

    // delay(50); // take data once per 0.05 s
}

void counter() {
    unsigned long now_t = micros();
    if (now_t - pre_t > 500) // > 500 us ~ pulse width
    {
        dt = PINC-1; // record tube number
        count[dt]++;
        pre_t = now_t;
    }
    Serial.print(dt);
    Serial.print(' ');
    Serial.print(count[dt]/2); // count is always somehow doubled, so divide by 2
    Serial.print(' ');
    Serial.println(micros()); // time stamp, in us

    // output format: #tube count(cumulative) time(start from 0, in us)
}

