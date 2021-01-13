import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.HashMap;

public class Main {
	static BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

	public static void main(String arg[]) {
		try {
			inputFunction();
		} catch (NumberFormatException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	public static void inputFunction() throws NumberFormatException, IOException {
		int N = Integer.parseInt(br.readLine());

		vertex[][] verTable = new vertex[N][N];
		ArrayList<vertex> verList = new ArrayList<vertex>();

		// input
		for (int i = 0; i < N; i++) {
			String[] tmp = br.readLine().split("");
			for (int j = 0; j < N; j++) {
				int a = Integer.parseInt(tmp[j]);
				if (a == 1) {
					vertex newVer = new vertex(i, j);

					verList.add(newVer);
					verTable[i][j] = newVer;

					inputInciVerToList(i, j, verTable, newVer, verList);
				}
			}
		}
	}

	public static void outputFunction(HashMap<Integer, ArrayList<vertex>> belongArr) {
		System.out.println(belongArr.size());
		for (ArrayList<vertex> a : belongArr.values()) {
			System.out.println(a.size());
		}
	}

	public static void inputInciVerToList(int i, int j, vertex[][] arr, vertex ver, ArrayList<vertex> verList) {
		// 주위의 1인 vertex를 찾아 삽입
		vertex inciVer;
		if (i > 0 && arr[i - 1][j] != null) {
			inciVer = arr[i - 1][j];

			ver.addEdgeList(new edge(ver, inciVer));
			inciVer.addEdgeList(new edge(inciVer, ver));
		}
		if (j > 0 && arr[i][j - 1] != null) {
			inciVer = new vertex(i, j - 1);

			ver.addEdgeList(new edge(ver, inciVer));
			inciVer.addEdgeList(new edge(inciVer, ver));
		}

	}
}

class vertex {
	int i, j;
	boolean flag;
	// 방문 전 false
	// 방문 후 true
	ArrayList<edge> inciList;

	public vertex() {
		this.inciList = new ArrayList<edge>();
		this.flag = false;
	}

	public vertex(int i, int j) {
		this.i = i;
		this.j = j;
		this.inciList = new ArrayList<edge>();
		this.flag = false;
	}

	public void addEdgeList(edge edg) {
		this.inciList.add(edg);
	}
}

class edge {
	vertex s, e;
	boolean flag;

	// 방문 전 false
	// 방문 후 true
	public edge() {
		this.s = null;
		this.e = null;
		flag = false;
	}

	public edge(vertex s, vertex e) {
		this.s = s;
		this.e = e;
		flag = false;
	}
}