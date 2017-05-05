#define morning1 2
#define morning2 3
#define morning3 4
#define morning4 5

#define sun1 6
#define sun2 7
#define sun3 8

void setup() {
  // put your setup code here, to run once:
  pinMode(morning1, OUTPUT);
  pinMode(morning2, OUTPUT);
  pinMode(morning3, OUTPUT);
  pinMode(morning4, OUTPUT);
  pinMode(sun1, OUTPUT);
  pinMode(sun2, OUTPUT);
  pinMode(sun3, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  digitalWrite(morning1, HIGH);
  digitalWrite(morning2, HIGH); 
  digitalWrite(morning3, HIGH); 
  digitalWrite(morning4, HIGH);
  digitalWrite(sun1, LOW);
  digitalWrite(sun2, LOW); 
  digitalWrite(sun3, LOW); 
  delay(1000);  
  digitalWrite(sun1, HIGH);
  digitalWrite(sun2, HIGH); 
  digitalWrite(sun3, HIGH); 
  digitalWrite(morning1, LOW);
  digitalWrite(morning2, LOW); 
  digitalWrite(morning3, LOW); 
  digitalWrite(morning4, LOW);
  delay(1000);
}
