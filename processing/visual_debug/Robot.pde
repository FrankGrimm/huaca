/* Robot visualization with sensors */

class Robot {
  float xpos, ypos, diameter;
  
  IRSensor sensors[] = new IRSensor[4];
  
  Robot(float xpos, int ypos, float diameter) {
    this.xpos = xpos;
    this.ypos = ypos;
    this.diameter = max(diameter, 10.0);
    
    float halfAngle = PI/7/2;
    this.sensors[0] = this.createIR(0);
    this.sensors[0].startAngle = PI/2-halfAngle+PI+PI/5; //-halfAngle-PI/4; // Front right
    this.sensors[1] = this.createIR(0);
    this.sensors[1].startAngle = PI/2-halfAngle+PI; // Front center
    this.sensors[2] = this.createIR(0);
    this.sensors[2].startAngle = PI/2-halfAngle+PI-PI/5; // Front left
    this.sensors[3] = this.createIR(0);
    this.sensors[3].startAngle = PI/2-halfAngle;
    
    motors[0] = 0;
    motors[1] = 0;
  }
  
  IRSensor createIR(int idx) {
    IRSensor res = new IRSensor();
   
    res.position.X = (int)this.xpos;
    res.position.Y = (int)this.ypos;
    res.minDiameter = this.diameter;
    res.maxDiameter = this.diameter * 3;
    res.angle = PI/7;
    
    return res;
  }
  
  void draw_base() {
    noFill();
    strokeWeight(3);
    stroke(255, 200);
    ellipse(xpos, ypos, diameter, diameter);
  }

  public int motors[] = new int[2];

  void draw_wheel(float x, int idx) {
    noStroke();
    if (motors[idx] > 0) {
      fill(#55DE38);
    } else {
      fill(127);
    }
    rect(x-3, ypos-4, 6, diameter/3);
  }
  
  void draw_wheels() {
    draw_wheel(xpos-diameter/2+1, 0);
    draw_wheel(xpos+diameter/2+1, 1);
  }
  
  boolean bumperHit = false;
  
  void draw_bumpers() {
    noFill();
    strokeCap(SQUARE);
    strokeWeight(10);
    if (!this.bumperHit) {
      stroke(255);
    } else {
      stroke(255, 0, 0);
    }
    float arcw = PI/6;
    float arcstart = PI+PI/2;
    arc(xpos, ypos, diameter, diameter, arcstart-arcw/2, arcstart+arcw/2);
    arcstart = PI+PI/2-arcw*1.6;
    arc(xpos, ypos, diameter, diameter, arcstart-arcw/2, arcstart+arcw/2);
    arcstart = PI+PI/2+arcw*1.6;
    arc(xpos, ypos, diameter, diameter, arcstart-arcw/2, arcstart+arcw/2);
    strokeWeight(1);
    stroke(0, 0, 255);
    arcstart = PI+PI/2-arcw*1.6-arcw/2;
    float arcend = PI+PI/2+arcw*1.6+arcw/2;
    arc(xpos, ypos, diameter-10, diameter-10, arcstart, arcend);
    arc(xpos, ypos, diameter+10, diameter+10, arcstart, arcend);
  }
  
  void draw_ir() {
    for (int irIdx = 0; irIdx < this.sensors.length; irIdx++) {
      this.sensors[irIdx].display();
    }
  }
  
  void display() {
    draw_base();
    draw_wheels();
    draw_ir();
    draw_bumpers();
  }
}
