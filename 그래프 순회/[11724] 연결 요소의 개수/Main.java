
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Queue;
import java.util.StringTokenizer;

public class Main {
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

		String input = br.readLine();
		StringTokenizer inputToken = new StringTokenizer(input);

		int N, M;
		N = Integer.parseInt(inputToken.nextToken());
		M = Integer.parseInt(inputToken.nextToken());

		int[][] edges = new int[M][2];
		for (int i = 0; i < M; i++) {
			input = br.readLine();
			inputToken = new StringTokenizer(input);
			edges[i][0] = Integer.parseInt(inputToken.nextToken());
			edges[i][1] = Integer.parseInt(inputToken.nextToken());
		}

		System.out.println(solution(N, M, edges));
	}

	public static int solution(int N, int M, int[][] edges) {
		Vertex[] vertexes = new Vertex[N + 1];
		for (int[] edge : edges) {
			for (int ver : edge) {
				if (vertexes[ver] == null) {
					vertexes[ver] = new Vertex(ver);
				}
			}
			Vertex.addInciEdge(vertexes[edge[0]], vertexes[edge[1]]);
		}

		int answer = 0;
		for (int i = 1; i < N + 1; i++) {
			if(vertexes[i] == null) {
				answer ++;
			}
			else if (!vertexes[i].flag) {
				answer++;
				bfsFunction(vertexes[i], vertexes);
			}
		}
		return answer;
	}

	public static void bfsFunction(Vertex ver, Vertex[] vertexes) {
		Queue<Edge> inciEdges = new LinkedList<Edge>();
		inciEdges.addAll(ver.inciEdge);
		ver.flag = true;

		while (!inciEdges.isEmpty()) {
			Edge tmpEdge = inciEdges.remove();
			if (tmpEdge.flag) {
				continue;
			}
			tmpEdge.flag = true;
			Vertex otherVertex = tmpEdge.otherVertex(ver);
			if (otherVertex != null) {
				if (!otherVertex.flag) {
					bfsFunction(otherVertex, vertexes);
				} else {
					tmpEdge.flag = true;
					continue;
				}
			}
		}
	}
}

class Vertex {
	int number;
	boolean flag;
	ArrayList<Edge> inciEdge;

	public Vertex(int number) {
		this.number = number;
		flag = false;
		inciEdge = new ArrayList<Edge>();
	}

	public static void addInciEdge(Vertex ver1, Vertex ver2) {
		Edge edge = new Edge(ver1, ver2);
		ver1.inciEdge.add(edge);
		ver2.inciEdge.add(edge);
	}
}

class Edge {
	Vertex ver1, ver2;
	boolean flag;

	public Edge(Vertex ver1, Vertex ver2) {
		this.ver1 = ver1;
		this.ver2 = ver2;
		flag = false;
	}

	public Vertex otherVertex(Vertex ver) {
		if (ver == ver1) {
			return ver2;
		} else if (ver == ver2) {
			return ver1;
		}
		return null;
	}
}