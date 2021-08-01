#define BUILT_IN_LED 13
#define PHOTO_SENSOR A0

const int trigPin = 9;
const int echoPin = 10;

long duration;
int distance;


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
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  setupTimer1();
}

void loop() {
  ultra_sonic_calc(); //can be simply be used in the normal loop, because its just used for trigger and echo. 
                      // generally for time calculations. 
}

void ultra_sonic_calc() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance= duration*0.034/2;
}

ISR(TIMER1_COMPA_vect) {
  Serial.print("PhotoSensor: ");
  Serial.println(analogRead(PHOTO_SENSOR));
  int SensorReading = analogRead(PHOTO_SENSOR);

  Serial.print("Distance: ");
  Serial.println(distance);

  if(distance <= 10) {
    Serial.println("DISTANCE LOW");
    digitalWrite(BUILT_IN_LED, HIGH);
  } else {
    Serial.println("DISTANCE HIGH");
    digitalWrite(BUILT_IN_LED, LOW);
  }
  
  if(SensorReading >= 1000) {
    Serial.println("HIGH");
    digitalWrite(BUILT_IN_LED, HIGH);
  } else {
    Serial.println("LOW");
    digitalWrite(BUILT_IN_LED, LOW);
  }
}
