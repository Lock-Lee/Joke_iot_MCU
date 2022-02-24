    #include <Keypad.h>
#include <Wire.h>

long previousMillis = 0;
long interval = 1000;
int sec  = 0;
char state = '0' ;
int rond = 1;
int reLayMotorR = 4;
int reLayMotorL = 5;
int pumpvax = 6;
int pumpwater = 7;
int reLayLed = 8;
int reLayFan = A3;
int checkDoor =0;
const byte ROWS = 4; //four rows
const byte COLS = 3; // four columns
char keys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

byte rowPins[ROWS] = {9, A3, A2, A0 }; //connect to the row pinouts of the keypad
byte colPins[COLS] = {10, 8, A1}; 
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);
  pinMode(reLayMotorR, OUTPUT);
  pinMode(reLayMotorL, OUTPUT);
  pinMode(reLayFan, OUTPUT);
  pinMode(reLayLed, OUTPUT);
  pinMode(pumpwater, OUTPUT);
  pinMode(pumpvax, OUTPUT);
  
  
 
}

void loop() {
char key = keypad.getKey();
  
if (key){
 state =   key ;
 Serial.println(state);
  }
  else if(state == '1'){
    
    door(state);
  }else if(state == '2'){
      door(state);
  }
 
  else if(state == '3'){
   Serial.println("ทำความเย็น");
     digitalWrite(reLayFan, 1);
      digitalWrite(pumpvax, 1);
  }
   else if(state == '4'){
    digitalWrite(reLayFan, 0);
      digitalWrite(pumpvax, 0);
    
  }
   else if(state == '5'){
     Serial.println("ไฟ");
   
     digitalWrite(reLayLed, 1);
    
  } 
  else if(state == '6'){
     digitalWrite(reLayLed, 0);
    
  }
else if(state == '7'){
   Serial.println("น้ำ");
     digitalWrite(pumpwater, 1);
  }  
else if(state == '8'){
     digitalWrite(pumpwater, 0);
  }  
}
void door(char state) {
  if (state == '1') {
    rond = 1;
     
  }else if(state == '2'){
    rond = 2;
  }
    if ( checkDoor == 0 &&  rond == 1) {
     
        unsigned long currentMillis = millis();
      if (currentMillis - previousMillis > interval && checkDoor == 0) {
      previousMillis = currentMillis;
        sec++;
        Serial.print("1 = ");
        Serial.println(sec);
    }
    else if(sec<12 && checkDoor ==0){
      digitalWrite(reLayMotorR,1);
      digitalWrite(reLayMotorL,0);
    }else if(sec>12){
      checkDoor = 1;
      sec=0;
      digitalWrite(reLayMotorR,0);
      digitalWrite(reLayMotorL,0);
    }
    }else {
     
    }
     if(checkDoor ==1 && rond == 2){
    
        unsigned long currentMillis = millis();
      if (currentMillis - previousMillis > interval) {
      previousMillis = currentMillis;
        sec++;
        Serial.print("2 = ");
        Serial.println(sec);
    }
    else if(sec<12 && checkDoor ==1){
      digitalWrite(reLayMotorR,0);
      digitalWrite(reLayMotorL,1);
    }else if(sec>12){
      checkDoor=0;
      sec =0;
      digitalWrite(reLayMotorR,0);
      digitalWrite(reLayMotorL,0);
    }
    
    }else {
      
    }
      
    
  }
