#include "DHT.h"
#include <SigFox.h>
#include <OneWire.h>
#include "HX711.h"

#define LOADCELL_DOUT_PIN  3
#define LOADCELL_SCK_PIN  2
const byte tmp_i_add_1[]  = {0x28,  0x90,  0x12,  0x56,  0xB5,  0x1,  0x3C,  0xD1};
const byte tmp_i_add_2[]  = {0x28,  0xB0,  0xDE,  0x34,  0xC,  0x0,  0x0,  0x18};
const byte tmp_i_add_3[]  = {0x28,  0xBD,  0x96,  0x56,  0xB5,  0x1,  0x3C,  0xF9};

#define DHTPIN 4     
#define DHTTYPE DHT22 


float calibration_factor = 21666; //-7050 worked for my 440lb max scale setup
HX711 scale;
DHT dht(DHTPIN, DHTTYPE);
OneWire  ds(5);  // on pin 10 (a 4.7K resistor is necessary)

typedef struct __attribute__ ((packed)) sigfox_message {
 int16_t temp_i_1;
 int16_t temp_i_2;
 int16_t temp_i_3;
 int16_t temp_o_1;
 int16_t humi_o;
} SigfoxMessage;

SigfoxMessage msg;
//------------------------------------Setup--------------------------------------
void setup() {
  Serial.begin(9600);
  Serial.println(F("DHTxx test!"));
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale();
  scale.tare(); //Reset the scale to 0
  long zero_factor = scale.read_average(); //Get a baseline reading
  dht.begin();
}
//------------------------------------Envoi--------------------------------------
void envoi(){
  SigFox.begin();
  SigFox.beginPacket();
  SigFox.write((uint8_t*)&msg, sizeof(SigfoxMessage));
  Serial.print("Status: ");
  Serial.println(SigFox.endPacket());
  SigFox.end();
}
//-------------------------------------------Poids-----------------------------------------------
void poids(){
  scale.set_scale(calibration_factor); //Adjust to this calibration factor
  Serial.println("\n********   Poids   ********\n");
  Serial.print("Reading: ");
  Serial.print(scale.get_units(), 1);
  Serial.print(" kg"); //Change this to kg and re-adjust the calibration factor if you follow SI units like a sane person
  Serial.print(" calibration_factor: ");
  Serial.print(calibration_factor);
  Serial.println();
  Serial.println("---------------------------------------------------------------");

  if(Serial.available())
  {
    char temp = Serial.read();
    if(temp == '+' || temp == 'a')
      calibration_factor += 10;
    else if(temp == '-' || temp == 'z')
      calibration_factor -= 10;
  }
}
//------------------------------------Température Interieur--------------------------------------
float temp_i(const byte addr[]){
  byte i;
  byte present = 0;
  byte type_s;
  byte data[12];
  float celsius;
  
  
 
  ds.reset();
  ds.select(addr);
  ds.write(0x44, 1);        // start conversion, with parasite power on at the end
  
  delay(1000);     // maybe 750ms is enough, maybe not
  // we might do a ds.depower() here, but the reset will take care of it.
  
  present = ds.reset();
  ds.select(addr);    
  ds.write(0xBE);         // Read Scratchpad

  for ( i = 0; i < 9; i++) {           // we need 9 bytes
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
//------------------------------------Tempreratur Exterieur--------------------------------------
void temp_hum_o(){
  // Wait a few seconds between measurements.
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  Serial.println("\n********   Températur Extérieur   ********\n");
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
 /* Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));*/
  msg.temp_o_1 = t;
  msg.humi_o = h;
}

void loop() {
  int cpt = 0;
  Serial.println("---------------------------------------------------------------");
  Serial.println("********   Température Intérieure   ********");
  Serial.println("\n******   Temp_i 1 :\n");
  msg.temp_i_1 = temp_i(tmp_i_add_1); 
  Serial.println("\n******   Temp_i 2 :\n");
  msg.temp_i_2 = temp_i(tmp_i_add_2);
  Serial.println("\n******   Temp_i 3 :\n");
  msg.temp_i_3 = temp_i(tmp_i_add_3);

  temp_hum_o(); 
  poids();
  //envoi();
  cpt += cpt;
  if(cpt == 2){
    while(1);
    
  }
  delay(6000);
  
}
