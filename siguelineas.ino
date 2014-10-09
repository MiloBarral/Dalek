#include <Servo.h>

//    <---    <-    .    .    ->    --->
//     179   130   105  102   85     0 
//     179   120   103  101   79     0

Servo Rservo;
Servo Lservo;
//Servo Hservo;
//Servo Bservo;
int LDR_l = A0;
int LDR_r = A1;
int LED_l = A2;
int LED_r = A3;
int Rforward = 140;  // Valor avance, encontrar valor central y jugar
int Lforward = 140;  // 

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

void setup(){
  Lservo.attach(9);
  Rservo.attach(10);
//  Hservo.attach(5);
//  Bservo.attach(6);
}

void loop()
{
  p=analogRead(LDR_l)-analogRead(LDR_r);  // Right-Left
  i=i+p;
  d=p-p_old;
  p_old=p;
  
  if ((p*i)<0) i=0;  	// corrige el overshooting - integral windup

  u=kp*p+ki*i+kd*d;             // Suma PID
  
Rservo.write(Rforward+u);
Lservo.write(Lforward-u);



// ANTENITAS FEEDBACK
int val_l = analogRead(LDR_l);
  val_l = map(val_l, 0, 1023, 100, 255);
  analogWrite(LED_l, val_l);
int val_r = analogRead(LDR_r);
  val_r = map(val_r, 0, 1023, 100, 255);
  analogWrite(LED_r, val_r);
}
