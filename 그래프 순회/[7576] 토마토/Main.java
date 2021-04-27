
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.LinkedList;
import java.util.Queue;
import java.util.StringTokenizer;

public class Main {
	public static void main(String[] args) {
		int[][] arr = {{0,0,0,0,0,0},{0,0,0,0,0,0},{0,0,0,0,0,0},{0,0,0,0,0,1}};
		solution(6, 4, arr);
	}

	public static void solution(int N, int M, int[][] arr) {
		Queue<Location> queue = new LinkedList<Location>();
		int todayTomato = 0; 		// 당일에 존재하는 익은 토마토 수
		int entireTomato = N * M; 	// 전체 토마토 수
		int completeTomato = 0; 	// 익은 토마토 수
		int day = 0; 				// 날짜
		for (int i = 0; i < M; i++) {
			for (int j = 0; j < N; j++) {
				if (arr[i][j] == 1) {
					queue.add(new Location(i, j));
					todayTomato++;
				} else if (arr[i][j] == -1) {
					entireTomato--;
				}
			}
		}

		completeTomato = todayTomato;

		while (!queue.isEmpty()) {
			if (todayTomato == 0) {
				todayTomato = queue.size();
				day++;
	//			System.out.println("day"+day+"-------------");
	//			for (int i = 0; i < M; i++) {
	//				for (int j = 0; j < N; j++) {
	//					System.out.print(arr[i][j] + " ");
	//				}
	//				System.out.println("");
	//			}
				}

			todayTomato--;

			Location tmp = queue.remove();
			int tmpI, tmpJ;
			tmpI = tmp.getI();
			tmpJ = tmp.getJ();

	//		위
			if (tmpI > 0) {
				if (arr[tmpI - 1][tmpJ] == 0) {
					arr[tmpI - 1][tmpJ] = 1;
					completeTomato++;
					queue.add(new Location(tmpI - 1, tmpJ));
				}
			}
	//		아래
			if (tmpI < M - 1) {
				if (arr[tmpI + 1][tmpJ] == 0) {
					arr[tmpI + 1][tmpJ] = 1;
					completeTomato++;
					queue.add(new Location(tmpI + 1, tmpJ));
				}
			}
	//		왼
			if (tmpJ > 0) {
				if (arr[tmpI][tmpJ - 1] == 0) {
					arr[tmpI][tmpJ - 1] = 1;
					completeTomato++;
					queue.add(new Location(tmpI, tmpJ - 1));
				}
			}
	//		오
			if (tmpJ < N - 1) {
				if (arr[tmpI][tmpJ + 1] == 0) {
					arr[tmpI][tmpJ + 1] = 1;
					completeTomato++;
					queue.add(new Location(tmpI, tmpJ + 1));
				}
			}
		}
		if (completeTomato < entireTomato) {
			System.out.println(-1);
		} else {
			System.out.println(day);
		}
	}
}

class Location {
	private int i, j;

	public Location(int i, int j) {
		this.i = i;
		this.j = j;
	}

	public int getI() {
		return i;
	}

	public int getJ() {
		return j;
	}
}