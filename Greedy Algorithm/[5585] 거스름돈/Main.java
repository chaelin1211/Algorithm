import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Main {
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

		String input = br.readLine();
		int N = Integer.parseInt(input.split(" ")[0]);

		System.out.println(function(N));
	}

	public static int function(int N) {
		int[] coins = { 500, 100, 50, 10, 5, 1 };
		int i = 0;
		int count = 0;
		N = 1000 - N;
		while (N > 0) {
			if (N >= coins[i]) {
				N -= coins[i];
				count++;
			} else {
				i++;
			}
		}
		return count;
	}
}
