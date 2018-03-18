public class Rectangle {
	final private Line A, B, C, D;

	final double Perimeter, Square;
	public Rectangle( Line A, Line B, Line C, Line D ){

		if ( ! A.ConnectedTo(B) || ! B.ConnectedTo(C) ||
				! C.ConnectedTo(D) || ! D.ConnectedTo(A) ) {
			// To Do
			throw new IllegalArgumentException(
				"Function expects you provide your lines in order."
			);
		}

		if ( A.length() != C.length() || B.length() != D.length() ) {
			throw new IllegalArgumentException(
				"Looks like opposite edges are not same"
			);
		}

		if ( Math.sqrt( A.length()*A.length() + B.length()*B.length() ) !=
			 Math.sqrt( C.length()*C.length() + D.length()*D.length() ) ) {
			throw new IllegalArgumentException(
				"Doesn't looks like rectangular to me"
			);
		}


		this.A = A;
		this.B = B;
		this.C = C;
		this.D = D;

		// System.out.format("Line A %s - %f\n", this.A, this.A.length());
		// System.out.format("Line B %s - %f\n", this.B, this.B.length());
		// System.out.format("Line C %s - %f\n", this.C, this.C.length());
		// System.out.format("Line D %s - %f\n", this.D, this.D.length());

		this.Perimeter = Perimeter();
		this.Square = Square();
	}


	public double GetPerimeter(){
		return this.Perimeter;
	}

	public double GetSquare(){
		return this.Square;
	}

	protected double Square(){
		return this.A.length() * this.B.length();
	}

	protected double Perimeter(){
		return (this.A.length() + this.B.length() ) * 2;
	}
}
