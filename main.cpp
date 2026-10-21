// C++ code
//

void setup()
{
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, INPUT);
  pinMode(11, INPUT);
  pinMode(12, INPUT);
  pinMode(13, INPUT);
  
  allRed();
}
void allRed() {
  digitalWrite(2, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(7, HIGH);
  digitalWrite(8, HIGH);
}
// LEFT
void detectLeft() {
  unsigned long start = millis();
  bool wasGreen = false;

  while (digitalRead(12) == HIGH) {
    digitalWrite(8, LOW);
    digitalWrite(9, HIGH);
    start = millis();
    wasGreen = true;
  }
  if (wasGreen) {
    while (millis() - start < 5000) { }
    digitalWrite(8, HIGH);
    digitalWrite(9, LOW);
  }
}
// RIGHT
void detectRight() {
  unsigned long start = millis();
  bool wasGreen = false;

  while (digitalRead(11) == HIGH) {
    digitalWrite(4, LOW);
    digitalWrite(5, HIGH);
    start = millis();
    wasGreen = true;
  }
  if (wasGreen) {
    while (millis() - start < 5000) { }
    digitalWrite(4, HIGH);
    digitalWrite(5, LOW);
  }
}
// TOP
void detectTop() {
  unsigned long start = millis();
  bool wasGreen = false;

  while (digitalRead(13) == HIGH) {
    digitalWrite(2, LOW);
    digitalWrite(3, HIGH);
    start = millis();
    wasGreen = true;
  }
  if (wasGreen) {
    while (millis() - start < 5000) { }
    digitalWrite(2, HIGH);
    digitalWrite(3, LOW);
  }
}
// BOTTOM
void detectBottom() {
  unsigned long start = millis();
  bool wasGreen = false;

  while (digitalRead(10) == HIGH) {
    digitalWrite(7, LOW);
    digitalWrite(6, HIGH);
    start = millis();
    wasGreen = true;
  }
  if (wasGreen) {
    while (millis() - start < 5000) { }
    digitalWrite(7, HIGH);
    digitalWrite(6, LOW);
  }
}

void loop()
{
  detectLeft();
  detectRight();
  detectTop();
  detectBottom();
}