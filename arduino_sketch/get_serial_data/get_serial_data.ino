#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define LOGO_HEIGHT   16
#define LOGO_WIDTH    16
static const unsigned char PROGMEM logo_bmp[] =
{ B00000000, B11000000,
  B00000001, B11000000,
  B00000001, B11000000,
  B00000011, B11100000,
  B11110011, B11100000,
  B11111110, B11111000,
  B01111110, B11111111,
  B00110011, B10011111,
  B00011111, B11111100,
  B00001101, B01110000,
  B00011011, B10100000,
  B00111111, B11100000,
  B00111111, B11110000,
  B01111100, B11110000,
  B01110000, B01110000,
  B00000000, B00110000 };

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
String stringVar = "";
int blnk_time = 1000; //время мигания
int ledState = LOW; // состояние светодиода
unsigned long previousMillis = 0; // храним время последнего переключения светодиода 

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  
  Serial.begin(9600);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
  Serial.println("SSD1306 allocation failed");
  for(;;); // Don't proceed, loop forever
}
  display.clearDisplay();
  display.display();
  display.setTextSize(2);             
  display.setTextColor(WHITE);
  display.setCursor(20,10);  
  testfillroundrect(); // Draw rounded rectangles (filled)
  //testdrawbitmap();    // Draw a small bitmap image;
  display.display();
  digitalWrite(LED_BUILTIN, LOW);
  stringVar = "";
}

void loop() {
  if (Serial.available() > 0) {
    ledblink();
    char data_char = Serial.read();
    Serial.print(data_char);
    stringVar = stringVar + data_char;
    display.clearDisplay();
    display.setCursor(20,10);  
    display.println(stringVar);
  } else {
    stringVar = "";
    display.display();
    Serial.println("Ready");
  }
}


void testdrawbitmap(void) {
  display.clearDisplay();
  display.drawBitmap(
    (display.width()  - LOGO_WIDTH ) / 2,
    (display.height() - LOGO_HEIGHT) / 2,
    logo_bmp, LOGO_WIDTH, LOGO_HEIGHT, 1);
  display.display();
  delay(1000);
}

void testfillroundrect(void) {
  display.clearDisplay();
  for(int16_t i=0; i<display.height()/2-2; i+=2) {
    // The INVERSE color is used so round-rects alternate white/black
    display.fillRoundRect(i, i, display.width()-2*i, display.height()-2*i,
      display.height()/4, SSD1306_INVERSE);
    display.display();
    delay(25);
  }
  delay(2000);
}


void ledblink() {
  //unsigned long currentMillis = millis();  
  //if (ledState == HIGH) {
  //    if (currentMillis - previousMillis >= blnk_time) {
  //      // сохраняем время последнего переключения
  //      previousMillis = currentMillis;
  //      ledState = LOW;
  //   }
  //}
  // проверяем не прошёл ли нужный интервал
  //if (ledState == LOW) {
  //  previousMillis = currentMillis;
  //  // сохраняем время начала свечения
  //  //ledState = HIGH;
  //  } 

  // устанавливаем состояние светодиода
    ledState == HIGH;
    digitalWrite(LED_BUILTIN, ledState);
    //delay(5);
    ledState = LOW;
    digitalWrite(LED_BUILTIN, ledState);
}  
