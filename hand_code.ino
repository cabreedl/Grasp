#include <SoftwareSerial.h>

#include <Servo.h> 

int thumbMin = 5;
int thumbMax = 160;
int pointerMin = 10;
int pointerMax = 160;

int middleMin = 10;
int middleMax = 165;

int ringMin = 60;
int ringMax = 140;

int pinkyMin = 70;
int pinkyMax = 160;

Servo thumb, pointer, middle, ring, pinky;
 
int pos = 0;    // variable to store the servo position 

void openAll(){
  for (pos = 0; pos < 180; pos +=1){
    if (pos < thumbMax && pos > thumbMin) thumb.write(pos);
    if (pos < pointerMax && pos > pointerMin) pointer.write(pos);
    if (pos < middleMax && pos > middleMin) middle.write(pos);
    if (pos < ringMax && pos > ringMin) ring.write(pos);
    if (pos < pinkyMax && pos > pinkyMin) pinky.write(pos);
    delay(3);
  }
}
void openThumb(){
  for(pos = thumbMin; pos < thumbMax; pos += 1)  // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    thumb.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(3);                       // waits 15ms for the servo to reach the position 
  }
}

void openPointer(){
  for(pos = pointerMin; pos < pointerMax; pos += 1)  // goes from 0 degrees to 180 degrees 
  {
    pointer.write(pos);
    delay(2);                       // waits 15ms for the servo to reach the position 
  } 
}

void openMiddle(){
  for(pos = middleMin; pos < middleMax; pos += 1)  // goes from 0 degrees to 180 degrees 
  {
    middle.write(pos);
    delay(2);                       // waits 15ms for the servo to reach the position 
  } 
}

void openRing(){
  for(pos = ringMin; pos < ringMax; pos += 1)  
  {
    ring.write(pos);
    delay(2);                       // waits 15ms for the servo to reach the position 
  }
}

void openPinky(){
   for(pos = pinkyMin; pos < pinkyMax; pos += 1)  
  {
    pinky.write(pos);
    delay(3);                       
  } 
}

void closeAll(){

  for (pos = 180; pos > 0; pos -=1){
    if (pos < thumbMax && pos > thumbMin) thumb.write(pos);
    if (pos < pointerMax && pos > pointerMin) pointer.write(pos);
    if (pos < middleMax && pos > middleMin) middle.write(pos);
    if (pos < ringMax && pos > ringMin) ring.write(pos);
    if (pos < pinkyMax && pos > pinkyMin) pinky.write(pos);
  }
}
void closeThumb(){
  for(pos = thumbMax; pos > thumbMin; pos -= 1)  // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    thumb.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(3);                       // waits 15ms for the servo to reach the position 
  }
}

void closePointer(){
  for(pos = pointerMax; pos > pointerMin; pos -=1)     // goes from 180 degrees to 0 degrees 
  {                                
    pointer.write(pos);
    delay(3);                       // waits 15ms for the servo to reach the position 
  } 
}

void closeMiddle(){
  for(pos = middleMax; pos > middleMin; pos -= 1)  // goes from 0 degrees to 180 degrees 
  {
    middle.write(pos);
    delay(2);                       // waits 15ms for the servo to reach the position 
  } 
}

void closeRing(){
  for(pos = ringMax; pos > ringMin; pos -= 1)  // goes from 0 degrees to 180 degrees 
  {
    ring.write(pos);
    delay(3);                       // waits 15ms for the servo to reach the position 
  } 
}

void closePinky(){
  for(pos = pinkyMax; pos > pinkyMin; pos -= 1)  // goes from 0 degrees to 180 degrees 
  {
    pinky.write(pos);
    delay(3);                       // waits 15ms for the servo to reach the position 
  } 
}



int chan1 = A3;
int chan2 = A2;
int chan3 = A1;
int chan4 = A0;
int analogPins[] = {
  chan1, chan2, chan3, chan4}; // array for loops
int tipswitch1 = 5;
int tipswitch2 = 4;
int tipswitch3 = 3;
int tipswitch4 = 2;
int tipSwitches[] = {
  tipswitch1, tipswitch2, tipswitch3, tipswitch4};
  
int NChan = 4;

boolean openHand = true;

