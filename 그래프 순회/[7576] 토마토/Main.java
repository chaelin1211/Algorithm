import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.HashMap;

public class Main {
	// BFS 적용
	static HashMap<Integer, ArrayList<edge>> edges = new HashMap<Integer, ArrayList<edge>>();
	static HashMap<Integer, vertex> verts = new HashMap<Integer, vertex>();

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
				int tmp = str.charAt(j) - ('1' - 1);
				index = i * M + j;

				// 각 원소를 Vertex로 보고 Vertex 해쉬맵에 삽입
				// 1인 경우만 삽입
				if (tmp == 1)
					verts.put(index, new vertex(index, tmp));
				else if (tmp == 0)
					numberOfZero++;

				// vertex가 -1이 아닐 경우 - edge를 가질 수 있음
				if (tmp != -1) {
					int ti = i, tj = j;
					int tmpInd;

					// >>주위를 확인하여 삽입하는 과정

					// 위
					if (i >= 1) {
						ti--;
						tmpInd = ti * M + tj;
						if (verts.get(tmpInd)!=null) {
							// 검색시 효율을 위해 Edge를 이중으로 저장
							// a-b인 경우 (a,b), (b,a) 두 가지로 저장
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
						if (verts.get(tmpInd)!=null) {
							// 검색시 효율을 위해 Edge를 이중으로 저장
							// a-b인 경우 (a,b), (b,a) 두 가지로 저장
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
		System.out.println(func(numberOfZero));
	}

	public static int func(int numberOfZero) {
		int ind = 0;
		int count = 0;

		ArrayList<vertex> tmpVerListA = new ArrayList<vertex>();
		ArrayList<vertex> tmpVerListB = new ArrayList<vertex>();

		// 한 레벨을 한 리스트에 넣고 다음 레벨은 다른 리스트에 넣어 레벨 간의 구별을 해주고자 함
		// 두 리스트를 번갈아 사용하고자 하였고 쉽게 이용하기 위해 리스트를 배열로 다시 구성
		ArrayList<vertex>[] ListToggle = new ArrayList[2];
		ListToggle[0] = tmpVerListA;
		ListToggle[1] = tmpVerListB;

		vertex ver = verts.get(0);

		// 현재 익은 토마토들
		ListToggle[0].addAll(verts.values());

		while (!ListToggle[ind].isEmpty()&&numberOfZero>0) {
			ver = ListToggle[ind].remove(0);

			ArrayList<edge> tmpList = edges.get(ver.index);

			// 현재 Vertex의 연결 Edge를 확인해 반대편 Vertex를 다른 리스트에 삽입
			while (!tmpList.isEmpty()) {
				edge edg = tmpList.remove(0);

				if (edg.flag != 1) {
					// 반대편 Vertex 리턴 - 오류 시 -1
					int oppsiteInd = edg.otherPoint(ver.index);

					if (oppsiteInd != -1) {
						vertex tmpVer = verts.get(oppsiteInd);

						// 해당 Edge는 트리 간선
						edg.flag = 1;

						if (tmpVer.number == 0) {
							numberOfZero--;
							tmpVer.number = 1;
							if (ind == 0)
								ListToggle[1].add(tmpVer);
							else
								ListToggle[0].add(tmpVer);
						} else {
							// 해당 Edge는 교차 간선
							// 현재 문제 상 필요한 로직은 아니므로 구현하지 않음
						}
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
		
		if(numberOfZero>0) {
			return -1;
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