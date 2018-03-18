public class Point {
	final private double x, y;

	// Other types of constructors.
	public Point( Double x, Double y){
		this( x.doubleValue(), y.doubleValue() );
	}

	public Point( float x, float y){
		this( (double) x, (double) y );
	}

	public Point( Float x, Float y){
		this( x.doubleValue(), y.doubleValue() );
	}

	public Point( int x, int y){
		this( (double) x, (double) y );
	}

	public Point( Integer x, Integer y){
		this( x.doubleValue(), y.doubleValue() );
	}

	public Point( double x, double y){
		this.x = x;
		this.y = y;
	}

	// Returns Point location on x-axis
	public double getX(){
		return this.x;
	}

	// Returns Point location on y-axis
	public double getY(){
		return this.y;
	}

	// Returns distance to Point b in some units
	public double DistanceTo(Point b){
		return Math.sqrt(
				Math.pow( this.getX() - b.getX(), 2) +
				Math.pow( this.getY() - b.getY(), 2) );
	}

	// Object as string represenation
	@Override
	public String toString() {
		// return String.format("P@{x:%d y:%d}", this.x, this.y);
		return String.format("P{%.2f;%.2f}", this.x, this.y);
	}

	// Equals implementation.
	@Override
	public boolean equals(Object other) {

		if (! (other instanceof Point) ) {
			return false;
		}

		final Point obj = (Point) other;

		// Custom equality check here.
		return  this.getX() == obj.getX() &&
				this.getY() == obj.getY();
	}
}
