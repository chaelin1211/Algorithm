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
        int i = 1, j = 2;
        int A =0, B=0;
        while (i < x) {
            i += j;
            j++;
        }
        A = j+1;
        B = 1;
        int tmp;
        tmp = A;
        A = B;
        B = tmp;

        while(i<x){
            i++;
            A++;
            B--;
        }
        return Integer.toString(A)+"/"+Integer.toString(B);
    }
}
