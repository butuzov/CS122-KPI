public class Triangle {
    final private Line A, B, C;

    final double Perimeter, Square;

    public Triangle( Line A, Line B, Line C ) {

        // Equality Check
        if ( A.equals(B) || A.equals(C) || C.equals(B) ) {
            throw new IllegalArgumentException("Some of the Lines are same");
        }

        // // Connectivity Check - naive check
        if ( ! A.ConnectedTo(B) || ! A.ConnectedTo(C) || ! C.ConnectedTo(B) ) {
            throw new IllegalArgumentException(
                "Some of the Lines are not connected."
            );
        }

        this.A = A;
        this.B = B;
        this.C = C;

        this.Perimeter = calculatePerimeter();
        this.Square = calculateSquare();
    }

    public double GetPerimeter(){
        return this.Perimeter;
    }

    public double GetSquare(){
        return this.Square;
    }

    private double calculatePerimeter(){
        return this.A.length() + this.B.length() + this.C.length();
    }

    private double calculateSquare(){

        double P = calculatePerimeter();

        double HalfP = P / 2;

        return Math.sqrt( HalfP * ( HalfP - this.A.length() )
                                * ( HalfP - this.B.length() )
                                * ( HalfP - this.C.length() ) );
    }


    // Object as string represenation
    @Override
    public String toString() {
        // Points Representation
        return String.format("Triangle{%s;%s;%s}",
                            this.A.ConnectedAt(this.B),
                            this.B.ConnectedAt(this.C),
                            this.C.ConnectedAt(this.A)
        );

        // Liness Representation - more details.
        // return String.format("T{%s;%s;%s}", this.A, this.B, this.C );
    }

}
