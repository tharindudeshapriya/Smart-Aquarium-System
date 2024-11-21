#include <LiquidCrystal.h>
#include <Servo.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
#define phSensorPin 0
#define turbiditySensorPin 1
#define waterlevelSensorPin 2

#define temepratureSensor 3


Servo feeding;

float tempc;

float vout;
float Celsius = 0;
float Fahrenheit = 0;
float volt;
float ntu;
float calibration_value = 21.34;
int pos = 0;  // variable to store the servo position
unsigned long int turbidityValue;
unsigned long int avgval, resval;
int buffer_arr[10], temp;
void setup() {

  Serial.begin(9600);
  lcd.begin(16, 2);
  feeding.attach(9);

}

void loop() {

  float ph = convertToPh();
  float turbidity = convertToTurbidity();
  float waterlevel = convertToWaterlevel();
  // float temperature = convertToTemperature();
  float temperatur = convertToTemperatur();
  float autofeeding = autoFeeding();

  delay(10);
}



float convertToPh() {


  for (int i = 0; i < 10; i++) {
    buffer_arr[i] = analogRead(phSensorPin);
    delay(10);
  }
  for (int i = 0; i < 9; i++) {
    for (int j = i + 1; j < 10; j++) {
      if (buffer_arr[i] > buffer_arr[j]) {
        temp = buffer_arr[i];
        buffer_arr[i] = buffer_arr[j];
        buffer_arr[j] = temp;
      }
    }
  }
  avgval = 0;
  for (int i = 2; i < 8; i++)
    avgval += buffer_arr[i];
  float volt = (float)avgval * 5.0 / 1024 / 6;
  float ph_act = 3.5 * volt;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(" pH Value : ");
  lcd.setCursor(5, 1);
  lcd.print(ph_act);
  delay(200);
}
float convertToTurbidity() {
  turbidityValue = analogRead(turbiditySensorPin);                                                                                                                 // read the analog value from the turbidity sensor
  turbidityValue = (5.0 / 1023.0) * turbidityValue;                                                                                                                // convert the analog value to voltage
  turbidityValue = (133.42 * turbidityValue * turbidityValue * turbidityValue) - (255.86 * turbidityValue * turbidityValue) + (857.39 * turbidityValue) - 827.67;  // calculate turbidity using the sensor's calibration curve
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("  Turbidity : ");
  lcd.setCursor(3, 1);
  lcd.print(turbidityValue);
  lcd.setCursor(8, 1);
  lcd.print(" NTU");
  delay(200);
}

float convertToWaterlevel() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("  Water Level : ");

  lcd.setCursor(0, 1);

  resval = analogRead(waterlevelSensorPin);  //Read data from analog pin and store it to resval variable

  if (resval <= 100) {
    lcd.println("     Empty    ");
  } else if (resval > 100 && resval <= 400) {
    lcd.println("       Low      ");
  } else if (resval > 400 && resval <= 750) {
    lcd.println("     Medium     ");
  } else if (resval > 750) {
    lcd.println("      High      ");
  }
  delay(200);
}

// float convertToTemperature() {
//   sensors.requestTemperatures();
//   Celsius = sensors.getTempCByIndex(0);
//     if (Celsius > -127 && Celsius < 85) {
//       lcd.clear();
//       lcd.setCursor(0, 0);
//       lcd.print("  Temperature : ");
//       lcd.setCursor(4, 1);
//       lcd.print(Celsius);
//       lcd.print("C");
//       delay(200);
//     }
//     else{
//       lcd.clear();
//       lcd.setCursor(0, 0);
//       lcd.print("  Temperature : ");
//       delay(200);
//     }

// }

float convertToTemperatur() {
  vout = analogRead(temepratureSensor);
  vout = (vout * 500) / 1023;
  tempc = vout;

  lcd.setCursor(0, 0);
  lcd.print("  Temperature : ");
  lcd.setCursor(4, 1);
  lcd.print(tempc);
  lcd.print("C");



  delay(200);
}


float autoFeeding() {
  lcd.clear();
  lcd.setCursor(4, 0);
  lcd.print("Feeding");
  lcd.setCursor(5, 1);
  lcd.print("Start");
  for (pos = 90; pos <= 180; pos += 1) {  // goes from 0 degrees to 180 degrees

    // in steps of 1 degree

    feeding.write(pos);  // tell servo to go to position in variable 'pos'

    delay(1);  // waits 15ms for the servo to reach the position
  }

  for (pos = 180; pos >= 90; pos -= 1) {  // goes from 180 degrees to 0 degrees

    feeding.write(pos);  // tell servo to go to position in variable 'pos'

    delay(1);  // waits 15ms for the servo to reach the position
  }
}
