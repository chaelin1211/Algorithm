
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.Queue;

public class Main {
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int N = Integer.parseInt(br.readLine()); // 정점 개수
		HashMap<Integer, ArrayList<Integer>> incidentHashMap = new HashMap<Integer, ArrayList<Integer>>();

		// input incidentTable
		for (int i = 0; i < N; i++) {
			String input = br.readLine();
			incidentHashMap.put(i, new ArrayList<Integer>());
			for (int j = 0; j < N; j++) {
				if (Integer.parseInt(input.split(" ")[j]) == 1) {
					incidentHashMap.get(i).add(j);
				}
			}
		}
		printArray(function(incidentTable, N));
	}

	public static void printArray(int[][] Arr) {
		for (int[] arr : Arr) {
			for (int i : arr) {
				System.out.print(i + " ");
			}
			System.out.println();
		}
	}

	public static int[][] function(HashMap<Integer, ArrayList<Integer>> incidentHashMap, int N) {
		int[][] possiblePath = new int[N][N];
		int i=0;
		// DFS 방식
		Queue<Integer> queue = new LinkedList<Integer>();
		while(i<=N){
			ArrayList tmpArrayList = incidentHashMap.get(i);
			if(tmpArrayList==null || tmpArrayList.size()==0){
				i++;
				continue;
			}else{
				queue.addAll(tmpArrayList);
			}
			int index = queue.remove();

			if(index == i){
				possiblePath[i][i] = 1;
				queue.clear();
				continue;
			}
			else{
				possiblePath[i][index] = 1;
			}
		}

		return possiblePath;
	}
}
