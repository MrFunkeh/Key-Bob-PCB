//this is my Key Bob code. It has a rotary encoder, OLED display, esp32-c3 super mini, and an mpu6050 gyro.

//libraries
#include <Arduino.h>
#include <Wire.h> //I2C talk
#include <SPI.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <esp_now.h>
#include <WiFi.h>

//screen size
#define SCREEN_HEIGHT 64
#define SCREEN_WIDTH 128

//initialize state
bool danceParty = false;
bool click = false;

//encoder
int counter = 0;
int currentStateCLK;
int previousStateCLK;
//LED pin
int LED = 10;
//OLED display pins
const int SDA_pin = 8;
const int SCL_pin = 9;
//encoder pins
const int ENC_SW = 7;
const int ENC_DT = 5;
const int ENC_CLK = 6;
//comunication for DFPlayer
const int pin20 = 20;
const int pin21 = 21;

//encoder direction
String encdir ="";

//screen setup
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

//format MAC address
void formatMacAddress(const uint8_t *macAddr, char *buffer, int maxLength)
{
    snprintf(buffer, maxLength, "%02x:%02x:%02x:%02x:%02x:%02x", macAddr[0], macAddr[1],macAddr[2],macAddr[3],macAddr[4],macAddr[5]);
}

void receiveCallback(const uint8_t *macAddr, const uint8_t *data, int dataLen)
{
    //only allow 250 characters in a message
    char buffer[ESP_NOW_MAX_DATA_LEN + 1];
    int msgLen = min(ESP_NOW_MAX_DATA_LEN, dataLen);
    strncpy(buffer, (const char *)data, msgLen);
    //veryify null
    buffer[msgLen] = 0;
    //format MAC address
    char macStr[18];
    //send log
    Serial.printf("recieved message :from %5 - %5\n", macStr, buffer);
    //sets danceParty value
    if (strcmp("on", buffer) == 0){
        danceParty = true;
    }
    else{
        danceParty = false;
    }
    //turn LED on when danceParty is true
    digitalWrite(LED, danceParty);
    
}

//called when data is sent
void sentCallback(const uint8_t *macAddr, esp_now_send_status_t status){
    char macStr[18];
    formatMacAddress(macAddr, macStr, 18);
    Serial.print("Last Packet Sent to: ");
    Serial.println(macStr);
    Serial.print("Last Packet Send status: ");
    Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void broadcast(const String &message){
    //broadcast a message to every device in range
    uint8_t broadcastAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,};
    esp_now_peer_info_t peerInfo = {};
    memcpy(&peerInfo.peer_addr, broadcastAddress, 6);
    if(!esp_now_is_peer_exist(broadcastAddress)){
    esp_now_add_peer(&peerInfo);
    }
    //send a message
    esp_err_t result = esp_now_send(broadcastAddress, (const uint8_t *)message.c_str(), message.length());
    if(result == ESP_OK){
        Serial.println("Broadcast Test");
    }
    else if(result == ESP_ERR_ESPNOW_NOT_FOUND){
        Serial.println("Peer not found");
    }
}
//OLED display and LED power indicator
void setup(){
    //serial moniter
    Serial.begin (9600);
    delay(1000);

    //set encoder pins as inputs with pullup resitors
    pinMode (ENC_CLK, INPUT_PULLUP);
    pinMode (ENC_DT,INPUT_PULLUP);
    pinMode (ENC_SW,INPUT_PULLUP);
    //reads the inital value
    previousStateCLK = digitalRead(ENC_CLK);

    //sets LED pin to output
    pinMode (LED,OUTPUT);

    //set ESP32 to STA mode
    WiFi.mode(WIFI_STA);
    Serial.print("MAC Address: ");
    Serial.println(WiFi.macAddress());
    WiFi.disconnect();
    //Initialize esp-now
    if(esp_now_init() == ESP_OK){
        Serial.println("ESP-NOW Init Success");
        esp_now_register_recv_cb(receiveCallback);
        esp_now_register_send_cb(sentCallback);
    }
    else{
        //if failed restart proccess
        Serial.println("ESP-NOW Init Failed");
        delay(3000);
        ESP.restart();
    }

    //testing example to see if display code works
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.clearDisplay();
    display.setTextSize(2);
    //keep the color white even if display is different color
    display.setTextColor(WHITE);
    display.println("Hello");
    display.display();
}

void loop(){
    //constantly read the encoder value
    currentStateCLK = digitalRead(ENC_CLK);
    //check if the state changed
    //if the CCW and CW are reversed in real life switch the variables if you like
    if (currentStateCLK != previousStateCLK){
        //the encoder is rotating
        if (digitalRead(ENC_DT) != currentStateCLK){
            //minus one from counter
            counter --;
            encdir ="CCW"; //set state to counter clockwise
        }
        else {
            counter ++;
            encdir ="CW"; //set state to clockwise
        }
        //this prints the direction and it's counter value
        Serial.print("Direction: ");
        Serial.print(encdir);
        Serial.print(" -- Value: ");
        Serial.println(counter);
    }
    //updates encoder variable
    previousStateCLK = currentStateCLK;

    if(digitalRead(ENC_SW)){
        if(!click){
        click = true;
        //toggle state
        danceParty = !danceParty;
        digitalWrite(LED, danceParty);
        //send message to all devices
        if(danceParty){
            broadcast("on");
        }
        else{
            broadcast("off");
        }
        }

        //avoid bouncing / multiipule click's
        delay(200);
    }
    else{
        //reset button state
        click = false;
    }
}