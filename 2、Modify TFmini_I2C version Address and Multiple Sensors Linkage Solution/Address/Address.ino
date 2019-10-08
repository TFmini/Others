/**
 * @Description: Modify TFmini address from @Addr to @value
 * Params:
 *        @Addr: current address of TFmini, ie 0x10
 *        @value: new address, ie 0x11
 */
void SET_TFMini_I2CAddr(byte Addr, byte value) {
  //Start a command, declare @Addr, Reg_H, Reg_L, DATA Length
  Wire.beginTransmission(Addr); // Begin a transmission to the I2C Slave device with the given address.
  Wire.write(0); // Reg's Address_H
  Wire.write(38); // Reg's Address_L , OCT 38 == HEX 0x26
  Wire.write(1); // Data Length
  Wire.endTransmission(0);  // Send a START Sign
  //Start a command, store new value to Addr
  Wire.beginTransmission(Addr); // Begin a transmission to the I2C Slave device with the given address.
  Wire.write(value); // I2C new Address
  Wire.endTransmission(1);  // Send a STOP Sign
  Serial.print("Set Addr ");
  Serial.print(Addr);
  Serial.print(" as ");
  Serial.print(value);
  Serial.print(".\r\n");
  delay(500);
}
