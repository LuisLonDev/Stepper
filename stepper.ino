#define r (2)
#define b (3)
#define y (4)
#define w (5)
#define v1 10
#define v2 40
#define v3 70
#define v4 100
#define v5 130

int i = 0;
int valor2 = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(w, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(r, OUTPUT);
  pinMode(y, OUTPUT);
  Serial.println("Ingrese los grados que desea mover: ");
}

void loop() {
  // put your main code here, to run repeatedly:
  float valor = leer();
  if ( valor != 0) {
    Serial.println(valor);
    Serial.println(" ");
    Serial.println("Ingrese 1 - 5 para variar velocidad: ");
    delay(3000);
    valor2 = leer2();
    while (valor2  != 0) {
      Serial.println(valor2);
      Serial.println(" ");
      delay(500);
      float pasos = round(valor / 0.9);
      stepperMover(pasos);
      Serial.println("Ingrese los grados que desea mover: ");
      valor2 = 0;
    }
  }
}

int velocidad(int val) {
  int milis = 0;
  switch (val) {
    case 1:
      milis = v1;
      break;
    case 2:
      milis = v2;
      break;
    case 3:
      milis = v3;
      break;
    case 4:
      milis = v4;
      break;
    case 5:
      milis = v5;
      break;
    default:
      break;
  }
  return milis;
}

float leer() {
  float data = 0;
  if (Serial.available() > 0)
  {
    String str = Serial.readStringUntil('\n');
    data = str.toFloat();
  }
  return data;
}

int leer2() {
  int data = 0;
  if (Serial.available() > 0)
  {
    String str = Serial.readStringUntil('\n');
    data = str.toInt();
  }
  return data;
}

void stepperMover(float pasos) {
  if (pasos >= 0) {
    stepperUp(pasos);
  } else if (pasos < 0) {
    if(i == 0){
      i = 5;
    }
    stepperDown(pasos);
  }
}

void stepperUp(float pasos) {
  int t = 0;
  while (t < pasos) {
    i++;
    if (i == 5) {
      i = 1;
      Serial.println("---");
    }
    sequence(i);
    t++;
    Serial.print("Va en la secuencia : ");
    Serial.println(i);
  }
  Serial.println("---");
  Serial.println("   ");
}

void stepperDown(float pasos) {
  int t = pasos * -1;
  while (t > 0) {
    i--;
    if (i == 0) {
      i = 4;
      Serial.println("---");
    }
    sequence(i);
    t--;
    Serial.print("Va en la secuencia : ");
    Serial.println(i);
  }
  Serial.println("---");
  Serial.println("   ");
}

void sequence(int p) {
  int vel = velocidad(valor2);
  switch (p) {
    case 1:
      digitalWrite(w, HIGH);
      digitalWrite(b, LOW);
      digitalWrite(y, LOW);
      digitalWrite(r, LOW);
      delay(vel);
      break;
    case 2:
      digitalWrite(w, LOW);
      digitalWrite(b, HIGH);
      digitalWrite(y, LOW);
      digitalWrite(r, LOW);
      delay(vel);
      break;
    case 3:
      digitalWrite(w, LOW);
      digitalWrite(b, LOW);
      digitalWrite(y, HIGH);
      digitalWrite(r, LOW);
      delay(vel);
      break;
    case 4:
      digitalWrite(w, LOW);
      digitalWrite(b, LOW);
      digitalWrite(y, LOW);
      digitalWrite(r, HIGH);
      delay(vel);
      break;
    default:
      break;
  }
}