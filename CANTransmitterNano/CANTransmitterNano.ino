/*Transmitter Nano
 * --------------------------------------------------------------------------------------------------------------------
 * Example to change UID of changeable MIFARE card.
 * --------------------------------------------------------------------------------------------------------------------
 * This is a MFRC522 library example; for further details and other examples see: https://github.com/miguelbalboa/rfid
 * 
 * This sample shows how to set the UID on a UID changeable MIFARE card.
 * NOTE: for more informations read the README.rst
 * 
 * @author Tom Clement
 * @license Released into the public domain.
 *
 * Typical pin layout used:
 * -----------------------------------------------------------------------------------------
 *             MFRC522      Arduino       Arduino   Arduino    Arduino          Arduino
 *             Reader/PCD   Uno           Mega      Nano v3    Leonardo/Micro   Pro Micro
 * Signal      Pin          Pin           Pin       Pin        Pin              Pin
 * -----------------------------------------------------------------------------------------
 * RST/Reset   RST          9             5         D9         RESET/ICSP-5     RST
 * SPI SS      SDA(SS)      10            53        D10        10               10
 * SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16
 * SPI MISO    MISO         12 / ICSP-1   50        D12        ICSP-1           14
 * SPI SCK     SCK          13 / ICSP-3   52        D13        ICSP-3           15
 */
#include <SPI.h> //Library for using SPI Communication
#include <mcp2515.h> //Library for using CAN Communication

 
#define DHTPIN A0
#define DHTTYPE DHT11
int h = 1;
int t = 3;
int PIN_5 = 5;
int PIN_6 = 6;
int PIN_7 = 7;
int Time = 1000 , Add = 500;
float StartTime;

struct can_frame canMsg;
MCP2515 mcp2515(10);
int Command ;

void setup(){
  while (!Serial);
  Serial.begin(9600);
  SPI.begin(); //Begins SPI communication

  mcp2515.reset();
  mcp2515.setBitrate(CAN_500KBPS, MCP_8MHZ); //Sets CAN at speed 500KBPS and Clock 8MHz
  mcp2515.setNormalMode();
  pinMode(PIN_5, OUTPUT);
  digitalWrite(PIN_5, HIGH);
  pinMode(PIN_6, OUTPUT);
  digitalWrite(PIN_6, HIGH);
}

void loop(){
  //h++;
  //t--;

//CAN Data Receibed from ID == 0x010
 if ((mcp2515.readMessage(&canMsg) == MCP2515::ERROR_OK) && (canMsg.can_id == 0x010)){
     int x = canMsg.data[0];         
     int y = canMsg.data[1];  
     Serial.print("RXCAN : ");
     Serial.println(x);

    if( x == 1 )
    {
      digitalWrite(PIN_5, LOW);
  
        canMsg.can_id = 0x036; //CAN id as 0x036 this ucontroler ID
        canMsg.can_dlc = 8; //CAN data length as 8
        canMsg.data[0] = 1; //Update humidity value in [0]
        canMsg.data[1] = 0x00; //Update temperature value in [1]
        canMsg.data[2] = 0x00; //Rest all with 0
        canMsg.data[3] = 0x00;
        canMsg.data[4] = 0x00;
        canMsg.data[5] = 0x00;
        canMsg.data[6] = 0x00;
        canMsg.data[7] = 0x00;
        mcp2515.sendMessage(&canMsg); //Sends the CAN message
      Serial.println(" ON "); 
    }
    
    if( x == 2 )
    {
      digitalWrite(PIN_6, LOW);
  
        canMsg.can_id = 0x036; //CAN id as 0x036 this ucontroler ID
        canMsg.can_dlc = 8; //CAN data length as 8
        canMsg.data[0] = 2; //Update humidity value in [0]
        canMsg.data[1] = 0x00; //Update temperature value in [1]
        canMsg.data[2] = 0x00; //Rest all with 0
        canMsg.data[3] = 0x00;
        canMsg.data[4] = 0x00;
        canMsg.data[5] = 0x00;
        canMsg.data[6] = 0x00;
        canMsg.data[7] = 0x00;
        mcp2515.sendMessage(&canMsg); //Sends the CAN message
        
      Serial.println(" ON ");
      delay(Time);
      digitalWrite(PIN_6, HIGH);  
      Serial.println("OFF");
    }
    if( x == 0)
    {
        canMsg.can_id = 0x036; //CAN id as 0x036 this ucontroler ID
        canMsg.can_dlc = 8; //CAN data length as 8
        canMsg.data[0] = 0; //Update humidity value in [0]
        canMsg.data[1] = 0x00; //Update temperature value in [1]
        canMsg.data[2] = 0x00; //Rest all with 0
        canMsg.data[3] = 0x00;
        canMsg.data[4] = 0x00;
        canMsg.data[5] = 0x00;
        canMsg.data[6] = 0x00;
        canMsg.data[7] = 0x00;
        mcp2515.sendMessage(&canMsg); //Sends the CAN message
        
      digitalWrite(PIN_5, HIGH);
      digitalWrite(PIN_6, HIGH);
      Serial.println("OFF");
    } 
    if( x == 5)
    {
        Time = Time + Add;
        StartTime = Time/1000;
        canMsg.can_id = 0x036; //CAN id as 0x036 this ucontroler ID
        canMsg.can_dlc = 8; //CAN data length as 8
        canMsg.data[0] = Time; //Update humidity value in [0]
        canMsg.data[1] = 0x00; //Update temperature value in [1]
        canMsg.data[2] = 0x00; //Rest all with 0
        canMsg.data[3] = 0x00;
        canMsg.data[4] = 0x00;
        canMsg.data[5] = 0x00;
        canMsg.data[6] = 0x00;
        canMsg.data[7] = 0x00;
        mcp2515.sendMessage(&canMsg); //Sends the CAN message
        
      digitalWrite(PIN_5, HIGH);
      digitalWrite(PIN_6, HIGH);
      Serial.println("OFF");
      Serial.println(Time);
      Serial.println(StartTime);
    }
    if( x == 6)
    {
        Time = Time - Add;
        StartTime = Time/1000;
        canMsg.can_id = 0x036; //CAN id as 0x036 this ucontroler ID
        canMsg.can_dlc = 8; //CAN data length as 8
        canMsg.data[0] = Time; //Update humidity value in [0]
        canMsg.data[1] = 0x00; //Update temperature value in [1]
        canMsg.data[2] = 0x00; //Rest all with 0
        canMsg.data[3] = 0x00;
        canMsg.data[4] = 0x00;
        canMsg.data[5] = 0x00;
        canMsg.data[6] = 0x00;
        canMsg.data[7] = 0x00;
        mcp2515.sendMessage(&canMsg); //Sends the CAN message
        
      digitalWrite(PIN_5, HIGH);
      digitalWrite(PIN_6, HIGH);
      Serial.println("OFF");
      Serial.println(Time);
      Serial.println(StartTime);
    }
   }
  //digitalWrite(led, HIGH);
  delay(100);
  //digitalWrite(led, LOW);

}
