#include <Arduino.h>
#include <postboxes.h>
#include <Adafruit_GPS.h>
#include <SoftwareSerial.h>

#define rxPin 7
#define txPin 6
#define beeperPin 2

SoftwareSerial mySerial(6, 7);
Adafruit_GPS GPS(&mySerial);

double distance(double lat1, double lon1, double lat2, double lon2){
    double R = 6378.137; // Radius of earth in KM
    double dLat = lat2 * PI / 180 - lat1 * PI / 180;
    double dLon = lon2 * PI / 180 - lon1 * PI / 180;
    double a = sin(dLat/2) * sin(dLat/2) + cos(lat1 * PI / 180) * cos(lat2 * PI / 180) * sin(dLon/2) * sin(dLon/2);
    double c = 2 * atan2(sqrt(a), sqrt(1-a));
    double d = R * c;
    return d * 1000; // meters
}

void setup()
{
	Serial.begin(74880);

	GPS.begin(9600);
	GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
	GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);

	pinMode(beeperPin, OUTPUT);
	
}

uint16_t getBeepGap(double myLat, double myLon)
{
	double minDist = 9999999;
	double dist;

	double nearestLat = 0;
	double nearestLon = 0;

	for(uint16_t i = 0; i < postboxCount; i++)
	{
		dist = pow(abs(postboxes[i][0] - myLat), 2) + pow(abs(postboxes[i][1] - myLon), 2);
		if(dist < minDist)
		{
			minDist = dist;
			nearestLat = postboxes[i][0];
			nearestLon = postboxes[i][1];
		}
	}

	Serial.println(nearestLat, 6);
	Serial.println(nearestLon, 6);
	minDist = distance(myLat, myLon, nearestLat, nearestLon);
	Serial.println(minDist);

	if(minDist > 500)
		return 1000;
	if(minDist > 400)
		return 800;
	if(minDist > 300)
		return 600;
	if(minDist > 200)
		return 400;
	if(minDist > 100)
		return 200;
	if(minDist > 50)
		return 100;
	return 0;
}

uint32_t timer = millis();
uint32_t beepTimer = millis();
uint16_t beepGap = 3000;

void loop()
{
	if(millis() - beepTimer > beepGap)
	{
		beepTimer = millis();
		Serial.println("Beep");

		pinMode(beeperPin, HIGH);
		delay(100);
		pinMode(beeperPin, LOW);
	}

	if (GPS.newNMEAreceived()) {
		if (!GPS.parse(GPS.lastNMEA()))
			return;
	}

	if (millis() - timer > 1000) {
		timer = millis();

		if (GPS.fix) {
			Serial.print("Location: ");
			Serial.print(GPS.latitudeDegrees, 6);
			Serial.print(", ");
			Serial.print(GPS.longitudeDegrees, 6);
			Serial.print("Satellites: ");
			Serial.println((int)GPS.satellites);

			beepGap = getBeepGap(GPS.latitudeDegrees, GPS.longitudeDegrees);
		} 
		else
		{
			beepGap = 3000;
		}
	}
}

