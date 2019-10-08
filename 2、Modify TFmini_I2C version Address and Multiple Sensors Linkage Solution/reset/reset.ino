/**
 * @Description: Reset TFmini
 */
void RESET_I2CBus() {
  //send 0x06 to address 0x00
  Wire.beginTransmission(0);
  Wire.write(6);
  Wire.endTransmission(1);
  delay(1000);
}
