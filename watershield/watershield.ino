/*
 WaterShield
 by Alexandre Dubois
 
 For more information, check out:
 http://blog.alexandredubois.com
 */
 
/************************
*** CONST & VARIABLES ***
************************/

const int probesInPin = A3;//Pin attached to the probes
const int lightInPin = A2;//Pin attached to the LDR

const int greenOutPin = 12;
const int yellowOutPin = 11;
const int redOutPin = 10;

int probesValue = 0;
int lightValue = 0;

const int debug = 1;

/****************
*** FUNCTIONS ***
****************/

/*Read moisture soil value from the probes*/
void readProbesValue()
{
  probesValue = analogRead(probesInPin);
  if(debug == 1)
  {
    Serial.print("probes value = " );                       
    Serial.println(probesValue);
  }
}

/*Read light walue received by the LDR*/
void readLightValue()
{
  delay(200);
  lightValue = analogRead(lightInPin);
  if(debug == 1)
  {
    Serial.print("light value = " );                       
    Serial.println(lightValue); 
  }
  delay(200);
}

/*Blink leds to warn the user before launching the main program*/
void launchWarning()
{
  for (int i=0;i<=6;i++)
  {
    digitalWrite(redOutPin, HIGH);
    digitalWrite(yellowOutPin, HIGH);
    digitalWrite(greenOutPin, HIGH);
    delay(250);
    digitalWrite(redOutPin, LOW);
    digitalWrite(yellowOutPin, LOW);
    digitalWrite(greenOutPin, LOW);
    delay(250);
  }
}

void blinkRed()
{
  digitalWrite(redOutPin, HIGH);
  delay(250);
  digitalWrite(redOutPin, LOW);
  delay(250);
}

void blinkYellow()
{
  digitalWrite(yellowOutPin, HIGH);
  delay(250);
  digitalWrite(yellowOutPin, LOW);
  delay(250);
}

void blinkGreen()
{
  digitalWrite(greenOutPin, HIGH);
  delay(250);
  digitalWrite(greenOutPin, LOW);
  delay(250);
}

/***************************
*** SETUP & MAIN PROGRAM ***
***************************/

/*Setup the device*/
void setup()
{
  pinMode(greenOutPin, OUTPUT);
  pinMode(yellowOutPin, OUTPUT);
  pinMode(redOutPin, OUTPUT);
  pinMode(lightInPin, INPUT);

  if(debug == 1){
    Serial.println("Initialising...");
    Serial.begin(9600);
    Serial.println("Initialisation complete.");
  }
  
  launchWarning();
}

/*Main program : wait and check the plant every X minutes*/
void loop () 
{
  readLightValue();
  readProbesValue();
  if(probesValue < 300)
  {
    if(lightValue < 400)
    {
       blinkRed(); 
    }
    else
    {
       blinkYellow();
    }
  } else {
    blinkGreen();
  }
} // end of loop
