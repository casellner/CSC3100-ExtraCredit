/*

*/

int variable = 777;

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.println(variable);
  delay(100);
}
