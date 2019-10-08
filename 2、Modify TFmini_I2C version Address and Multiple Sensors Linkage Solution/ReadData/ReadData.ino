/**
 * @Description: Get and print reading data from TFmini
 *  data_0  data_1 data_2 data_3 data_4     data_5     data_6
 *  Trigger   0    Dist_L Dist_H Strength_L Strength_H  Mode
 */
void GetAndPrintTFminiData(byte Addr) {
  byte rx_Num;
  byte rx_buf[7] = {0};
  byte i = 0;

  //Start a command, tell TFmini at Addr to measure distance
  Wire.beginTransmission(Addr); // Begin a transmission to the I2C Slave device with the given address.
  Wire.write(1); // Reg's Address_H
  Wire.write(2); // Reg's Address_L
  Wire.write(7); // Data Length
  Wire.endTransmission(0);  // Send a START Sign
  
  // Wire.requestFrom（AA,BB）;receive the data form slave.
  // AA: Slave Address ; BB: Data Bytes
  rx_Num = Wire.requestFrom(Addr, 7);

  // Wire.available: Retuens the number of bytes available for retrieval with read().
  while ( Wire.available())
  {
    rx_buf[i] = Wire.read(); // received one byte
    i++;
  }
      // OUTPUT
  Serial.print("Addr in OCT = ");
  Serial.print(Addr);
  Serial.print(":TrigFlag= ");
  Serial.print(rx_buf[0]);
  Serial.print(",Dist= ");
  Serial.print(rx_buf[2] | (rx_buf[3] << 8));
  Serial.print(",Strength= ");
  Serial.print(rx_buf[4] | (rx_buf[5] << 8));
  Serial.print(",Inttime= ");
  Serial.print(rx_buf[6]);
  Serial.print("\r\n");
}
