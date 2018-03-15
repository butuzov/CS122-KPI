public class main {
	public static void main(String[] args){

		RunAllTests();
		Point a, b, c;

		a = new Point(-3, 5) ;
		b = new Point(-3,-3) ;
		c = new Point(3,-3) ;

		System.out.printf("Distance betwen a and b is %s\n", a.DistanceTo(b));
		System.out.printf("Distance betwen b and c is %s\n", b.DistanceTo(c));
		System.out.printf("Distance betwen c and a is %s\n", c.DistanceTo(a));

		Line line1 = new Line(a, c);
		System.out.printf("Line %s Length %f\n", line1, line1.length());


		Triangle tr_p, tr_lines;

		tr_p = new Triangle( new Point(0, 4), new Point(3, 0), new Point(0, 0));

		System.out.printf("%s Square %f", tr_p, tr_p.square());

	}



	// Assertion
	private static void Assert(boolean expectedTrueResult, String message){
		if (expectedTrueResult != true ){
			Throwable t = new Throwable(message);
			t.printStackTrace();
			System.exit(1);
		}
	}


	public static void RunAllTests(){
		// JUnit fail to work. Sorry.
		TestPoints();
		TestLines();
	}

	public static void TestLines(){
		Line l1, l2, l3, l4, l5;

		l1 = new Line(new Point(1, 2), new Point(10, 11));
		l2 = new Line(new Point(1, 2), new Point(10, 11));

		l3 = new Line(new Point(10, 11), new Point(1, 2));
		l4 = new Line(new Point(1, 2), new Point(10, 10));
		l5 = new Line(new Point(11, 21), new Point(9, 9));
		// System.out.printf("Line %s Length %f\n", l2, l2.length());
		// System.out.printf("Line %s Length %f\n", l3, l3.length());


		// Equality

		Assert( l1.equals(l2),
			String.format("Line_Equality_Fail: %s & %s (Expected to be Equal)", l1, l2));


		Assert( l2.equals(l3),
			String.format("Line_Equality_Fail: %s & %s (Expected to be Equal)", l2, l3));

		Assert( ! l2.equals(l4),
			String.format("Line_Not_Equality_Fail: %s & %s (Expected to be NonEqual)", l2, l4));

		// Connection Checks.

		Assert( l3.IsConnectedTo(l4),
			String.format("Line_Connected_Fail: %s & %s (Expected to be Connected)", l3, l4));

		Assert( ! l5.IsConnectedTo(l4),
			String.format("Line_Connected_Fail: %s & %s (Expected to be Non Connected)", l5, l4));

		Line lc1, lc2, lc3;

		// Common Connection Point
		lc1 = new Line(new Point(1, 2), new Point(10, 11));
		lc2 = new Line(new Point(1, 2), new Point(10, 12));

		// Unconnected
		lc3 = new Line(new Point(10, 3), new Point(-19, 43));

		// Test 1 - Lines are connected
		try {
			// Comparing Connection at 1,2
			Point Connected = lc1.ConnectedAt(lc2);
			Point Actual = new Point(1, 2);
			Assert( Connected.equals(Actual),
				String.format("Connection_Point_in_Lines_Error Line_A %s, Line_B %s; Expected %s, Returned %s", lc1, lc2, Actual, Connected));

		} catch (IllegalArgumentException iae) {

			Point Actual = new Point(1, 2);
			Assert( false,
				String.format("Connection_Point_in_Lines_Error Line_A %s, Line_B %s; Expected %s, Returned %s", lc1, lc2, Actual, "none"));
		}

		// Test 2 - Lines are not connected
		try {
			// Comparing Connection at 1,2
			Point Connected = lc1.ConnectedAt(lc3);
			Assert( false,
				String.format("Connection_Point_in_Lines_Error Line_A %s, Line_B %s are not suppose to be connected. Exceptions expected.", lc1, lc2));

		} catch (IllegalArgumentException iae) {
			// todo bien! =)
		}

	}

	public static void TestPoints(){
		Point a = new Point(-3, 5);
		Point b = new Point(-3,-3);
		double ab = a.DistanceTo(b);
		double ba = b.DistanceTo(a);
		double Expected = 8.0d;

		Assert( Expected == ab,
			String.format("Point_Distance_Between: %s & %s (Expected %s vs Returned %s)", a, b, Expected, ab));

		Assert( ba == ab,
			String.format("Point_Distance_Compare: %s & %s (BA %s vs AB %s)", a, b, ba, ab));

		Assert( ! a.equals(b) ,
			String.format("Point_Equality_Fail: %s & %s (Equality Expectations %b)", a, b, false));

		Point a2 = new Point(-3, 5);
		Assert( a.equals(a2) ,
			String.format("Point_Equality_Fail: %s & %s (Equality Expectations %b)", a, a2, true));


	}



}
