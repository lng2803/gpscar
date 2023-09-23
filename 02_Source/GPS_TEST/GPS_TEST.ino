#include <HardwareSerial.h> //Thư viện uart của esp32
#include <TinyGPS++.h> //Thư viện module GPS NEO 6M v2

HardwareSerial ss(2); //Chọn cổng UART 2

TinyGPSPlus gps; //Khởi tạo biến cho module GPS

void setup() {
  ss.begin(9600, SERIAL_8N1, 16, 17); //Chọn baudrate là 9600 (vì module dùng 9600)
  //chân 16 17 RX TX cho ngõ ra
  Serial.begin(115200); // Chọn baudrate để giao tiếp với máy tính
}

void loop() {
  while (ss.available() > 0){ //Trong khi UART2 có tín hiệu
    gps.encode(ss.read()); //Đọc giá trị
    if (gps.location.isUpdated()){ //Cập nhật giá trị GPS
      Serial.print("Latitude= "); //Vĩ độ
      Serial.print(gps.location.lat(), 6); //In giá trị vĩ độ ra
      Serial.print(" Longitude= "); //Kinh độ
      Serial.println(gps.location.lng(), 6); //In giá trị kinh độ ra
    }
  }
}
