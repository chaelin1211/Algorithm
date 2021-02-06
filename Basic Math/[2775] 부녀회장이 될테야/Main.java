import java.io.BufferedReader;
import java.io.InputStreamReader;

public class Main {
    public static void main(String[] args) {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int T = Integer.parseInt(br.readLine());
        int k, n;

        for (int i = 0; i < T; i++) {
            k = Integer.parseInt(br.readLine());
            n = Integer.parseInt(br.readLine());

            System.out.println(function(k, n));
        }

    }

    public static int function(int k, int n) {
        // “a층의 b호에 살려면 자신의 아래(a-1)층의 1호부터 b호까지
        // 사람들의 수의 합만큼 사람들을 데려와 살아야 한다”

        // K층 n호에 몇 명이 살고 있는지!!!
        // 0층부터 있고 각 층에는 1호부터 있다.
        // 0층의 i호에는 i명이 산다.
        int[][] resident = new int[k][n+1];
        for (int i = 0; i < k; i++) {
            for (int j = 1; i < n; j++) {
                if (i == 0) {
                    resident[i][j] = j;
                } else if (j == 1) { // i != 0
                    resident[i][j] = resident[i - 1][j];
                } else {
                    resident[i][j] = resident[i][j-1] + resident[i-1][j];
                }
            }
        }
        return resident[k-1][n];
    }
}
