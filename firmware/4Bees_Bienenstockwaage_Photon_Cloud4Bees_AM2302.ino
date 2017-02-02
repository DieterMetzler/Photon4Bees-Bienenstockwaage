#include "idDHT22.h"
#include "SparkFunMAX17043.h"
#include "HX711.h"
#include "cloud4bees.h"



// declaration for DHT11 handler
int idDHT22pin = D3; //Digital pin for comunications
void dht22_wrapper(); // must be declared before the lib initialization

// DHT instantiate
idDHT22 DHT22(idDHT22pin, dht22_wrapper);



//Cloud4BeesLibrary::Cloud4Bees cloud4bees ("EF836YPX6SBK0ZZL");
Cloud4BeesLibrary::Cloud4Bees cloud4bees ("EF836YPX6SBK0ZZL");

#define DOUT  A0
#define CLK  A1

HX711 scale(DOUT, CLK);   // parameter "gain" is ommited; the default value 128 is used by the library


//float offset = 0;
//float scalefactor = 1;

float offset = 276.9;
float scalefactor = 31679.0;

double weight = 0;

double voltage = 0; // Variable to keep track of LiPo voltage
double soc = 0; // Variable to keep track of LiPo state-of-charge (SOC)
bool alert; // Variable to keep track of whether alert has been triggered

double temperature = 0;
double humidity = 0;
double dewpoint = 0;

  // This wrapper is in charge of calling
  // mus be defined like this for the lib work
  void dht22_wrapper() {
	DHT22.isrCallback();
  }


void setup()
{
  Serial.begin(9600);
  scale.set_scale(scalefactor);                      //this value is obtained by calibrating the scale with known weights;
                                                 /*   How to Calibrate Your Scale
                                                      1.Call set_scale() with no parameter.
                                                      2.Call set_tare() with no parameter.
                                                      3.Place a known weight on the scale and call get_units(10).
                                                      4.Divide the result in step 3 to your known weight. You should get about the parameter you need to pass to set_scale.
                                                      5.Adjust the parameter in step 4 until you get an accurate reading.
                                                */
  // Set up the MAX17043 LiPo fuel gauge:
  lipo.begin(); // Initialize the MAX17043 LiPo fuel gauge

  // Quick start restarts the MAX17043 in hopes of getting a more accurate
  // guess for the SOC.
  lipo.quickStart();

  // We can set an interrupt to alert when the battery SoC gets too low.
  // We can alert at anywhere between 1% - 32%:
  lipo.setThreshold(20); // Set alert threshold to 20%.

}


void loop()
{
    Particle.process();
    //scale.get_units(10) returns the medium of 10 measures
    weight = (scale.get_units(10) - offset);

    //lipo.getVoltage() returns a voltage value (e.g. 3.93)
	  voltage = lipo.getVoltage();
	  //lipo.getSOC() returns the estimated state of charge (e.g. 79%)
	  soc = lipo.getSOC();
	  //lipo.getAlert() returns a 0 or 1 (0=alert not triggered)
	  alert = lipo.getAlert();

	  // Temperature, Humidity and Dewpoint from the DHT22 Sensor
    DHT22.acquire();
	  while (DHT22.acquiring());
	  temperature = DHT22.getCelsius();
	  humidity = DHT22.getHumidity();
	  dewpoint = DHT22.getDewPoint();

    //Send Value to cloud4Bees
    cloud4bees.recordValue(1, String(weight));
    cloud4bees.recordValue(2, String(soc));
   	cloud4bees.recordValue(3, String(temperature));
	  cloud4bees.recordValue(4, String(humidity));
	  cloud4bees.recordValue(5, String(dewpoint));

	cloud4bees.sendValues();
    //delay(3600000);
    delay(1000);
    System.sleep(SLEEP_MODE_DEEP, 3600);


}
