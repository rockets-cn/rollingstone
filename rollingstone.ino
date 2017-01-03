/* -----rollingstone 蓝牙两轮小车控制程序 
//------2016.6.29 by LL
//------适用于Romeo BLE mini 控制器
//http://www.dfrobot.com.cn/goods-1182.html
*/
#include "GoBLE.h"
#include <Romeo_m.h>

#define LED 13

 //GoBLE Goble(Serial);
 int joystickX, joystickY;   
 int buttonState[7];
 unsigned int led_count;
 
void setup() {
  Romeo_m.Initialise();
  Goble.begin();
  pinMode(LED,OUTPUT);
}

void loop() {
  
 if (Goble.available()) 
 {
      readGoBle();
      motorContrl();
  }
  delayLedBlink();//delay 10ms and led blink

}
//读取GoBle所有按键摇杆值
//read all value of joystick from GoBle
 void readGoBle()
 {
    // read joystick value when there's valid command from bluetooth
    joystickX = Goble.readJoystickX();
    joystickY = Goble.readJoystickY();
    // read button state when there's valid command from bluetooth
    buttonState[SWITCH_UP]     = Goble.readSwitchUp();
    buttonState[SWITCH_DOWN]   = Goble.readSwitchDown();
    buttonState[SWITCH_LEFT]   = Goble.readSwitchRight();
    buttonState[SWITCH_RIGHT]  = Goble.readSwitchLeft();
    buttonState[SWITCH_SELECT] = Goble.readSwitchSelect();
    buttonState[SWITCH_START]  = Goble.readSwitchStart();
    /*Serial.println("========================");
     Serial.print("Joystick Value: ");
    Serial.print(joystickX);
    Serial.print("  ");
    Serial.println(joystickY);
    for (int i = 1; i <= 6; i++) {
      if (buttonState[i] == PRESSED) {
        Serial.print(" ID: ");
        Serial.print(i);
        Serial.print("\t ");
        Serial.println("Pressed!");
      }
    
      if (buttonState[i] == RELEASED){
        Serial.print("ID: ");
        Serial.print(i);
        Serial.print("\t ");
        Serial.println("Released!");
      }
    }*/
 }
 //根据GoBle按键值进行小车运动控制
//use joystick to control the motion of the Rollingstone
 //摇杆左右为转大弯，按键左右为原地转弯
//joystick for the tune, button for the circle.
 void motorContrl()
 {
    if ((buttonState[SWITCH_UP] == PRESSED)||((joystickX>128)&&(joystickY>=64)&&(joystickY<=192)))
    {
      Romeo_m.motorControl(Forward,200,Forward,200);//前进
     //fowarwd
      return;//结束子函数
    }
  
    if ((buttonState[SWITCH_DOWN] == PRESSED)||((joystickX<128)&&(joystickY>=64)&&(joystickY<=192)))
   {
     Romeo_m.motorControl(Reverse,150,Reverse,150);//后退
    //backward
     return;//结束子函数
   }
   
    if(buttonState[SWITCH_LEFT] == PRESSED)
    {
        Romeo_m.motorControl(Reverse,100,Forward,100);//左转
     //turn left
        return;//结束子函数
    }
    
    if((joystickY<128 )&&(joystickX>=64 )&&( joystickX<=192) )
   {
     
       Romeo_m.motorControl_M1(Forward,200);//左转大弯
    //go left
       Romeo_m.motorControl_M2(Forward,80);
       
        return;//结束子函数
   }
   
    if( buttonState[SWITCH_RIGHT] == PRESSED)
    {
        Romeo_m.motorControl(Forward,100,Reverse,100);//右转
     //turn right
        return;//结束子函数
    }
    
    if((joystickY>128)&&(joystickX>=64)&&(joystickX<=192))
    {
       
        Romeo_m.motorControl_M2(Forward,200); //右转大弯
     //go right
        Romeo_m.motorControl_M1(Forward,80);
  
        return;//结束子函数
    }
    
    Romeo_m.motorStop();//没有按键按下则停止
  //stop when no value
 }
//led blink函数，每次执行延时10ms，100次时执行一次电平反向
 void delayLedBlink()
 {
    delay(10);
  led_count++;
 if(led_count>100) 
 {    
    digitalWrite(LED,!digitalRead(LED)); 
    led_count=0;
 }
 }
 
