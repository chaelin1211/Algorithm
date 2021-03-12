import java.util.Scanner;

public class Main {
    static boolean[] Array;

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int T = sc.nextInt();
        int maxNumber = -1;
        int[] testCases = new int[T];

        for (int i = 0; i < T; i++) {
            testCases[i] = sc.nextInt();
            if (maxNumber < testCases[i]) {
                maxNumber = testCases[i];
            }
        }

        Array = new boolean[maxNumber+1];
        // 최대 범위까지의 소수들 찾기
        setPrimeNumber(maxNumber);

        // 입력 받은 testcase에 대해 골드바흐 function
        for (int i = 0; i < T; i++) {
            GoldbachFunction(testCases[i]);
        }
        sc.close();
    }

    public static void setPrimeNumber(int N) {
        if (N <= 1) {
            return;
        }
        for (int i = 2; i <= N; i++) {
            Array[i] = true;
        }
        for (int i = 2; i * i <= N; i++) {
            if (Array[i]) {
                for (int j = i * i; j <= N; j += i) {
                    // 소수 아님
                    Array[j] = false;
                }
            }
        }
    }

    public static void GoldbachFunction(int N) {
        for (int i = N/2; i <=N; i++) {
            if(Array[i] && Array[N-i]){
                System.out.println((N-i)+" "+i);
                return;
            }
        }
    }
}
