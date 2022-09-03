#include <UTFTGLUE.h>
#include <TimeLib.h>
#include <TouchScreen.h>

#define MINPRESSURE 10
#define MAXPRESSURE 1000

#define driver1_in1 30
#define driver1_in2 31
#define driver1_in3 32
#define driver1_in4 33
#define driver1_enA 10
#define driver1_enB 10

#define driver2_in1 22
#define driver2_in2 35

#define driver2_enA 12
#define driver2_enB 13

#define driver3_in1 36
#define driver3_in2 37
#define driver3_in3 38
#define driver3_in4 39
#define driver3_enA 12
#define driver3_enB 13


const int XP = 9, XM = A3, YP = A2, YM = 8;
const int TS_LEFT = 158, TS_RT = 890, TS_TOP = 89, TS_BOT = 907;
int x, y, currentpage;
int IRsensor1 = 2, IRsensor2 = 2, IRsensor3 = 2, IRsensor4 = 2 , IRsensor5 = 2, IRsensor1_old, IRsensor2_old, IRsensor3_old, IRsensor4_old, IRsensor5_old , Left, M1_Speed = 100, M2_Speed = 100;
unsigned long myTime;

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
UTFTGLUE LCD(0, A2, A1, A3, A4, A0);

void loadingscreen() {                 //loading screen
  LCD.fillScr(255, 255, 255);       //FRAME
  LCD.setColor(192, 192, 192);
  LCD.fillRect(0, 0, 480, 30);
  LCD.fillRect(0, 0, 10, 320);
  LCD.fillRect(470, 0, 480, 320);
  LCD.fillRect(0, 310, 480, 320);
  LCD.setFont(SmallFont);
  LCD.setColor(0, 0, 0);
  LCD.print("Developed by 3rd year Embedded System students", CENTER, 310); //FRAME

  LCD.setFont(BigFont);                                                     //loading screen content
  LCD.setBackColor(255, 255, 255);
  LCD.setColor(0, 0, 0);
  LCD.print("Stereo Garage", CENTER, 10);
  delay(1000);
  LCD.print("Quinee Paalaman", CENTER, 118);
  LCD.print("Sheera Ciano", CENTER, 133);
  LCD.print("Lady Cathy Yocor", CENTER, 148);
  LCD.print("Jerome Rendon", CENTER, 163);
  LCD.print("Oriel Alforque", CENTER, 178);
  delay(1500);
  LCD.clrScr();
}
//MAIN MENU
void mainmenu() {                                                           //main menu content
  LCD.setFont(BigFont);                                                     //FRAME
  LCD.fillScr(255, 255, 255);
  LCD.setColor(192, 192, 192);
  LCD.fillRect(0, 0, 480, 30);
  LCD.fillRect(0, 0, 10, 320);
  LCD.fillRect(470, 0, 480, 320);
  LCD.fillRect(0, 310, 480, 320);
  LCD.setColor(0, 0, 0);
  LCD.setBackColor(192, 192, 192);
  LCD.print("PARKING SYSTEM", CENTER, 7);
  LCD.setFont(SmallFont);
  LCD.setColor(0, 0, 0);
  LCD.print("Developed by 3rd year Embedded System students", CENTER, 310); //FRAME

  LCD.setFont(BigFont);                                                     //getcar UI
  LCD.setBackColor(255, 255, 255);
  LCD.print("Main Menu", 43, 50);
  LCD.setColor(255, 0, 0);
  LCD.drawLine(30, 83, 200, 83);                                           //upper line
  LCD.drawLine(30, 250, 200, 250);                                         //botton line
  LCD.setBackColor(16, 167, 103);
  LCD.setColor(16, 167, 103);
  LCD.fillRoundRect(40, 200, 190, 240);
  LCD.setColor(0, 0, 0);
  LCD.print("GET CAR", 55, 210);

  LCD.setBackColor(255, 255, 255);
  LCD.setColor(101, 67, 33);
  LCD.setFont(SmallFont);
  LCD.print("Date: August 22,2022", 35, 260);                               //date
  LCD.setFont(BigFont);
  LCD.print("Time:", 13, 280);                                             //time

  LCD.setFont(BigFont);
  LCD.setColor(0, 0, 0);
  LCD.drawRoundRect(40, 200, 190, 240);
  LCD.setBackColor(16, 167, 103);
  LCD.setColor(16, 167, 103);                                              //parkcar UI
  LCD.fillRoundRect(40, 150, 190, 190);
  LCD.setColor(0, 0, 0);
  LCD.print("PARK CAR", 50 , 160);
  LCD.setColor(0, 0, 0);
  LCD.drawRoundRect(40, 150, 190, 190);

  LCD.setColor(16, 167, 103);                                              //platform status
  LCD.fillRoundRect(40, 100, 190, 140);
  LCD.setColor(0, 0, 0);
  LCD.print("Platforms", 45, 110);
  LCD.setColor(0, 0, 0);
  LCD.drawRoundRect(40, 100, 190, 140);

  LCD.setColor(0, 0, 0);                                                   //NOTICE BOARD
  LCD.fillRoundRect(220, 50, 440, 300);
  LCD.setColor(255, 255, 255);
  LCD.setBackColor(0, 0, 0);
  LCD.print("Notice Board:", 230, 50);
  LCD.setColor(0, 0, 255);
  LCD.drawLine(230, 83, 430, 83);                                          //upper line
  LCD.drawLine(230, 290, 430, 290);                                          //upper line
  LCD.drawRoundRect(220, 50, 440, 300);

}
void setup() {
  LCD.InitLCD();
  currentpage = 0;
  Serial.begin(9600);
  loadingscreen();
  mainmenu();
  pinMode(A8, INPUT);
  pinMode(A9, INPUT);
  pinMode(A10, INPUT);
  pinMode(A11, INPUT);
  pinMode(A12, INPUT);

  pinMode(driver1_in1, OUTPUT);
  pinMode(driver1_in2, OUTPUT);
  pinMode(driver1_in3, OUTPUT);
  pinMode(driver1_in4, OUTPUT);

  pinMode(driver1_enA, OUTPUT);
  pinMode(driver1_enB, OUTPUT);

  pinMode(driver2_in1, OUTPUT);
  pinMode(driver2_in2, OUTPUT);


  pinMode(driver2_enA, OUTPUT);
  pinMode(driver2_enB, OUTPUT);


  pinMode(driver3_in1, OUTPUT);
  pinMode(driver3_in2, OUTPUT);
  pinMode(driver3_enA, OUTPUT);
  pinMode(driver3_enB, OUTPUT);
}

