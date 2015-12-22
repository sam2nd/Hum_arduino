// Example testing sketch for various DHT humidity/temperature sensors
// Written by ladyada, public domain

#include "DHT.h"

//Display TFT Red 1.8 TReiber ST7735
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library
#include <SPI.h>


// For the breakout, you can use any 2 or 3 pins
// These pins will also work for the 1.8" TFT shield
#define TFT_CS     10
#define TFT_RST    9  // you can also connect this to the Arduino reset
                      // in which case, set this #define pin to 0!
#define TFT_DC     8

#define DHTPIN 2     // what digital pin we're connected to

// Uncomment whatever type you're using
#define DHTTYPE DHT11   // DHT 11 blaues gehäuse 
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

// Connect pin 1 (on the left) of the sensor to +5V
// NOTE: If using a board with 3.3V logic like an Arduino Due connect pin 1
// to 3.3V instead of 5V!
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor

// Note that older versions of this library took an optional third parameter to
// tweak the timings for faster processors.  This parameter is no longer needed
// as the current DHT reading algorithm adjusts itself to work on faster procs.
// Option 1 (recommended): must use the hardware SPI pins
// (for UNO thats sclk = 13 and sid = 11) and pin 10 must be
// an output. This is much faster - also required if you want
// to use the microSD card (see the image drawing example)
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS,  TFT_DC, TFT_RST);

// Initialize DHT sensor.
DHT dht(DHTPIN, DHTTYPE);
//Counter
long i=0L;
float max_hum=0;
float min_hum=0;
float max_T=0;
float min_T=0;

void setup() {
  Serial.begin(9600);
  Serial.println("Begin");
 //Start Display 
 // Use this initializer if you're using a 1.8" TFT
  tft.initR(INITR_BLACKTAB);   // initialize a ST7735S chip, black tab
  tft.setRotation(1);  // 0 - Portrait, 1 - Lanscape
 // Start DHT Sensor 
  dht.begin();
}
void min_max_hum(float hum, long a)
{
 Serial.print(hum);
 Serial.println(a);
  if (a==1){
    Serial.print("EVENT");
   min_hum=hum;
   max_hum=hum;
         }
 else {
    if (hum >= max_hum){
    max_hum = hum;}
    if (hum < min_hum){
    min_hum = hum;}
    else {
    ;
    }
 }}

void min_max_temp(float temp, long a)
{
 
 Serial.print(temp);
 Serial.println(a);
  if (a==1){
    Serial.print("EVENT");
   min_T=temp;
   max_T=temp;
         }
 else {
    if (temp >= max_T){
    max_T = temp;}
    if (temp < min_T){
    min_T = temp;}
    else {
    ;
    }
 }}
void loop() {
i=i+1;

  // Wait a few seconds between measurements.
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();


  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) ) {
    Serial.println("Failed to read from DHT sensor!");
    tft.setTextWrap(false);
    tft.fillScreen(ST7735_BLACK);
    tft.setCursor(0, 30);
    tft.setTextColor(ST7735_RED);
    tft.setTextSize(1);
    tft.println(" Failed to read from DHT Sensor!");
    return;
  }

  
min_max_hum(h,i);
min_max_temp(t,i);

  Serial.print("Humidity: ");
  Serial.print(h);
  // Dispaly ausgabe:
tft.setTextWrap(false);
    tft.fillScreen(ST7735_BLACK);
    tft.setCursor(0, 30);
    tft.setTextColor(ST7735_RED);
    tft.setTextSize(1);
  tft.println(" Rel. Feuchte: ");
  tft.print(" ");
  tft.print(h);
  tft.println(" %");
 

  tft.print(" MAX: ");
 tft.print(max_hum);

  tft.print("  MIN: ");
 tft.println(min_hum);
 
  //Serielle Ausgabe Temperatur
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" *C ");
  //Tft Ausgabe Temperatur
  tft.println();
  tft.println(" Temperatur ");
  tft.print(" ");
  tft.print(t);
  tft.println(" C");

    tft.print(" MAX: ");
 tft.print(max_T);

  tft.print("  MIN: ");
 tft.println(min_T);
 tft.println();
 tft.print(" ");
 tft.print(i*2);
 tft.print(" Sekunden");
 tft.println();
}
