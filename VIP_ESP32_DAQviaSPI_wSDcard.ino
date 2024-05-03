#include <SPI.h>
//#include "FS.h"
//#include "SD.h"
//#include "stdint.h"

#define SD_CS_PIN 4  // Define chip select pin
#define ADC_CS_PIN 5  // Define chip select pin
#define SAMPLES_PER_BUFFER 44100//2646000// Number of samples per buffer
#define SPI_CLOCK_SPEED 3000000 // SPI clock speed (2 MHz)
#define SINGLE_BIT  0x00
#define START_BIT  0x01



//void listDir(fs::FS &fs, const char * dirname, uint8_t levels){
//    Serial.printf("Listing directory: %s\n", dirname);
//
//    File root = fs.open(dirname);
//    if(!root){
//        Serial.println("Failed to open directory");
//        return;
//    }
//    if(!root.isDirectory()){
//        Serial.println("Not a directory");
//        return;
//    }
//
//    File file = root.openNextFile();
//    while(file){
//        if(file.isDirectory()){
//            Serial.print("  DIR : ");
//            Serial.println(file.name());
//            if(levels){
//                listDir(fs, file.path(), levels -1);
//            }
//        } else {
//            Serial.print("  FILE: ");
//            Serial.print(file.name());
//            Serial.print("  SIZE: ");
//            Serial.println(file.size());
//        }
//        file = root.openNextFile();
//    }
//}
//
//void createDir(fs::FS &fs, const char * path){
//    Serial.printf("Creating Dir: %s\n", path);
//    if(fs.mkdir(path)){
//        Serial.println("Dir created");
//    } else {
//        Serial.println("mkdir failed");
//    }
//}
//
//void removeDir(fs::FS &fs, const char * path){
//    Serial.printf("Removing Dir: %s\n", path);
//    if(fs.rmdir(path)){
//        Serial.println("Dir removed");
//    } else {
//        Serial.println("rmdir failed");
//    }
//}
//
//void readFile(fs::FS &fs, const char * path){
//    Serial.printf("Reading file: %s\n", path);
//
//    File file = fs.open(path);
//    if(!file){
//        Serial.println("Failed to open file for reading");
//        return;
//    }
//
//    Serial.print("Read from file: ");
//    while(file.available()){
//        Serial.write(file.read());
//    }
//    file.close();
//}
//
//void writeFile(fs::FS &fs, const char * path, const char * message){
//    Serial.printf("Writing file: %s\n", path);
//
//    File file = fs.open(path, FILE_WRITE);
//    if(!file){
//        Serial.println("Failed to open file for writing");
//        return;
//    }
//    if(file.print(message)){
//        Serial.println("File written");
//    } else {
//        Serial.println("Write failed");
//    }
//    file.close();
//}
//
//void appendFile(fs::FS &fs, const char * path, const char * message){
//    Serial.printf("Appending to file: %s\n", path);
//
//    File file = fs.open(path, FILE_APPEND);
//    if(!file){
//        Serial.println("Failed to open file for appending");
//        return;
//    }
//    if(file.print(message)){
//        Serial.println("Message appended");
//    } else {
//        Serial.println("Append failed");
//    }
//    file.close();
//}
//
//void renameFile(fs::FS &fs, const char * path1, const char * path2){
//    Serial.printf("Renaming file %s to %s\n", path1, path2);
//    if (fs.rename(path1, path2)) {
//        Serial.println("File renamed");
//    } else {
//        Serial.println("Rename failed");
//    }
//}
//
//void deleteFile(fs::FS &fs, const char * path){
//    Serial.printf("Deleting file: %s\n", path);
//    if(fs.remove(path)){
//        Serial.println("File deleted");
//    } else {
//        Serial.println("Delete failed");
//    }
//}
//
//void testFileIO(fs::FS &fs, const char * path){
//    File file = fs.open(path);
//    static uint8_t buf[512];
//    size_t len = 0;
//    uint32_t start = millis();
//    uint32_t end = start;
//    if(file){
//        len = file.size();
//        size_t flen = len;
//        start = millis();
//        while(len){
//            size_t toRead = len;
//            if(toRead > 512){
//                toRead = 512;
//            }
//            file.read(buf, toRead);
//            len -= toRead;
//        }
//        end = millis() - start;
//        Serial.printf("%u bytes read for %u ms\n", flen, end);
//        file.close();
//    } else {
//        Serial.println("Failed to open file for reading");
//    }
//
//
//    file = fs.open(path, FILE_WRITE);
//    if(!file){
//        Serial.println("Failed to open file for writing");
//        return;
//    }
//
//    size_t i;
//    start = millis();
//    for(i=0; i<2048; i++){
//        file.write(buf, 512);
//    }
//    end = millis() - start;
//    Serial.printf("%u bytes written for %u ms\n", 2048 * 512, end);
//    file.close();
//}


