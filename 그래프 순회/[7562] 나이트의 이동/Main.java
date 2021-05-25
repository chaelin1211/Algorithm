import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.LinkedList;
import java.util.Queue;

public class Main {
    public static void main(String[] arg) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String input;

        int T = Integer.parseInt(br.readLine());
        for (int i = 0; i < T; i++) {
            int l = Integer.parseInt(br.readLine());
            int x1, y1, x2, y2;
            input = br.readLine();
            x1 = Integer.parseInt(input.split(" ")[0]);
            y1 = Integer.parseInt(input.split(" ")[1]);

            input = br.readLine();
            x2 = Integer.parseInt(input.split(" ")[0]);
            y2 = Integer.parseInt(input.split(" ")[1]);
            System.out.println(Solution.solution(l, x1, y1, x2, y2));
        }

    }
}

class Solution {
    public static int solution(int l, int x1, int y1, int x2, int y2) {
        int answer = 0;
        int[][] terms = { { -2, 1 }, { -2, -1 }, { 2, -1 }, { 2, 1 }, { -1, 2 }, { -1, -2 }, { 1, 2 }, { 1, -2 } };
        boolean[][] flags = new boolean[l][l];
        Queue<Position> queue = new LinkedList<Position>();
        queue.add(new Position(x1, y1));
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

            if (flags[x][y]) {
                continue;
            }
            flags[x][y] = true;
            if (x == x2 && y == y2) {
                return answer;
            }

            for (int[] term : terms) {
                int dx = x + term[0];
                int dy = y + term[1];

                if (dx < 0 || dx >= l || dy < 0 || dy >= l) {
                    continue;
                }

                queue.add(new Position(dx, dy));
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