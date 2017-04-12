#define PIN_OUT_TRANSISTOR 11
#define PIN_IN_TEMP         1

#define THRESHOLD_LOW      25.0
#define THRESHOLD_MID      30.0
#define THRESHOLD_HIGH     35.0

#define FAN_OFF            0  // 0 V
#define FAN_LOW            70 //~3.3 V
#define FAN_MID           106 //~5 V
#define FAN_HIGH          255 //12 V

#define DEBUG             true

void setup()
{
  //analog reference is 1.1V for TMP35
  analogReference(INTERNAL);

  if (DEBUG) {
    Serial.begin(9600);
  }

  //Shut transistor
  pinMode(PIN_OUT_TRANSISTOR, OUTPUT);
  analogWrite(PIN_OUT_TRANSISTOR, FAN_OFF);
}

void loop()
{
  setFan();
  delay(1500);
}

void setFan() {
  float currTemp = readTmp();

  byte newSpeed = FAN_OFF;

  if (currTemp < THRESHOLD_LOW) {
    newSpeed = FAN_OFF;
  } else  if (currTemp < THRESHOLD_MID) {
    newSpeed = FAN_LOW;
  } else  if (currTemp < THRESHOLD_HIGH) {
    newSpeed = FAN_MID;
  } else {
    newSpeed = FAN_HIGH;
  }

  if (DEBUG) {
    Serial.println(currTemp);
    Serial.println(newSpeed);
  }
  analogWrite(PIN_OUT_TRANSISTOR, newSpeed);
}

float readTmp() {
  //temp = (aRef * analogRead() * 100.0) / 1024; (analogRead() * 1.1 * 100) / 1024; analogRead() * 1.0742;
  //10 mv / 1.0724 = 1 °C = 9.31
  float temp = analogRead(PIN_IN_TEMP) ;
  delay(50);
  temp += analogRead(PIN_IN_TEMP);
  delay(50);
  temp += analogRead(PIN_IN_TEMP) ;
  delay(50);
  temp += analogRead(PIN_IN_TEMP) ;
  delay(50);
  temp += analogRead(PIN_IN_TEMP) ;
  //average of 5 reads
  return temp / 46.546;
}
