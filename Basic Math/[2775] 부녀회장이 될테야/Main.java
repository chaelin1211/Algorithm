import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Main {
    public static void main(String[] args) throws NumberFormatException, IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int T = Integer.parseInt(br.readLine());

        int[][] testCase = new int[T][2];
        int maxK = 0, maxN = 0;
        int k, n;
        for (int i = 0; i < T; i++) {
            k = Integer.parseInt(br.readLine());
            n = Integer.parseInt(br.readLine());

            if (k > maxK) {
                maxK = k;
            }
            if (n > maxN) {
                maxN = n;
            }

            testCase[i][0] = k;
            testCase[i][1] = n;
        }
        int[][] resid = new int[maxK + 1][maxN + 1];
        for (int i = 0; i < T; i++) {
            k = testCase[i][0];
            n = testCase[i][1];
            System.out.println(function(resid, k, n));
        }

    }

    public static int function(int [][]resident, int k, int n) {
        // “a층의 b호에 살려면 자신의 아래(a-1)층의 1호부터 b호까지
        // 사람들의 수의 합만큼 사람들을 데려와 살아야 한다”

        // K층 n호에 몇 명이 살고 있는지!!!
        // 0층부터 있고 각 층에는 1호부터 있다.
        // 0층의 i호에는 i명이 산다.
        if(n == 0){     // 1호부터 있으니 제외
            return 0;
        }
        if(resident[k][n] == 0){
            if(k == 0){
                resident[k][n] = n;
            } 
            else{
                resident[k][n] = function(resident, k-1, n) + function(resident, k, n-1);
            }
        }
        return resident[k][n];
    }
}
