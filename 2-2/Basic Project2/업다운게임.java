import java.util.*;

public class UpDown {
	public static void main(String[] args) {
		var sc = new Scanner(System.in);
		Random random = new Random();
		while (true) {
			int com = random.nextInt(100) + 1;
			int cnt = 0;
			int start;
			int user = 101;
			// 게임 진행
			while (user != com) {
				cnt++;
				System.out.print("1~100까지 숫자를 입력하세요:");
				user = sc.nextInt();
				if (com > user) {
					System.out.println("UP, 더 높은 숫자입니다.");
				} else if (com < user) {
					System.out.println("Down, 더 낮은 숫자입니다.");
				}
			}
			System.out.println(cnt + "번만에 정답!");
			// 재시작 선택
			while (true) {
				System.out.print("1(재시작) 0(종료):");
				start = sc.nextInt();
				if (start == 0 || start == 1)
					break;
				System.out.println("다시 입력하세요!");
			}
			if (start == 0)
				break;
		}
		System.out.print("종료");
	}
}
