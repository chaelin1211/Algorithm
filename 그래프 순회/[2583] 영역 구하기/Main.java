import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Stack;
import java.util.StringTokenizer;

public class Main {
    public static void main(String[] arg) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String input = br.readLine();
        StringTokenizer stk = new StringTokenizer(input);
        int M = Integer.parseInt(stk.nextToken());
        int N = Integer.parseInt(stk.nextToken());
        int K = Integer.parseInt(stk.nextToken());
        Solution sol = new Solution(M, N);
        int[][] arr = new int[K][4];
        for (int i = 0; i < K; i++) {
            input = br.readLine();
            stk = new StringTokenizer(input);
            int j = 0;
            while (stk.hasMoreTokens()) {
                arr[i][j++] = Integer.parseInt(stk.nextToken());
            }
        }
        sol.solution(arr);
    }
}

class Solution {
    int N, M;
    boolean[][] place;

    public Solution(int M, int N) {
        this.M = M;
        this.N = N;
        place = new boolean[N][M];
    }

    public void setBlock(int lx, int ly, int rx, int ry) {
        for (int j = ly; j < ry; j++) {
            for (int i = lx; i < rx; i++) {
                place[i][j] = true;
            }
        }
    }

    public void solution(int[][] arr) {
        for (int[] position : arr) {
            int lx = position[0];
            int ly = position[1];
            int rx = position[2];
            int ry = position[3];
            setBlock(lx, ly, rx, ry);
        }

        ArrayList<Integer> areas = DFS();
        System.out.println(areas.size());
        for (int x : areas) {
            System.out.print(x + " ");
        }
    }

    public ArrayList<Integer> DFS() {
        Stack<Position> stack = new Stack<Position>();

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                if (!place[i][j]) {
                    stack.add(new Position(i, j));
                }
            }
        }

        int[][] terms = { { 1, 0 }, { 0, 1 }, { -1, 0 }, { 0, -1 } };
        ArrayList<Integer> areas = new ArrayList<Integer>();
        int area = 0;
        while (!stack.isEmpty()) {
            Position tmpPosition = stack.pop();
            int x = tmpPosition.x;
            int y = tmpPosition.y;
            if (!place[x][y]) {
                if (area != 0) {
                    areas.add(area);
                    area = 0;
                }
                area++;
                place[x][y] = true;
            }
            for (int[] term : terms) {
                int dx = x + term[0];
                int dy = y + term[1];
                if (dx < 0 || dx >= N || dy < 0 || dy >= M || place[dx][dy]) {
                    continue;
                }
                if (!place[dx][dy]) {
                    place[dx][dy] = true;
                    area++;
                    stack.add(new Position(dx, dy));
                }

            }
        }
        if (area != 0) {
            areas.add(area);
        }

        areas.sort(null);
        return areas;
    }
}

class Position {
    int x, y;

    public Position(int x, int y) {
        this.x = x;
        this.y = y;
    }
}