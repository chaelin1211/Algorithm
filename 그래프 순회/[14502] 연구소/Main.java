import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Queue;
import java.util.StringTokenizer;

public class Main {
    static int MAX = 0;

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String input = br.readLine();
        StringTokenizer stk = new StringTokenizer(input);

        int N, M;
        N = Integer.parseInt(stk.nextToken());
        M = Integer.parseInt(stk.nextToken());
        int[][] lab = new int[N][M];

        for (int i = 0; i < N; i++) {
            input = br.readLine();
            stk = new StringTokenizer(input);
            int j = 0;
            while (stk.hasMoreTokens()) {
                lab[i][j++] = Integer.parseInt(stk.nextToken());
            }
        }

        Solution solution = new Solution(N, M, lab);
        System.out.println(solution.makeWall());
    }
}

class Solution {
    int max = 0;
    int N, M;
    int[][] lab;

    public Solution(int N, int M, int[][] lab) {
        this.N = N;
        this.M = M;
        this.lab = lab;
    }

    public int makeWall() {
        return this.makeWall(0);
    }

    public int makeWall(int count) {
        int tmp;
        if (count == 3) {
            tmp = BFS();
            if (max < tmp) {
                max = tmp;
            }
        } else {
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < M; j++) {
                    if (lab[i][j] == 0) {
                        lab[i][j] = 1;
                        tmp = makeWall(count + 1);
                        lab[i][j] = 0;
                    }
                }
            }
        }
        return max;
    }

    public int BFS() {
        int[] dx = { 1, -1, 0, 0 };
        int[] dy = { 0, 0, 1, -1 };

        Queue<Position> queue = new LinkedList<Position>();
        int safeZone = 0;

        int[][] copyLab = new int[N][M];

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                copyLab[i][j] = lab[i][j];
                if (lab[i][j] == 0) {
                    safeZone++;
                } else if (lab[i][j] == 2) {
                    queue.add(new Position(i, j));
                }
            }
        }

        while (!queue.isEmpty()) {
            Position p = queue.remove();
            for (int i = 0; i < 4; i++) {
                int px = p.x + dx[i];
                int py = p.y + dy[i];
                if (px < 0 || px >= N || py < 0 || py >= M) {
                    continue;
                }
                if (copyLab[px][py] != 0) {
                    continue;
                }
                copyLab[px][py] = 2;
                queue.add(new Position(px, py));
                safeZone--;
            }
        }
        return safeZone;
    }
}

class Position {
    int x, y;

    public Position(int x, int y) {
        this.x = x;
        this.y = y;
    }
}