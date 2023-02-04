#define BTN1 7

#define SW_LEFT 15
#define SW_RIGHT 16
#define SW_PRESS 0
#define EC_S 40
#define EC_B 39
#define EC_A 38

bool press_state = false;
bool left_state = false;
bool right_state = false;

void buttons_isr() {
  press_state = digitalRead(SW_PRESS);
  left_state = digitalRead(SW_LEFT);
  right_state = digitalRead(SW_RIGHT);
}

void setupButtons() {
  pinMode(BTN1,      INPUT);
  pinMode(SW_LEFT,   INPUT);
  pinMode(SW_RIGHT,  INPUT);
  pinMode(SW_PRESS,  INPUT);
  pinMode(EC_S,      INPUT);
  pinMode(EC_B,      INPUT);
  pinMode(EC_A,      INPUT);
  attachInterrupt(digitalPinToInterrupt(BTN1), buttons_isr, CHANGE);
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
  Serial.print(press_state);
  Serial.print(left_state);
  Serial.println(right_state);
  delay(100);
  // put your main code here, to run repeatedly:
}
