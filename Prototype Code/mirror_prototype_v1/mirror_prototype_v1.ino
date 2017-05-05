#define night 2
#define evening 3
#define morning 4
#define afternoon 5

void setup() {
  // put your setup code here, to run once:
  pinMode(morning, OUTPUT);
  pinMode(afternoon, OUTPUT);
  pinMode(evening, OUTPUT);
  pinMode(night, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(night, LOW);
  digitalWrite(morning, HIGH);
  delay(1000); 
  digitalWrite(morning, LOW);
  digitalWrite(afternoon, HIGH); 
  delay(1000); 
  digitalWrite(afternoon, LOW); 
  digitalWrite(evening, HIGH); 
  delay(1000);
  digitalWrite(evening, LOW);
  digitalWrite(night, HIGH);
  delay(1000);  
}
