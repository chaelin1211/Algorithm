import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Main {
	public static void main(String[] args) throws IOException {
		int N, M;

		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

		String input = br.readLine();

		M = Integer.parseInt(input.split(" ")[0]);
		N = Integer.parseInt(input.split(" ")[1]);

		findPrimeNumbers(M, N);
	}

	public static void findPrimeNumbers(int M, int N) {
		if (N <= 1) {
			return;
		}
		boolean[] Array = new boolean[N + 1];
		for (int i = 2; i <= N; i++) {
			Array[i] = true;
		}
		for (int i = 2; i * i <= N; i++) {
			if (Array[i]) {
				for (int j = i * i; j <= N; j += i) {
					Array[j] = false;
				}
			}
		}
		for (int i = M; i <= N; i++) {
			if (Array[i]) {
				System.out.println(i);
			}
		}
	}
}
