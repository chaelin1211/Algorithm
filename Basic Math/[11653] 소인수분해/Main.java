import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Main {
    public static void main(String[] args) throws NumberFormatException, IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        int N = Integer.parseInt(br.readLine());

        Factorization(N);
    }
    public static void Factorization(int N){
        if(N==1) return;
        for(int i = 2;i <= Math.sqrt(N);i++){
            while(N % i == 0){
                N /= i;
                System.out.println(i);
            }
        }
        if(N>1)
        	System.out.println(N);
    }
}
