#include "DHT.h"
#include <SigFox.h>
#include <OneWire.h>
#include "ArduinoLowPower.h"
#include "HX711.h"

//Define pour le temps d'envoie des messages 
#define mSecondes 720000
#define ndrMessages 140

// Define utiles pour le capteur de température extérieure
#define DHT_PINInt 7 
#define DHT_PINExt 6   
#define DHT_TYPE DHT22 

// Variables utiles pour le capteur de poids
#define HX711_DATA_PIN  3
#define HX711_SCK_PIN  2
float HX711_calibration_factor = 21666; //-7050 worked for my 440lb max scale setup
HX711 scale;

// Variables utiles pour l'envoi de Sig
typedef struct __attribute__ ((packed)) sigfox_message {
 int8_t TempInt_1;
 int8_t TempInt_2;
 int8_t TempInt_3;
 int8_t TempExt;
 int8_t HumiExt;
 int16_t Poids;
 int8_t ADC_Batterie;
 int8_t ADC_PhotoDiode;
 
} SigfoxMessage;

SigfoxMessage msg;

// Variables utiles pour le capteur de température extérieure
DHT dhtInt(DHT_PINInt, DHT_TYPE);
DHT dhtExt(DHT_PINExt, DHT_TYPE);
// Variables utiles pour le capteur de température intérieure Poids::float:64:little-endian
//const byte TempInt_Add_1[]  = {0x28,  0x90,  0x12,  0x56,  0xB5,  0x1,  0x3C,  0xD1};
//const byte TempInt_Add_2[]  = {0x28,  0xB0,  0xDE,  0x34,  0xC,  0x0,  0x0,  0x18};
//const byte TempInt_Add_3[]  = {0x28,  0xBD,  0x96,  0x56,  0xB5,  0x1,  0x3C,  0xF9};
const byte TempInt_Add_1[]  = {0x28,  0xB8,  0xCB,  0x6,  0x1C,  0x19,  0x1,  0x12};
const byte TempInt_Add_2[]  = {0x28,  0xFE,  0x90,  0x14,  0x1C,  0x19,  0x1,  0xF};
const byte TempInt_Add_3[]  = {0x28,  0xFF,  0x9F,  0xF5,  0x24,  0x17,  0x3,  0xA};
OneWire  ds(5);  // on pin 10 (a 4.7K resistor is necessary)

//Vraiables utiles pour l'ADC 
const int analogInPinPV = A3;  // Analog input pin that the potentiometer is attached to 
const int analogInPinBatterie = A2;

//Variables utiles pour la photo Diode
const int photoDiode = A1;

//Vriable utile pour la Led
const int Led = 1;

int sensorValue = 0;        // value read from the pot
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
  dhtInt.begin(); // Setup capteur temp interieur dht
  dhtExt.begin(); // Setup capteur temp exterieur dht
  pinMode(photoDiode, INPUT); // Photo Diode
  pinMode(Led, OUTPUT);
  clignioter_Led();
}

//------------------------------------Clignioter La Led--------------------------------------
void clignioter_Led(){
  digitalWrite(Led,HIGH);
  delay(2000);
  digitalWrite(Led,LOW);
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
  scale.power_up();
  float poids;
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
  scale.power_down();
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

  float h = dhtInt.readHumidity();
  float t = dhtInt.readTemperature();

  msg.TempExt = t*2;
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

//------------------------------------ ADC PV --------------------------------------
void get_ADC_PV(){
  Serial.println("********   ADC PV   ********");
  // read the analog in value:
  sensorValue = analogRead(analogInPinPV);
  //int8_t value = map(sensorValue, 63, 975, 0, 100);
  float val_volt = sensorValue*3.3/1023;

  // print the results to the Serial Monitor:
  Serial.print("sensor = ");
  Serial.println(val_volt);
 // msg.ADC_PV = val_volt*100;
}

//------------------------------------ADC Batterie--------------------------------------
void get_ADC_Batterie(){
   Serial.println("********   ADC Batterie   ********");
  // read the analog in value:
  sensorValue = analogRead(analogInPinBatterie);
  int8_t value = map(sensorValue, 781, 983, 0, 100);
  float val_volt = sensorValue*4.2/1023;

  // print the results to the Serial Monitor:
  Serial.print("sensor = ");
  Serial.println(value);
  Serial.println(val_volt);
  msg.ADC_Batterie = value;
}
//------------------------------------ADC Photo Diode--------------------------------------
void get_Photo_Diode(){
  //int tmp = 
  msg.ADC_PhotoDiode = analogRead(photoDiode);
  Serial.println("********   Photo Diode   ********");
  Serial.println("Photo Diode  : " + analogRead(photoDiode));
}
void loop() {
  
  Serial.println("---------------------------------------------------------------");
  
  Serial.println("********   Température Intérieure   ********");
  Serial.println("\n******   Temp_i 1 :\n");
  msg.TempInt_1 = get_interior_temperature(TempInt_Add_1)*2; 
  Serial.println("\n******   Temp_i 2 :\n");
  msg.TempInt_2 = get_interior_temperature(TempInt_Add_2)*2;
  Serial.println("\n******   Temp_i 3 :\n");
  msg.TempInt_3 = get_interior_temperature(TempInt_Add_3)*2;

  get_exterior_temperature(); 
  
  get_weight();
  
  //get_ADC_PV();
  get_ADC_Batterie();
  
  //get Photo Diode
  get_Photo_Diode();
  
  send_message_sigfox();
  LowPower.sleep(10000);
  Serial.println("************************** Fin de delay ****************************************");
  if(cpt == 6){
    Serial.println("************************** Fin d'envoi ****************************************");
    while(1);
  }
  
  
}
