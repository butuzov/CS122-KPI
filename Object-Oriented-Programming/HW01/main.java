public class main {
    public static void main(String[] argc){

        printHeader("Rectangle by Points");
        Rectangle r1 = new RectangularPointsExtruder(
            new Point(3, 3), new Point(0, 0), new Point(0, 3), new Point(3, 0)
        ).Extrude();
        System.out.format("Square is %f\n", r1.GetSquare());
        System.out.format("Perimeter is %f\n", r1.GetPerimeter());

        printHeader("Rectangle by Lines");
        Rectangle r2 = new Rectangle(
            new Line(new Point(3, 3), new Point(0, 3)),
            new Line(new Point(0, 3), new Point(0, 0)),
            new Line(new Point(0, 0), new Point(3, 0)),
            new Line(new Point(3, 0), new Point(3, 3))
        );
        System.out.format("Square of %s is %f\n", r2, r2.GetSquare());
        System.out.format("Perimeter of %s is %f\n", r2, r2.GetPerimeter());


        printHeader("Triangle by Points");
        Triangle tp = new TriangularPointsExtruder(
            new Point(0, 0),
            new Point(0, 4),
            new Point(3, 0)
        ).Extrude();

        System.out.format("Square of %s is %f\n", tp, tp.GetSquare());
        System.out.format("Perimeter of %s is %f\n", tp, tp.GetPerimeter());


        printHeader("Triangle by Points");
        Triangle tl = new Triangle(
            new Line(new Point(1, 1), new Point(500, 16)),
            new Line(new Point(500, 16), new Point(100, 500)),
            new Line(new Point(100, 500), new Point(1, 1))
        );

        System.out.format("Square of %s is %f\n", tl, tl.GetSquare());
        System.out.format("Perimeter of %s is %f\n", tl, tl.GetPerimeter());
    }

    static void printHeader( String message ){
        System.out.println("// ***************************************");
        System.out.format( "//    %s  \n", message );
        System.out.println("// ***************************************");

    }

    // Assertion
    private static void Assert(boolean expectedTrueResult, String message){
        if (expectedTrueResult != true ){
            Throwable t = new Throwable(message);
            t.printStackTrace();
            System.exit(1);
        }
    }
}


