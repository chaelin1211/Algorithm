import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.LinkedList;
import java.util.Queue;

public class Main {
	// BFS 적용
	static Queue<edge>[] edges = new LinkedList[1001];
	static vertex[] verts = new vertex[1001];
	static Queue<vertex> OneVerts = new LinkedList<vertex>();

	public static void main(String arg[]) throws NumberFormatException, IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

		String str = br.readLine();

		int M = Integer.parseInt(str.split(" ")[0]);
		int N = Integer.parseInt(str.split(" ")[1]);

		int index;
		int numberOfZero = 0;
		for (int i = 0; i < N; i++) {
			str = br.readLine();
			for (int j = 0; j < M; j++) {
				int tmp = Integer.parseInt(str.split(" ")[j]);
				index = i * M + j;

				// 각 원소를 Vertex로 보고 Vertex 해쉬맵에 삽입
				// -1이 아닌 경우만 삽입
				if (tmp == -1)
					continue;

				vertex v = new vertex(index, tmp);
				verts[index]= v;

				if (tmp == 1) {
					OneVerts.add(v);
				} else if (tmp == 0)
					numberOfZero++;

				// vertex가 -1이 아닐 경우 - edge를 가질 수 있음
				int ti = i, tj = j;
				int tmpInd;

				// >>주위를 확인하여 삽입하는 과정

				// 위
				if (i >= 1) {
					ti--;
					tmpInd = ti * M + tj;
					if (verts[tmpInd] != null) {
						// 검색시 효율을 위해 Edge를 이중으로 저장
						// a-b인 경우 (a,b), (b,a) 두 가지로 저장

						if (edges[tmpInd] == null)
							edges[tmpInd] = new LinkedList<edge>();
						if (edges[index] == null)
							edges[index] = new LinkedList<edge>();
						edges[tmpInd].add(new edge(index, tmpInd));
						edges[index].add(new edge(tmpInd, index));
					}
				}

				ti = i;
				tj = j;
				// 왼쪽
				if (j >= 1) {
					tj--;
					tmpInd = ti * M + tj;
					if (verts[tmpInd] != null) {
						// 검색시 효율을 위해 Edge를 이중으로 저장
						// a-b인 경우 (a,b), (b,a) 두 가지로 저장

						if (edges[tmpInd] == null)
							edges[tmpInd] = new LinkedList<edge>();
						if (edges[index] == null)
							edges[index] = new LinkedList<edge>();
						edges[tmpInd].add(new edge(index, tmpInd));
						edges[index].add(new edge(tmpInd, index));
					}
				}
			}
		}
		System.out.println(func(numberOfZero));
	}

	public static int func(int numberOfZero) {
		int ind = 0;
		int count = 0;

		Queue<vertex> tmpVerListA = new LinkedList<vertex>();
		Queue<vertex> tmpVerListB = new LinkedList<vertex>();

		// 한 레벨을 한 리스트에 넣고 다음 레벨은 다른 리스트에 넣어 레벨 간의 구별을 해주고자 함
		// 두 리스트를 번갈아 사용하고자 하였고 쉽게 이용하기 위해 리스트를 배열로 다시 구성
		Queue<vertex>[] ListToggle = new LinkedList[2];
		ListToggle[0] = tmpVerListA;
		ListToggle[1] = tmpVerListB;

		vertex ver;

		// 현재 익은 토마토들
		ListToggle[0].addAll(OneVerts);

		while (!ListToggle[ind].isEmpty() && numberOfZero > 0) {
			ver = ListToggle[ind].remove();

			Queue<edge> tmpList = edges[ver.index];

			// 현재 Vertex의 연결 Edge를 확인해 반대편 Vertex를 다른 리스트에 삽입
			while (!tmpList.isEmpty()) {
				edge edg = tmpList.remove();

				if (edg.flag != 1) {
					// 반대편 Vertex 리턴 - 오류 시 -1
					int oppsiteInd = edg.otherPoint(ver.index);
					vertex tmpVer = verts[oppsiteInd];
					// 해당 Edge는 트리 간선
					edg.flag = 1;

					if (tmpVer != null && tmpVer.number == 0) {
						numberOfZero--;
						tmpVer.number = 1;
						if (ind == 0)
							ListToggle[1].add(tmpVer);
						else
							ListToggle[0].add(tmpVer);
					}
				}
			}
			if (ListToggle[ind].isEmpty()) {
				count++;
				if (ind == 0)
					ind = 1;
				else
					ind = 0;
			}
		}
		if (numberOfZero > 0)
			return -1;

		if (!ListToggle[0].isEmpty() && !ListToggle[1].isEmpty()) {
			count++;
		}

		return count;
	}
}

class vertex {
	int index;
	int number;

	public vertex() {
		this.index = 0;
		this.number = 0;
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
	// 1: 트리 간선

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