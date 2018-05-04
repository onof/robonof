#include <Servo.h> // include la Libreria Servo.h
 
const int triggerPort = 9;
const int echoPort = 10;
const int led = 13;

const int servo = 8;

Servo myservo; 

long servo_pos = 0;
long max_distance = 0;
long max_distancepos = 0;

long distanza_90 = 0;

void setup() {

  myservo.attach(servo);
 
  pinMode(triggerPort, OUTPUT);
  pinMode(echoPort, INPUT);
  pinMode(led, OUTPUT);
  Serial.begin(9600);
  Serial.println("Sensore Ultrasuoni: OK");
}

void decide() {

  Serial.print("distanza massima: ");
  Serial.print(max_distance);
  Serial.print(" in pos ");
  Serial.print(max_distancepos);

  if(distanza_90 < 20) {
    // vai verso max_distanzapos
    if(max_distancepos < 90) {
      // vai a sinistra
      Serial.println(" vai a sinistra");
    }
    else {
      Serial.println(" vai a destra");
    }
  }
  else {
    Serial.println(" vai dritto");
  }
}

long calcola_distanza() {
  digitalWrite( triggerPort, LOW );
  digitalWrite( triggerPort, HIGH );
  delayMicroseconds( 10 );
  digitalWrite( triggerPort, LOW );
 
  long durata = pulseIn( echoPort, HIGH );
  // Centimetri
  long distanza = 0.034 * durata / 2;

  if( durata > 38000) {
    // fuori portata 
  }
  return distanza;
}
 
void loop() {
  
  servo_pos = (servo_pos + 10) % 180;
  myservo.write(servo_pos);

  if(servo_pos == 0) {
    decide();
    
    max_distance = 0;
  }

  long distanza = calcola_distanza();
    
  if(distanza > max_distance) {
    max_distance = distanza;
    max_distancepos = servo_pos;
  }

  if(servo_pos == 90) {
    distanza_90 = distanza;
  }
  
  delay(10);
}

