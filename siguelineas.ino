#include <Servo.h>

//    TOWERPRO SG90 modified to continuous rotation with 2.2K ohm SMD resistors movement values:
//    <---    <-    .STOP.    ->    --->
//     179   130   105-102   85     0 
//     179   120   103-101   79     0

Servo Rservo;
Servo Lservo;
//Servo Hservo;
//Servo Bservo;
int LDR_l = A0;
int LDR_r = A1;
int LED_l = A2;
int LED_r = A3;
//int Rforward = 50;  // Intermediate value for the servo to go forward
//int Lforward = 140;  // Servos are instaled mirrored, so they have to rotate in opposed directions
int Lforward = 179;
int Rforward = 0;

/* PID part, left aside for now  
int forward=120;
float kp=.04;
float ki=0.00002;
float kd=50;
float p,d;
float i=0;
float p_old=0;
int u;

int val_l =0;
int val_r =0;
*/

void setup(){
  Lservo.attach(9);
  Rservo.attach(10);
//  Hservo.attach(5);
//  Bservo.attach(6);
delay(1000);

// Insert some code to get the threshold values for 0 and 1.
// beep - analogread over white - wait half a second - beep - wait a second - beep -wait half a second -analogread over black?  
}

void loop()
{

int val_l = analogRead(LDR_l);
int val_r = analogRead(LDR_r);

/* PID part, left aside for now  
  p=val_l)-analogRead(val_r);  // Right-Left
  i=i+p;
  d=p-p_old;
  p_old=p;
  
  if ((p*i)<0) i=0;  		// corrige el overshooting - integral windup

  u=kp*p+ki*i+kd*d;             // Suma PID
*/
if (val_l>val_r){               // if left value is higher, turn right slowing (stopping) right wheel
Rservo.write(100);
Lservo.write(Lforward);
}
if (val_l<val_r){
Rservo.write(Rforward);
Lservo.write(100);
}

// Feedback head lights
int polarization = 100;    // Due to the lack of enough PWM pins in the Arduino PRO MICRO, we map from the value of polarization of the given LED and the full brightness.
val_l = map(val_l, 0, 1023, polarization, 255);    
analogWrite(LED_l, val_l);
val_r = map(val_r, 0, 1023, polarization, 255);
analogWrite(LED_r, val_r);
}
