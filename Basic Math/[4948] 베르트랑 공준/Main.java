import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int N = sc.nextInt();;
        while(N!=0){
            System.out.println(findPrimeNumbers(N));
            N = sc.nextInt();
        }
        sc.close();
    }
    public static int findPrimeNumbers(int N) {
        int ans = 0;
		boolean[] Array = new boolean[2*N+1];
		for (int i = 2; i <= 2 * N; i++) {
			Array[i] = true;
		}
		for (int i = 2; i * i <= 2 * N; i++) {
			if (Array[i]) {
				for (int j = i * i; j <= 2 * N; j += i) {
					Array[j] = false;
				}
			}
		}
		for (int i = N+1; i <= 2 * N; i++) {
			if (Array[i]) {
				ans ++;
			}
		}
        return ans;
	}
}
