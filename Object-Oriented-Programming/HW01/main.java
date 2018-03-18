public class main {
	public static void main(String[] argc){


		Rectangle r = new RectangularPointsExtruder(
			new Point(3, 3), new Point(0, 0), new Point(0, 3), new Point(3, 0)
		).Extrude();

		System.out.format("Square is %f\n", r.GetSquare());
		System.out.format("Perimeter is %f\n", r.GetPerimeter());
		// System.out.println(t.square());

		// Triangle t = new TriangularPointsExtruder(
		// 	new Point(0, 0),
		// 	new Point(0, 4),
		// 	new Point(3, 0)
		// ).Extrude();


		// System.out.println(t);
		// System.out.println(t.square());
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


