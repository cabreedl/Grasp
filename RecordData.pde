//This program collects data from the serial port and prints it
//into a csv labeled with a timestamp
//To exit hit any button on the keyboard

import processing.serial.*;
PrintWriter output;
//keeps count so that index%numChan prints teh correct thing
int index = 0;
//number of recording channels
int NChan = 4;
int baudRate = 460800;
int[] channels;
int lowVal;
int highVal;
Serial myPort;
String inString;
int startTime = 0;
int recordTime = 60000; //In milliseconds

void setup() {
   String day = str(day());
   String month = str(month());
   String year = str(year());
   String hr = str(hour());
   String min = str(minute());
   String sec = str(second());
   String filename = "HandTest-"+year+"."+month+"."+day+"-"+hr+"."+min+"."+sec+".txt";
   output = createWriter(filename); 
      
   size(200,200);
   //use this to find the serial port and set it in the
   //instantiation of port. the first is list()[0]
   println(Serial.list());
   //CHANGE ME
   myPort = new Serial(this, Serial.list()[2], baudRate);
   myPort.bufferUntil('\n');
   
   //keeps count so that index%numChan prints teh correct thing
   int index = 0;
   //number of recording channels
   channels = new int[NChan];
}

void draw() {
    background(0);
}

void serialEvent(Serial p) {
  
  if (startTime == 0) {
    startTime = millis();
  }
  else if((millis() - startTime) >= recordTime) {
    exit();
  }
  inString = p.readString();
  output.print(inString);
}

void keyPressed() {
  output.flush();
  output.close(); 
  exit(); 
}
