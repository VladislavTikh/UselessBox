#include <Servo.h> //Servo lib
#include <AFMotor.h> // DC Motor liv
Servo doorServo;
Servo handServo;

int switch_pin = 14;               //set switch on pin 14 (analog)
int pir_pin=2;                     //pin for PIR
AF_DCMotor motor(4);
int pirData=0;

int pos = 0;
int selectedMove = 0;             //move selector
int Testmove = 0;                 //test mode: set to move number to test only one selected move
                                  //(set to Zero to run normally i.e: roundrobbin on amm moves)

void setup()
{
  Serial.begin(9600);
  pinMode(switch_pin, INPUT);
  doorServo.attach(9);           //set door servo on Pin 9 pwm
  handServo.attach(10);          //set hand servo on Pin 10 pwm
  doorServo.write(80);           //set door to hiding position
  handServo.write(0);            //set hand to hiding position
 
}


void loop()
{
  if (Testmove != 0)
  {
    selectedMove = Testmove;
  }
 
  //if the switch is on, then move door and hand to switch it off...
  if(digitalRead(switch_pin) == HIGH)
  {   
  if (selectedMove > 4) { selectedMove = 0; } //when all moves are played, repeat the moves from beginning
  if (selectedMove == 0) { switchoff(); }
  else if (selectedMove == 1) { switchoff(); }  
  else if (selectedMove == 2) { switchoffdelay(); }
  else if (selectedMove == 3) { crazydoor(); }
  else if (selectedMove == 4) { rideswitchoff(); } 
  if (Testmove == 0) {
  selectedMove++;         //swith to next move if not in test mode
  }
}
}

   // basic move
   void switchoff()
   {   
   //Moving door
    for(pos = 80; pos < 155; pos += 3)  
    {                                  
    doorServo.write(pos);             
    delay(15);                      
    }
  
    //Moving hand
    for(pos = 0; pos < 129; pos += 4) 
    {                                  
    handServo.write(pos);              
    delay(15);                      
    } 
   
    //hiding hand
    for(pos = 129; pos>=0; pos-=4)     
    {                               
    handServo.write(pos);              
    delay(15);                       
    }
     
    //hiding door
    for(pos = 155; pos>=80; pos-=3)    
    {                               
    doorServo.write(pos);             
    delay(15);                     
    }
   }
    
   // move 2: open and wait, then move hand and wait, then switch of and hide 
    void switchoffdelay()
   {
    //Moving door
    for(pos = 80; pos < 155; pos += 3)  
    {                                  
      doorServo.write(pos);             
      delay(15);                      
    }
    delay(800);
    //Moving hand
    for(pos = 0; pos < 100; pos += 4) 
    {                                  
      handServo.write(pos);              
      delay(15);                      
    }
    delay(1000);
    for(pos = 100; pos < 129; pos += 4) 
    {                                  
      handServo.write(pos);              
      delay(15);                      
    }   
   
    //hiding hand
    for(pos = 129; pos>=0; pos-=5)     
    {                               
      handServo.write(pos);              
      delay(15);                       
    }
     
    //hiding door
    for(pos = 155; pos>=80; pos-=3)    
    {                               
    doorServo.write(pos);             
    delay(15);                          
    }    
   }
 
   //move 3: open door then close it many times, wait, then quickly reoprn a nd switch off and hide.
 
   void crazydoor()
  {
   
   //Moving door
    for(pos = 80; pos < 125; pos += 3)  
    {                                  
    doorServo.write(pos);             
    delay(15);                      
    }
 
    //hiding door
    for(pos = 125; pos>=80; pos-=5)    
    {                               
    doorServo.write(pos);             
    delay(15);                     
    }
   //Moving door
    for(pos = 80; pos < 110; pos += 3)  
    {                                  
    doorServo.write(pos);             
    delay(15);                      
    }
 
    //hiding door
    for(pos = 110; pos>=80; pos-=15)    
    {                               
    doorServo.write(pos);             
    delay(15);                     
    }
    delay(700);
   //Moving door
    for(pos = 80; pos < 125; pos += 3)  
    {                                  
    doorServo.write(pos);             
    delay(15);                      
    }
    delay(700);
    //hiding door
    for(pos = 125; pos>=80; pos-=5)    
    {                               
    doorServo.write(pos);             
    delay(15);                     
    }

   
    //----of switch of----//
  //Moving door
    for(pos = 80; pos < 155; pos += 8)  
    {                                  
    doorServo.write(pos);             
    delay(15);                      
    }
  
    //Moving hand
    for(pos = 0; pos < 129; pos += 3) 
    {                                  
    handServo.write(pos);              
    delay(15);                      
    } 
   
    //hiding hand
    for(pos = 129; pos>=0; pos-=3)     
    {                               
    handServo.write(pos);              
    delay(15);                       
    }
     
    //hiding door
    for(pos = 155; pos>=80; pos-=15)    
    {                               
    doorServo.write(pos);             
    delay(15);                     
    }   
   
  }  
  
   void rideswitchoff()
   {   
   //Moving door
    for(pos = 80; pos < 155; pos += 3)  
    {                                  
      doorServo.write(pos);             
      delay(15);                      
    }
     //Wait for opening door than track moves
    delay(1500);
    pirData=digitalRead(pir_pin);
    //motor run forward and backwards
    if(pirData==HIGH)
    {
      motor.run(FORWARD);
      delay(100);
      motor.run(RELEASE);
      delay(100);
      motor.run(BACKWARDS);
      delay(300);  
    }
    //Moving hand
    for(pos = 0; pos < 129; pos += 4) 
    {                                  
      handServo.write(pos);              
      delay(15);                      
    }    
    //hiding hand
    for(pos = 129; pos>=0; pos-=4)     
    {                               
      handServo.write(pos);              
      delay(15);                       
    }    
    //hiding door
    for(pos = 155; pos>=80; pos-=3)    
    {                               
      doorServo.write(pos);             
      delay(15);                     
    }
   }
