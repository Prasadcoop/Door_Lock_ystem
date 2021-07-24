#include <Key.h>
#include <Keypad.h>
#include<LiquidCrystal.h>
#include<Wire.h>
#include<Servo.h>
Servo myservo;
int pos=0;

const int ROW_NUM = 4; //four rows
const int COLUMN_NUM = 3; //three columns

char keys[ROW_NUM][COLUMN_NUM] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

byte pin_rows[ROW_NUM] = {3,2,1,0}; //connect to the row pinouts of the keypad
byte pin_column[COLUMN_NUM] = {4,5,6}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM );

LiquidCrystal lcd(13,12,11,10,9,8);
char keycount=0;
char code[4];
char userInput[90];
void setup(){
 
 lcd.begin(16,2);
 lcd.print("Password Aceess:");
 lcd.setCursor(0,1);
 lcd.cursor();
 myservo.attach(7);
}

void loop(){
  char key = keypad.getKey();
 
  if(key&&(keycount<4)&&(key !='*')&&(key!='#')){
 
    lcd.print('$');
    code[keycount]=key;
    keycount++;
    
  }
  if(key=='*'){
   // lcd.print("Password Aceess:");
    lcd.setCursor(0 ,1);
   // lcd.clear();
   // delay(1000);
   clearData();
    
  }
  if(key=='#'){
    if((code[0]=='1')&&(code[1]=='2')&&(code[2]=='3')&&(code[3]=='4'))
    {
     
      for(pos=0;pos<=180;pos+=1)
      {
        lcd.setCursor(0,1);
        lcd.print("Door Open");
        myservo.write(pos);
        delay(25);
        clearData();
        
      }
      for(pos=180; pos>=0; pos-=1){
        myservo.write(pos); 
        lcd.setCursor(0,1);
        
       }
 
     
      
    }
    else{
      lcd.setCursor(0,1);
      lcd.print("Invalid");
      delay(1000);
    }
    
  }
}
void Lock(){
  lcd.setCursor(0,1);
  lcd.print("Door Locked");
  delay(1000);
  lcd.setCursor(0,1);
  lcd.print(" ");
  lcd.setCursor(0,1);
  keycount=0;
}
void clearData(){
  while(keycount !=0){
    userInput[keycount--]=0;
  }
  setup();
}
