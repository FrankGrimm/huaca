class SlideControl {
  int value = 0;
  int minValue = 0;
  int maxValue = 255;
  
  public Rectangle position = new Rectangle(0, 0, 1, 1);

  SlideControl(int minValue, int maxValue, int initialValue) {
    this.minValue = minValue;
    this.maxValue = maxValue;
    this.value = initialValue;
  }
  
  public void setMaxValue(int maxValue) {
    this.maxValue = maxValue;
  }
  
  public void setMinValue(int minValue) {
    this.minValue = minValue;
  }
  
  public void setValue(int value) {
    this.value = value;
  }
  
  public int getValue() {
    return this.value;
  }
  
  public int getMaxValue() {
    return this.maxValue;
  }
  
  public int getMinValue() {
    return this.minValue;
  }
  
  public void display() {
    this.position.display();
    
    fill(255, 200);
    noStroke();
    float valP = (float)this.value / (this.maxValue - this.minValue);
    valP *= this.position.H;
    rect(this.position.X + 1, this.position.Y + this.position.H - valP + 1, 
          this.position.W - 1, 
          valP - 1);
  }
}
