// run this on Processing: 
// https://processing.orghttps://processing.org
// -- compile Arduino code first -> upload to board 
// -> run this script -> output 'data.txt' in the 'proc_1' folder

import processing.serial.*;

Serial mySerial;
PrintWriter output;
void setup() 
{
   mySerial = new Serial( this, Serial.list()[2], 9600 ); 
   // 9600 must equal the Serial number in Arduino code ! 
   
   output = createWriter( "data.txt" );
   // the output is stored in 'proc_1' folder
}
void draw() 
{
    if (mySerial.available() > 0 ) {
         String value = mySerial.readStringUntil('\n');
         // recognize data stream by '\n'
         if ( value != null ) {
              println(value);
              output.println( value );
         }
    }
}

void keyPressed() {
    output.flush();  // Writes the remaining data to the file
    output.close();  // Finishes the file
    exit();  // Stops the program by pressing any key
}