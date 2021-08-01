#define BUILT_IN_LED 13
#define PHOTO_SENSOR A0

void setupTimer1() {
  noInterrupts();
  // Clear registers
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;

  // 1 Hz (16000000/((15624+1)*1024))
  OCR1A = 15624;
  // CTC
  TCCR1B |= (1 << WGM12);
  // Prescaler 1024
  TCCR1B |= (1 << CS12) | (1 << CS10);
  // Output Compare Match A Interrupt Enable
  TIMSK1 |= (1 << OCIE1A);
  interrupts();
}

void setup() {
  Serial.begin(9600);
  pinMode(BUILT_IN_LED, OUTPUT);
  setupTimer1();
}

void loop() {
}

ISR(TIMER1_COMPA_vect) {
  Serial.println(analogRead(PHOTO_SENSOR));
  int SensorReading = analogRead(PHOTO_SENSOR);
  if(SensorReading >= 1000) {
    Serial.println("HIGH");
    digitalWrite(BUILT_IN_LED, HIGH);
  } else {
    Serial.println("LOW");
    digitalWrite(BUILT_IN_LED, LOW);
  }
}
