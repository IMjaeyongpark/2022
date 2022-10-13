import java.util.Scanner;

class Test<T> {

	private T a;
	private T b;

	public T getA() {
		return a;
	}

	public void setA(T a) {
		this.a = a;
	}

	public T getB() {
		return b;
	}

	public void setB(T b) {
		this.b = b;
	}
}

public class Main {

	public static void main(String[] ags) {

		var sc = new Scanner(System.in);
		Test<String> test1 = new Test<String>();
		test1.setA(sc.next());
		System.out.println(test1.getA());
		Test<Integer> test2 = new Test<Integer>();
		test2.setA(2);
		System.out.println(test2.getA());
	}
}
