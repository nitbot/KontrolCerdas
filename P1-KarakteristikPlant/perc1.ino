const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
const int analogOutPin = 9; // Analog output pin that the LED is attached to

int bacaADC = 0;        // value read from the pot
float PWM = 0;
float Kecepatan;
int outputValue = 0;        // value output to the PWM (analog out)
int SettingPoint = 0;
float W=0.0f,B=0.0f;
float OutK = 0;

void setup() {
  Serial.begin(19200);
}

void loop() {
  if (Serial.available() >= 3) 
  {
    int s;
    // read the incoming byte:
    if (Serial.read()=='s'){
        String str = Serial.readString();
        SettingPoint = str.toInt();
    }
  }
  bacaADC = analogRead(analogInPin);
  Kecepatan = (float)bacaADC*2000.0f/1023.0f;
  //Lakukan proses kompensasi
  W=1.0f;
  B=0.0f;
  OutK=(float)SettingPoint*W+B;
  PWM = OutK*255/2000;
  if(PWM>255) PWM = 255;
  if(PWM<0) PWM = 0;
  PWM = ((float)SettingPoint*255.0f/2000.0f);
  outputValue = (int)PWM;
  analogWrite(analogOutPin, outputValue);
  Serial.print(",R");
  Serial.print((unsigned int)SettingPoint);
  Serial.print(",S");
  Serial.print((unsigned int)Kecepatan);
  Serial.print(",P");
  Serial.print((unsigned int)PWM);
  Serial.print(",W");
  Serial.print((float)W);
  Serial.print(",B");
  Serial.print((float)B);
  Serial.print("\r");
  delay(10);
}
