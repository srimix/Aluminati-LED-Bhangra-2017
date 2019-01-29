#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <Adafruit_NeoPixel.h>
#define PIN D4
Adafruit_NeoPixel strip = Adafruit_NeoPixel(150, PIN, NEO_GRB + NEO_KHZ800);
//const char* ssid = "Verizon-SM-G925V-F98C";
//const char* password = "aqzm614!";

//const char* ssid = "ATT8EDq6lB";
//const char* password = "9rg5m5n39hrj";

const char* ssid = "TP-LINK_5A9F";
const char* password = "12468478";


ESP8266WebServer server(80);

const int led = 13;

void handleRoot() {
  server.send(200, "text/plain", "hello from esp8266!");
}

void handleNotFound(){
  digitalWrite(led, 1);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  digitalWrite(led, 0);
}
// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
void setup(void){
  pinMode(led, OUTPUT);
  digitalWrite(led, 0);
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.hostname("15sonia");
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("15sonia")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);

  server.on("/ip",[](){
    server.send(200, "text/plain", WiFi.localIP().toString());
  });
  
  server.on("/khunde",[](){
    server.send(200, "text/plain", "khunde running");
    khunde();
  });

  server.on("/rainbow", [](){
    server.send(200, "text/plain", "rainbow on");
    rainbow(20);
  });
  
  server.on("/turnoff", [](){
    server.send(200, "text/plain", "all pixels off");
    turnOff();
  });

  server.on("/testflash", [](){
    server.send(200, "text/plain", "testing - look for flash");
    testFlash();
  });
  
  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void fixedColor(uint16_t r, uint16_t g, uint16_t b) {
  uint16_t i;
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, r, g, b);
    }
    strip.show();
}

void red(){
  fixedColor(255,0,0);
  }
void green(){
  fixedColor(0,255,0);
  }
void blue(){
  fixedColor(0,0,255);
  }

void pink(){
  fixedColor(255,100,100);
  }
void purple(){
  fixedColor(75,25,127);
  }
void orange(){
  fixedColor(255,128,0);
  }
void teal(){
  fixedColor(0,128,128);
  }
void yellow(){
  fixedColor(255,255,0);
  }
void magenta(){
  fixedColor(255,0,255);
  }
void white(){
  fixedColor(127,127,127);
  }

void fireNation(){
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+0, 255, 0, 0);    //turn every third pixel on
      }
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+1, 255, 127, 0);    //turn every third pixel on
      }
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+2, 255, 255, 0);    //turn every third pixel on
      }
      strip.show();
}

void pixelMania(){
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+0, 255, 0, 0);    //turn every third pixel on
      }
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+1, 0, 255, 0);    //turn every third pixel on
      }
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+2, 0, 0, 255);    //turn every third pixel on
      }
      strip.show();
}
  
void jugni(){
  theaterChase(strip.Color(127, 127, 127), 50);
  theaterChase(strip.Color(127, 127, 127), 50); //repeat to get 3000ms total
  //delay(100); //compensate
  }


void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

void rainbow3CountKick() {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(7);
  }
  turnOff();
  delay(682); //compensate
}

void rainbow4Count() {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(9);
  }
  delay(170); //compensate
}

void rainbow8Count() {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(14);
  }

}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

void turnOff() {
  fixedColor(0,0,0);
}

void testFlash() {
  fixedColor(255,255,255);
  delay(500);
  fixedColor(0,0,0);
}

void khunde() {
  Serial.println("intro"); // first entry
  delay(58000); //  -subtract both
  Serial.println("lightsaber start"); // first entry
  colorWipe(strip.Color(255, 0, 0), 10); // Red
  delay(3092);
  //lightsaber start
    Serial.println("first entry"); // first entry
    pink();
    delay(2474);
    Serial.println("second entry"); // second entry
    red();
    delay(2474);
    Serial.println("third entry"); // third entry
    red();
    delay(2474);
    Serial.println("up, hoi, 360 spin"); // up, hoi, 360 spin
    red();
    delay(2474);
    Serial.println("punjabs"); // punjabs
    green();
    delay(2474);
    Serial.println("faslan"); // faslan
    green();
    delay(2474);
    Serial.println("advance and twirl"); // advance and twirl
    green();
    delay(2474);
    Serial.println("hurl around"); // hurl around
    green();
    delay(2474);
    Serial.println("sways and jabs"); // sways and jabs
    rainbow8Count();
    rainbow8Count();
    //delay(84); //compensate
    //Serial.println("tohr teri allarhan"); // tohr teri allarhan
    //red(); //rainbow4Count();
    //delay(2474);
    //Serial.println("chardi jawani, falcon kick"); // chardi jawani, falcon kick
    //blue(); //rainbow3CountKick();
    //delay(2474);
    Serial.println("first diag"); // first diag
    red();
    delay(2474);
    Serial.println("second diag"); // second diag
    turnOff();
    delay(2474);
    Serial.println("360 behtke"); //360 behtke
    orange();
    delay(2474);
    Serial.println("if you got a fat ass"); // if you got a fat ass
    pixelMania();
    delay(2474);
    Serial.println("bustout slashes"); // bustout slashes
    fireNation();
    delay(2474);
    Serial.println("slide -> ding"); // slide -> ding
    fireNation();
    delay(1855);
    turnOff();
    delay(618);
    Serial.println("jumps"); // jumps
    magenta();
    delay(618);
    teal();
    delay(618);
    magenta();
    delay(618);
    teal();
    delay(620);
    Serial.println("sammi throws"); // sammi throws
    teal();
    delay(2474);
    Serial.println("charge on hoi's"); // charge on hoi's
    teal();
    delay(2474);
    Serial.println("windup"); // windup
    teal();
    delay(1237);
    Serial.println("spin"); // spin
    turnOff();
    delay(1540);
    Serial.println("strobe"); // strobe
    jugni();
    jugni();
    Serial.println("final cascade"); // final cascade
    red();
    // jugni to the end
}

void loop(void){
  server.handleClient();
}
