
#include <ESP8266WiFi.h>
#include <MicroGear.h>

const char* ssid     = "LAB2210";//<WIFI_SSID>;
const char* password = "12345678";//<WIFI_KEY>;

#define APPID   "projectTestLek"//<APPID>
#define KEY     "ImT7JjrAiaY9xPR"//<APPKEY>
#define SECRET  "y7WJqEUiOyWajPzuPXi7Zu7V7"//<APPSECRET>
#define ALIAS   "esp8266"

WiFiClient client;


MicroGear microgear(client);

/* If a new message arrives, do this */
void onMsghandler(char *topic, uint8_t* msg, unsigned int msglen) {
     
    Serial.print("Incoming message --> ");
    msg[msglen] = '\0';
    Serial.println((char *)msg);
   
  
}

void onFoundgear(char *attribute, uint8_t* msg, unsigned int msglen) {
    Serial.print("Found new member --> ");
    for (int i=0; i<msglen; i++)
        Serial.print((char)msg[i]);
    Serial.println();  
}

void onLostgear(char *attribute, uint8_t* msg, unsigned int msglen) {
    Serial.print("Lost member --> ");
    for (int i=0; i<msglen; i++)
        Serial.print((char)msg[i]);
    Serial.println();
}

/* When a microgear is connected, do this */
void onConnected(char *attribute, uint8_t* msg, unsigned int msglen) {
    Serial.println("Connected to NETPIE...");
    /* Set the alias of this microgear ALIAS */
    microgear.setAlias(ALIAS);
}


void setup() {
    /* Add Event listeners */

    /* Call onMsghandler() when new message arraives */
    microgear.on(MESSAGE,onMsghandler);
    /* Call onFoundgear() when new gear appear */
    microgear.on(PRESENT,onFoundgear);
    /* Call onLostgear() when some gear goes offline */
    microgear.on(ABSENT,onLostgear);
    /* Call onConnected() when NETPIE connection is established */
    microgear.on(CONNECTED,onConnected);

    Serial.begin(115200);
    Serial.println("Starting...");

    /* Initial WIFI, this is just a basic method to configure WIFI on ESP8266.                       */
    /* You may want to use other method that is more complicated, but provide better user experience */
    if (WiFi.begin(ssid, password)) {
        while (WiFi.status() != WL_CONNECTED) {
            delay(500);
            Serial.print(".");
        }
    }

    Serial.println("WiFi connected");  
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    /* Initial with KEY, SECRET and also set the ALIAS here */
    microgear.init(KEY,SECRET,ALIAS);
    /* connect to NETPIE to a specific APPID */
    microgear.connect(APPID);
}
int timer=0;
int sensorPin = A0;
int sensorValue = 0; 
void loop() {
    /* To check if the microgear is still connected */
    if (microgear.connected()) {
        Serial.println("connected");
        /* Call this method regularly otherwise the connection may be lost */
        microgear.loop();
        if (timer >= 1000) {
            sensorValue = analogRead(sensorPin); 
            Serial.println("Publish...");
            String data=String(sensorValue);
            /* Chat with the microgear named ALIAS which is myself */
            //microgear.chat(ALIAS,data);
            microgear.publish("/A/a0", sensorValue);
            timer = 0;
        } 
        else timer += 100;
    }
    else {
        Serial.println("connection lost, reconnect...");
        if (timer >= 5000) {
            microgear.connect(APPID);
            timer = 0;
        }
        else timer += 100;
    }
    delay(100);
}
