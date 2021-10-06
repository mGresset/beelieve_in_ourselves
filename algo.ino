#include "DHT.h"
#include <SigFox.h>
#include <OneWire.h>
#include "HX711.h"

// Define utiles pour le capteur de température extérieure
#define DHT_PIN 4     
#define DHT_TYPE DHT22 

// Variables utiles pour le capteur de poids
#define HX711_DATA_PIN  3
#define HX711_SCK_PIN  2
float HX711_calibration_factor = 21666; //-7050 worked for my 440lb max scale setup
HX711 scale;

// Variables utiles pour l'envoi de Sig
typedef struct __attribute__ ((packed)) sigfox_message {
 int16_t TempInt_1;
 int16_t TempInt_2;
 int16_t TempInt_3;
 int16_t TempExt;
 int16_t HumiExt;
 int16_t Poids;
} SigfoxMessage;

SigfoxMessage msg;

// Variables utiles pour le capteur de température extérieure
DHT dht(DHT_PIN, DHT_TYPE);

// Variables utiles pour le capteur de température intérieure Poids::float:64:little-endian
const byte TempInt_Add_1[]  = {0x28,  0x90,  0x12,  0x56,  0xB5,  0x1,  0x3C,  0xD1};
const byte TempInt_Add_2[]  = {0x28,  0xB0,  0xDE,  0x34,  0xC,  0x0,  0x0,  0x18};
const byte TempInt_Add_3[]  = {0x28,  0xBD,  0x96,  0x56,  0xB5,  0x1,  0x3C,  0xF9};
OneWire  ds(5);  // on pin 10 (a 4.7K resistor is necessary)
int cpt = 0;
//------------------------------------ Setup --------------------------------------
void setup() {
  Serial.begin(9600); // Setup console 
  Serial.println("Setup");
 // SigFox.begin();
  scale.begin(HX711_DATA_PIN, HX711_SCK_PIN); // Setup capteur de poids
  scale.set_scale();
  scale.tare();
  long zero_factor = scale.read_average();
  SigFox.debug();
  
  delay(1);
  dht.begin(); // Setup capteur temp ext
}


//------------------------------------Envoi--------------------------------------
void send_message_sigfox(){
  SigFox.begin();
  SigFox.beginPacket();
  SigFox.status();
  SigFox.write((uint8_t*)&msg, sizeof(SigfoxMessage));
  Serial.print("Status: ");
  Serial.println(SigFox.endPacket());
  SigFox.end();
  cpt = cpt + 1;
}


//-------------------------------------------Poids-----------------------------------------------
void get_weight(){
  
  int16_t poids;
  scale.set_scale(HX711_calibration_factor); // Adjust to this calibration factor
  poids = scale.get_units(10);
  msg.Poids = poids*100;
  
  Serial.println("\n********   Poids   ********\n");
  Serial.print(poids);
  Serial.println("kg");
  Serial.println("---------------------------------------------------------------");

  // Useful for calibration phase
  if(Serial.available())
  {
    char temp = Serial.read();
    if(temp == '+' || temp == 'a')
      HX711_calibration_factor += 10;
    else if(temp == '-' || temp == 'z')
      HX711_calibration_factor -= 10;
  }
}


//------------------------------------Température Interieure--------------------------------------
float get_interior_temperature(const byte addr[]){
  byte i;
  byte present = 0;
  byte type_s;
  byte data[12];
  float celsius;
 
  ds.reset();
  ds.select(addr);
  ds.write(0x44, 1); // start conversion, with parasite power on at the end
  
  delay(1000); // maybe 750ms is enough, maybe not
  
  present = ds.reset();
  ds.select(addr);    
  ds.write(0xBE); // Read Scratchpad

  for ( i = 0; i < 9; i++) {
    data[i] = ds.read();
  }

  int16_t raw = (data[1] << 8) | data[0];
  if (type_s) {
    raw = raw << 3; // 9 bit resolution default
    if (data[7] == 0x10) {
      raw = (raw & 0xFFF0) + 12 - data[6];
    }
  } else {
    byte cfg = (data[4] & 0x60);
    // at lower res, the low bits are undefined, so let's zero them
    if (cfg == 0x00) raw = raw & ~7;  // 9 bit resolution, 93.75 ms
    else if (cfg == 0x20) raw = raw & ~3; // 10 bit res, 187.5 ms
    else if (cfg == 0x40) raw = raw & ~1; // 11 bit res, 375 ms
    //// default is 12 bit resolution, 750 ms conversion time
  }
  celsius = (float)raw / 16.0;
  Serial.print("  Temperature = ");
  Serial.print(celsius);
  Serial.print(" Celsius, ");
  return celsius;
  
}
//------------------------------------Temprerature Exterieure--------------------------------------
void get_exterior_temperature(){
  // Wait a few seconds between measurements.
  delay(2000);

  float h = dht.readHumidity();
  float t = dht.readTemperature();

  msg.TempExt = t;
  msg.HumiExt = h;

  // Check if any reads failed and exit early (to try again).
  Serial.println("\n********   Température Extérieure   ********\n");
  if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
}

void loop() {
  
  Serial.println("---------------------------------------------------------------");
  
  Serial.println("********   Température Intérieure   ********");
  Serial.println("\n******   Temp_i 1 :\n");
  msg.TempInt_1 = get_interior_temperature(TempInt_Add_1); 
  Serial.println("\n******   Temp_i 2 :\n");
  msg.TempInt_2 = get_interior_temperature(TempInt_Add_2);
  Serial.println("\n******   Temp_i 3 :\n");
  msg.TempInt_3 = get_interior_temperature(TempInt_Add_3);

  get_exterior_temperature(); 
  get_weight();

  send_message_sigfox();
  delay(6000);
  
  if(cpt == 2){
  Serial.println("************************** ici ****************************************");
  while(1);
  }
  
  
}