void loop() {
  int IRsensor1 = digitalRead(A8);
  int IRsensor2 = digitalRead(A8);
  int IRsensor3 = digitalRead(A8);
  int IRsensor4 = digitalRead(A8);
  int IRsensor5 = digitalRead(A8);

  TSPoint p = ts.getPoint();                                                // Read pislit
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);

  get_status();                                                             //initialize get_status para mag loop ang IR reading
  if (p.z > 0 ) {                                                           //for ui purposes para makita sa serial monitor asa ni pislit
    Serial.print("\tmao ni width = "); Serial.print(p.x);
    Serial.print("\tmao ni height = "); Serial.print(p.y);
  }
  //MAIN MENU TOUCH
  if (currentpage == 0) {
    if (p.x > 449 && p.x < 539 && p.y > 152 && p.y < 430) {                 //park car page
      currentpage = 1;
      LCD.setColor(15, 134, 86);
      LCD.fillRoundRect(40, 150, 190, 190);
      LCD.clrScr();
      parkcar();
    }
    if (p.x > 338 && p.x < 410 && p.y > 152 && p.y < 430) {                  //get car page
      Serial.println("get");
      currentpage = 2;
      LCD.setColor(15, 134, 86);
      LCD.fillRoundRect(40, 200, 190, 240);
      LCD.clrScr();
      getcar();
    }

    if  (p.x > 579 && p.x < 640 && p.y > 152 && p.y < 430) {                //platform status page
      Serial.println("platform");
      currentpage =  3;
      LCD.setColor(15, 134, 86);
      LCD.fillRoundRect(40, 100, 190, 140);
      LCD.clrScr();
      platform_status();
    }
  }
  //BACK BUTTON TOUCH
  if (currentpage == 1 || currentpage == 2 || currentpage == 3 ) {         //back button for all pages
    if (p.x > 761 && p.x < 800 && p.y > 113 && p.y < 194) {
      currentpage = 0;
      LCD.setColor(139, 0, 0);
      LCD.fillRect(20, 40, 70, 66);
      LCD.clrScr();
      mainmenu();
      IRsensor1_old = 2;                                                  //reset for IRsensor1 para mo print bsag mo back
      IRsensor2_old = 2;
      IRsensor3_old = 2;
      IRsensor4_old = 2;
      IRsensor5_old = 2;
    }
  }
  if (currentpage == 4 || currentpage == 5 || currentpage == 6 || currentpage == 7 || currentpage == 8 ) {
    if (p.x > 761 && p.x < 800 && p.y > 113 && p.y < 194) {
      currentpage = 1;
      LCD.setColor(139, 0, 0);
      LCD.fillRect(20, 40, 70, 66);
      LCD.clrScr();
      parkcar();
      IRsensor1_old = 2;                                                  //reset for IRsensor1 para mo print bsag mo back
      IRsensor2_old = 2;
      IRsensor3_old = 2;
      IRsensor4_old = 2;
      IRsensor5_old = 2;
    }
  }
  if (currentpage == 1) {
    if (p.x > 243 && p.x < 374 && p.y > 275 && p.y < 400) {               //FOR PLATFORM 1
      currentpage = 4;
      LCD.setColor(0, 0, 0);
      LCD.fillRoundRect(110, 215, 180, 275);
      LCD.clrScr();
      control_page_for_gfloor();
    }
    if (p.x > 243 && p.x < 374 && p.y > 503 && p.y < 611) {               //FOR PLATFORM 2
      currentpage = 5;
      LCD.setColor(0, 0, 0);
      LCD.fillRoundRect(225, 215, 295, 275);
      LCD.clrScr();
      control_page_for_gfloor();
    }
    if (p.x > 509 && p.x < 640 && p.y > 280 && p.y < 400) {               //FOR PLATFORM 3
      currentpage = 6;
      LCD.setColor(0, 0, 0);
      LCD.fillRect(110, 110, 180, 170);
      LCD.clrScr();
      control_page_for_1floor();
    }
    if (p.x > 509 && p.x < 640 && p.y > 490 && p.y < 616) {               //FOR PLATFORM 4
      currentpage = 7;
      LCD.setColor(0, 0, 0);
      LCD.fillRoundRect(225, 110, 295, 170);
      LCD.clrScr();
      control_page_for_1floor();
    }
    if (p.x > 509 && p.x < 640 && p.y > 744 && p.y < 862) {               //FOR PLATFORM 5
      currentpage = 8;
      LCD.setColor(0, 0, 0);
      LCD.fillRoundRect(355, 110, 425, 170);
      LCD.clrScr();
      control_page_for_1floor();
    }
  }
  // MOTOR CONTROL
  if (currentpage == 4) {                                             // PLATFORM 1
    if (p.x > 230 && p.x < 673 && p.y > 200 && p.y < 476) {           //left
      digitalWrite(driver1_in1, HIGH);
      digitalWrite(driver1_in2, LOW);
      digitalWrite(driver1_in3, LOW);
      digitalWrite(driver1_in4, LOW);

      analogWrite(driver1_enA, M1_Speed);
      analogWrite(driver1_enB, M2_Speed);
    }
    if (p.x > 240 && p.x < 689 && p.y > 572 && p.y < 839) {          //RIGHT
      digitalWrite(driver1_in1, LOW);
      digitalWrite(driver1_in2, HIGH);
      digitalWrite(driver1_in3, LOW);
      digitalWrite(driver1_in4, LOW);

      analogWrite(driver1_enA, M1_Speed);
      analogWrite(driver1_enB, M2_Speed);
    }
    if (p.z == 0) {
      digitalWrite(driver1_in1, LOW);
      digitalWrite(driver1_in2, LOW);
      digitalWrite(driver1_in3, LOW);
      digitalWrite(driver1_in4, LOW);
    }
  }
  if (currentpage == 5) {                                             // PLATFORM 2
    if (p.x > 230 && p.x < 673 && p.y > 200 && p.y < 476) {
      digitalWrite(driver1_in1, LOW);
      digitalWrite(driver1_in2, LOW);
      digitalWrite(driver1_in3, LOW);
      digitalWrite(driver1_in4, HIGH);

      analogWrite(driver1_enA, M1_Speed);
      analogWrite(driver1_enB, M2_Speed);
    }
    if (p.x > 240 && p.x < 689 && p.y > 572 && p.y < 839) {
      digitalWrite(driver1_in1, LOW);
      digitalWrite(driver1_in2, LOW);
      digitalWrite(driver1_in3, HIGH);
      digitalWrite(driver1_in4, LOW);

      analogWrite(driver1_enA, M1_Speed);
      analogWrite(driver1_enB, M2_Speed);
    }
    if (p.z == 0) {
      digitalWrite(driver1_in1, LOW);
      digitalWrite(driver1_in2, LOW);
      digitalWrite(driver1_in3, LOW);
      digitalWrite(driver1_in4, LOW);
    }
  }
  if (currentpage == 6) {                                             // PLATFORM 3
    if (p.x > 481 && p.x < 700 && p.y > 353 && p.y < 686) {     // up
      digitalWrite(driver3_in3, HIGH);
      digitalWrite(driver3_in4, LOW);
      analogWrite(driver2_enA, M1_Speed);
      analogWrite(driver2_enB, M2_Speed);
    }
    if (p.x > 220 && p.x < 428 && p.y > 353 && p.y < 686) {
      digitalWrite(driver3_in3, LOW);
      digitalWrite(driver3_in4, HIGH);
      analogWrite(driver2_enA, M1_Speed);
      analogWrite(driver2_enB, M2_Speed);
    }
    if (p.z == 0) {
      digitalWrite(driver3_in3, LOW);
      digitalWrite(driver3_in4, LOW);
    }
  }
  if (currentpage == 7) {                                             // PLATFORM 4
    if (p.x > 481 && p.x < 700 && p.y > 353 && p.y < 686) {
      digitalWrite(driver3_in1, LOW);
      digitalWrite(driver3_in2, HIGH);

      analogWrite(driver2_enA, M1_Speed);
      analogWrite(driver2_enB, M2_Speed);
    }
    if (p.x > 220 && p.x < 428 && p.y > 353 && p.y < 686) {
      digitalWrite(driver3_in1, HIGH);
      digitalWrite(driver3_in2, LOW);

      analogWrite(driver2_enA, M1_Speed);
      analogWrite(driver2_enB, M2_Speed);
    }
    if (p.z == 0) {
      digitalWrite(driver3_in1, LOW);
      digitalWrite(driver3_in2, LOW);
    }
  }
  if (currentpage == 8) {                                             // PLATFORM 5
    if (p.x > 481 && p.x < 700 && p.y > 353 && p.y < 686) {         //up
      digitalWrite(driver2_in1, HIGH);
      digitalWrite(driver2_in2, LOW);

      analogWrite(driver2_enA, M1_Speed);
      analogWrite(driver2_enB, M2_Speed);
    }
    if (p.x > 220 && p.x < 428 && p.y > 353 && p.y < 686) {          //DOWN
      digitalWrite(driver2_in1, LOW);
      digitalWrite(driver2_in2, HIGH);

      analogWrite(driver1_enA, M1_Speed);
      analogWrite(driver1_enB, M2_Speed);
    }
    if (p.z == 0) {
      digitalWrite(driver2_in1, LOW);
      digitalWrite(driver2_in2, LOW);
    }
  }
}

