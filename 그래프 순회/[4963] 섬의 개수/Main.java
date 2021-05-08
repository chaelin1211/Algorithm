import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Stack;
import java.util.StringTokenizer;

public class Main {
    public static void main(String arg[]) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String input = br.readLine();
        int N, M;
        int[][] arr = new int[50][50];

        StringTokenizer stk = new StringTokenizer(input);
        M = Integer.parseInt(stk.nextToken());
        N = Integer.parseInt(stk.nextToken());

        while (N != 0 && M != 0) {
            for (int i = 0; i < N; i++) {
                input = br.readLine();
                stk = new StringTokenizer(input);
                for (int j = 0; j < M; j++) {
                    arr[i][j] = Integer.parseInt(stk.nextToken());
                }
            }

            System.out.println(Solution.solution(N, M, arr));

            input = br.readLine();
            stk = new StringTokenizer(input);
            M = Integer.parseInt(stk.nextToken());
            N = Integer.parseInt(stk.nextToken());
        }
    }
}

class Solution {
    public static int solution(int N, int M, int[][] arr) {
        boolean[][] flags = new boolean[N][M];
        Stack<Position> stack = new Stack<Position>();
        int[][] terms = { { 1, 0 }, { 0, 1 }, { 1, 1 }, { -1, 0 }, { 0, -1 }, { -1, -1 }, { 1, -1 }, { -1, 1 } };
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                if (arr[i][j] == 1) {
                    stack.add(new Position(i, j));
                }
            }
        }
        int answer = 0;
        while (!stack.isEmpty()) {
            Position pos = stack.pop();
            if (!flags[pos.x][pos.y]) {
                answer++;
                flags[pos.x][pos.y] = true;
            }
            for (int[] term : terms) {
                int dx = pos.x + term[0];
                int dy = pos.y + term[1];
                if (dx < 0 || dx >= N || dy < 0 || dy >= M) {
                    continue;
                }
                if (arr[dx][dy] == 0)
                    continue;
                if (arr[dx][dy] == 1 && !flags[dx][dy]) {
                    stack.add(new Position(dx, dy));
                    flags[dx][dy] = true;
                }
            }
        }
        return answer;
    }
}

class Position {
    int x, y;

    public Position(int x, int y) {
        this.x = x;
        this.y = y;
    }
}