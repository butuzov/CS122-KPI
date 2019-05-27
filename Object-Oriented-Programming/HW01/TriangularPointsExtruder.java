public class TriangularPointsExtruder implements Extrudable<Triangle> {
	final private Point a, b, c;

	public TriangularPointsExtruder(Point a, Point b, Point c){

		// All we need to check before passing three points as
		// lines to  Triangle class in order to create Trianlge
		// is to check do they lay on same line or not.

		double Summ = a.getX() * ( b.getY() - c.getY() )
					+ b.getX() * ( c.getY() - a.getY() )
					+ c.getX() * ( a.getY() - b.getY() );

		if ( Summ == 0.0d ){
			throw new ArithmeticException("This Points lays on same line.");
		}

		this.a = a;
		this.b = b;
		this.c = c;
	}

	public Triangle Extrude() {
		return new Triangle(
			new Line(this.a, this.b),
			new Line(this.b, this.c),
			new Line(this.c, this.a)
		);
	}
}
