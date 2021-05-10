import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Stack;
import java.util.StringTokenizer;

public class Main {
    public static void main(String arg[]) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String input = br.readLine();
        int N = Integer.parseInt(input);

        StringTokenizer stk;
        int[][] arr = new int[N][N];
        for (int i = 0, j = 0; i < N; i++) {
            input = br.readLine();
            stk = new StringTokenizer(input);
            j = 0;
            while (stk.hasMoreTokens()) {
                arr[i][j++] = Integer.parseInt(stk.nextToken());
            }
        }
        System.out.println(new Solution().solution(N, arr));
    }
}

class Solution {
    int[][] terms = { { 1, 0 }, { 0, 1 }, { -1, 0 }, { 0, -1 } };

    public int solution(int N, int[][] arr) {
        int answer = 0;
        int[] range = findRange(arr);
        int min = range[0] - 1;
        int max = range[1];
        for (int i = min; i <= max; i++) {
            int tmpAnswer = DFS(i, N, arr);
            answer = answer > tmpAnswer ? answer : tmpAnswer;
        }
        return answer;
    }

    public int[] findRange(int[][] arr) {
        int min = 101, max = -1;
        for (int[] w : arr) {
            for (int n : w) {
                min = n < min ? n : min;
                max = n > max ? n : max;
            }
        }
        int[] range = { min, max };
        return range;
    }

    public int DFS(int h, int N, int[][] arr) {
        int answer = 0;
        boolean[][] flags = applyFlag(h, N, arr);
        Stack<Position> stack = settingStack(h, N, arr);
        while (!stack.isEmpty()) {
            Position tmpPosition = stack.pop();
            int x = tmpPosition.x;
            int y = tmpPosition.y;
            if (!flags[x][y]) {
                flags[x][y] = true;
                answer++;
            }
            for (int[] term : terms) {
                int tmpX = x + term[0];
                int tmpY = y + term[1];
                if (tmpX < 0 || tmpX >= N || tmpY < 0 || tmpY >= N) {
                    continue;
                }
                if (!flags[tmpX][tmpY]) {
                    stack.add(new Position(tmpX, tmpY));
                    flags[tmpX][tmpY] = true;
                }
            }
        }
        return answer;
    }

    public Stack<Position> settingStack(int h, int N, int[][] arr) {
        Stack<Position> stack = new Stack<Position>();
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (arr[i][j] > h) {
                    stack.add(new Position(i, j));
                }
            }
        }
        return stack;
    }

    public boolean[][] applyFlag(int h, int N, int[][] arr) {
        boolean[][] flags = new boolean[N][N];
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (arr[i][j] <= h) {
                    flags[i][j] = true;
                }
            }
        }
        return flags;
    }
}

class Position {
    int x, y;

    public Position(int x, int y) {
        this.x = x;
        this.y = y;
    }
}