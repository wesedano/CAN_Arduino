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
//#include <DHT.h> //Library for using DHT sensor
 
#define DHTPIN A0
#define DHTTYPE DHT11
int h = 1;
int t = 3;


struct can_frame canMsg;
MCP2515 mcp2515(10);
//DHT dht(DHTPIN, DHTTYPE); //initialize object dht for class DHT with DHT pin with STM32 and DHT type as DHT11

void setup(){
  while (!Serial);
  Serial.begin(9600);
  SPI.begin(); //Begins SPI communication
//  dht.begin(); //Begins to read temperature & humidity sensor value
  mcp2515.reset();
  mcp2515.setBitrate(CAN_500KBPS, MCP_8MHZ); //Sets CAN at speed 500KBPS and Clock 8MHz
  mcp2515.setNormalMode();
}

void loop(){
//  int h = dht.readHumidity(); //Gets Humidity value
//  int t = dht.readTemperature(); //Gets Temperature value
  canMsg.can_id = 0x036; //CAN id as 0x036
  canMsg.can_dlc = 8; //CAN data length as 8
  canMsg.data[0] = h; //Update humidity value in [0]
  canMsg.data[1] = t; //Update temperature value in [1]
  canMsg.data[2] = 0x00; //Rest all with 0
  canMsg.data[3] = 0x00;
  canMsg.data[4] = 0x00;
  canMsg.data[5] = 0x00;
  canMsg.data[6] = 0x00;
  canMsg.data[7] = 0x00;
  mcp2515.sendMessage(&canMsg); //Sends the CAN message
  delay(1000);
}
