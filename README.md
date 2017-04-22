# fanControl
Arduino code to use a thermal sensor and transistor to adjust voltage to a brushless DC fan. I used an LM35 temperature sensor and therefor set the reference voltage to 1.1 V to increase resolution (http://playground.arduino.cc/Main/LM35HigherResolution). If you are using another sensor or more components considers this.

Connect your Arduino like shown in the fritzing diagramm and flash with the source code.

Use the constants to change used PINs, console output, update interval or temperature thresholds.