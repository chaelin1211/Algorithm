import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.LinkedList;
import java.util.Queue;
import java.util.StringTokenizer;

public class Main {
    public static void main(String[] arg) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String input = br.readLine();
        StringTokenizer stk = new StringTokenizer(input);
        int N = Integer.parseInt(stk.nextToken());
        int M = Integer.parseInt(stk.nextToken());

        int[][] arr = new int[N + 1][M + 1];
        for (int i = 1; i <= N; i++) {
            input = br.readLine();
            stk = new StringTokenizer(input);
            for (int j = 0; j < M; j++) {
                arr[i][j + 1] = input.charAt(j) - ('1' - 1);
            }
        }
        System.out.println(Solution.solution(N, M, arr));
    }
}

class Solution {
    public static int solution(int N, int M, int[][] arr) {
        int answer = 1;
        boolean[][][] visited = new boolean[N + 1][M + 1][2];

        Queue<Position> queue = new LinkedList<Position>();
        queue.add(new Position(1, 1));
        int[][] terms = { { 1, 0 }, { 0, 1 }, { -1, 0 }, { 0, -1 } };
        int sizeOfQueue = 1;

        while (!queue.isEmpty()) {
            if (sizeOfQueue == 0) {
                answer++;
                sizeOfQueue = queue.size();
            }
            Position pos = queue.remove();
            sizeOfQueue--;

            int x = pos.x;
            int y = pos.y;
            boolean isBreaked = pos.isBreaked;
            int flagIndex = 0;
            if (isBreaked)
                flagIndex = 1;

            if (visited[x][y][flagIndex]) {
                continue;
            }

            visited[x][y][flagIndex] = true;

            if (arr[x][y] == 1 && !isBreaked) {
                // 벽 부수기
                isBreaked = true;
                flagIndex = 1;
            }

            if (x == N && y == M) {
                break;
            }

            for (int[] term : terms) {
                int dx = x + term[0];
                int dy = y + term[1];

                if (dx <= 0 || dx > N || dy <= 0 || dy > M) {
                    continue;
                }
                if ((isBreaked && arr[dx][dy] == 1) || visited[dx][dy][flagIndex]) {
                    // 이전에 벽을 부순 적이 있을 때, 벽을 부술 수 없으니 1일 경우 continue
                    // 이전에 방문한 적이 있는 좌표일 떄 continue
                    continue;
                }
                queue.add(new Position(dx, dy, isBreaked));
            }
        }
        if (!visited[N][M][0] && !visited[N][M][1]) {
            // 어떤 경로로도 도달하지 못했을 때
            return -1;
        }
        return answer;
    }
}

class Position {
    int x, y;
    boolean isBreaked;

    public Position(int x, int y) {
        this.x = x;
        this.y = y;
        isBreaked = false;
    }

    public Position(int x, int y, boolean isBreaked) {
        this.x = x;
        this.y = y;
        this.isBreaked = isBreaked;
    }
}