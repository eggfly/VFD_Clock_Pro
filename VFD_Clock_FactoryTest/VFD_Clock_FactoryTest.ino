#define BTN1 7
#define BTN2 0
#define SW_LEFT 15
#define SW_RIGHT 16
#define SW_PRESS 17
#define EC_S 40
#define EC_B 39
#define EC_A 38

void buttons_isr() {
  Serial.println("c!");
}

void setupButtons() {
  pinMode(BTN1,      INPUT);
  pinMode(BTN2,      INPUT);
  pinMode(SW_LEFT,   INPUT);
  pinMode(SW_RIGHT,  INPUT);
  pinMode(SW_PRESS,  INPUT);
  pinMode(EC_S,      INPUT);
  pinMode(EC_B,      INPUT);
  pinMode(EC_A,      INPUT);
  attachInterrupt(digitalPinToInterrupt(BTN1), buttons_isr, CHANGE);
  attachInterrupt(digitalPinToInterrupt(BTN2), buttons_isr, CHANGE);
  attachInterrupt(digitalPinToInterrupt(SW_LEFT), buttons_isr, CHANGE);
  attachInterrupt(digitalPinToInterrupt(SW_RIGHT), buttons_isr, CHANGE);
  attachInterrupt(digitalPinToInterrupt(SW_PRESS), buttons_isr, CHANGE);
  attachInterrupt(digitalPinToInterrupt(EC_S), buttons_isr, CHANGE);
  attachInterrupt(digitalPinToInterrupt(EC_B), buttons_isr, CHANGE);
  attachInterrupt(digitalPinToInterrupt(EC_A), buttons_isr, CHANGE);
}

void setup() {
  Serial.begin(115200);
  setupButtons();
}

void loop() {
  // put your main code here, to run repeatedly:
}