//OTHER FUNCTIONS
void getcar() {                                                              //getcar function
  LCD.setFont(BigFont);                                                      //FRAME
  LCD.fillScr(255, 255, 255);
  LCD.setColor(192, 192, 192);
  LCD.fillRect(0, 0, 480, 30);
  LCD.fillRect(0, 0, 10, 320);
  LCD.fillRect(470, 0, 480, 320);
  LCD.fillRect(0, 310, 480, 320);
  LCD.setColor(0, 0, 0);
  LCD.setBackColor(192, 192, 192);
  LCD.print("PARKING SYSTEM", CENTER, 7);
  LCD.setFont(SmallFont);
  LCD.setColor(0, 0, 0);
  LCD.print("Developed by 3rd year Embedded System students", CENTER, 310); //FRAME

  LCD.setFont(BigFont);
  LCD.setColor(255, 0, 0);                                                  //back buttoon
  LCD.fillRoundRect (20, 40, 70, 66);
  LCD.setBackColor(255, 0, 0);
  LCD.setColor(0, 255, 255);
  LCD.drawRoundRect (20, 40, 70, 66);
  LCD.setColor(0, 0, 0);
  LCD.print("<-", 30, 46);
  LCD.setBackColor(255, 255, 255);
  LCD.setColor(0, 0, 0);
  LCD.print("Back to Main Menu", 75, 46);
}
void parkcar() {                                                              //parkcar function
  LCD.setFont(BigFont);                                                         //FRAME
  LCD.fillScr(255, 255, 255);
  LCD.setColor(192, 192, 192);
  LCD.fillRect(0, 0, 480, 30);
  LCD.fillRect(0, 0, 10, 320);
  LCD.fillRect(470, 0, 480, 320);
  LCD.fillRect(0, 310, 480, 320);
  LCD.setColor(0, 0, 0);
  LCD.setBackColor(192, 192, 192);
  LCD.print("PARKING SYSTEM", CENTER, 7);
  LCD.setFont(SmallFont);
  LCD.setColor(0, 0, 0);
  LCD.print("Developed by 3rd year Embedded System students", CENTER, 310);    //FRAME

  LCD.setFont(BigFont);
  LCD.setColor(255, 0, 0);                                                     //back buttoon
  LCD.fillRoundRect (20, 40, 70, 66);
  LCD.setBackColor(255, 0, 0);
  LCD.setColor(0, 255, 255);
  LCD.drawRoundRect (20, 40, 70, 66);
  LCD.setColor(0, 0, 0);
  LCD.print("<-", 30, 46);
  LCD.setBackColor(255, 255, 255);
  LCD.setColor(0, 0, 0);
  LCD.print("Back to Main Menu", 75, 46);

  LCD.setColor(192, 192, 192);                                                //park car - platform icon box
  LCD.fillRect(30, 90, 450, 300);
  LCD.setColor(0, 0, 0);
  LCD.fillRect(30, 75, 450, 90);
  LCD.fillRect(30, 75, 70, 300);
  LCD.setColor(255, 255, 255);
  LCD.setBackColor(0, 0, 0);
  LCD.print("PARK CAR: CHOOSE PLATFORM", CENTER, 77);


  LCD.print("G", 40, 230);                                                       // park car - platform icon kunohay
  LCD.print("1", 40, 130);
  LCD.setBackColor(192, 192, 192);
  LCD.setFont(SevenSegNumFont);
  LCD.setColor(255, 255, 0);
  LCD.print("1", 73, 220);                                                       //park car - platform numbers
  LCD.print("2", 190, 220);
  LCD.print("5", 320, 113);
  LCD.print("4", 190, 113);
  LCD.print("3", 75, 113);

}



