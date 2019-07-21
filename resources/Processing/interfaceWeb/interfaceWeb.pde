import processing.serial.*;

JSONObject json;
Serial myPort;  // Create object from Serial class

void setup() {
  String portName = Serial.list()[0]; //change the 0 to a 1 or 2 etc. to match your port
  myPort = new Serial(this, portName, 9600);
}

void draw()
{
  json = loadJSONObject("http://localhost/arduino/app/config/config.json");

  JSONObject display = json.getJSONObject("display");
  
  String line1 = display.getString("line1");
  String line2 = display.getString("line2");
  int servoPos = json.getInt("servo");
  
  myPort.write((String)(line1+"."+line2+"."+servoPos));
  println(line1);
  println(line2);
  println("------------------------------------------");
  delay(2000);
}
