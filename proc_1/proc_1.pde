import processing.serial.*;

Serial mySerial;
PrintWriter output;
void setup() {
   mySerial = new Serial( this, Serial.list()[2], 9600 );
   output = createWriter( "data.txt" );
   // the output is stored in 'proc_1' folder
}
void draw() {
    if (mySerial.available() > 0 ) {
         String value = mySerial.readStringUntil('\n');
         if ( value != null ) {
              println(value);
              output.println( value );
         }
    }
}

void keyPressed() {
    output.flush();  // Writes the remaining data to the file
    output.close();  // Finishes the file
    exit();  // Stops the program
}