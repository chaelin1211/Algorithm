import java.io.BufferedReader;

import jdk.internal.org.jline.utils.InputStreamReader;

public class Main {
    public static void main(String[] args) {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int N = Integer.parseInt(br.readLine());

        String P = br.readLine();
        int[] arr = new int[N];
        for (int i = 0; i < N; i++) {
            arr[i] = Integer.parseInt(P.split(" ")[i]);
        }
    }
}
