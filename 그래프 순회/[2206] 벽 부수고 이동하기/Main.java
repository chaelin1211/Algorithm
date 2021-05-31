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
	public static int solution(int N, int M, char[][] map) {
//		BFS 수행
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

			if (map[rx][ry] == 'O' && map[bx][by] != 'O') {
				redMarbleGoal = true;
				break;
			}
			if (map[bx][by] == 'O') {
				redMarbleGoal = false;
				continue;
			}

//			구슬이 현재 위치에서 이동할 수 있는 범위 큐에 저장
			for (int[] term : terms) {
				queue.add(moveMarbles(pos, term, map));
			}
		}
		if (!redMarbleGoal || answer > 10) {
			return -1;
		}

		return answer;
	}

	public static Position findMarble(int N, int M, char[][] map) {
//		구슬들의 위치를 찾아 Position 객체에 담아 리턴
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

	public static Position moveMarbles(Position pos, int[] term, char[][] map) {
//		빨간 구슬과 파란 구슬을 이동시킨다

		int drx, dry, dbx, dby;
//		빨간 구슬 이동
		int[] position = moveMarble(pos.rx, pos.ry, term, map);
		drx = position[0];
		dry = position[1];

//		파란 구슬 이동
		position = moveMarble(pos.bx, pos.by, term, map);
		dbx = position[0];
		dby = position[1];

//		구슬과 구슬이 마주칠 때
		if (drx == dbx && dry == dby) {
//			두 구슬이 구멍에 들어간 경우 제외
//			원래 뒤에 있던 구슬을 다른 구슬 뒤로 이동
			if (map[drx][dry] != 'O' && map[dbx][dby] != 'O') {
//				각 구슬 이동한 거리 구하기
				int rCount = Math.max(Math.abs(drx - pos.rx), Math.abs(dry - pos.ry));
				int bCount = Math.max(Math.abs(dbx - pos.bx), Math.abs(dby - pos.by));
				if (rCount < bCount) {
					dbx -= term[0];
					dby -= term[1];
				} else {
					drx -= term[0];
					dry -= term[1];
				}
			}
		}
		return new Position(drx, dry, dbx, dby);
	}

	public static int[] moveMarble(int x, int y, int[] term, char[][] map) {
//		한 구슬을 이동시킨다.

		boolean flag = false;
		int dx = x;
		int dy = y;

		while (!flag) {
			dx += term[0];
			dy += term[1];
//			벽이나 구멍을 만나기 전까지 이동
			if (map[dx][dy] != '.') {
				if (map[dx][dy] == '#') {
//					벽과 좌표가 같아지면 뒤로 이동
					dx -= term[0];
					dy -= term[1];
				}
				flag = true;
			}
		}

		int[] position = new int[2];
		position[0] = dx;
		position[1] = dy;

		return position;
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