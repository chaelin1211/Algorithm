import java.io.BufferedReader;

import jdk.internal.org.jline.utils.InputStreamReader;

public class Main {
    public static void main(String[] args) {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int N = Integer.parseInt(br.readLine());

        System.out.println(funtion(N));
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
