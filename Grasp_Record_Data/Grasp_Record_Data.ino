#include <SoftwareSerial.h>

static int chan1 = A3;
static int chan2 = A2;
static int chan3 = A1;
static int chan4 = A0;
int analogPins[] = {
  chan1, chan2, chan3, chan4}; // array for loops
static int tipswitch1 = 5;
static int tipswitch2 = 4;
static int tipswitch3 = 3;
static int tipswitch4 = 2;
static int tipSwitches[] = {
  tipswitch1, tipswitch2, tipswitch3, tipswitch4};
  
static const int NChan = 4;

//Band pass butterworth filter order=5 Cut-off frequencies 20 Hz and 450 Hz (alpha1=0.02 alpha2=0.45) 
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
			v[10] = (4.873111993662e-1 * x)
				 + (  0.2374721311 * v[0])
				 + (  0.1454893602 * v[1])
				 + ( -1.4777807632 * v[2])
				 + ( -0.7890998815 * v[3])
				 + (  3.7671531142 * v[4])
				 + (  1.6513505611 * v[5])
				 + ( -4.9549505128 * v[6])
				 + ( -1.5945097838 * v[7])
				 + (  3.4017026454 * v[8])
				 + (  0.6126559842 * v[9]);
			return 
				 (v[10] - v[0])
				+5 * (v[2] - v[8])
				+10 * (v[6] - v[4]);
		}
};

filter filters[NChan];

void setup(void){
  // set pin modes
  for(int i = 0; i < NChan; i++){ // loop through channels
    pinMode(analogPins[i],INPUT);
    pinMode(tipSwitches[i],INPUT);
  }  
  for (int i = 0; i < NChan; i ++) {
    filters[i] = filter();
  }
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
  float val = 0;
  int tmp = 0;
  float filtered = 0;
  float powers[NChan];
    for (int i = 0; i<NChan; i++){ // loop through channels
    	val = analogRead(analogPins[i]);  // read channel.  10-bit ADC.  returns int
        filtered = filters[i].step(val);
        powers[i] = filtered;
        //Serial.println(highByte(val)); // 0000 00**  high byte is mostly 0's
    	//tmp += (lowByte(val)>>(2*i), DEC);
    }
    
    for (int i=0; i < NChan-1; i++) {
      Serial.print(powers[i]);
      Serial.print(",");
    }
    Serial.print(powers[NChan-1]);
    Serial.print("\n");
    
}
