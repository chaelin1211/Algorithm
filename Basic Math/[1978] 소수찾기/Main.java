import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Main {
	public static void main(String[] args) throws NumberFormatException, IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

		int N;
		N = Integer.parseInt(br.readLine());

		int answer = 0;
		String input = br.readLine();
		for (int i = 0; i < N; i++) {
			int intInput = Integer.parseInt(input.split(" ")[i]);
			if (function(intInput)) {
				answer++;
			}
		}
		System.out.println(answer);
		br.close();
	}

	public static boolean function(int N) {
		if (N <= 1) {
			return false;
		}
		for (int i = 2; i <= Math.sqrt(N); i++) {
			if(N%i==0) {
				return false;
			}
		}
		return true;
	}
}
