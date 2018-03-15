public class Triangle implements Squarable {
	private final Line A;
	private final Line B;
	private final Line C;

	private final double square;

	public Triangle(Point a, Point b, Point c){
		this( new Line(a, b), new Line(b, c), new Line(c, a) );
	}

	public Triangle(Line A, Line B, Line C){

		// Equality Check
		if ( A.equals(B) || A.equals(C) || C.equals(B) ) {
			throw new IllegalArgumentException("Some of the Lines are same");
		}

		// Connectivity Check - naive check
		if ( ! A.IsConnectedTo(B) || ! A.IsConnectedTo(C) || ! C.IsConnectedTo(B) ) {
			throw new IllegalArgumentException("Some of the Lines are not connected.");
		}

		// // The only case not covered is /|\ when lines starts in same point.
		Point ConnectedB = A.ConnectedAt(B);
		Point ConnectedC = A.ConnectedAt(C);
		if ( ConnectedB.equals(ConnectedC) ) {
			throw new IllegalArgumentException("Shared Connection Points");
		}

		this.A = A;
		this.B = B;
		this.C = C;

		this.square = square();
	}

	public double square(){
		double P = this.A.length() + this.B.length() + this.C.length();

		double HalfP = P / 2;

		return Math.sqrt( HalfP * ( HalfP - this.A.length() )
								* ( HalfP - this.B.length() )
								* ( HalfP - this.C.length() ) );
	}


	// Object as string represenation
	@Override
	public String toString() {
		return String.format("Triangualr(%s:%s:%s)",
							this.A.ConnectedAt(this.B),
							this.B.ConnectedAt(this.C),
							this.C.ConnectedAt(this.A)
		);
	}


}
