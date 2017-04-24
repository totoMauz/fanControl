#define PIN_OUT_TRANSISTOR 11
#define PIN_IN_TEMP         1
#define DEBUG            false

#define INTERVAL         2000
#define HYSTERESE           3.0

//3.3 V, 5 V, 12 V
const byte VOLTAGE[] = {0, 127, 191, 255};
//°C
const float THRESHOLD[] = {25.0, 30.0, 35.0};
byte currentState = 0;

void setup()
{
  //analog reference is 1.1V for TMP35
  analogReference(INTERNAL);

  if (DEBUG) {
    Serial.begin(9600);
  }

  pinMode(PIN_OUT_TRANSISTOR, OUTPUT);
  //Shut transistor
  analogWrite(PIN_OUT_TRANSISTOR, 0);
}

void loop()
{
  setFan();
  delay(INTERVAL);
}

void setFan() {
  float currTemp = readTmp();
  byte newSpeed = getNewSpeed(currTemp);

  if (DEBUG) {
    Serial.println(currTemp);
    Serial.println(newSpeed);
  }

  analogWrite(PIN_OUT_TRANSISTOR, newSpeed);
}

byte getNewSpeed(float currTemp) {
  byte newState;
  for (newState = 0; newState < 2; newState++) {
    if (currTemp < THRESHOLD[newState]) {
      break;
    }
  }

  if (newState > currentState) {
    //temperature increased, speedup fan
    currentState = newState;
  } else if (newState < currentState) {
    //temperature decreased, apply hystersis
    if (THRESHOLD[newState] + HYSTERESE < currTemp) {
      currentState = newState;
    }
  }

  return VOLTAGE[currentState];
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
