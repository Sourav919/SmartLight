// Pin definitions
const int LDR_PIN = A0;
const int TRIGGER_PIN = 7;
const int ECHO_PIN = 6;
const int LED_PIN = 13;
const int BUZZER_PIN = 8;

// Variables
long duration;
int distance;
int brightness;
bool is_led_on = false;

void setup() {
  Serial.begin(9600);
  pinMode(LDR_PIN, INPUT);
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
  // Read LDR sensor value
  int ldr_value = analogRead(LDR_PIN);
  Serial.println(ldr_value);
  
  // Check if LDR value is low and ultrasonic value is less than 50
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);
  duration = pulseIn(ECHO_PIN, HIGH);
  distance = duration * 0.034 / 2;
  Serial.print(distance);
  Serial.println(" cm");
  
  if (ldr_value > 600 && distance < 50 && !is_led_on) {
    digitalWrite(LED_PIN, HIGH);
    
    digitalWrite(BUZZER_PIN, HIGH);
    delay(200);
    digitalWrite(BUZZER_PIN, LOW);
    is_led_on = true;
  } else if ((ldr_value <= 600 || distance >= 50) && is_led_on) {
    digitalWrite(LED_PIN, LOW);
    digitalWrite(BUZZER_PIN, HIGH);
    delay(200);
    digitalWrite(BUZZER_PIN, LOW);
    is_led_on = false;
  }

  delay(100);
}
