/*Reciver Arduino Mega
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

struct can_frame canMsg; 
MCP2515 mcp2515(53); // SPI CS Pin 53 

void setup() {
  SPI.begin();   //Begins SPI communication
  Serial.begin(9600); //Begins Serial Communication at 9600 baud rate 
  mcp2515.reset();                          
  mcp2515.setBitrate(CAN_500KBPS,MCP_8MHZ); //Sets CAN at speed 500KBPS and Clock 8MHz 
  mcp2515.setNormalMode();  //Sets CAN at normal mode
}

void loop(){
 char Command = Serial.read();

  if(Command == '1')//sending ON command
  {
    //Serial.println(Command);
    //digitalWrite(led, LOW);
    Serial.println("Send ON");
    //delay(1000);
    //digitalWrite(led, HIGH);
    //Serial.println("Send OFF");
    //digitalWrite(led, HIGH);
    //delay(1000);
    //digitalWrite(led, LOW);
    canMsg.can_id = 0x010; //CAN id as 0x036 this ucontroler ID
    canMsg.can_dlc = 8; //CAN data length as 8
    canMsg.data[0] = 1; //Update ON command
    canMsg.data[1] = 0x00; //Update temperature value in [1]
    canMsg.data[2] = 0x00; //Rest all with 0
    canMsg.data[3] = 0x00;
    canMsg.data[4] = 0x00;
    canMsg.data[5] = 0x00;
    canMsg.data[6] = 0x00;
    canMsg.data[7] = 0x00;
    mcp2515.sendMessage(&canMsg); //Sends the CAN message
  }
  if(Command == '0')//Sending OFF command
  {
    //Serial.println(Command);
    //digitalWrite(led, HIGH);
    Serial.println("Send : OFF");
    canMsg.can_id = 0x010; //CAN id as 0x036 this ucontroler ID
    canMsg.can_dlc = 8; //CAN data length as 8
    canMsg.data[0] = 0; //Update OFF command
    canMsg.data[1] = 0x00; //Update temperature value in [1]
    canMsg.data[2] = 0x00; //Rest all with 0
    canMsg.data[3] = 0x00;
    canMsg.data[4] = 0x00;
    canMsg.data[5] = 0x00;
    canMsg.data[6] = 0x00;
    canMsg.data[7] = 0x00;
    mcp2515.sendMessage(&canMsg); //Sends the CAN message
  }
 
 //CAN Data Receibed from ID ==0x036  
 if ((mcp2515.readMessage(&canMsg) == MCP2515::ERROR_OK) && (canMsg.can_id == 0x036)){
     int x = canMsg.data[0];         
     int y = canMsg.data[1];  
     Serial.print("CAN : ");
     Serial.println(x);
     //Serial.print(" Y: ");
     //Serial.println(y);      
   }
  //char myFirstCharacter = Serial.read();
}
