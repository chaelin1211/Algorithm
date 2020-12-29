
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;

public class Main {
	static long[] arr0 = new long[1001];

	public static void main(String arg[]) throws NumberFormatException, IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));// 선언

		int N = Integer.parseInt(br.readLine());
		long k;

		arr0[1] = 1;
		arr0[2] = 2;
		k = rfunc(N);

		bw.write(k + "\n");
		bw.flush();
	}

	// 재귀
	public static long rfunc(int N) {
		if (N == 1 || N == 2) {
			return arr0[N];
		}

		if(arr0[N-1]==0) {
			arr0[N-1] = rfunc(N-1);
		}
		if(arr0[N-2]==0) {
			arr0[N-2] = rfunc(N-2);
		}
		
		// 첫째 줄에 2×n 크기의 직사각형을 채우는 방법의 수를
		// 10,007로 나눈 나머지를 출력한다.
		return arr0[N] = (arr0[N-1] + arr0[N-2])%10007;
	}
}
