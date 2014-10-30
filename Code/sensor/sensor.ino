// Getting the same input from both LDR
// Check with serial monitor and adjust until getting 0

int analogInPin = A0;  // Analog output pin that the LED is attached to
int analogInPin1 = A1;  

int sensorValue = 0;        // value read from the pot
int sensorValue1 = 0; 

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600); 
}

void loop() {
  // read the analog in value:
  sensorValue = analogRead(analogInPin);            
  sensorValue1 = analogRead(analogInPin1);        

  // print the results to the serial monitor:
  Serial.print("sensorA0 = " );                       
  Serial.println(sensorValue);      
  Serial.print(" sensorA1 = " );                       
  Serial.println(sensorValue1);  
  Serial.println(sensorValue1-sensorValue); 


  // wait 2 milliseconds before the next loop
  // for the analog-to-digital converter to settle
  // after the last reading:
  delay(100);
}
