#include <Wire.h>

#define device_id 0b1101000

long AX, AY, AZ;
float AX_out, AY_out, AZ_out;
long GX, GY, GZ;
float GX_out, GY_out, GZ_out;


void setup() {
  //Basic Setup
  Serial.begin(9600);
  Wire.begin();
  
  //MPU 9150 Configuration
  Wire.beginTransmission(device_id);
  Wire.write(0x6B); // Power management register
  Wire.write(0b00000000);
  Wire.endTransmission();  
  Wire.beginTransmission(device_id);
  Wire.write(0x1B); // Gyro config register
  Wire.write(0x00000000);
  Wire.endTransmission(); 
  Wire.beginTransmission(device_id);
  Wire.write(0x1C); //Accelerometer config register
  Wire.write(0b00000000); 
  Wire.endTransmission(); 
  
  // Bluetooth Configuration
}

void loop() {
  getData();
  printData();
  //printData2();
  delay(500);
}

void getData() {
  //Reads data from accelerometer and stores it in AX_out, AY_out, and AZ_out
  Wire.beginTransmission(device_id); 
  Wire.write(0x3B); //First register in the 6 register block for accelerometer
  Wire.endTransmission();
  Wire.requestFrom(device_id,6); 
  while(Wire.available() < 6);
  AX = Wire.read()<<8|Wire.read();
  AY = Wire.read()<<8|Wire.read(); 
  AZ = Wire.read()<<8|Wire.read(); 
  AX_out = AX / 16384.0;
  AY_out = AY / 16384.0; 
  AZ_out = AZ / 16384.0;

  //Reads data from Gyroscope and stores it in GX_out, GY_out, GZ_out
  Wire.beginTransmission(device_id); 
  Wire.write(0x43);// First register in the 6 register block for gyro
  Wire.endTransmission();
  Wire.requestFrom(device_id,6); 
  while(Wire.available() < 6);
  GX = Wire.read()<<8|Wire.read(); 
  GY = Wire.read()<<8|Wire.read(); 
  GZ = Wire.read()<<8|Wire.read();
  GX_out = GX / 131.0;
  GY_out = GY / 131.0; 
  GZ_out = GZ / 131.0;
}

void printData() {
  //Prints readings of accelerometer and gyro to serial port
  Serial.print("Gyro: X=");
  Serial.print(GX_out);
  Serial.print(" Y=");
  Serial.print(GY_out);
  Serial.print(" Z=");
  Serial.print(GZ_out);
  Serial.print(" Acc: X=");
  Serial.print(AX_out);
  Serial.print(" Y=");
  Serial.print(AY_out);
  Serial.print(" Z=");
  Serial.println(AZ_out);
}

void printData2(){
  String output;
  output.concat("$");
  output.concat(GX_out);
  output.concat(",");
  output.concat(GY_out);
  output.concat(",");
  output.concat(GZ_out);
  output.concat(",");
  output.concat(AX_out);
  output.concat(",");
  output.concat(AY_out);
  output.concat(",");
  output.concat(AZ_out);
  output.concat("$");
  Serial.println(output); 
}

