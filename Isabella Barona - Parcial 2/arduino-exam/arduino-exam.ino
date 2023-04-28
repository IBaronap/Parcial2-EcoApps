const int Led1 = 5;
const int Led2 = 6;

const int btn_A_PIN = 2;
const int btn_B_PIN = 4;

int btn_A_value = 0;
int btn_B_value = 0;

int previous_btn_A_value = 0;
int previous_btn_B_value = 0;

const int POTEN_PIN = A1;

int POTEN_PINvalue = 0;

int actuatorValue = 0;
int previousValue = 0;

void setup() {
  pinMode(Led1, OUTPUT);
  pinMode(Led2, OUTPUT);

  pinMode(btn_A_PIN, INPUT);
  pinMode(btn_B_PIN, INPUT);

  pinMode(POTEN_PIN, INPUT);

  Serial.begin(9600);
}

void loop() {
    if(Serial.available() > 0) {
      receivingData();
    } else {
      sendingData();
    }
    
    delay(100);
}

void sendingData() {
  
  btn_A_value = digitalRead(btn_A_PIN);
  btn_B_value = digitalRead(btn_B_PIN);

  POTEN_PINvalue = analogRead(POTEN_PIN);
  actuatorValue = POTEN_PINvalue;

  if (previousValue != actuatorValue) {
    sendSerialMessage(actuatorValue, btn_A_value, btn_B_value);
    previousValue = actuatorValue;
  }

  if (previous_btn_A_value != btn_A_value) {
    sendSerialMessage(actuatorValue, btn_A_value, btn_B_value);
    previous_btn_A_value = btn_A_value;
  }

    if (previous_btn_B_value != btn_B_value) {
    sendSerialMessage(actuatorValue, btn_A_value, btn_B_value);
    previous_btn_B_value = btn_B_value;
  }

  delay(100);
}

void sendSerialMessage(int actuatorValue, int btn_A_value, int btn_B_value) {
  Serial.print(actuatorValue);
  Serial.print(' ');
  Serial.print(btn_A_value);
  Serial.print(' ');
  Serial.print(btn_B_value);
  Serial.print(' ');
  Serial.println();
}

void receivingData() {
  char inByte = Serial.read();

  switch(inByte){
    case 'S':

      digitalWrite(Led1, HIGH);
      digitalWrite(Led2, HIGH);

      delay(500);

      digitalWrite(Led1, LOW);
      digitalWrite(Led2, LOW);

      delay (500);
      break;
    case 'L':

      digitalWrite(Led1, HIGH);
      digitalWrite(Led2, HIGH);

      delay (500);
      break;
  }
  Serial.flush();
}
