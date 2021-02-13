import java.io.BufferedReader;

import jdk.internal.org.jline.utils.InputStreamReader;

public class Main {
    public static void main(String[] args) {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        int N;
        N = Integer.parseInt(br.readLine());

        int answer = 0;
        String input = br.readLine();
        for (int i = 0; i < N; i++) {
            int intInput = Integer.parseInt(input.split(" ")[i]);
            if (function(intInput)) {
                answer++;
            }
        }
    }

    public static boolean function(int N) {
        if (N == 1 || N == 2 || N == 3 || N == 5 || N == 7) {
            return true;
        }
        if (N % 2 != 0 && N % 3 != 0 && N % 5 != 0 && N % 7 != 0) {
            return true;
        }
        return false;
    }
}
