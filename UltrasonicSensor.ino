#define BLYNK_TEMPLATE_ID "TMPL6_GF8IEAX"
#define BLYNK_TEMPLATE_NAME "Ultrasonic"
#define BLYNK_AUTH_TOKEN "YLAjCe7E51WtW2MKL-mays7hQXidey2H"

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define  trig  D1
#define  echo  D2
#define LED10_3 D3
#define LED5_6 D4

long duration;
int distance;

// You should get Auth Token in the Blynk App.

char auth[] = "YLAjCe7E51WtW2MKL-mays7hQXidey2H";
char ssid[] = "IoTHan";   // your ssid 
char pass[] = "mantapbang"; // your pass

BlynkTimer timer;

void setup()
{
  // Debug console
  pinMode(trig, OUTPUT);  // Sets the trigPin as an Output
  pinMode(echo, INPUT);   // Sets the echoPin as an Input
  pinMode(LED10_3, OUTPUT);
  pinMode(LED5_6, OUTPUT);
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);

  // Setup a function to be called every second
  timer.setInterval(1000L, sendSensor);
}

void loop()
{
  Blynk.run();
  timer.run();
}
void sendSensor()
{
  digitalWrite(trig, LOW);   // Makes trigPin low
  delayMicroseconds(2);       // 2 micro second delay

  digitalWrite(trig, HIGH);  // tigPin high
  delayMicroseconds(10);      // trigPin high for 10 micro seconds
  digitalWrite(trig, LOW);   // trigPin low

  duration = pulseIn(echo, HIGH);   //Read echo pin, time in microseconds
  distance = duration * 0.034 / 2;   //Calculating actual/real distance

  Serial.print("Distance = ");        //Output distance on arduino serial monitor
  Serial.println(distance);
  
  if(distance <= 5){
  digitalWrite(LED10_3, HIGH);
  digitalWrite(LED5_6, HIGH);
  Blynk.virtualWrite(V0, distance);
  Blynk.virtualWrite(V1, "Jarak <= 5 cm!");
  delay(1000);
  }
  else if(distance <= 10){
  digitalWrite(LED5_6, HIGH);
  Blynk.virtualWrite(V0, distance);
  Blynk.virtualWrite(V1, "Jarak <= 10 cm!");
  delay(1000);
  }
  else{
  digitalWrite(LED5_6, LOW);
  digitalWrite(LED10_3, LOW);
  Blynk.virtualWrite(V0, distance);
  delay(1000);  
  }                        
  //3 lampu 10 cm
  //6 lampu 5 cm
}