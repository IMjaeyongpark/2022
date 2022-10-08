import java.util.*;

public class try_catch extends Exception {

	public try_catch(String message) {
		super(message);
	}
	

	public static void main(String[] args) {
		var sc = new Scanner(System.in);
		int cnt = 0;
		float sum = 0;
		while (cnt < 5)
			try {
				System.out.print("점수 입력:");
				String tmp = sc.next();
				float score = Float.parseFloat(tmp);
				withdraw(score);
				sum += score;
				cnt++;
			} catch (try_catch e) {
				System.out.println(e.getMessage());
			} catch (Exception e) {
				System.out.println("숫자를 입력하세요!");
			}

		System.out.println("평균 점수: " + sum / 5.0);
	}

	static void withdraw(float score) throws try_catch {
		if (score < 0 || score > 100)
			throw new try_catch("0~100사이를 입력하세요!");
	}
}
