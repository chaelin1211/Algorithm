import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.util.ArrayList;
import java.util.HashMap;

public class Main {

	public static void main(String arg[]) throws NumberFormatException, IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

		String str = br.readLine();

		int M = Integer.parseInt(str.split(" ")[0]);
		int N = Integer.parseInt(str.split(" ")[1]);

		int numberOfZero = 0, numberOfOne;
		int index;

		HashMap<Integer, vertex> verts = new HashMap<Integer, vertex>();

		// 현재 익어있는 토마토~
		ArrayList<Integer> vertexesOfOne = new ArrayList<Integer>();

		for (int i = 0; i < N; i++) {
			str = br.readLine();
			for (int j = 0; j < M; j++) {
				int tmp = Integer.parseInt(str.split(" ")[j]);
				index = i * M + j;

				verts.put(index, new vertex(index, tmp));
				verts.get(index).incidentList = incidentList(i, j, N, M);

				if (tmp == 1) {
					vertexesOfOne.add(index);
				} else if (tmp == 0) {
					numberOfZero++;
				}
			}
		}

		System.out.println(func(verts, vertexesOfOne, numberOfZero));
	}

	public static int func(HashMap<Integer, vertex> verts, ArrayList<Integer> vertexesOfOne, int numberOfZero) {
		int count = 0;

		if (numberOfZero == 0) {
			return count;
		}

		ArrayList<ArrayList> ListofList = new ArrayList<ArrayList>();
		ListofList.add(vertexesOfOne);

		while (ListofList.get(0).size() > 0 && numberOfZero > 0) {
			vertex nowVer = verts.get(ListofList.get(0).remove(0));

			ArrayList<Integer> incidentList = nowVer.incidentList;

			if (incidentList.size() == 0) {
				continue;
			}

			ArrayList<Integer> tmpList = new ArrayList<Integer>();
			for (int i : incidentList) {
				vertex inciVer = verts.get(i);

				if (inciVer.number == 0) {
					// 주위의 토마토가 익는 중~
					inciVer.number = 1;
					numberOfZero--;

					tmpList.add(inciVer.index);
				}
			} 
			
			if (ListofList.size() < 2) {
				ListofList.add(tmpList);
				count++;
			} else
				ListofList.get(1).addAll(tmpList);

			if (ListofList.get(0).size() == 0) {
				ListofList.remove(0);
			}
		}

		if (numberOfZero > 0) {
			count = -1;
		}
		return count;
	}

	public static ArrayList<Integer> incidentList(int i, int j, int N, int M) {
		ArrayList<Integer> tmp = new ArrayList<Integer>();
		int x;

		// 상
		if (i > 0) {
			x = (i - 1) * M + j;
			tmp.add(x);
		}

		// 하
		if (i < N - 1) {
			x = (i + 1) * M + j;
			tmp.add(x);
		}

		// 좌
		if (j > 0) {
			x = i * M + (j - 1);
			tmp.add(x);
		}

		// 우
		if (j < M - 1) {
			x = i * M + (j + 1);
			tmp.add(x);
		}
		return tmp;
	}
}

class vertex {
	int index;
	int number;
	ArrayList<Integer> incidentList;

	public vertex() {
		this.index = 0;
		this.number = 0;
	}

	public vertex(int index, int number) {
		this.index = index;
		this.number = number;
	}
}
