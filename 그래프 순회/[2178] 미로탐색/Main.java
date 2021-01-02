import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.util.ArrayList;
import java.util.HashMap;

public class Main {
	static HashMap<Integer, ArrayList<edge>> edges = new HashMap<Integer, ArrayList<edge>>();
	static HashMap<Integer, vertex> verts = new HashMap<Integer, vertex>();

	public static void main(String arg[]) throws NumberFormatException, IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));// 선언

		String str = br.readLine();

		int N = Integer.parseInt(str.split(" ")[0]);
		int M = Integer.parseInt(str.split(" ")[1]);

		int[][] arr = new int[N][M];
		int[][] flag = new int[N][M];
		// ArrayList<vertex> verts = new ArrayList<vertex>();
		int index;
		int a, b;
		for (int i = 0; i < N; i++) {
			str = br.readLine();
			for (int j = 0; j < M; j++) {
				int tmp = str.charAt(j) - ('1' - 1);
				index = i * M + j;

				verts.put(index, new vertex(index, tmp));

				if (tmp == 1) {
					int ti = i, tj = j;
					int tmpInd;
					// 위
					if (i >= 1) {
						ti--;
						tmpInd = ti * M + tj;
						if (verts.get(tmpInd).number == 1) {
							if (edges.get(tmpInd) == null)
								edges.put(tmpInd, new ArrayList<edge>());
							if (edges.get(index) == null)
								edges.put(index, new ArrayList<edge>());
							edges.get(tmpInd).add(new edge(index, tmpInd));
							edges.get(index).add(new edge(tmpInd, index));
						}
					}

					ti = i;
					tj = j;
					// 왼쪽
					if (j >= 1) {
						tj--;
						tmpInd = ti * M + tj;
						if (verts.get(tmpInd).number == 1) {
							if (edges.get(tmpInd) == null)
								edges.put(tmpInd, new ArrayList<edge>());
							if (edges.get(index) == null)
								edges.put(index, new ArrayList<edge>());
							edges.get(tmpInd).add(new edge(index, tmpInd));
							edges.get(index).add(new edge(tmpInd, index));
						}
					}
				}
			}
		}
		a = func();

		bw.write(a);
		bw.flush();
	}

	public static int func() {
		int ind = 0;
		int count = -1;

		ArrayList<vertex> tmpVerListA = new ArrayList<vertex>();
		ArrayList<vertex> tmpVerListB = new ArrayList<vertex> ();
		
		ArrayList<vertex>[] ListToggle = new ArrayList[2];
		ListToggle[0] = tmpVerListA;
		ListToggle[1] = tmpVerListB;
		
		vertex ver = verts.get(0);

		ListToggle[0].add(ver);
		count++;

		while (!ListToggle[ind].isEmpty()) {
			ver = ListToggle[ind].remove(0);
			ver.flag = 1;

			if (ver.number == 1) {
				ArrayList<edge> tmpList = edges.get(ver.index);
				
				
				while (!tmpList.isEmpty()) {
					edge edg = tmpList.remove(0);

					int oppsiteInd = edg.otherPoint(ver.index);
					if (oppsiteInd != -1) {
						vertex tmpVer = verts.get(oppsiteInd);
						count++;
						if (tmpVer.flag != 1) {
							tmpVerListB.add(tmpVer);
						} 
					}
				}
			}
			
		}
		return count;
	}
}

class vertex {
	int index;
	int number;
	int flag;

	public vertex() {
		this.index = 0;
		this.number = 0;
		this.flag = 0;
	}

	public vertex(int index, int number) {
		this.index = index;
		this.number = number;
	}
}

class edge {
	int s, e;
	int flag;
	// 0: 초기 상태
	// 1: 방문된 상태

	public edge() {
		this.s = 0;
		this.e = 0;
		this.flag = 0;
	}

	public edge(int s, int e) {
		this.s = s;
		this.e = e;
		this.flag = 0;
	}

	public int otherPoint(int a) {
		if (a == this.s) {
			return this.e;
		} else if (a == this.e) {
			return this.s;
		} else {
			return -1;
		}
	}
}