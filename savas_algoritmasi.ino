//OPPONENT SENSORS
int LSens = A2;
int RSens = A4;
int MSens = A3;

int LFSens = A5;
int RFSens = 4;

//EDGE & CONTRAST SENSORS
int Redge = A1;
int Ledge = A0;

//TRIMPOTS
int SPD = A7;
int TRN = A6;

//LED & BUZZER
int buzzer = 9;
int ArduLed = 8;

// DIPSWITCH & BUTTON
int Button = 10; // Can be used as start pin too.
int DS1 = 5;
int DS2 = 6;
int DS3 = 7;

//VALUES
int EdgeTurn = 190; 
int Duration; 
int LastValue = 5; 

//motor kontrol
int RPwm = 11;
int RDir = 13;

int LPwm = 3;
int LDir = 12; 

//SETUP-------------------------------------------------
void setup() {
  
  pinMode(LSens, INPUT);    // Left Opponent Sensor Input
  pinMode(RSens, INPUT);    // Right Opponent Sensor Input
  pinMode(MSens, INPUT);    // Middle Opponent Sensor Input
  
  pinMode(buzzer, OUTPUT);  // Buzzer Declared as Output
  pinMode(ArduLed, OUTPUT); // Buzzer Declared as Output
  pinMode(Button, INPUT); // Buzzer Declared as Output
  
  pinMode(RPwm, OUTPUT);  // Four PWM Channel Declared as Output
  pinMode(RDir, OUTPUT); 
  pinMode(LPwm, OUTPUT); 
  pinMode(LDir, OUTPUT); 
  
  digitalWrite(buzzer, LOW); // Buzzer Pin Made Low for Silence :)
  digitalWrite(ArduLed, LOW);  // Arduino Mode Led Made Low
  digitalWrite(DS1, HIGH); // 3 Dipswitch Pin Pullups Made
  digitalWrite(DS2, HIGH);
  digitalWrite(DS3, HIGH);
  
  digitalWrite(RFSens, HIGH); 
  digitalWrite(MSens, HIGH); 
  
  Serial.begin(9600);
  
  tone(9, 523, 300);
  delay(300);
  noTone(9); 
}

//setMotor---------------------------------------
void setMotor(float Lval, float Rval, int timex){
  Lval = Lval*2.5;
  Rval = Rval*2.5; 
  
  if (Lval >=0) { 
    analogWrite(LPwm, Lval);  
    digitalWrite(LDir, HIGH);       
  } 
  else {
    Lval=abs(Lval); 
    digitalWrite(LDir, LOW);  
    analogWrite(LPwm, Lval); 
  }
  
  if (Rval >=0) {    
    analogWrite(RPwm, Rval);  
    digitalWrite(RDir, HIGH);       
  } 
  else {
    Rval=abs(Rval);     
    digitalWrite(RDir, LOW);  
    analogWrite(RPwm, Rval); 
  }      
  delay(timex);
}

//LOOP-----------------------------------------
void loop() {
  digitalWrite(RPwm, LOW);
  digitalWrite(LPwm, LOW);
  tone(buzzer, 18, 100); 

  Start:
    /// Edge Sensor Control Routine ///
    digitalWrite(ArduLed, LOW);
   if (analogRead(Ledge)>100 && analogRead(Redge)< 100) {
     digitalWrite(buzzer, LOW);
     digitalWrite(ArduLed, HIGH);
     setMotor(-100, -100,35); // Geri   
     setMotor(-100,100, EdgeTurn); // Left f, Right b, 
     LastValue=5;
   }
   else  if (analogRead(Ledge)< 100 && analogRead(Redge)> 100) {
     digitalWrite(buzzer, LOW);
     digitalWrite(ArduLed, HIGH);
     setMotor(-100, -100,35); // Back 35 Milliseconds
     setMotor(100, -100, EdgeTurn); // Right f, Left b, 
     LastValue=5;
  }
  else  if (analogRead(Ledge)> 100 && analogRead(Redge)> 100) {
     digitalWrite(buzzer, LOW);
     digitalWrite(ArduLed, HIGH);
     setMotor(-100, -100,35); // Back 35 Milliseconds    
     setMotor(100, -100, EdgeTurn); // Right b, Left f, 
     LastValue=5; 
    
  }else
    /// Opponent Sensor Control Routine ///
    if (digitalRead(MSens)==HIGH) {setMotor(100, 100,1); digitalWrite(buzzer, HIGH); LastValue=5;} else
    if (digitalRead(LSens)== HIGH) {setMotor(-50, 50,1); digitalWrite(buzzer, HIGH); LastValue=7;} else
    if (digitalRead(RSens)==HIGH) {setMotor(50, -50,1); digitalWrite(buzzer, HIGH); LastValue=3;} else
    {
    digitalWrite(buzzer, LOW);
    
    if (LastValue==5) { setMotor(40, 40,1);} else 
    if (LastValue==7) { setMotor(-20, 80,2);} else  
    if (LastValue==3) { setMotor(80, -20,2);}  
    }
  goto Start;
}
