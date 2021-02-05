import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Main {
    public static void main(String[] args) throws NumberFormatException, IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int N = Integer.parseInt(br.readLine());

        System.out.println(function(N));
    }

    public static int function(int N) {
        int level = 1;
        if (N == 1) {
            return level;
        }

        int i = 2;
        while (true) {
            if (i <= N && N < (i += (level * 6))) {
                return level;
            } else {
                level++;
            }
        }
    }
}
