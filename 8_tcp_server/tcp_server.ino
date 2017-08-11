#include <ESP8266WiFi.h>
#define SERVER_PORT 8000 //ก าหนด Port ใช้งาน
const char* ssid = "stk"; //ก าหนด SSID
const char* password = "stk123456"; //ก าหนด Password
WiFiServer server(SERVER_PORT); //สร้าง object server และก าหนด port

void setup()
{
 Serial.begin(115200); //เปิดใช้ Serial
 Serial.println("");
 Serial.println("");
 WiFi.begin(ssid, password); //เชื่อมต่อกับ AP
 while (WiFi.status() != WL_CONNECTED) //รอการเชื่อมต่อ
 {
 delay(500);
 Serial.print(".");
 }
 Serial.println("WiFi connected"); //แสดงข้อความเชื่อมต่อส าเร็จ
 Serial.println("IP address: ");
 Serial.println(WiFi.localIP()); //แสดงหมายเลข IP
 server.begin(); //เริ่มต้นท างาน TCP Server
 Serial.println("Server started"); //แสดงข้อความ server เริ่มท างาน
ESP.wdtDisable(); //ปิด watch dog Timer
}

void loop()
{
 WiFiClient client = server.available(); //รอรับ การเชื่อมต่อจาก Client
 if (client) //ตรวจเช็คว่ามี Client เชื่อมต่อเข้ามาหรือไม่
 {
 Serial.println("new client"); //แสดงข้อความว่ามี Client เชื่อมต่อเข้ามา
 while(1) //วนรอบตลอด
 {
 while(client.available()) //ตรวจเช็ตว่ามี Data ส่งมาจาก Client หรือไม่
 {
 uint8_t data =client.read(); //อ่าน Data จาก Buffer
 Serial.write(data); //แสดงผล Data ทาง Serial
 }
 if(server.hasClient()) //ตรวจเช็คว่ายังมี Client เชื่อมต่ออยู่หรือไม่
 {
 return; //ถ้าไม่มีให้ออกจาก ลูป ไปเริ่มต้นรอรับ Client ใหม่
 }
 }

 }
}