class rms
{
        public:
                rms()
                {
                        for (int i=0; i < 10; i++)
                                v[i]=0.0;
                }
       private:
               float v[10];
       public:
               float step(float x)
               {
                        int arrayLength = sizeof(v) / sizeof(float);
                        for (int i =0; i < arrayLength-1; i++) {
                            v[i] = v[i+1];
                        }
                        v[arrayLength-1] = x;

                        float sumSquare = 0;

                        for (int i=0; i <arrayLength; i++) {
                            sumSquare += v[i]*v[i];
                        }
                        
                        float meanSquare = sumSquare / arrayLength;
                        float rootMeanSquare = sqrt(meanSquare);
                        return rootMeanSquare;
               }
};

class filter
{
	public:
		filter()
		{
			for(int i=0; i <= 10; i++)
				v[i]=0.0;
		}
	private:
		float v[11];
	public:
		float step(float x) //class II 
		{
			v[0] = v[1];
			v[1] = v[2];
			v[2] = v[3];
			v[3] = v[4];
			v[4] = v[5];
			v[5] = v[6];
			v[6] = v[7];
			v[7] = v[8];
			v[8] = v[9];
			v[9] = v[10];
			v[10] = (2.918540128084e-2 * x)
				 + ( -0.0069673489 * v[0])
				 + (  0.1106384486 * v[1])
				 + ( -0.6646286456 * v[2])
				 + (  2.5878859032 * v[3])
				 + ( -6.9511486724 * v[4])
				 + ( 13.1483064732 * v[5])
				 + (-18.1690250214 * v[6])
				 + ( 18.4193575893 * v[7])
				 + (-12.8663886192 * v[8])
				 + (  5.3919687883 * v[9]);
			return 
				 (v[10] - v[0])
				+5 * (v[2] - v[8])
				+10 * (v[6] - v[4]);
		}
};

filter butter = filter();  
rms mean = rms();

void setup(void){
  // set pin modes
  for(int i = 0; i < NChan; i++){ // loop through channels
    pinMode(analogPins[i],INPUT);
    pinMode(tipSwitches[i],INPUT);
  }
  
  thumb.attach(8);  // attaches the servo on pin 9 to the servo object 
  pointer.attach(7);
  middle.attach(6);
  ring.attach(5);
  pinky.attach(4);
  
  // establish com
  Serial.begin(115200);  // set baud rate.
}

long updatetime = 0;
int TimingOffset = -6; // Arduino takes 6 us to execute command - offest for accuracy
int UserFrequency = 1000;
long measurementdelay = 1000000/long(UserFrequency);// converted to microseconds

void loop(){
  if (micros() > updatetime){  // check if it's time to send next sample
      updatetime = micros()+measurementdelay-TimingOffset;  // reset timer.
      ProcessOutput(); // handles data formats, filters, and channels
  }
}

void ProcessOutput(void) {
  int val = 0;
  int tmp = 0;
  float filtered = 0;
  float rmsValue = 0;
  float powers[NChan];
  float normal[NChan];
  float gestureThreshold = .9;
    for (int i = 0; i<NChan; i++){ // loop through channels
    	val = analogRead(analogPins[i]);  // read channel.  10-bit ADC.  returns int
        //filtered = butter.step(val);
        //rmsValue = mean.step(val);
        //powers[i] = rmsValue;
        //Serial.println(rmsValue); 
    	//Serial.println(val);
        powers[i] = val;
        //Serial.println(highByte(val)); // 0000 00**  high byte is mostly 0's
    	//tmp += (lowByte(val)>>(2*i), DEC);
    }
    float maxNum;
    maxNum = max(powers[0],powers[1]);
    for (int i =2; i < NChan; i++) {
      maxNum = max(maxNum,powers[i]);
    }
    for (int i=0; i < NChan; i++){
       normal[i] = powers[i]/maxNum; 
    }
    
    for (int i=0; i < NChan-1; i++) {
      Serial.print(powers[i]);
      Serial.print(",");
    }
    Serial.print(powers[NChan-1]);
    Serial.print("\n");
    
    if ((powers[0] / powers[1]) < .08) {
      if (openHand == false) {
        openHand = true;
        //Serial.println("open\n\n");
        //openAll();
      } 
    }
    else if ((powers[1] / powers[0]) < .35) {
      if (openHand == true) { 
        openHand = false;
        //Serial.println("close\n\n"); 
        //closeAll();
      }
    }
    else if ((powers[0] / powers[2]) < gestureThreshold && (powers[1] / powers[2]) < .40) { 
      
      //Serial.println("thumb stuff\n\n"); 
    }
    //Serial.println("\n\n");
    //Serial.println(lowByte(tmp), DEC);
}
