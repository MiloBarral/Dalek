// TOWERPRO SG90 modified to continuous rotation with 2.2K ohm SMD resistors movement values:
// <--- <- .STOP. -> --->
// 180 130 105-102 85 0
// 180 120 103-101 79 0
#include <Servo.h>

#define HEAD_SERVO 5
#define BODY_SERVO 6
#define LEFT_SERVO 9
#define RIGHT_SERVO 10
#define LEFT_SENSOR A0
#define RIGHT_SENSOR A1
#define LEFT_LED A2
#define RIGHT_LED A3
#define LEFT_FORWARD 180
#define RIGHT_FORWARD 0

Servo Rservo;
Servo Lservo;
Servo Hservo;
Servo Bservo;
int LED_l = A2;
int LED_r = A3;
int Lforward = 180; // left wheel brakes with --
int Rforward = 0; // right wheel brakes with ++
float kp=.04;
float ki=0.00002;
float kd=50;
float p,d;
float i=0;
float p_old=0;
int u;

void setup(){
  Hservo.attach(HEAD_SERVO);
  Bservo.attach(LEFT_SERVO);
  Lservo.attach(LEFT_SERVO);
  Rservo.attach(RIGHT_SERVO);

  delay(2000);
// Insert some code to get the threshold values for 0 and 1. ¿beep - analogread over white - wait half a second - beep - wait a second - beep -wait half a second -analogread over black?
}

void loop(){
  int val_l = analogRead(LEFT_SENSOR);  // POSIBLE USAR DIRECTAMENTE LO DEL DEFINE Y AHORRAR VARIABLE LDR_l?
  int val_r = analogRead(RIGHT_FORWARD);
  p=val_l-val_r; // left-right
  i=i+p;
  d=p-p_old;
  p_old=p;
  if ((p*i)<0) i=0; // corrects overshooting - integral windup
    u=kp*p+ki*i+kd*d; // Suma PID
    if (u>0){ // turn right
    Lservo.write(Lforward);
    Rservo.write(Rforward+u);
  }
  if (u<0){ // turn left
    Lservo.write(Lforward-u);
    Rservo.write(Rforward);
  }
// Feedback head LEDs
int polarization = 100; // Due to the lack of enough PWM pins in the Arduino PRO MICRO, we map from the value of polarization of the given LED and the full brightness.
val_l = map(val_l, 0, 1023, polarization, 255);
analogWrite(LED_l, val_l);
val_r = map(val_r, 0, 1023, polarization, 255);
analogWrite(LED_r, val_r);
// Head and body random movements
if(nextMillis<millis()){
Hservo.write(random(180));
nextMillis = millis() + random(500, 2000);
}
if(nextMillis<millis()){
Bservo.write(random(180));
nextMillis = millis() + random(500, 2000);
}
/* Other two possibilities
if(i>=veces){ servo.write(random(180)); i=0; } else{i++;}
if(veces<1){ servo.write(random(180)); veces=random(20000, 50000); } else{veces--}
*/
}