void setup() {
  Serial.begin(115200); // Initialize serial communication
  
//  if(!SD.begin()){
//      Serial.println("Card Mount Failed");
//      return;
//  }
//  uint8_t cardType = SD.cardType();
  SPI.begin(); // Initialize SPI communication
  SPI.beginTransaction(SPISettings(SPI_CLOCK_SPEED, MSBFIRST, SPI_MODE0)); // Set SPI clock speed
  pinMode(ADC_CS_PIN, OUTPUT); // Set CS pin as output
  //pinMode(SD_CS_PIN, OUTPUT); // Set CS pin as output
  digitalWrite(ADC_CS_PIN, HIGH); // Deselect MCP3008
  //digitalWrite(SD_CS_PIN, LOW); // select SD Card
//  if(cardType == CARD_NONE){
//      Serial.println("No SD card attached");
//      return;
//  }
//
//  Serial.print("SD Card Type: ");
//  if(cardType == CARD_MMC){
//      Serial.println("MMC");
//  } else if(cardType == CARD_SD){
//      Serial.println("SDSC");
//  } else if(cardType == CARD_SDHC){
//      Serial.println("SDHC");
//  } else {
//      Serial.println("UNKNOWN");
//  }
  
}

void loop() {
  //int16_t buffer[SAMPLES_PER_BUFFER]; // Buffer to store samples
  uint16_t buffer[SAMPLES_PER_BUFFER];
  char buffer_str[SAMPLES_PER_BUFFER][4];
  // int samples = 0;
  // Select MCP3008
  digitalWrite(ADC_CS_PIN, LOW);
  //digitalWrite(SD_CS_PIN, HIGH); // select SD Card

  // Sample data in batches
  for (int i = 0; i < SAMPLES_PER_BUFFER; i++) {
    // Send command byte to request data from channel 0 in single-ended mode
    byte commandByte = START_BIT | (0x00 << 1) |SINGLE_BIT; // Start bit (1), single-ended mode (0), channel select (0)
    byte adcDataMSB, adcDataLSB;
    byte adc1_data[6];
    adcDataMSB = SPI.transfer(commandByte);
    //adcDataLSB = SPI.transfer(0x00); // Dummy byte to receive the second part of the data
    adc1_data[0] = SPI.transfer(0x00); // Read third byte for ADC 1
    adc1_data[1] = SPI.transfer(0x00); // Read third byte for ADC 1
    adc1_data[2] = SPI.transfer(0x00); // Read third byte for ADC 1
    adc1_data[3] = SPI.transfer(0x00); // Read third byte for ADC 1
    adc1_data[4] = SPI.transfer(0x00); // Read third byte for ADC 1
    adc1_data[5] = SPI.transfer(0x00); // Read third byte for ADC 1
    // Combine the received bytes to get the ADC value
    int adcValue1 = ((adc1_data[1] & 0x03) << 8) | adc1_data[2];
    int adcValue2 = ((adc1_data[4] & 0b11000000) >> 8) | (adc1_data[3] << 2);

    // Store sample in buffer
    buffer[i] = adcValue1;
    sprintf(buffer_str[i], "%c", adcValue1);
    
    //Serial.println(adcValue2);
  }
  Serial.println(buffer_str[-1]);
  // Deselect MCP3008
  digitalWrite(ADC_CS_PIN, HIGH);
  //digitalWrite(SD_CS_PIN, LOW);
  //delay(1000);
//  for (int i = 0; i < SAMPLES_PER_BUFFER; i++) {
//    writeFile(SD, "/05022024_test0.txt", buffer_str[i]);
//  }
  delay(1000);
}

/*
 * Connect the SD card to the following pins:
 *
 * SD Card | ESP32
 *    D2       -
 *    D3       SS
 *    CMD      MOSI
 *    VSS      GND
 *    VDD      3.3V
 *    CLK      SCK
 *    VSS      GND
 *    D0       MISO
 *    D1       -
 */
