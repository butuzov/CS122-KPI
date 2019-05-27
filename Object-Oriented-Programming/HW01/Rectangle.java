import java.util.ArrayList;
import java.util.HashMap;

public class Rectangle {
    final private Line A, B, C, D;

    final double Perimeter, Square;
    public Rectangle( Line A, Line B, Line C, Line D ){

        if ( ! LinesCanFormRectangle( A, B, C, D ) ){
            throw new IllegalArgumentException(
                "This lines can't form rectangle"
            );
        }

        this.A = A;
        this.B = B;
        this.C = C;
        this.D = D;

        this.Perimeter = Perimeter();
        this.Square = Square();
    }

    private boolean LinesCanFormRectangle(Line A, Line B, Line C, Line D ){
        if ( ! A.ConnectedTo(B) || ! B.ConnectedTo(C) ||
              ! C.ConnectedTo(D) || ! D.ConnectedTo(A) ) {
            throw new IllegalArgumentException(
                "Function expects you provide your lines in order."
            );
            // return false;
        }

        if ( A.length() != C.length() || B.length() != D.length() ) {
            throw new IllegalArgumentException(
                "Looks like opposite edges are not same"
            );
            // return false;
        }

        if ( Math.sqrt( A.length()*A.length() + B.length()*B.length() ) !=
            Math.sqrt( C.length()*C.length() + D.length()*D.length() ) ) {
            throw new IllegalArgumentException(
                "Doesn't looks like rectangular to me"
            );
            // return false;
        }

        // still need to check connection in each point.
        HashMap<String, Integer> map = new HashMap<String, Integer>();

        for (Line l: (new Line[] {A, B, C, D}) )  {
            for (Point point: (new Point[] { l.getA(), l.getB() })){
                String key = point.toString();
                if ( ! map.containsKey( key ) ) {
                    map.put(key, 1);
                } else {
                    map.replace(key, (map.get(key) + 1) );
                }
            }
        }

        for ( Integer i : map.values() ){
            if ( i != 2 ) {
                System.out.println(map);
                return false;
            }
        }

        return true;
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

    // Object as string represenation
    @Override
    public String toString() {
        // Points Representation
        return String.format("Rectangle{}");

        // Liness Representation - more details.
        // return String.format("T{%s;%s;%s}", this.A, this.B, this.C );
    }
}
