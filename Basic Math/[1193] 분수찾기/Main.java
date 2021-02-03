import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Main {
	public static void main(String[] args) throws NumberFormatException, IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

		// X(1 ≤ X ≤ 10,000,000)
		int x;
		x = Integer.parseInt(br.readLine());
		// 1 1/1
		// 1+2 3 2/1
		// 1+2+3 6 3/1
		// 1+2+3+4 10 4/1
		System.out.println(findNumber(x));
	}

	public static String findNumber(int x) {
		int i = 1, j = 1;
		int A = 0, B = 0;
		int flag = -1;

        // 포함되는 열의 앞부분을 먼저 찾아 수행시간을 줄임
		while (i + j < x) {
			j++;
			i += j;
			flag *= -1;
		}
        
		if (flag == 1) {
			A = j;
			B = 1;
		} else {
			A = 1;
			B = j;
		}

		while (i < x) {
			i++;
			A += flag;
			B -= flag;
			if (A <= 0) {
				A = 1;
				flag *= -1;
			}
			if (B <= 0) {
				B = 1;
				flag *= -1;
			}
        }
        
		return Integer.toString(A) + "/" + Integer.toString(B);
	}
}
