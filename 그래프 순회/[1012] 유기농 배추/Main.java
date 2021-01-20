import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.LinkedList;
import java.util.Queue;

public class Main {
	static int[][] arr;

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		String input = br.readLine();
		int T = Integer.parseInt(input.split(" ")[0]);
		for (int i = 0; i < T; i++) {
			input = br.readLine();
			int N = Integer.parseInt(input.split(" ")[0]);
			int M = Integer.parseInt(input.split(" ")[1]);
			int K = Integer.parseInt(input.split(" ")[2]);

			arr = new int[N][M];
			ArrayList<Vertex> arrayList = new ArrayList<Vertex>();
			for (int j = 0; j < K; j++) {
				input = br.readLine();
				int a = Integer.parseInt(input.split(" ")[0]);
				int b = Integer.parseInt(input.split(" ")[1]);
				arr[a][b] = 1;
				arrayList.add(new Vertex(a, b));
			}
			System.out.println(function(N, M, arrayList));
		}
	}

	public static int function(int N, int M, ArrayList<Vertex> arrayList) {
		int larva = arrayList.size();
		Queue<Vertex> queue = new LinkedList<Vertex>();
		boolean[][] flags = new boolean[N][M];

		while (!arrayList.isEmpty()||!queue.isEmpty()) {
			if(queue.isEmpty()) {
				Vertex vertex = arrayList.remove(0);
				int i = vertex.getI();
				int j = vertex.getJ();

				if(!flags[i][j]) {
					queue.add(vertex);
					flags[i][j] = true;
				}
				else continue;
			}
			Vertex vertex = queue.remove();
			int i = vertex.getI();
			int j = vertex.getJ();

			if(i>0 && arr[i-1][j]==1 && !flags[i-1][j]) {
				queue.add(new Vertex(i-1, j));
				flags[i-1][j]=true;
				larva--;
			}
			if(i<N-1 && arr[i+1][j]==1 && !flags[i+1][j]) {
				queue.add(new Vertex(i+1, j));
				flags[i+1][j]=true;
				larva--;
			}
			if(j>0 && arr[i][j-1]==1 && !flags[i][j-1]) {
				queue.add(new Vertex(i, j-1));
				flags[i][j-1]=true;
				larva--;
			}
			if(j<M-1 && arr[i][j+1]==1 && !flags[i][j+1]) {
				queue.add(new Vertex(i, j+1));
				flags[i][j+1]=true;
				larva--;
			}
		}
		return larva;
	}
}

class Vertex {
	private int i, j;
	public int getI() {
		return this.i;
	}

	public int getJ() {
		return this.j;
	}

	public Vertex(int i, int j) {
		this.i = i;
		this.j = j;
	}
}