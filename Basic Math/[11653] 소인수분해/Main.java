import java.io.BufferedReader;
import java.io.InputStreamReader;

public class Main {
    public static void main(String[] args) {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        int N = Integer.parseInt(br.readLine());

        Factorization(N);
    }
    public static void Factorization(int N){
        if(isPrimeNumber(N)){
            System.out.println(N);
            return;
        }
        
        int[] miniPrimes = {2, 3, 5, 7};
        for(int x: miniPrimes){
            while(N%x == 0){
                N /= x;
                System.out.println(x);
            }
        }
    }
    public static boolean isPrimeNumber(int N) {
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