void platform_status () {                                                        //platform status function

  LCD.setFont(BigFont);                                                          //FRAME
  LCD.fillScr(255, 255, 255);
  LCD.setColor(192, 192, 192);
  LCD.fillRect(0, 0, 480, 30);
  LCD.fillRect(0, 0, 10, 320);
  LCD.fillRect(470, 0, 480, 320);
  LCD.fillRect(0, 310, 480, 320);
  LCD.setColor(0, 0, 0);
  LCD.setBackColor(192, 192, 192);
  LCD.print("PARKING SYSTEM", CENTER, 7);
  LCD.setFont(SmallFont);
  LCD.setColor(0, 0, 0);
  LCD.print("Developed by 3rd year Embedded System students", CENTER, 310);       //FRAME

  LCD.setFont(BigFont);
  LCD.setColor(255, 0, 0);                                                      //back buttoon
  LCD.fillRoundRect (20, 40, 70, 66);
  LCD.setBackColor(255, 0, 0);
  LCD.setColor(0, 255, 255);
  LCD.drawRoundRect (20, 40, 70, 66);
  LCD.setColor(0, 0, 0);
  LCD.print("<-", 30, 46);
  LCD.setBackColor(255, 255, 255);
  LCD.setColor(0, 0, 0);
  LCD.print("Back to Main Menu", 75, 46);

  LCD.setColor(192, 192, 192);                                                //platform icon box
  LCD.fillRect(30, 90, 450, 300);
  LCD.setColor(0, 0, 0);
  LCD.fillRect(30, 75, 450, 90);
  LCD.fillRect(30, 75, 70, 300);
  LCD.setColor(255, 255, 255);
  LCD.setBackColor(0, 0, 0);
  LCD.print("Platforms", CENTER, 77);


  LCD.print("G", 40, 230);                                                       //platform icon kunohay
  LCD.print("1", 40, 130);
  LCD.setBackColor(192, 192, 192);
  LCD.setFont(SevenSegNumFont);
  LCD.setColor(255, 255, 0);
  LCD.print("1", 73, 220);                                                       //platform numbers
  LCD.print("2", 190, 220);
  LCD.print("5", 320, 113);
  LCD.print("4", 190, 113);
  LCD.print("3", 75, 113);



}
void get_status() {
  int IRsensor1 = digitalRead(A8);
  int IRsensor2 = digitalRead(A9);
  int IRsensor3 = digitalRead(A10);
  int IRsensor4 = digitalRead(A11);
  int IRsensor5 = digitalRead(A12);

  if (IRsensor1 == 0 && ( currentpage == 3 || currentpage == 2 || currentpage == 1) && IRsensor1 != IRsensor1_old) {                 //IRSENSOR 1
    LCD.setColor(255, 0, 0);
    LCD.fillRoundRect(225, 215, 295, 275);                                             //for sensor 1
    LCD.setBackColor(255, 0, 0);
    LCD.setColor(0, 255, 0);
    LCD.setFont(SmallFont);
    IRsensor1_old = IRsensor1;
  }
  if (IRsensor1 == 1 && ( currentpage == 3 || currentpage == 2 || currentpage == 1) && IRsensor1 != IRsensor1_old) {
    LCD.setColor(0, 255, 0);
    LCD.fillRoundRect(225, 215, 295, 275);   //for sensor 1
    LCD.setBackColor(0, 255, 0);
    LCD.setColor(0, 0, 0);
    LCD.setFont(SmallFont);
    LCD.setColor(255, 0, 0);
    IRsensor1_old = IRsensor1;
  }

  if (IRsensor2 == 0 && ( currentpage == 3 || currentpage == 2 || currentpage == 1) && IRsensor2 != IRsensor2_old) {                 //IRSENSOR 2
    LCD.setColor(255, 0, 0);
    LCD.fillRoundRect(110, 215, 180, 275);                                              //for sensor 2
    LCD.setBackColor(255, 0, 0);
    LCD.setColor(0, 255, 0);
    LCD.setFont(SmallFont);
    IRsensor2_old = IRsensor2;
  }
  if (IRsensor2 == 1 && ( currentpage == 3 || currentpage == 2 || currentpage == 1) && IRsensor2 != IRsensor2_old) {
    LCD.setColor(0, 255, 0);
    LCD.fillRoundRect(110, 215, 180, 275);                                             //for sensor 2
    LCD.setBackColor(0, 255, 0);
    LCD.setColor(0, 0, 0);
    LCD.setFont(SmallFont);
    LCD.setColor(255, 0, 0);
    IRsensor2_old = IRsensor2;
  }
  if (IRsensor3 == 0 && ( currentpage == 3 || currentpage == 2 || currentpage == 1) && IRsensor3 != IRsensor3_old) {                 //IRSENSOR 3
    LCD.setColor(255, 0, 0);
    LCD.fillRoundRect(355, 110, 425, 170);                                                //for sensor 3
    LCD.setBackColor(255, 0, 0);
    LCD.setColor(0, 255, 0);
    LCD.setFont(SmallFont);
    IRsensor3_old = IRsensor3;
  }
  if (IRsensor3 == 1 && ( currentpage == 3 || currentpage == 2 || currentpage == 1) && IRsensor3 != IRsensor3_old) {
    LCD.setColor(0, 255, 0);
    LCD.fillRoundRect(355, 110, 425, 170);
    //for sensor 3
    LCD.setBackColor(0, 255, 0);
    LCD.setColor(0, 0, 0);
    LCD.setFont(SmallFont);
    LCD.setColor(255, 0, 0);
    IRsensor3_old = IRsensor3;
  }
  if (IRsensor4 == 0 && ( currentpage == 3 || currentpage == 2 || currentpage == 1) && IRsensor4 != IRsensor4_old) {                 //IRSENSOR 4
    LCD.setColor(255, 0, 0);
    LCD.fillRoundRect(225, 110, 295, 170);                                             //for sensor 4
    LCD.setBackColor(255, 0, 0);
    LCD.setColor(0, 255, 0);
    LCD.setFont(SmallFont);
    IRsensor4_old = IRsensor4;
  }
  if (IRsensor4 == 1 && ( currentpage == 3 || currentpage == 2 || currentpage == 1) && IRsensor4 != IRsensor4_old) {
    LCD.setColor(0, 255, 0);
    LCD.fillRoundRect(225, 110, 295, 170);                                             //for sensor 4
    LCD.setBackColor(0, 255, 0);
    LCD.setColor(0, 0, 0);
    LCD.setFont(SmallFont);
    LCD.setColor(255, 0, 0);
    IRsensor4_old = IRsensor4;
  }
  if (IRsensor5 == 0 && ( currentpage == 3 || currentpage == 2 || currentpage == 1) && IRsensor5 != IRsensor5_old) {                 //IRSENSOR 5
    LCD.setColor(255, 0, 0);
    LCD.fillRoundRect(110, 110, 180, 170);                                            //for sensor 5
    LCD.setBackColor(255, 0, 0);
    LCD.setColor(0, 255, 0);
    LCD.setFont(SmallFont);
    IRsensor5_old = IRsensor5;
  }
  if (IRsensor5 == 1 && ( currentpage == 3 || currentpage == 2 || currentpage == 1) && IRsensor5 != IRsensor5_old) {
    LCD.setColor(0, 255, 0);
    LCD.fillRoundRect(110, 110, 180, 170);                                             //for sensor 5
    LCD.setBackColor(0, 255, 0);
    LCD.setColor(0, 0, 0);
    LCD.setFont(SmallFont);
    LCD.setColor(255, 0, 0);
    IRsensor5_old = IRsensor5;
  }
}

