import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class Main {
    public static void main(String arg[]) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String input = br.readLine();
        StringTokenizer stk = new StringTokenizer(input);
        int R = Integer.parseInt(stk.nextToken());
        int C = Integer.parseInt(stk.nextToken());

        char[][] arr = new char[R][C];
        for (int i = 0; i < R; i++) {
            input = br.readLine();
            for (int j = 0; j < C; j++) {
                arr[i][j] = input.charAt(j);
            }
        }
        System.out.println(new Solution(R, C, arr).solution());
    }
}

class Solution {
    int[][] terms = { { 1, 0 }, { 0, 1 }, { -1, 0 }, { 0, -1 } };
    int R, C;
    char[][] arr;

    public Solution(int R, int C, char[][] arr) {
        this.R = R;
        this.C = C;
        this.arr = arr;
    }

    public int solution() {
        boolean[] alCheck = new boolean[100];
        return rDFS(0, 0, alCheck);
    }

    public int rDFS(int x, int y, boolean[] alCheck) {
        int answer = 1;

        if (!alCheck[arr[x][y]]) {
            alCheck[arr[x][y]] = true;
        }

        int max = 0;
        for (int[] term : terms) {
            int tmpX = x + term[0];
            int tmpY = y + term[1];
            if (tmpX < 0 || tmpX >= R || tmpY < 0 || tmpY >= C) {
                continue;
            }
            if (!alCheck[arr[tmpX][tmpY]]) {
                alCheck[arr[tmpX][tmpY]] = true;
                int tmp = rDFS(tmpX, tmpY, alCheck);
                alCheck[arr[tmpX][tmpY]] = false;
                max = max < tmp ? tmp : max;
            }
        }
        answer += max;
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