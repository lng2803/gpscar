#include <HardwareSerial.h> 
#include <TinyGPS++.h> 
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#define ENA 2
#define IN1 15
#define IN2 4
#define IN3 33
#define IN4 25
#define ENB 26

LiquidCrystal_I2C lcd(0x3F,16,2); 

HardwareSerial ss(2); 

TinyGPSPlus gps; 

int vitri = 5;
int vitricu = 10;

float vd, kd;

void setup() {
  ss.begin(9600, SERIAL_8N1, 16, 17); 
  Serial.begin(115200); 
  lcd.init();                  
  lcd.backlight(); 
  lcd.setCursor(4,0); 
  lcd.print("Start");   
  lcd.setCursor(4,1); 
  lcd.print("Do an 2"); 
    // cài đặt Kênh, tần số, độ phân giải cho băm xung (điều khiển tốc độ động cơ)
  ledcSetup(0, 5000, 8);
  ledcSetup(1, 5000, 8);
  
  // Chọn chân và kênh để băm xung
  ledcAttachPin(ENA, 0);
  ledcAttachPin(ENB, 1);

  //Chọn mode cho chân điều khiển động cơ là OUTPUT
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

void loop() {
  while (ss.available() > 0){ 
    gps.encode(ss.read()); 
    if (gps.location.isUpdated()){ 
      Serial.print("Latitude= "); 
      Serial.print(gps.location.lat(), 6); 
      Serial.print("Longitude= "); 
      Serial.println(gps.location.lng(), 6); 

      vd = gps.location.lat();
      kd = gps.location.lng();

      // lcd.setCursor(0,0); 
      // lcd.print("VD: ");   
      // lcd.setCursor(0,1); 
      // lcd.print("KD: ");

      // lcd.setCursor(3,0);
      // lcd.print(gps.location.lat(), 6);
      // lcd.setCursor(3,1);
      // lcd.print(gps.location.lng(), 6);
    }
  }

  if (vd < 10.8511) {
    if (kd < 106.7728 && kd > 106.7725) vitri = 0; else vitri = 5;
  } else {
    if (vd > 10.8514){
      if (kd < 106.7728 && kd > 106.7725) vitri = 4; else vitri = 5;
    } else {
      if (kd < 106.7725) {
        vitri = 3;
      } else {
        if (kd > 106.7729){
          vitri = 2;
        } else {
          vitri = 1;
        }
      }
    }
  }

  lcd.setCursor(14,0); 
  lcd.print(vitri);
}

void xuly()
{
  if (vitri == 0){
    vitricu = 0;
    lcd.setCursor(0,0);
    lcd.print("         "); 
    lcd.print("DiThang");  
    diThang(150,150);
  }
  if (vitri == 1 && vitricu == 0)
  {
    vitricu = 1;
    lcd.setCursor(0,0); 
    lcd.print("         "); 
    lcd.print("ReTrai"); 
    diThang(0,150);
  }
  if (vitri == 3 && vitricu == 1)
  {
    vitricu = 3;
    lcd.setCursor(0,0); 
    lcd.print("         "); 
    lcd.print("QuayDau"); 
    diThang(255,0);
  }
  if (vitri == 1 && vitricu == 3)
  {
    vitricu = 1;
    lcd.setCursor(0,0); 
    lcd.print("         "); 
    lcd.print("DiThang"); 
    diThang(255,255);
  }
  if (vitri == 2 && vitricu == 1)
  {
    vitricu = 2;
    lcd.setCursor(0,0); 
    lcd.print("         "); 
    lcd.print("QuayDau"); 
    diThang(255,0);
  }
  if (vitri == 1 && vitricu == 2)
  {
    vitricu = 1;
    lcd.setCursor(0,0); 
    lcd.print("         "); 
    lcd.print("RePhai");
    diThang(155,0); 
  }
  if (vitri == 4 && vitricu == 1)
  {
    vitricu = 4;
    lcd.setCursor(0,0); 
    lcd.print("         "); 
    lcd.print("Stop"); 
    diThang(0,0); 
  }
}

void diThang(int SpeedLeft, int SpeedRight)
{
  digitalWrite(IN1,1);
  digitalWrite(IN2,0);
  digitalWrite(IN3,1);
  digitalWrite(IN4,0);
  ledcWrite(0, SpeedLeft);
  ledcWrite(1, SpeedRight);
}

void diLui(int SpeedLeft, int SpeedRight)
{
  digitalWrite(IN1,0);
  digitalWrite(IN2,1);
  digitalWrite(IN3,0);
  digitalWrite(IN4,1);
  ledcWrite(0, SpeedLeft);
  ledcWrite(1, SpeedRight);
}

void stop()
{
  digitalWrite(IN1,0);
  digitalWrite(IN2,0);
  digitalWrite(IN3,0);
  digitalWrite(IN4,0);
  ledcWrite(0, 0);
  ledcWrite(1, 0);
}