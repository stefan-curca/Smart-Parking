#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
#include <Servo.h>

// Define Trig and Echo pin:
#define trigPin1 10
#define echoPin1 13
#define trigPin 11
#define echoPin 12

Servo myservo;
Servo myservo1;

// Define variables:
int IR1 = 2;
int IR2 = 4;
int flag1 = 0;
int flag2 = 0;

int Slot = 2;

long duration;
int distance;
int sensorValue = 0;
int lastCommand = 0, currentCommand = 0;

int distance1;
long duration1;
int sensorValue1 = 0;
int lastCommand1 = 0, currentCommand1 = 0;

void setup() {
  
  lcd.init();
  lcd.backlight();
  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  myservo.attach(6);  // attaches the servo on pin 9 to the servo object
  myservo1.attach(7);
  myservo.write(90);
  myservo1.write(90);
  lastCommand = 90;
  lastCommand1 = 90;
  Serial.begin(9600);

  lcd.setCursor (0,0);
  lcd.print("     ARDUINO    ");
  lcd.setCursor (0,1);
  lcd.print(" PARKING SYSTEM ");
  delay (2000);
  lcd.clear();
}

void loop() {
 
  // Clear the trigPin by setting it LOW:
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);

  // Trigger the sensor by setting the trigPin high for 10 microseconds:
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);


  // Read the echoPin, pulseIn() returns the duration (length of the pulse) in microseconds:
  duration = pulseIn(echoPin, HIGH);
  // Calculate the distance:
  distance = duration * 0.034 / 2;


  // Print the distance on the Serial Monitor (Ctrl+Shift+M):
  Serial.print("Distance = ");
  Serial.print(distance);
  Serial.println(" cm");

  if(digitalRead(IR1)==LOW && flag1==0)
  {
    if(Slot>0)
    {
      flag1=1;
      myservo.write(10);
      //currentCommand = 10;
      Slot = Slot-1;
    }
    else
  {
      lcd.setCursor (0,0);
      lcd.print("    Scuze    ");  
      lcd.setCursor (0,1);
      lcd.print("  Parcare plina  "); 
      delay (3000);
      lcd.clear(); 
  }
  }

    if(distance < 15 && Slot > 0)
    {
      currentCommand = 10;
      flag1=0;
    }

    if(distance < 15 && Slot == 0)
    {
      delay(2000);
      myservo.write(90);
      flag1=0;
    }

    if(distance > 15)
    {
      currentCommand = 90;
    }

    if(lastCommand != currentCommand)
    {
      myservo.write(currentCommand);
    }
    lastCommand = currentCommand;

    delay(100); // Wait for 50 millisecond(s)

     digitalWrite(trigPin1, LOW);
     delayMicroseconds(5);

     digitalWrite(trigPin1, HIGH);
     delayMicroseconds(10);

     digitalWrite(trigPin1, LOW);

     duration1 = pulseIn(echoPin1, HIGH);
  // Calculate the distance:
    distance1 = duration1 * 0.034 / 2;

    lcd.setCursor (0,0);
    lcd.print("    WELCOME!    ");
    lcd.setCursor (0,1);
    lcd.print("Slot Left: ");
    lcd.print(Slot);

   Serial.print("Distance 1= ");
   Serial.print(distance1);
   Serial.println(" cm");

  if(digitalRead(IR2) == LOW && flag2==0)
  {
      flag2=1;
      myservo1.write(160);
      //currentCommand1 = 160;
      if(Slot < 2)
      {
        Slot = Slot+1;
      }
  }

  if(distance1 < 15 )
    {
      currentCommand1 = 160;
      flag2=0;
    }

    else if(distance1 > 15)
    {
      currentCommand1 = 90;
    }

    if(lastCommand1 != currentCommand1)
    {
      myservo1.write(currentCommand1);
    }
    lastCommand1 = currentCommand1;

    delay(100);
}