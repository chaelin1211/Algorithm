import java.util.ArrayList;
import java.util.HashMap;
import java.util.Scanner;

public class Main {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);

		int N = sc.nextInt();
		HashMap<Integer, Vertex> hash = new HashMap<Integer, Vertex>();

		for (int i = 1; i <= N; i++) {
			int num = sc.nextInt();
			hash.put(i, new Vertex(i, num));
		}

		for (int i = 1; i <= N; i++) {
			Vertex s = hash.get(i);
			Vertex e = hash.get(s.value);
			s.incidentEdge = new Edge(s, e);
		}
		printFunction(function(hash, N));
	}

	public static void printFunction(ArrayList<Integer> arr) {
		System.out.println(arr.size());
		for (int a : arr) {
			System.out.println(a);
		}
	}

	public static ArrayList<Integer> function(HashMap<Integer, Vertex> hash, int N) {
		// DFS 방식 (깊이 우선 방식)
		// Hash의 Value = 다음에 이동할 Vertex의 Key

		int key = 1;
		ArrayList<Integer> verList = new ArrayList<Integer>();
		Vertex ver = null;

		while (key <= N + 1) {
			if (ver == null || hash.get(ver.key) == null) {
				ver = hash.get(key++);
			}

			Vertex oppsiteVertex = ver.incidentEdge.oppositeVertex();

			if (ver.incidentEdge.visits == 0) {
				if (!oppsiteVertex.flag) {
					// 최초 방문
					ver.incidentEdge.visits++;
					ver.flag = true;
					ver = oppsiteVertex;
				} else {
					// 싸이클은 아니나 이전에 방문된 경로 - 다시 방문할 필요가 없음
					ver.flag = true;
					ver = null;
				}
			} else if (ver.incidentEdge.visits > 0) {
				// 싸이클
				if (!verList.contains(oppsiteVertex.key)) {
					verList.add(oppsiteVertex.key);
					ver.incidentEdge.visits++;
					ver.flag = true;
					ver = oppsiteVertex;
				}else {
					//모든 싸이클 내의 Number를 ArrayList에 저장 끝
					ver = null;
				}
			} 
		}
		verList.sort(null);
		return verList;
	}
}

class Vertex {
	int key;
	int value;
	Edge incidentEdge;
	boolean flag;

	public Vertex(int key, int value) {
		this.key = key;
		this.value = value;
		this.flag = false;
	}

	public void setIncidentEdge(Vertex e) {
		this.incidentEdge = new Edge(this, e);
	}
}

class Edge {
	Vertex s;
	Vertex e;
	int visits;

	public Edge() {
		this.visits = 0;
	}

	public Edge(Vertex s, Vertex e) {
		this.s = s;
		this.e = e;
		this.visits = 0;
	}

	public Vertex oppositeVertex() {
		return this.e;
	}
}
