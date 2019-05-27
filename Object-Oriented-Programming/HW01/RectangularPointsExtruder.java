import java.util.ArrayList;

public class RectangularPointsExtruder implements Extrudable<Rectangle> {
    final private Point a, b, c, d;
    private ArrayList<Point> Checked = new ArrayList<Point>();

    public RectangularPointsExtruder(Point a, Point b, Point c, Point d){
        if ( ! CanFormRectangle( a, b, c, d ) ) {
            throw new IllegalArgumentException(
                "These points can't form rectangle"
            );
        }

        PopulateCheckedInLogicOrder(a,b,c,d);

        this.a = Checked.get(0);
        this.b = Checked.get(1);
        this.c = Checked.get(2);
        this.d = Checked.get(3);
    }

    private void PopulateCheckedInLogicOrder(Point a, Point b, Point c, Point d){
        Point[] ToCheck = {a,b,c,d};

        int index = 0;

        while ( true ) {
            Line A, B, C;            // Lines to check.
            double AA, BB, CC;       // Squares
            Line C_A, C_B;           // C_ for corner

            A = new Line(ToCheck[ index ], ToCheck[ (index + 1) % 4 ]);
            AA = A.length() * A.length();

            B = new Line(ToCheck[ index ], ToCheck[ (index + 2) % 4 ]);
            BB = B.length()*B.length();

            C = new Line(ToCheck[ index ], ToCheck[ (index + 3) % 4 ]);
            CC = C.length() * C.length();

            if ( Math.sqrt(AA+BB) == C.length() ) {
                C_A = B; C_B = C;
            } else if ( Math.sqrt(AA+CC) == B.length() ) {
                C_A = A; C_B = C;
            } else {
                C_A = B; C_B = C;
            }

            // System.out.format( "Lines %s | %s\n", C_A, C_B);
            Checked.add(  C_A.ConnectedAt( C_B ) );

            Point Next = NotInChecked(
                C_A.getA().equals( Checked.get( Checked.size()-1 ) )
                    ? C_A.getB() : C_A.getA(),
                C_B.getA().equals( Checked.get( Checked.size()-1 ) )
                    ? C_B.getB() : C_B.getA()
            );

            // Return to normal thread of execution
            if ( Checked.size() == 4) {
                break;
            }

            // Checking for Next Point
            int i = 0;
            for (Point p : ToCheck ) {
                if ( p.equals( Next ) ) {
                    index = i;
                    break;
                }
                i++;
            }
        }
    }

    private Point NotInChecked( Point... Points ) {

        if ( Points.length == 0 ) {
            throw new IllegalArgumentException("Empty input not allowed");
        }
        Point next = Points[0];

        for (Point point : Points ){
            if ( ! Checked.contains(point) ) {
                next = point;
                break;
            }
        }

        return next;
    }

    private boolean CanFormRectangle(Point a, Point b, Point c, Point d){
        Point centerMass = new Point(
            ( a.getX() + b.getX() + c.getX() + d.getX() ) / 4,
            ( a.getY() + b.getY() + c.getY() + d.getY() ) / 4
        );

        double d_a, d_b, d_c, d_d;

        d_a = Math.pow(centerMass.getX() - a.getX(), 2) +
                Math.pow(centerMass.getY() - a.getY(), 2);

        d_b = Math.pow(centerMass.getX() - b.getX(), 2) +
                Math.pow(centerMass.getY() - b.getY(), 2);

        d_c = Math.pow(centerMass.getX() - c.getX(), 2) +
                Math.pow(centerMass.getY() - c.getY(), 2);

        d_d = Math.pow(centerMass.getX() - d.getX(), 2) +
                Math.pow( centerMass.getY() - d.getY(), 2);

        return d_d == d_a && d_a == d_b && d_b == d_c ;
    }

    public Rectangle Extrude() {
        return new Rectangle(
                    new Line(this.a, this.b),
                    new Line(this.b, this.c),
                    new Line(this.c, this.d),
                    new Line(this.d, this.a)
        );
    }
}
