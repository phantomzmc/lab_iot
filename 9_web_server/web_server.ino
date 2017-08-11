
#include <ESP8266WiFi.h>
#define LED D1 //ก าหนดขาที่ต่อ LED เป็นขา D1
const char* ssid = "stk"; //ก าหนด SSID (อย่าลืมแก้เป็นของตัวเอง)
const char* password = "stk123456"; //ก าหนด Password(อย่าลืมแก้เป็นของตัวเอง)
unsigned char status_led=0; //ก าหนดตัวแปร ที่เก็บค่าสถานะของ LED
WiFiServer server(80); //ก าหนดใช้งาน TCP Server ที่ Port 80
void setup() {
 Serial.begin(115200); //เปิดใช้ Serial
 pinMode(LED, OUTPUT); //ก าหนด Pin ที่ต่อกับ LED เป็น Output
 Serial.println();
 Serial.println();
 Serial.print("Connecting to ");
 Serial.println(ssid);
 WiFi.begin(ssid, password); //เชื่อมต่อกับ AP
 while (WiFi.status() != WL_CONNECTED) //รอการเชื่อมต่อ
 {
 delay(500);
 Serial.print(".");
 }
  Serial.println("");
 Serial.println("WiFi connected"); //แสดงข้อความเชื่อมต่อส าเร็จ
 server.begin(); //เปิด TCP Server
 Serial.println("Server started");
 Serial.println(WiFi.localIP()); // แสดงหมายเลข IP ของ Server
}
void loop() {
 WiFiClient client = server.available(); //รอรับ การเชื่อมต่อจาก Client
 if (!client) { //ถ้าไม่มี Client เข้ามาให้เริ่มกับไปวน loop รอรับใหม่
 return;
 }

 Serial.println("new client");
 while(!client.available())
 {
 delay(1);
 }
String req = client.readStringUntil('\r'); //อ่านค่าที่ได้รับจากclient จากข้อมูลแรกถึง ‘\r’
 Serial.println(req); //แสดงค่าที่ได้รับทาง Serial
 client.flush();
 if (req.indexOf("/ledoff") != -1) //ตรวจสอบว่า data ที่เข้ามามีข้อความ”/ledoff”หรือไม่
 {
 status_led=0; //ถ้ามีให้ก าหนดค่า ในตัวแปรใน status_led=0
 digitalWrite(LED,LOW); //ให้ LED ดับ
 Serial.println("LED OFF");
 }
 else if(req.indexOf("/ledon") != -1) //ตรวจสอบว่า data ที่เข้ามามีข้อความ”/ledon”หรือไม่
 {
 status_led=1; //ถ้ามีให้ก าหนดค่า ในตัวแปรใน status_led=1
digitalWrite(LED,HIGH); //ให้ LED ติด
 Serial.println("LED ON");
 }
//เก็บ Code HTML ลงในตัวแปรสตริง web
 String web = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
 web += "<html>\r\n";
 web += "<body>\r\n";
 web += "<h1>LED Status</h1>\r\n";
 web += "<p>\r\n";
 if(status_led==1) // ตรวจเช็คสถานะของ LED ว่า On หรือ Off
 web += "LED On\r\n";
 else
 web += "LED Off\r\n";
 web += "</p>\r\n";
 web += "</body>\r\n";
 web += "</html>\r\n";
 client.print(web); //ส่ง HTML Code ไปยัง client
}

 
