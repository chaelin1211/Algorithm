import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Main {
	public static void main(String[] args) throws IOException {
		// 땅 위에 달팽이가 있다. 이 달팽이는 높이가 V미터인 나무 막대를 올라갈 것이다.
		// 달팽이는 낮에 A미터 올라갈 수 있다. 하지만, 밤에 잠을 자는 동안 B미터 미끄러진다. 또, 정상에 올라간 후에는 미끄러지지 않는다.
		// 달팽이가 나무 막대를 모두 올라가려면, 며칠이 걸리는지 구하는 프로그램을 작성하시오.

		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

		int A, B, V;
		String input;
		input = br.readLine();

		A = Integer.parseInt(input.split(" ")[0]);
		B = Integer.parseInt(input.split(" ")[1]);
		V = Integer.parseInt(input.split(" ")[2]);

		System.out.println(function(A, B, V));
	}

	public static int function(int A, int B, int V) {
		// A: 낮에 올라갈 수 있는 높이
		// B: 자는 동안 미끄러지는 높이
		// V: 막대의 높이
		int day = 0;
		day = V / (A - B);

		int tmp = V % (A - B);

		if (tmp > B) {	// (V%(A-B) + (A-B)) > A
						// 마지막에 미끄러지기 전에 꼭대기에 도착한 경우
			day++;
		}
		
		day -= A / (A - B); // 마지막에 미끄러지는 동작을 제외시켜주기 위해 day에서 뻬줌
		return day + 1;
	}
}
