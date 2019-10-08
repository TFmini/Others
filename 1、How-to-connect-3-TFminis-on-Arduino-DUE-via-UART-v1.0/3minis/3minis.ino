/* 
 Multiple TFminis ---- Arduino DUE ----- UART
 This is a sample code for connecting 3TFminis to Arduino DUE board via UART, each TFmini use one UART.
 For details, refer to Product Specifications.
 The Arduino DUE comes with four hardware UART interfaces. We use three of them to connect one TFmini separately. 
 Another connects to the computer for viewing data.
 This is just to provide testing, not my company's official product. Do not use for commercial purposes
 In principle, we do not provide technical support for this code. 
 Author:Mincy Zhao
 Update date:2018.08.14
*/
int dist,dist2,dist3; //actual distance measurements of LiDAR
int strength,strength2,strength3; //signal strength of LiDAR
unsigned char check,check2,check3; //save check value
int i;
unsigned char uart[9],uart2[9],uart3[9]; //save data measured by LiDAR
const int HEADER=0x59; //frame header of data package
int rec_debug_state = 0x01,rec_debug_state2 = 0x01,rec_debug_state3 = 0x01;//receive state for frame
//unsigned char rec_flag = 0,rec_flag2 = 0,rec_flag3 = 0;
void setup() {
 Serial.begin(115200); //set bit rate of serial port connecting Arduino with computer
 Serial1.begin(115200); //set bit rate of serial port connecting LiDAR1 with Arduino
 Serial2.begin(115200); //set bit rate of serial port connecting LiDAR2 with Arduino
 Serial3.begin(115200); //set bit rate of serial port connecting LiDAR3 with Arduino
}
void loop() { 
 Get_Lidar1_data();//if this channel is not be used, comment out this line
 Get_Lidar2_data();//if this channel is not be used, comment out this line
 Get_Lidar3_data();//if this channel is not be used, comment out this line
}
void Get_Lidar1_data(){
 if (Serial1.available()) { //check if serial port has data input
 
 if(rec_debug_state == 0x01){//the first byte
 uart[0]=Serial1.read();
 if(uart[0] == 0x59){
 check = uart[0];
 rec_debug_state = 0x02;
 }
 }
 
 else if(rec_debug_state == 0x02){//the second byte
 uart[1]=Serial1.read();
 if(uart[1] == 0x59){
 check += uart[1];
 rec_debug_state = 0x03;
 }
 else{
 rec_debug_state = 0x01;
 }
 }
else if(rec_debug_state == 0x03){
 uart[2]=Serial1.read();
 check += uart[2];
 rec_debug_state = 0x04;
 }
 else if(rec_debug_state == 0x04){
 uart[3]=Serial1.read();
 check += uart[3];
 rec_debug_state = 0x05;
 }
 else if(rec_debug_state == 0x05){
 uart[4]=Serial1.read();
 check += uart[4];
 rec_debug_state = 0x06;
 }
 else if(rec_debug_state == 0x06){
 uart[5]=Serial1.read();
 check += uart[5];
 rec_debug_state = 0x07;
 }
 else if(rec_debug_state == 0x07){
 uart[6]=Serial1.read();
 check += uart[6];
 rec_debug_state = 0x08;
 }
 else if(rec_debug_state == 0x08){
 uart[7]=Serial1.read();
 check += uart[7];
 rec_debug_state = 0x09;
 }
 else if(rec_debug_state == 0x09){
 uart[8]=Serial1.read();
 if(uart[8] == check){
 dist = uart[2] + uart[3]*256;//the distance
 strength = uart[4] + uart[5]*256;//the strength
 Serial.print("dist = ");
 Serial.print(dist); //output measure distance value of LiDAR
 Serial.print('\t');
 Serial.print("strength = ");
Serial.print(strength); //output signal strength value
 Serial.print('\n');
 }
 rec_debug_state = 0x01;
 }
 }
}
void Get_Lidar2_data(){
 if (Serial2.available()) { //check if serial port has data input
 
 if(rec_debug_state2 == 0x01){//
 uart2[0]=Serial2.read();
 if(uart2[0] == 0x59){
 check2 = uart2[0];
 rec_debug_state2 = 0x02;
 }
 }
 
 else if(rec_debug_state2 == 0x02){//
 uart2[1]=Serial2.read();
 if(uart2[1] == 0x59){
 check2 += uart2[1];
 rec_debug_state2 = 0x03;
 }
 else{
 rec_debug_state2 = 0x01;
 }
 }
 else if(rec_debug_state2 == 0x03){
 uart2[2]=Serial2.read();
 check2 += uart2[2];
 rec_debug_state2 = 0x04;
 }
 else if(rec_debug_state2 == 0x04){
 uart2[3]=Serial2.read();
 check2 += uart2[3];
 rec_debug_state2 = 0x05;
 }
 else if(rec_debug_state2 == 0x05){
 uart2[4]=Serial2.read();
 check2 += uart2[4];
rec_debug_state2 = 0x06;
 }
 else if(rec_debug_state2 == 0x06){
 uart2[5]=Serial2.read();
 check2 += uart2[5];
 rec_debug_state2 = 0x07;
 }
 else if(rec_debug_state2 == 0x07){
 uart2[6]=Serial2.read();
 check2 += uart2[6];
 rec_debug_state2 = 0x08;
 }
 else if(rec_debug_state2 == 0x08){
 uart2[7]=Serial2.read();
 check2 += uart2[7];
 rec_debug_state2 = 0x09;
 }
 else if(rec_debug_state2 == 0x09){
 uart2[8]=Serial2.read();
 if(uart2[8] == check2){
 dist2 = uart2[2] + uart2[3]*256;//the distance
 strength2 = uart2[4] + uart2[5]*256;//the strength
 Serial.print(" dist2 = ");
 Serial.print(dist2); //output measure distance value of LiDAR
 Serial.print('\t');
 Serial.print("strength2 = ");
 Serial.print(strength2); //output signal strength value
 Serial.print('\n');
 }
 rec_debug_state2 = 0x01;
 }
 }
}
void Get_Lidar3_data(){
 if (Serial3.available()) { //check if serial port has data input
 
 if(rec_debug_state3 == 0x01){//
 uart3[0]=Serial3.read();
 if(uart3[0] == 0x59){
 check3 = uart3[0];
rec_debug_state3 = 0x02;
 }
 }
 
 else if(rec_debug_state3 == 0x02){//
 uart3[1]=Serial3.read();
 if(uart3[1] == 0x59){
 check3 += uart3[1];
 rec_debug_state3 = 0x03;
 }
 else{
 rec_debug_state3 = 0x01;
 }
 }
 else if(rec_debug_state3 == 0x03){
 uart3[2]=Serial3.read();
 check3 += uart3[2];
 rec_debug_state3 = 0x04;
 }
 else if(rec_debug_state3 == 0x04){
 uart[3]=Serial3.read();
 check3 += uart3[3];
 rec_debug_state3 = 0x05;
 }
 else if(rec_debug_state3 == 0x05){
 uart3[4]=Serial3.read();
 check3 += uart3[4];
 rec_debug_state3 = 0x06;
 }
 else if(rec_debug_state3 == 0x06){
 uart3[5]=Serial3.read();
 check3 += uart3[5];
 rec_debug_state3 = 0x07;
 }
 else if(rec_debug_state3 == 0x07){
 uart3[6]=Serial3.read();
 check3 += uart3[6];
 rec_debug_state3 = 0x08;
 }
else if(rec_debug_state3 == 0x08){
 uart3[7]=Serial3.read();
 check3 += uart3[7];
 rec_debug_state3 = 0x09;
 }
 else if(rec_debug_state3 == 0x09){
 uart3[8]=Serial3.read();
 if(uart3[8] == check3){
 dist3 = uart3[2] + uart3[3]*256;//the distance
 strength3 = uart3[4] + uart3[5]*256;//the strength
 Serial.print(" dist3 = ");
 Serial.print(dist3); //output measure distance value of LiDAR
 Serial.print('\t');
 Serial.print("strength3 = ");
 Serial.print(strength3); //output signal strength value
 Serial.print('\n');
 }
 rec_debug_state3 = 0x01;
 }
 }
}
