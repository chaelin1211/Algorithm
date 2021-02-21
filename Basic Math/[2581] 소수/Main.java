import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int M, N;

        M = Integer.parseInt(br.readLine());
        N = Integer.parseInt(br.readLine());

        int sum = findSumOfPrimeNumber(M, N);
        int min = findMinPrimeNumber(M, N);

        if(min!=-1)
            System.out.println(sum);
        System.out.println(min);
    }

    public static int findMinPrimeNumber(int M, int N) {
        for (int i = M; i <= N; i++) {
            if (function(i)) {
                return i;
            }
        }
        return -1;
    }

    public static int findSumOfPrimeNumber(int M, int N){
        int sum = 0;
        for (int i = M; i <= N; i++) {
            if (function(i)) {
                sum += i;
            }
        }
        return sum;
    }

    public static boolean function(int N) {
        if (N <= 1) {
            return false;
        }
        for (int i = 2; i <= Math.sqrt(N); i++) {
            if (N % i == 0) {
                return false;
            }
        }
        return true;
    }
}
