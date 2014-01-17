class Position extends Rectangle {
  int rectspacing = 5;
  
  Position(int pw, int ph, int px, int py) {
    super(px, py, pw, ph);
    rectspacing = (int)(this.W/10);
  }
  
  void display() {
    // border
    super.display();
    noFill();
    
    // grid
    strokeCap(SQUARE);
    strokeWeight(1);
    stroke(255);
    
    for (int cx = this.X+rectspacing; cx < (this.X+this.W); cx+=rectspacing) {
      line(cx, this.Y, cx, this.Y+this.H);
      for (int cy = this.Y+rectspacing; cy < (this.Y+this.H); cy+=rectspacing) {
        line(this.X, cy, this.X + this.W, cy);
      }
    }
    
    
  }
}
