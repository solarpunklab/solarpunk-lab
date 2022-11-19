#include <Arduino.h>
#include <analogWrite.h>

int ledPin = 2; // or 2
int pumpPin = 23;
long unsigned int pumpONtime = 60 * 1000 ;
long unsigned int pumpOFFtime = 15 * 60 * 1000;
bool pumpstate = false;

//////////////////////////////
void setup()
{
    pinMode(ledPin, OUTPUT);
    pinMode(pumpPin, OUTPUT);
    Serial.begin(112500);

    Serial.println(">> INIT PUMP TIMER TASK");
    
    /* create a new task here */
//    xTaskCreate(
//    pumpTask, /* Task function. */
//    "pump Task", /* name of task. */
//    10000, /* Stack size of task */
//    NULL, /* parameter of the task */
//    1, /* priority of the task */
//    NULL); /* Task handle to keep track of created task */

    pumpstate = false;

    xTaskCreate(pumpTask, "pump Task", 1000, NULL, 1, NULL);
}
 
//////////////////////////////
void loop()
{
//    Serial.println(">> ESP32 main loop");
//    delay(1000);
}


////////////////////////////// 
/* this function will be invoked when additionalTask was created */
void pumpTask( void * parameter )
{

  for(;;){
    

    if(pumpstate == false){
        pumpstate = true;
        Serial.println("switching pump ON");
        digitalWrite(ledPin, HIGH);
        digitalWrite(pumpPin, HIGH);
  //      analogWrite(pumpPin, 0);
        delay(pumpONtime); 
    }else{
        pumpstate = false;
        Serial.println("switching pump OFF");
        digitalWrite(ledPin, LOW);
        digitalWrite(pumpPin, LOW);
  //      analogWrite(pumpPin, 0);
        delay(pumpOFFtime);    
    }

  }
  
  
//  }
  /* delete a task when finish,
  this will never happen because this is infinity loop */
//  vTaskDelete( NULL );
//  xTaskCreate(pumpTask, "pump Task", 1000, NULL, 1, NULL);
}
