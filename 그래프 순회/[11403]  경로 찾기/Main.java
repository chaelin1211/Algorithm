
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.LinkedList;
import java.util.Queue;

public class Main {
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int N = Integer.parseInt(br.readLine()); // 정점 개수
		Vertex[] Vers = new Vertex[N];

		for (int i = 0; i < N; i++) {
			Vers[i] = new Vertex(i);
		}

		// input incidentTable
		// set vertexes 
		for (int i = 0; i < N; i++) {
			String input = br.readLine();
			for (int j = 0; j < N; j++) {
				if (Integer.parseInt(input.split(" ")[j]) == 1) {
					// 방향 그래프라 단방향으로 Edge 저장
					Vers[i].addIncidentList(new Edge(Vers[i], Vers[j]));
				}
			}
		}
		printArray(function(Vers, N));
	}
	public static void printArray(int[][] Arr) {
		for(int[] arr:Arr) {
			for(int i:arr) {
				System.out.print(i+" ");
			}
			System.out.println();
		}
	}
	public static int[][] function(Vertex[] vers, int N) {
		int[][] possiblePath = new int[N][N];
		int i=0;
		//DFS 방식
		Vertex ver = null;
		Queue<Edge> queue = new LinkedList<Edge>();
		while(i < N) {
			if(queue.isEmpty()) {
				if(i>=N) {
					break;
				}
				ver = vers[i++];
				queue.addAll(ver.getIncidentList());
			}
			Edge tmpEdge = queue.remove();
			if(tmpEdge.getFlag()) {
				continue;
			}
			tmpEdge.setFlag(true);
			Vertex tmpVer = tmpEdge.getVer2();
			if (possiblePath[ver.getI()][tmpVer.getI()] == 0) {
				possiblePath[ver.getI()][tmpVer.getI()] = 1;
			}
			queue.addAll(tmpVer.getIncidentList());
			Vertex[] verArr = tmpEdge.getVertex();
			possiblePath[verArr[0].getI()][verArr[1].getI()] = 1;	
		}
		return possiblePath;
	}
}

class Vertex {
	private int i;
	private Queue<Edge> incidentEdge;

	public Vertex(int i) {
		this.i = i;
		this.incidentEdge = new LinkedList<Edge>();
	}

	public int getI() {
		return this.i;
	}

	public Queue<Edge> getIncidentList() {
		return this.incidentEdge;
	}

	public void addIncidentList(Edge edg) {
		this.incidentEdge.add(edg);
	}
}
class Edge{
	// 방향 그래프 ver1 -> ver2
	private Vertex ver1, ver2;
	private boolean flag;
	public Edge(Vertex ver1, Vertex ver2){
		this.ver1 = ver1;
		this.ver2 = ver2;
		this.flag = false;
	}
	
	public Vertex getVertex(Vertex ver) {
		if(ver == this.ver1) {
			return this.ver2;
		}else if(ver == this.ver2) {
			return this.ver1;
		}else return null;
	}

	public boolean getFlag() {
		return this.flag;
	}
	public Vertex getVer1() {
		return this.ver1;
	}
	public Vertex getVer2() {
		return this.ver2;
	}
	
	public void setFlag(boolean fl) {
		this.flag = fl;
	}
	
	public Vertex[] getVertex() {
		Vertex[] verArr = {this.ver1, this.ver2};
		return verArr;
	}
}