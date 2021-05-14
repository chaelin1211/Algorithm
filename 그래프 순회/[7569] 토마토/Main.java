import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.LinkedList;
import java.util.Queue;
import java.util.StringTokenizer;

public class Main {
    public static void main(String[] arg) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int M, N, H;
        String input = br.readLine();
        StringTokenizer stk = new StringTokenizer(input);
        M = Integer.parseInt(stk.nextToken());
        N = Integer.parseInt(stk.nextToken());
        H = Integer.parseInt(stk.nextToken());
        int[][][] arr = new int[H][N][M];

        for (int i = 0; i < H; i++) {
            for (int j = 0; j < N; j++) {
                input = br.readLine();
                stk = new StringTokenizer(input);
                for (int k = 0; k < M; k++) {
                    arr[i][j][k] = Integer.parseInt(stk.nextToken());
                }
            }
        }

        Solution sol = new Solution(M, N, H, arr);
        System.out.println(sol.solution());
    }
}

class Solution {
    int M, N, H;
    int[][][] arr;

    public Solution(int M, int N, int H, int[][][] arr) {
        this.M = M;
        this.N = N;
        this.H = H;
        this.arr = arr;
    }

    public int solution() {
        int answer = 0;
        int zero = 0;
        Queue<Position> queue = new LinkedList<Position>();
        for (int i = 0; i < H; i++) {
            for (int j = 0; j < N; j++) {
                for (int k = 0; k < M; k++) {
                    if (arr[i][j][k] == 1) {
                        queue.add(new Position(k, j, i));
                    }
                    if (arr[i][j][k] == 0) {
                        zero++;
                    }
                }
            }
        }
        int[][] terms = { { 0, 0, 1 }, { 0, 0, -1 }, { 0, 1, 0 }, { 0, -1, 0 }, { 1, 0, 0 }, { -1, 0, 0 } };
        int dayTomato = queue.size();

        while (!queue.isEmpty()) {
            if (dayTomato == 0) {
                answer++;
                dayTomato = queue.size();
            }
            Position tmpPosition = queue.remove();
            dayTomato--;
            for (int[] term : terms) {
                int dx = tmpPosition.x + term[0];
                int dy = tmpPosition.y + term[1];
                int dz = tmpPosition.z + term[2];
                if (dx < 0 || dx >= M || dy < 0 || dy >= N | dz < 0 || dz >= H) {
                    continue;
                }
                if (arr[dz][dy][dx] == 1 || arr[dz][dy][dx] == -1)
                    continue;
                arr[dz][dy][dx] = 1;
                zero--;
                queue.add(new Position(dx, dy, dz));
            }
        }
        if (zero != 0) {
            answer = -1;
        }
        return answer;
    }
}

class Position {
    int x, y, z;

    public Position(int x, int y, int z) {
        this.x = x;
        this.y = y;
        this.z = z;
    }
}