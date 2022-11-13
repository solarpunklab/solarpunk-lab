// https://www.youtube.com/watch?v=tVwQ8cb8HbQ
// ATtyny85 chirping and sleep

int analogPin = 3;

/////////////
#include <avr/sleep.h>
void setup() {
  pinMode(PB4, OUTPUT); //BEEP
  pinMode(PB3, INPUT); // ANALOG INPUT FOR RANDOM
//  randomSeed(analogRead(0));
  randomSeed(analogRead(PB3));
  setup_watchdog(7);  //8 seconds
}

/////////////
void loop() {
  sleep();  
}

/////////////
void sleep() {

    digitalWrite (PB4,LOW);
    ADCSRA &= ~_BV(ADEN);                   // ADC off
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);    
    sleep_enable();                         // Sets the Sleep Enable bit in the MCUCR Register (SE BIT)
    sei();                                  // Enable interrupts
    sleep_cpu();                            // sleep

//    cli();                                  // Disable interrupts
//   sleep_disable();                        // Clear SE bit
//    sei();                                  // Enable interrupts 

  
} 

// Watchdog Interrupt Service / is executed when watchdog timed out
ISR(WDT_vect) {
   cli();                                  // Disable interrupts
   sleep_disable();                        // Clear SE bit
   sei();                                  // Enable interrupts 
   chirp(); 

//   setup_watchdog(random(5)+4); // add by tez
//   randomSeed(analogRead(analogPin));
   setup_watchdog(random(5)+random(3) + 2); // add by tez
}
 
// 0=16ms, 1=32ms,2=64ms,3=128ms,4=250ms,5=500ms
// 6=1 sec,7=2 sec, 8=4 sec, 9= 8sec
void setup_watchdog(int ii) {
  byte bb;
  int ww;
  if (ii > 9 ) ii=9;
  bb=ii & 7;
  if (ii > 7) bb|= (1<<5);
  bb|= (1<<WDCE);
  ww=bb;

  MCUSR &= ~(1<<WDRF);
  // start timed sequence
  WDTCR |= (1<<WDCE) | (1<<WDE);
  // set new watchdog timeout value
  WDTCR = bb;
  WDTCR |= _BV(WDIE);
}   

/////////////
void chirp() {
  int inten_rand, chirpNum_rand;
  inten_rand = int(random(2,4));
  chirpNum_rand = int(random(3,6));
  highChirp(inten_rand,chirpNum_rand);
//  delay(100);
  delay(random(50,200));
  if(random(2) == true){
    lowChirp(200,2);
  }
//  delay(100);
  delay(random(50,200));
//  tweet(4,2);
}

/////////////
void highChirp(int intensity, int chirpsNumber){
  int i;
  int x;
  int chirp_delay;
//  chirp_delay = random(6, 9)*4;

  chirp_delay = random(1, 15)*4;

  int reptimes = random(60, 300);
  
  for(int veces=0; veces<=chirpsNumber; veces++){
    for (i=50; i<reptimes; i=(i+1)) // 200
    {
      for  (x=0; x<intensity;  x++)
      {
        digitalWrite (PB4,HIGH);
        delayMicroseconds(i);
        //if(i>300) delayMicroseconds(i);
        //else delayMicroseconds ((400-i));
        digitalWrite (PB4,LOW);
        delayMicroseconds(i);
        //if(i>300) delayMicroseconds(i);
        //else delayMicroseconds ((400-i));
        //delayMicroseconds (i);
      }
    }
    delay(chirp_delay);
    chirp_delay=chirp_delay*0.75;
  }
}

/////////////
void lowChirp(int intensity, int chirpsNumber){
  int i;
  int x;

   int reptimes = random(100, 300);
   
  for(int veces=0; veces<=chirpsNumber; veces++){
    for (i=0; i<reptimes; i++) // 200
    {
      digitalWrite (PB4,HIGH);
      delayMicroseconds(i);
      digitalWrite(PB4,LOW);
      delayMicroseconds(i);
    } 

    int i_hi = random(90,150);
    int i_lo = abs(i_hi - random(30,90));
//    for (i=90; i>80; i--)
    for (i=i_hi; i>i_lo; i--)
    {
      int xrep = random(1,9);
      for  ( x=0; x<xrep;  x++) // 5
      {
        digitalWrite (PB4,HIGH);
        delayMicroseconds (i);
        digitalWrite (PB4,LOW);
        delayMicroseconds (i);
      }
    }
  }
}

/////////////
void tweet(int intensity, int chirpsNumber){
int i;
int x;
//normal chirpsNumber 3, normal intensity 5
for(int veces=0; veces<chirpsNumber; veces++){
  for (int i=80; i>0; i--)
  {
   for  (int x=0; x<intensity;  x++)
   {
     digitalWrite (PB4,HIGH);
     delayMicroseconds (i);
     digitalWrite (PB4,LOW);
     delayMicroseconds (i);
   }
  }
}
delay(1000);
}
