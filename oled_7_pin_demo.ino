/**
 * Example showing how to use and display a 7 pin monochrome OLED display in I2C mode, such as the one linked below:
 *  IZOKEE 0.96'' I2C IIC SPI Serial 12864 128X64 Pixel OLED LCD Display https://www.amazon.com/gp/product/B076PP6WMW/
 *  
 * Documentation for this board is non-existent.  From the factory it is configured to communicate through 4-wire SPI.  
 * Through trial and error I determined that one must do the following to get the adafruit OLED library to work with it:
 * - On the back of the board, desolder the surface mount resistor R4 and move it to position R3
 * - On the back of the board, bridge resistor R6 (eg with a blob of solder)
 * - Change "Adafruit_SSD1306.h" at the top to "#define SSD1306_128_64" instead of "#define SSD1306_128_32"
 * - Wire up the pins as follows:
 *   +----------+-----------------------------------+
 *   | OLED Pin | Microconroller Pin                |
 *   +----------+-----------------------------------+
 *   | GND      |  Ground                           |
 *   | VCC      |  3.3v (or 5v if you logic is 5v)  |
 *   | D0       |  SCL                              |
 *   | D1       |  SDA                              |
 *   | RES      |  Any digital out pin (eg 19)      |
 *   | DC       |  Ground                           |
 *   | CS       |  Ground                           |
 *   +----------+-----------------------------------+
 */
#include <Adafruit_SSD1306.h>

// Change this to whatever pin you wired RES to. 
#define OLED_RESET 19
Adafruit_SSD1306 display(OLED_RESET);

void setup()   {
  // The reset pin needs to be low during boot, otherwise the display 
  // doesn't work until you reset the device without a power cycle.
  pinMode(OLED_RESET, OUTPUT);
  digitalWrite(OLED_RESET, LOW);

  // Not sure how long you actually need to wait but 1000ms worked for me and 100ms didn't
  delay(1000);

  // Start the display.  Its I2C address is 0x3C, which I suspect can be changed by pulling DC or CS high but I didn't experiment.
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  
  Serial.begin(115200);
}

unsigned long frames[10] = {0};
int position = 0;
void loop() {
  frames[(++position)%10] = millis();
  // Print some text that will change on each loop.
  display.setCursor(0,0);
  display.clearDisplay();
  display.println("It worked! ");
  display.print("Millis: ");
  display.println(millis());
  display.print("FPS: ");
  display.println(10.0/((frames[position%10] - frames[(position+9)%10])/1000.0));
  display.display();
  delay(1);
}

