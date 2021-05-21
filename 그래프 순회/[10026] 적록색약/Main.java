import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Stack;
import java.util.StringTokenizer;

public class Main {
    public static void main(String[] arg) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int N;
        String input = br.readLine();
        StringTokenizer stk = new StringTokenizer(input);

        N = Integer.parseInt(stk.nextToken());
        char[][] arr = new char[N][N];

        for (int i = 0; i < N; i++) {
            input = br.readLine();
            for (int j = 0; j < N; j++) {
                arr[i][j] = input.charAt(j);
            }
        }

        Solution sol = new Solution(N, arr);
        sol.solution();
    }
}

class Solution {
    int N;
    char[][] arr;

    public Solution(int N, char[][] arr) {
        this.N = N;
        this.arr = arr;
    }

    public void solution() {
        Stack<Position> stack = new Stack<Position>();
        Stack<Position> copyStack = new Stack<Position>();
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                stack.add(new Position(i, j));
            }
        }
        System.out.print(DFS01((Stack<Position>) stack.clone()) + " " + DFS02((Stack<Position>) stack.clone()));

    }

    public int DFS01(Stack<Position> stack) {
        int answer = 0;
        boolean[][] flags = new boolean[N][N];
        int[][] terms = { { 1, 0 }, { 0, 1 }, { 0, -1 }, { -1, 0 } };
        int sizeOfBlock = 0;
        while (!stack.isEmpty()) {
            Position pos = stack.pop();
            sizeOfBlock--;
            int x = pos.x;
            int y = pos.y;
            if (flags[x][y]) {
                continue;
            }
            if (sizeOfBlock < 0) {
                sizeOfBlock = 0;
                answer++;
            }
            flags[x][y] = true;
            for (int[] term : terms) {
                int dx = x + term[0];
                int dy = y + term[1];
                if (dx < 0 || dx >= N || dy < 0 || dy >= N) {
                    continue;
                }

                if (arr[dx][dy] == arr[x][y] && !flags[dx][dy]) {
                    stack.add(new Position(dx, dy));
                    sizeOfBlock++;
                }
            }
        }
        return answer;
    }

    public int DFS02(Stack<Position> stack) {
        int answer = 0;
        boolean[][] flags = new boolean[N][N];
        int[][] terms = { { 1, 0 }, { 0, 1 }, { 0, -1 }, { -1, 0 } };
        int sizeOfBlock = 0;
        while (!stack.isEmpty()) {
            Position pos = stack.pop();
            sizeOfBlock--;
            int x = pos.x;
            int y = pos.y;
            if (flags[x][y]) {
                continue;
            }
            if (sizeOfBlock < 0) {
                sizeOfBlock = 0;
                answer++;
            }
            flags[x][y] = true;
            for (int[] term : terms) {
                int dx = x + term[0];
                int dy = y + term[1];
                if ((dx < 0 || dx >= N || dy < 0 || dy >= N) || flags[dx][dy]) {
                    continue;
                }

                if (arr[dx][dy] == arr[x][y] || Math.abs(arr[dx][dy] - arr[x][y]) == ('R' - 'G')) {
                    stack.add(new Position(dx, dy));
                    sizeOfBlock++;
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
