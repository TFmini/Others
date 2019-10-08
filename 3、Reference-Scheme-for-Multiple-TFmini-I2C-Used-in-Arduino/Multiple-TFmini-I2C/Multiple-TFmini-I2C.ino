/*This is a reference code about Arduino UNO receive TFmini-I²C Data from I²C bus
 * Arduino is Master, TFmini-I²C is slave. Master send check 
 * Author:zhaomingxin@Benewake
 * Update date:2019.4.28
 */
#include <Wire.h>
void setup() {
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(115200);  // start serial for output
  pinMode(LED_BUILTIN, OUTPUT);//LED
}
void loop() {
  Get_LidarDatafromIIC(0x10);
  Get_LidarDatafromIIC(0x11);
  Get_LidarDatafromIIC(0x12);
  Get_LidarDatafromIIC(0x13);
  delay(250);
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(250); 
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
}
void Get_LidarDatafromIIC(byte address){
  char i = 0; 
  byte rx_buf[7] = {0}; 
  Wire.beginTransmission(address); // Begin a transmission to the I2C Slave device with the given address. 
  Wire.write(1); // Reg's Address_H 
  Wire.write(2); // Reg's Address_L 
  Wire.write(7); // Data Length 
  Wire.endTransmission(0);  // Send a START Sign 
  Wire.requestFrom(address, 7); // request 7 bytes from slave device address
  //print the result via serial
  Serial.print("Address=0x");
  Serial.print(address,HEX);
  Serial.print(":   ");
   while ( Wire.available()) 
  { 
    rx_buf[i] = Wire.read(); // received one byte 
    Serial.print("0x");
    Serial.print(rx_buf[i],HEX);
    Serial.print(";");
    i++; 
    if(i>=7)
    {
      i=0;
      Serial.print("---------->");
      Serial.print("Distance=");
      Serial.print(rx_buf[3]*256+rx_buf[2]);
      Serial.print(";");
      Serial.print("Strength=");
      Serial.print(rx_buf[5]*256+rx_buf[4]);
    }
  }
  Serial.print("\r\n"); 
}
