
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.LinkedList;
import java.util.Queue;
import java.util.StringTokenizer;

public class Main {
	public static void main(String[] args) {
		int N, M;
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		try {
			String input = br.readLine();
			StringTokenizer inputToken = new StringTokenizer(input, " ");
			N = Integer.parseInt(inputToken.nextToken());
			M = Integer.parseInt(inputToken.nextToken());

			int[][] arr = new int[M][N];
			for (int i = 0; i < M; i++) {
				input = br.readLine();
				inputToken = new StringTokenizer(input, " ");
				int j = 0;
				while (inputToken.hasMoreTokens()) {
					arr[i][j++] = Integer.parseInt(inputToken.nextToken());
				}
			}
			solution(N, M, arr);
		} catch (NumberFormatException | IOException e) {
			e.printStackTrace();
		}
	}

	public static void solution(int N, int M, int[][] arr) {
		Queue<Location> queue = new LinkedList<Location>();
		int numberOfTomato = 0; // 당일에 존재하는 익은 토마토 수
		int allTomato = N * M; // 전체 익어야할 토마토 수
		int dayTomato = 0; // 아직 주변 토마토에 영향을 주지 않은 익은 토마토 수
		int day = 0; // 날짜
		for (int i = 0; i < M; i++) {
			for (int j = 0; j < N; j++) {
				if (arr[i][j] == 1) {
					queue.add(new Location(i, j));
					numberOfTomato++;
				} else if (arr[i][j] == -1) {
					allTomato--;
				}
			}
		}
		dayTomato = numberOfTomato;
		while (!queue.isEmpty()) {
			if (dayTomato == 0) {
				dayTomato = queue.size();
				day++;
//				System.out.println("day"+day+"-------------");
//				for (int i = 0; i < M; i++) {
//					for (int j = 0; j < N; j++) {
//						System.out.print(arr[i][j] + " ");
//					}
//					System.out.println("");
//				}
			}

			dayTomato--;

			Location tmp = queue.remove();
			int tmpI, tmpJ;
			tmpI = tmp.getI();
			tmpJ = tmp.getJ();

//			위
			if (tmpI > 0) {
				if (arr[tmpI - 1][tmpJ] == 0) {
					arr[tmpI - 1][tmpJ] = 1;
					numberOfTomato++;
					queue.add(new Location(tmpI - 1, tmpJ));
				}
			}
//			아래
			if (tmpI < M - 1) {
				if (arr[tmpI + 1][tmpJ] == 0) {
					arr[tmpI + 1][tmpJ] = 1;
					numberOfTomato++;
					queue.add(new Location(tmpI + 1, tmpJ));
				}
			}
//			왼
			if (tmpJ > 0) {
				if (arr[tmpI][tmpJ - 1] == 0) {
					arr[tmpI][tmpJ - 1] = 1;
					numberOfTomato++;
					queue.add(new Location(tmpI, tmpJ - 1));
				}
			}
//			오
			if (tmpJ < N - 1) {
				if (arr[tmpI][tmpJ + 1] == 0) {
					arr[tmpI][tmpJ + 1] = 1;
					numberOfTomato++;
					queue.add(new Location(tmpI, tmpJ + 1));
				}
			}
		}
		if (numberOfTomato < allTomato) {
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