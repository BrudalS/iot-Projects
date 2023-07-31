// Include the library
#include <JPEGDecoder.h>

// Define Slave Select pin
#define SD_CS 53

void setup() {
  // Set pin 13 to output, otherwise SPI might hang
  pinMode(13, OUTPUT);

  // Begin Serial port for communication with PC
  Serial.begin(115200);

  // Start the SD
  if(!SD.begin(SD_CS)) {
    // If the SD can't be started, loop forever
    Serial.println("SD failed or not present!");
    while(1);
  }

  // Open the root directory
  File root = SD.open("/");

  // Wait for the PC to signal
  while(!Serial.available());

  // Send all files on the SD card
  while(true) {
    // Open the next file
    File jpgFile = root.openNextFile();

    // We have sent all files
    if(!jpgFile) {
      break;
    }

    // Decode the JPEG file
    JpegDec.decodeSdFile(jpgFile);

    // Create a buffer for the packet
    char dataBuff[240];

    // Fill the buffer with zeros
    initBuff(dataBuff);

    // Create a header packet with info about the image
    String header = "$ITHDR,";
    header += JpegDec.width;
    header += ",";
    header += JpegDec.height;
    header += ",";
    header += JpegDec.MCUSPerRow;
    header += ",";
    header += JpegDec.MCUSPerCol;
    header += ",";
    header += jpgFile.name();
    header += ",";
    header.toCharArray(dataBuff, 240);

    // Send the header packet
    for(int j=0; j<240; j++) {
      Serial.write(dataBuff[j]);
    }

    // Pointer to the current pixel
    uint16_t *pImg;

    // Color of the current pixel
    uint16_t color;

    // Create a data packet with the actual pixel colors
    strcpy(dataBuff, "$ITDAT");
    uint8_t i = 6;

    // Repeat for all MCUs in the image
    while(JpegDec.read()) {
      // Save pointer the current pixel
      pImg = JpegDec.pImage;

      // Get the coordinates of the MCU we are currently processing
      int mcuXCoord = JpegDec.MCUx;
      int mcuYCoord = JpegDec.MCUy;

      // Get the number of pixels in the current MCU
      uint32_t mcuPixels = JpegDec.MCUWidth * JpegDec.MCUHeight;

      // Repeat for all pixels in the current MCU
      while(mcuPixels--) {
        // Read the color of the pixel as 16-bit integer
        color = *pImg++;

        // Split it into two 8-bit integers
        dataBuff[i] = color >> 8;
        dataBuff[i+1] = color;
        i += 2;

        // If the packet is full, send it
        if(i == 240) {
          for(int j=0; j<240; j++) {
            Serial.write(dataBuff[j]);
          }
          i = 6;
        }

        // If we reach the end of the image, send a packet
        if((mcuXCoord == JpegDec.MCUSPerRow - 1) &&
        (mcuYCoord == JpegDec.MCUSPerCol - 1) &&
        (mcuPixels == 1)) {

          // Send the pixel values
          for(int j=0; j<i; j++) {
            Serial.write(dataBuff[j]);
          }

          // Fill the rest of the packet with zeros
          for(int k=i; k<240; k++) {
            Serial.write(0);
          }
        }
      }
    }
  }

  // Safely close the root directory
  root.close();
}

// Function to fill the packet buffer with zeros
void initBuff(char* buff) {
  for(int i = 0; i < 240; i++) {
    buff[i] = 0;
  }
}

void loop() {
  // Nothing here
  // We don't need to send the same images over and over again
}
