//MOTOR Kontrol
int RPwm = 11;//sağ motorun hızı
int RDir = 13;//sağ motorun yönü
int LPwm = 3;//sol motorun hızı
int LDir = 12;//sol motorun yönü

//EDGE & CONTRAST SENSORS
int Redge = A1;
int Ledge = A0;

void Set_Motor (float Lval, float Rval){
  Lval = Lval*2.5; 
  Rval = Rval*2.5; 
  
  if (Lval >=0) { 
      analogWrite(LPwm, Lval);  
      digitalWrite(LDir, LOW);       
      } else {
      Lval=abs(Lval); 
      digitalWrite(LDir, HIGH);  
      analogWrite(LPwm, Lval); 
      }
   if (Rval >=0) {    
      analogWrite(RPwm, Rval);  
      digitalWrite(RDir, HIGH);       
      } else {
      Rval=abs(Rval);     
      digitalWrite(RDir, LOW);  
      analogWrite(RPwm, Rval); 
      }       
}

void setup() {
pinMode(RPwm, OUTPUT);  // 4 tane kanal çıktı olarak atandı
pinMode(RDir, OUTPUT); 
pinMode(LPwm, OUTPUT); 
pinMode(LDir, OUTPUT); 
}

void loop() {
 Start:
 if(analogRead(Ledge)>100 &&analogRead(Redge)>100){//Sol ve sağ sensör siyah zeminde olduğu için motorun düz gitmesi istenir.
    Set_Motor(100,100);
 }
 if(analogRead(Ledge)<100&&analogRead(Redge)>100){//Sol sensör beyaz zeminde, sağ sensör siyah zeminde olduğu için motorun sağa gitmesi istenir.
    Set_Motor(100,-100);
 }
 if(analogRead(Ledge)>100&&analogRead(Redge)<100){//Sol sensör siyah zeminde, sağ sensör beyaz zeminde olduğu için motorun sola gitmesi istenir.
    Set_Motor(-100,100);
 }
 if(analogRead(Ledge)<100&&analogRead(Redge)<100){//Sol ve sağ sensör beyaz zeminde olduğu için motorun geri gitmesi istenir.
    Set_Motor(-100,-100);
 }
 goto Start;
}
