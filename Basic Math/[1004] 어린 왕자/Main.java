import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class Main {
    public static void main(String[] arg) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int T;
        String input = br.readLine();
        StringTokenizer stk = new StringTokenizer(input);
        T = Integer.parseInt(stk.nextToken());
        int[] s = new int[2];
        int[] e = new int[2];

        Solution sol = new Solution();
        for (int i = 0; i < T; i++) {
            input = br.readLine();
            stk = new StringTokenizer(input);
            s[0] = Integer.parseInt(stk.nextToken());
            s[1] = Integer.parseInt(stk.nextToken());
            e[0] = Integer.parseInt(stk.nextToken());
            e[1] = Integer.parseInt(stk.nextToken());

            input = br.readLine();
            stk = new StringTokenizer(input);

            int N = Integer.parseInt(stk.nextToken());
            int[][] arr = new int[N][3];
            for (int j = 0; j < N; j++) {
                input = br.readLine();
                stk = new StringTokenizer(input);
                arr[j][0] = Integer.parseInt(stk.nextToken());
                arr[j][1] = Integer.parseInt(stk.nextToken());
                arr[j][2] = Integer.parseInt(stk.nextToken());
            }
            System.out.println(sol.solution(s, e, arr));
        }

    }
}

class Solution {
    public int solution(int[] s, int[] e, int[][] arr) {
        int answer = 0;
        for (int[] circle : arr) {
            int[] pos = { circle[0], circle[1] };
            int r = circle[2];
            double disStoPos = distance(s, pos);
            double disEtoPos = distance(e, pos);
            if (disStoPos < r || disEtoPos < r) {
                if (disStoPos < r && disEtoPos < r) {
                    continue;
                }
                answer++;
            }
        }
        return answer;
    }

    public double distance(int[] s, int[] e) {
        int x = s[0] - e[0];
        int y = s[1] - e[1];
        return Math.sqrt(x * x + y * y);
    }
}

class Position {
    int x, y;

    public Position(int x, int y) {
        this.x = x;
        this.y = y;
    }
}
