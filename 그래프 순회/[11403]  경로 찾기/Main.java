
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
		// key: 정점 번호
		// value: 인접 정점 (진출간선에 의해 도달할 수 있는 간선)

		// input incidentTable----------------------------
		for (int i = 0; i < N; i++) {
			String input = br.readLine();
			incidentHashMap.put(i, new ArrayList<Integer>());
			for (int j = 0; j < N; j++) {
				if (Integer.parseInt(input.split(" ")[j]) == 1) {
					incidentHashMap.get(i).add(j);
				}
			}
		}
		// ------------------------------------------------

		// function and print ----------------------------
		printArray(function(incidentHashMap, N));
		// ------------------------------------------------
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
		int i = -1; // 시작점을 가리키는 인덱스
		// BFS 방식으로 순회

		// 진출할 수 있는 정점들을 저장하는 큐
		Queue<Integer> queue = new LinkedList<Integer>();

		while (i <= N) {
			if (queue.isEmpty()) {
				i++;
				ArrayList tmpArrayList = incidentHashMap.get(i);

				// 인접 정점이 없는 경우 (진출 간선이 없는 경우)
				if (tmpArrayList == null || tmpArrayList.size() == 0) {
					continue;
				} else {
					queue.addAll(tmpArrayList);
				}
			}
			int index = queue.remove();

			if (index == i) {	//사이클을 통해 시작점으로 돌아옴
				possiblePath[i][i] = 1;
				continue;
			} else {
				if (possiblePath[i][index] == 0) {		// 중복 순회를 방지
					possiblePath[i][index] = 1;
					queue.addAll(incidentHashMap.get(index));
				}
			}
		}

		return possiblePath;
	}
}
