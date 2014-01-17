class Rectangle extends Coordinate {
  public int X = 0;
  public int Y = 0;
  public int W = 1;
  public int H = 1;
  
  Rectangle(int setX, int setY, int setWidth, int setHeight) {
    super(setX, setY);
    this.X = setX;
    this.Y = setY;
    this.W = setWidth;
    this.H = setHeight;
  }
  
  void display() {
    stroke(255);
    noFill();
    rect(this.X, this.Y, this.W, this.H);
  }
}