///////////////////////////////////////////////////CONTROL FUNCTIONS///////////////////////////////////////////////////////////////////
void control_page_for_1floor() {                                                 // control_page_for_1floor

  LCD.setFont(BigFont);                                                          //FRAME
  LCD.fillScr(255, 255, 255);
  LCD.setColor(192, 192, 192);
  LCD.fillRect(0, 0, 480, 30);
  LCD.fillRect(0, 0, 10, 320);
  LCD.fillRect(470, 0, 480, 320);
  LCD.fillRect(0, 310, 480, 320);
  LCD.setColor(0, 0, 0);
  LCD.setBackColor(192, 192, 192);
  LCD.print("PARKING SYSTEM", CENTER, 7);
  LCD.setFont(SmallFont);
  LCD.setColor(0, 0, 0);
  LCD.print("Developed by 3rd year Embedded System students", CENTER, 310);       //FRAME

  LCD.setFont(BigFont);
  LCD.setColor(255, 0, 0);                                                        //back buttoon
  LCD.fillRoundRect (20, 40, 70, 66);
  LCD.setBackColor(255, 0, 0);
  LCD.setColor(0, 255, 255);
  LCD.drawRoundRect (20, 40, 70, 66);
  LCD.setColor(0, 0, 0);
  LCD.print("<-", 30, 46);
  LCD.setBackColor(255, 255, 255);
  LCD.setColor(0, 0, 0);
  LCD.print("Back to Park Car", 75, 46);                                         //back button

  LCD.setColor(16, 167, 103);
  LCD.fillRect(30, 70, 450, 300);
  LCD.setColor(255, 255, 255);
  LCD.fillRect(150, 90, 330, 180);
  LCD.fillRect(150, 200, 330, 290);
  LCD.setColor(0, 0, 0);
  LCD.print("UP", CENTER, 125);
  LCD.print("DOWN", CENTER, 230);
}
void control_page_for_gfloor() {                                                 //control_page_for_gfloor()
  LCD.setFont(BigFont);                                                          //FRAME
  LCD.fillScr(255, 255, 255);
  LCD.setColor(192, 192, 192);
  LCD.fillRect(0, 0, 480, 30);
  LCD.fillRect(0, 0, 10, 320);
  LCD.fillRect(470, 0, 480, 320);
  LCD.fillRect(0, 310, 480, 320);
  LCD.setColor(0, 0, 0);
  LCD.setBackColor(192, 192, 192);
  LCD.print("PARKING SYSTEM", CENTER, 7);
  LCD.setFont(SmallFont);
  LCD.setColor(0, 0, 0);
  LCD.print("Developed by 3rd year Embedded System students", CENTER, 310);     //FRAME

  LCD.setFont(BigFont);
  LCD.setColor(255, 0, 0);                                                      //back buttoon
  LCD.fillRoundRect (20, 40, 70, 66);
  LCD.setBackColor(255, 0, 0);
  LCD.setColor(0, 255, 255);
  LCD.drawRoundRect (20, 40, 70, 66);
  LCD.setColor(0, 0, 0);
  LCD.print("<-", 30, 46);
  LCD.setBackColor(255, 255, 255);
  LCD.setColor(0, 0, 0);
  LCD.print("Back to Park Car", 75, 46);                                       //back button

  LCD.setColor(16, 167, 103);
  LCD.fillRect(30, 70, 450, 300);
  LCD.setColor(255, 255, 255);
  LCD.fillRect(70, 100, 220, 280);
  LCD.fillRect(260, 100, 410, 280);
  LCD.setColor(0, 0, 0);
  LCD.print("LEFT", 103, 175);
  LCD.print("RIGHT", 295, 175);

}
