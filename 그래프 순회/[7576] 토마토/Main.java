import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Queue;

public class Main {
	// BFS 적용
	static Queue<vertex> startPoint = new LinkedList<vertex>();
	static int[][] arr;

	public static void main(String arg[]) throws NumberFormatException, IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

		String str = br.readLine();

		int M = Integer.parseInt(str.split(" ")[0]);
		int N = Integer.parseInt(str.split(" ")[1]);

		arr = new int[N][M];

		int numberOfZero = 0;
		for (int i = 0; i < N; i++) {
			str = br.readLine();
			for (int j = 0; j < M; j++) {
				int tmp = Integer.parseInt(str.split(" ")[j]);
				arr[i][j] = tmp;
				if (tmp == 1) {
					startPoint.add(new vertex(i, j, tmp));
				}
				if (tmp == 0) {
					numberOfZero++;
				}
			}
		}
		System.out.print(findDay(startPoint, N, M, numberOfZero));
	}

	static public int findDay(Queue<vertex> startPoint, int N, int M, int numberOfZero) {
		int i = startPoint.size();
		int j = 0;
		int day = -1;

		while (!startPoint.isEmpty()) {
			vertex ver = startPoint.remove();
			j++;

			ArrayList<edge> inci = ver.inciList;
			if (inci.isEmpty()) {
				inci = setInciList(ver, arr, N, M);
			}

			while (!inci.isEmpty()) {
				edge edg = inci.remove(0);

				if (edg.flag != 0)
					continue;
				edg.flag = 1;
				vertex otherVer = edg.otherPoint(ver.i, ver.j);
				if (otherVer != null) {
					if (otherVer.num == 0) {
						numberOfZero--;
						arr[otherVer.i][otherVer.j] = 1;
						otherVer.num = 1;
						startPoint.add(otherVer);
					}
				}
			}

			if (i == j) {
				j = 0;
				i = startPoint.size();
				day++;
			}
		}
		if (numberOfZero != 0)
			return -1;
		return day;
	}

	static public ArrayList<edge> setInciList(vertex ver, int[][] arr, int N, int M) {
		int i = ver.i;
		int j = ver.j;
		if (i < N - 1) {
			if (arr[i + 1][j] == 0) {
				ver.inciList.add(new edge(ver, new vertex(i + 1, j, arr[i + 1][j])));
			}
		}
		if (i > 0) {
			if (arr[i - 1][j] == 0) {
				ver.inciList.add(new edge(ver, new vertex(i - 1, j, arr[i - 1][j])));
			}
		}
		if (j < M - 1) {
			if (arr[i][j + 1] == 0) {
				ver.inciList.add(new edge(ver, new vertex(i, j + 1, arr[i][j + 1])));
			}
		}
		if (j > 0) {
			if (arr[i][j - 1] == 0) {
				ver.inciList.add(new edge(ver, new vertex(i, j - 1, arr[i][j - 1])));
			}
		}
		return ver.inciList;
	}
}

class vertex {
	int i;
	int j;
	int num;
	ArrayList<edge> inciList;

	vertex(int i, int j, int num) {
		this.i = i;
		this.j = j;
		this.num = num;
		inciList = new ArrayList<edge>();
	}
}

class edge {
	vertex s;
	vertex e;
	int flag;

	public edge(vertex s, vertex e) {
		this.s = s;
		this.e = e;
		flag = 0;
	}

	public vertex otherPoint(int i, int j) {
		if (s.i == i && s.j == j) {
			return e;
		}
		if (e.i == i && e.j == j) {
			return s;
		}
		return null;
	}
}