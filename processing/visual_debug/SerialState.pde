class SerialState {
  PFont outputFont;
  Serial serialPort;
  int lf = 50;
  String inputBuffer = "";
  
  private double deg2rad(double deg) {
    return (deg * Math.PI/180.0);
  }
  
  SerialState(PApplet recv, String useSerialPort) {
    outputFont = loadFont("CourierNewPSMT-48.vlw");
    println(Serial.list());
    if (useSerialPort == null) {
      serialPort = new Serial(recv, Serial.list()[0], 19200);
    } else {
      serialPort = new Serial(recv, useSerialPort, 19200);
    }
    serialPort.bufferUntil(lf);
  };
  
  void display() {
  };
  
  void serialEvent(Serial p) {
    String inString = p.readString();
    if (null != inString && !"".equals(inString)) {
      inputBuffer = inputBuffer + inString;
      if (inputBuffer.indexOf("{") > -1) {
        // make sure buffer starts with a JSON message
        inputBuffer = inputBuffer.substring(inputBuffer.indexOf("{"));
      } 
      
      // process messages in the buffer on a line by line basis
      String[] inputBufferLines = inputBuffer.split("\n");
      int lineIndex = 0;
      for (String line: inputBufferLines) {
        String linedata = line.trim();
        if (linedata.startsWith("{") && linedata.endsWith("}")) {
          //println("L:<" + linedata + ">");
          this.process(linedata);
        } else if (lineIndex < (inputBufferLines.length - 1)) {
          println("Malformed line: <" + linedata + ">");
        } else {
          // incomplete last line, keep in buffer
          inputBuffer = line;
        }
     
        lineIndex++;
      }
    }
  }
  
  boolean recvInit = false;
  
  void process(String recv) {
    JSONObject parsedMessage = null;
    
    try {
      parsedMessage = JSONObject.parse(recv);
    } catch (Exception e) {
      println("Invalid message. Failed to parse JSON content (" + e.getClass().getName() + ")");
      println("<" + recv + ">");
    }
    
    if (parsedMessage != null) {
      if (parsedMessage.hasKey("init") && "ROBOTBASE".equals( parsedMessage.getString("init") )) {
        println("Got initialization signal from actuator controller.");
        this.recvInit = true;
        return; 
      }
      
      if (parsedMessage.hasKey("relayActive")) {
        boolean relayActive = parsedMessage.getBoolean("relayActive");
        // TODO store and add to viz
        //println(relayActive);
        return;
      }
      
      if (parsedMessage.hasKey("motorRPM")) {
        JSONArray motorRPM = parsedMessage.getJSONArray("motorRPM");
        robot.motors[0] = motorRPM.getInt(0);
        robot.motors[1] = motorRPM.getInt(1);
        return;
      }
      
      if (parsedMessage.hasKey("bumpers") && parsedMessage.hasKey("states")) {
        int bumperCount = parsedMessage.getInt("bumpers");
        JSONArray bumperStates = parsedMessage.getJSONArray("states");
        
        boolean isHit = false;
        for (int i = 0; i < bumperStates.size(); i++) {
          if (bumperStates.getInt(i) == 1) {
            isHit = true;
          }
        }
        robot.bumperHit = isHit;
          
        return;
      }
      
      if (parsedMessage.hasKey("irsensors") && parsedMessage.hasKey("values")) {
        int irCount = parsedMessage.getInt("irsensors");
        JSONArray irValues = parsedMessage.getJSONArray("values");
        
        float irFr1 = max(irValues.getFloat(0), 0.0);
        float irFr2 = max(irValues.getFloat(1), 0.0);
        float irFr3 = max(irValues.getFloat(2), 0.0);
        float irBack = max(irValues.getFloat(3), 0.0);
        
        robot.sensors[0].setValue((int)irFr1);
        robot.sensors[1].setValue((int)irFr2);
        robot.sensors[2].setValue((int)irFr3);
        
        robot.sensors[3].setValue((int)irBack);
        return;
      }
      
      if (parsedMessage.hasKey("rcvKey")) {
        println("Key event: " + parsedMessage.getString("rcvKey"));
        return;
      }

      println("Unhandled message:");      
      println(parsedMessage.toString());
    }
    
  }
  
  void write(int key) {
    println("Sending " + key);
    serialPort.write(key);    
  }
  
}
