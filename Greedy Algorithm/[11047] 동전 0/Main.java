import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        String input = br.readLine();
        int N = Integer.parseInt(input.split(" ")[0]);
        int K = Integer.parseInt(input.split(" ")[1]);

        int[] A = new int[N];

        for (int i = 0; i < N; i++) {
            input = br.readLine();
            A[i] = Integer.parseInt(input);
        }
        System.out.println(function(K, A));
    }

    public static int function(int K, int[] A) {
        int i = A[A.length - 1];
        int count = 0;

        while (K != 0) {
            if (K < A[i]) {
                i--;
                continue;
            }
            K -= A[i];
            count++;
        }
        return count;
    }
}
