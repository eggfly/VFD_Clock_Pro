

void setup() {
  Serial.begin(115200);
  pinMode(13, OUTPUT);
}

void loop() {
  Serial.println("HIGH");
  digitalWrite(13, HIGH);
  delay(5000);

  Serial.println("LOW");
  digitalWrite(13, LOW);
  delay(5000);
}
