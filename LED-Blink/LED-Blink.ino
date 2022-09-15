const int LED1 = 2;
const int LED2 = 4;
const int LED3 = 5;
const int LED4 = 14;


void setup() {
  Serial.begin(115200);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
}

void loop() {
  delay(1000);
 
  Serial.print("Setup: Executing on core ");
  Serial.println(xPortGetCoreID());
  
  Serial.println();
  Serial.println("Hello");
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, HIGH);
  digitalWrite(LED3, HIGH);
  digitalWrite(LED4, HIGH);
  delay(200);   
 
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);
  delay(200); 
}
