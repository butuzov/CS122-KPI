public class Line{
	final private Point a, b;

	final private double length;

	public Line(Point a, Point b){

		if ( a.equals(b) ) {
			throw new ArithmeticException("These Points are same");
		}
		this.a = a;
		this.b = b;

		this.length = (this.a).DistanceTo(this.b);
	}


	public Point getA(){
		return this.a;
	}

	public Point getB(){
		return this.b;
	}

	// You need to cehck for expection in this block, or check
	// IsConnectedTo Beforehand
	public Point ConnectedAt(Line line) {

		if ( this.getA().equals( line.getA() ) ||
				this.getA().equals( line.getB() ) ) {
			return this.getA();
		}


		if ( this.getB().equals( line.getA() ) ||
				this.getB().equals( line.getB() ) ) {
			return this.getB();
		}

		throw new IllegalArgumentException(
			"Connection Point between this lines not found"
		);
	}

	public boolean ConnectedTo(Line line) {

		try {
			Point point =  ConnectedAt(line);
		} catch (IllegalArgumentException iae) {
			return false;
		}

		return true;
	}

	public double length(){
		return this.length;
	}

	// Object as string represenation
	@Override
	public String toString() {
		return String.format("L{%s:%s}", this.a, this.b);
	}

	// Equals implementation.
	@Override
	public boolean equals(Object other) {
		if (! (other instanceof Line) ) {
			return false;
		}

		final Line obj = (Line) other;

		// Custom equality check here.
		boolean AisA = this.getA().equals(obj.getA());
		boolean AisB = this.getA().equals(obj.getB());


		if ( ! AisA && ! AisB ) {
			return false;
		} else if ( AisA && this.getB().equals(obj.getB()))  {
			return true;
		} else if ( AisB && this.getB().equals(obj.getA())) {
			return true;
		}

		return false;
	}

}
