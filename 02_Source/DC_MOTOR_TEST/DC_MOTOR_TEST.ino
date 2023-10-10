//khai báo chân điều khiển động cơ
// ENA là chân bật động cơ 1 và dùng chân này để băm xung ( điều khiển tốc độ)
// IN1 IN2 điều khiển chiều động cơ A
// ví dụ: IN1 = 1; IN2 = 0 thì động cơ quay thuận và ngược lại
// chú ý: IN1 = IN2 thì động cơ k quay
// 34 35 32 ... ở dưới là tương ứng với chân trên board ESP32
#define ENA 2
#define IN1 15
#define IN2 4
#define IN3 33
#define IN4 25
#define ENB 26
 
void setup(){
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
 
void loop(){
  diThang(150,150);
  delay(1000);
  diLui(150,150);
  delay(1000);
  stop();
  delay(1000);
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