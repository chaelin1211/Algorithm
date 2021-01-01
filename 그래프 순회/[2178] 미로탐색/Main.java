import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;

public class Main {
	public static void main(String arg[]) throws NumberFormatException, IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));// 선언

		String str = br.readLine();

		int N = Integer.parseInt(str.split(" ")[0]);
		int M = Integer.parseInt(str.split(" ")[1]);

		int[][] arr = new int[N][M];
		int[][] flag = new int[N][M];

		for (int i = 0; i < N; i++) {
			str = br.readLine();
			for (int j = 0; j < M; j++) {
				arr[i][j] = str.charAt(j) - ('1' - 1);
				flag[i][j] = 0;
			}
		}
		int a = func(0, 0, N, M, arr, flag);

		bw.write(a);
		bw.flush();
	}

	public static int func(int i, int j, int N, int M, int[][] arr, int[][] flag) {
		int count = 0, tmp;
		int finalFlag = 0;

		if (i < 0 || j < 0 || i >= N || j >= M) {
			return 0;
		}
	}
}

class edge {
	int s, e;
	int flag;
	//0: 초기 상태
	//1: 방문된 상태
	
	public edge() {
		this.s = 0;
		this.e = 0;
		this.flag = 0;
	}

	public edge(int s, int e) {
		this.s = s;
		this.e = e;
		this.flag = 0;
	}
}