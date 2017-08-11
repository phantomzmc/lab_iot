#include <ESP8266WiFi.h>
const char* ssid = "your-ssid"; //อย่าลืมแก้เป็นชื่อ SSID ของตัวเอง
const char* password = "your-password"; //อย่าลืมแก้เป็นชื่อ password ของตัวเอง
void setup()
{
 Serial.begin(115200); //ตั้งค่าใช้งาน serial ที่ baudrate 115200
 delay(10);
 Serial.println();
 Serial.println();
 Serial.print("Connecting to "); //แสดงข้อความ “Connecting to”
 Serial.println(ssid); //แสดงข้อความ ชื่อ SSID
 WiFi.begin(ssid, password); // เชื่อมต่อไปยัง AP

 while (WiFi.status() != WL_CONNECTED) //รอจนกว่าจะเชื่อมต่อส าเร็จ
{
  delay(500);
 Serial.print(".");
 }

 IPAddress local_ip = {192,168,1,144}; //ตั้งค่า IP
 IPAddress gateway={192,168,1,1}; //ตั้งค่า IP Gateway
 IPAddress subnet={255,255,255,0}; //ตั้งค่า Subnet
 WiFi.config(local_ip,gateway,subnet); //setค่าไปยังโมดูล
 Serial.println("");
 Serial.println("WiFi connected"); //แสดงข้อความเชื่อมต่อส าเร็จ
 Serial.println("IP address: ");
 Serial.println(WiFi.localIP()); //แสดงหมายเลข IP ของ ESP8266
}
void loop() 
{
  
}

