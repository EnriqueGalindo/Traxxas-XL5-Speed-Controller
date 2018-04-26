#include <Servo.h> // The ESC will be treated as a Servo

Servo myESC, myservo;  //creating myESC as a servo
int i, a, n, x, y, b=1, xfactor=10; //initial value of the pulse that will be sent to the ESC
// Will be between 0 to 180
void setup()
{
  Serial.begin(9600); //Syncing the Serial Monitor so you can observe the pulse
  myservo.attach(9);
  myESC.attach(3); //stating that the ESC's signal is plugged into Pin 3 on the Arduino
  myESC.write(92);
  delay(1000); 
}
void rset()
{
  for(int i=90; i>25;i--)
  {
    //Serial.println(i); // prints the current pulse on the Serial Monitor
    myESC.write(i);    //Writes the pulse to the ESC
  }
  for(int i=25; i<91;i++)
  {
    //Serial.println(i); // prints the current pulse on the Serial Monitor
    myESC.write(i);    //Writes the pulse to the ESC
  }
  myESC.write(92);
  delay(100);
}
void reverse(int x)
{
  rset();
  int n = (92 - (67*x)/100);
  for(i=92; i>n;i--)
  {
    //Serial.println(i); // prints the current pulse on the Serial Monitor
    myESC.write(i);    //Writes the pulse to the ESC
    delay(10); 
  }
  while(!Serial.available())
    myESC.write(i);
  a = Serial.parseInt();
  eval();
} 
void neutral()
{
  if (i<92)
  {
   for(i=n; i<=92;i++)
    {
      //Serial.println(i); // prints the current pulse on the Serial Monitor
      myESC.write(i);    //Writes the pulse to the ESC
      delay(2); 
    } 
  }
  else if(i>92)
  {
    for(i=n; i>91;i--)
    {
      //Serial.println(i); // prints the current pulse on the Serial Monitor
      myESC.write(i);    //Writes the pulse to the ESC
      delay(2); 
    }
  }
}
void forward(int x)
{
 
  n = (92 +(68*x)/100);
  for(i=92; i<n;i++)
  {
   //Serial.println(i); // prints the current pulse on the Serial Monitor
    myESC.write(i);    //Writes the pulse to the ESC
    delay(10); 
  }  
  while(!Serial.available())
    myESC.write(i);
  a = Serial.parseInt();
  eval();
}
void eval()
{
  if(a<101&&a>-101)
  {
    neutral();
    if(a>0&&a<=100)
    {
      x=1;
      y=(a);
    }    
    else if(a<0&&a>=-100)
    {
      x=2;
      y=-a;
    }
    else if(a==0)
      x=0;
    else
      Serial.println("Invalid Input");
  }
  else if(a>=1000&&a<=1180)
  {
    myservo.write(a-1000+xfactor); 
  }
  else
    Serial.println("Invalid Input");
}
void calib()
{
  while(b!=0)
  {
   //Serial.println("Enter x factor");
   //while(!Serial.available());
   //xfactor= Serial.parseInt();
   xfactor=10;
   if(xfactor>90||xfactor<-90)
   {
    Serial.println("Invalid Input");
    continue;
   }
   myservo.write(xfactor+90); 
   Serial.println("Ok - 0, try again - 1");
   //while(!Serial.available());
   //b = Serial.parseInt();
   b=0;
  }
}
void loop()
{
  myservo.write(90);
  calib();
  Serial.println("Waiting for Input");
  while(!Serial.available());
  a = Serial.parseInt();
  while(1)
  {
    eval();
    if(x==1)
    {
      Serial.println("FWD");
      forward(y);
    }
    if(x==2)
    {
      Serial.println("REV");
      reverse(y);
    }
    if(x==0)
      {
        Serial.println("Neutral");
        neutral();
        while(!Serial.available());
        a = Serial.parseInt();  
      }
  }
}

