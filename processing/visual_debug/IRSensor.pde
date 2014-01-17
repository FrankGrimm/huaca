class IRSensor {
  public float minDiameter = 1;
  public float maxDiameter = 10;
  public float startAngle = 0;
  public float angle = PI/2;
  
  public Coordinate position = new Coordinate(0, 0);
  
  public int minValue = 0;
  public int maxValue = 25;
  public int value = 0;
  
  public void setValue(int val) {
    if (val < 0) val = 0;
    this.value = val;
    if (this.value > maxValue) {
      maxValue = this.value;
    }
  }
  
  public float getPercentage() {
    return (float)this.value / (this.maxValue - this.minValue);
  }
  
  public void display() {
    noFill();
    
    stroke(255, 127);
    strokeWeight(2);
    arc(this.position.X, this.position.Y, 
        this.minDiameter, this.minDiameter,
        this.startAngle, this.startAngle+this.angle);
    
    stroke(0, 255, 0, 200);
    strokeWeight(4);
    float valueDiameter = this.minDiameter + this.getPercentage()*(this.maxDiameter - this.minDiameter);
    arc(this.position.X, this.position.Y, 
        valueDiameter, valueDiameter,
        this.startAngle, this.startAngle+this.angle);
        
    stroke(255, 127);
    strokeWeight(2);
    arc(this.position.X, this.position.Y, 
        this.maxDiameter, this.maxDiameter,
        this.startAngle, this.startAngle+this.angle);

  }
}
