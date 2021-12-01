#define D2 2

void setup() {
  // put your setup code here, to run once:
pinMode(D2,INPUT);
}

void loop() {

int motion= digitalRead (D2);

if(D2 == 1)
{
  
  Serial.print("sensor high");
  
  }
  
  // put your main code here, to run repeatedly:

}
