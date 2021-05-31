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
        char[][] map = new char[N][M];
        for (int i = 0; i < N; i++) {
            input = br.readLine();
            for (int j = 0; j < M; j++) {
                map[i][j] = input.charAt(j);
            }
        }
        System.out.println(Solution.solution(N, M, map));
    }
}

class Solution {
    public static Position findMarble(int N, int M, char[][] map) {
        Position pos = new Position();
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                if (map[i][j] == 'R') {
                    pos.rx = i;
                    pos.ry = j;
                } else if (map[i][j] == 'B') {
                    pos.bx = i;
                    pos.by = j;
                }
            }
        }
        return pos;
    }

    public static int[] findWhole(int N, int M, char[][] map) {
        int[] whole = new int[2];
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                if (map[i][j] == 'O') {
                    whole[0] = i;
                    whole[1] = j;
                    return whole;
                }
            }
        }
        return whole;
    }

    public static int solution(int N, int M, char[][] map) {
        int answer = 0;
        boolean[][][][] visited = new boolean[N][M][N][M];
        boolean redMarbleGoal = false;

        Queue<Position> queue = new LinkedList<Position>();
        Position pos = findMarble(N, M, map);

        queue.add(pos);
        map[pos.rx][pos.ry] = '.';
        map[pos.bx][pos.by] = '.';

        int[][] terms = { { 1, 0 }, { 0, 1 }, { -1, 0 }, { 0, -1 } };
        int sizeOfRedQueue = 1;

        while (!queue.isEmpty()) {
            if (sizeOfRedQueue == 0) {
                answer++;
                sizeOfRedQueue = queue.size();
            }
            pos = queue.remove();
            sizeOfRedQueue--;

            int rx = pos.rx;
            int ry = pos.ry;

            int bx = pos.bx;
            int by = pos.by;

            if (visited[rx][ry][bx][by]) {
                continue;
            }

            visited[rx][ry][bx][by] = true;

            if (map[rx][ry] == 'O') {
                redMarbleGoal = true;
                if (map[bx][by] == 'O') {
                    redMarbleGoal = false;
                } else {
                    break;
                }
            }

            // 구슬이 현재 위치에서 이동할 수 있는 범위 큐에 저장
            for (int[] term : terms) {
                queue.add(moveMarbles(pos, term, map));
            }
        }
        if (!redMarbleGoal || answer > 10) {
            return -1;
        }

        return answer;
    }

    public static Position moveMarbles(Position pos, int[] term, char[][] map) {
        int drx = pos.rx;
        int dry = pos.ry;
        int dbx = pos.bx;
        int dby = pos.by;
        boolean redFlag = false;
        boolean blueFlag = false;

        while (true) {
            if (!redFlag) {
                if (map[drx][dry] == 'O') {
                    redFlag = true;
                } else {
                    drx += term[0];
                    dry += term[1];
                    // 벽에 부딪힐 때 이전으로 이동
                    if (map[drx][dry] == '#') {
                        drx -= term[0];
                        dry -= term[1];
                        redFlag = true;
                    }
                    // 구슬과 구슬이 마주칠 때
                    if (drx == dbx && dry == dby) {
                        // 두 구슬이 모두 구멍에 들어간 경우 같은 좌표일 수 있음
                        // 위 경우는 제외하고 이전으로 이동
                        if (map[drx][dry] != 'O') {
                            drx -= term[0];
                            dry -= term[1];
                        }
                        redFlag = true;
                    }
                    // 빨간 구슬이 이동 후, 파란 구슬이 다시 이동할 수 있는지 확인
                    if (!redFlag && blueFlag) {
                        blueFlag = false;
                    }
                }
            }
            if (!blueFlag) {
                if (map[dbx][dby] == 'O') {
                    blueFlag = true;
                } else {
                    dbx += term[0];
                    dby += term[1];
                    // 벽에 부딪힐 때 이전으로 이동
                    if (map[dbx][dby] == '#') {
                        dbx -= term[0];
                        dby -= term[1];
                        blueFlag = true;
                    }
                    // 구슬과 구슬이 마주칠 때
                    if (drx == dbx && dry == dby) {
                        // 두 구슬이 모두 구멍에 들어간 경우 같은 좌표일 수 있음
                        // 위 경우는 제외하고 이전으로 이동
                        if (map[dbx][dby] != 'O') {
                            dbx -= term[0];
                            dby -= term[1];
                        }
                        blueFlag = true;
                    }
                    // 빨간 구슬이 이동 후, 파란 구슬이 다시 이동할 수 있는지 확인
                    if (!blueFlag && redFlag) {
                        redFlag = false;
                    }
                }
            }
            // 두 구슬 모두 정지되었을 때 종료
            if (redFlag && blueFlag) {
                break;
            }
        }
        return new Position(drx, dry, dbx, dby);
    }
}

class Position {
    int rx, ry;
    int bx, by;

    public Position() {

    }

    public Position(int rx, int ry, int bx, int by) {
        this.rx = rx;
        this.ry = ry;
        this.bx = bx;
        this.by = by;
    }
}