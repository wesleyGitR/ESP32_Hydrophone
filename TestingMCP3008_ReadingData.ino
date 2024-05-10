#include <Adafruit_MCP3008.h>

#define LED_PIN 16 // Define the pin for the LED

Adafruit_MCP3008 adc;

void setup() {
  Serial.begin(9600);
  while (!Serial);

  Serial.println(" ");
  Serial.println(" ");
  Serial.println("MCP3008 simple test.");
  
  // Initialize the LED pin as OUTPUT
  pinMode(LED_PIN, OUTPUT);
  
  // Initialize the MCP3008
  adc.begin();
}

void loop() {
  boolean ledOn = false; // Flag to indicate if LED should be turned on

  // for (int chan=0; chan<8; chan++) {
  //   int value = adc.readADC(chan);
  //   Serial.print(value); Serial.print("\t");
    
  //   if (value > 400) {
  //     ledOn = true;
  //   }
  // }

  int chan = 0;
  int value = adc.readADC(chan);
  Serial.print(value); Serial.print("\t");
    
  if (value > 400) {
    ledOn = true;
  }

  // Turn on the LED if any of the channels read a value past 600
  if (ledOn) {
    digitalWrite(LED_PIN, HIGH);
  } else {
    digitalWrite(LED_PIN, LOW);
  }

  Serial.println();
  
  delayMicroseconds(23);
}


