import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.HashMap;

public class Main {
	public static void main(String arg[]) throws NumberFormatException, IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

		int N = Integer.parseInt(br.readLine());

		String[][] arr = new String[N][N];
		vertex[][] verList = new vertex[N][N];
		HashMap<Integer, ArrayList<vertex>> belongArr = new HashMap<Integer, ArrayList<vertex>>();

		int idx = 1;

		// input
		for (int i = 0; i < N; i++) {
			String[] tmp = br.readLine().split("");
			arr[i] = tmp;
			for (int j = 0; j < N; j++) {
				if (arr[i][j].equals("1")) {
					// belongArr.put(idx++, new ArrayList<vertex>());
					verList[i][j] = new vertex(i, j);
					verList[i][j].index = idx;

					int minInd = verList[i][j].index;
					int flag = 1;

					if (i > 0 && verList[i - 1][j] != null) {
						if (minInd > verList[i - 1][j].index) {
							minInd = verList[i - 1][j].index;
							flag = 0;
						}
					}
					if (j > 0 && verList[i][j - 1] != null) {
						if (minInd > verList[i][j - 1].index) {
							minInd = verList[i][j - 1].index;
							flag = 0;
						}
					}

					if (i > 0 && verList[i - 1][j] != null) {
						if (minInd < verList[i - 1][j].index) {
							belongArr.get(minInd).addAll(belongArr.get(verList[i - 1][j].index));
							belongArr.remove(verList[i - 1][j].index);
							verList[i - 1][j].index = minInd;
						}
					}
					if (j > 0 && verList[i][j - 1] != null) {
						if (minInd < verList[i][j - 1].index) {
							belongArr.get(minInd).addAll(belongArr.get(verList[i][j - 1].index));
							belongArr.remove(verList[i][j - 1].index);
							verList[i][j - 1].index = minInd;
						}
					}
					idx += flag;
					verList[i][j].index = minInd;
					if (belongArr.get(minInd) == null)
						belongArr.put(minInd, new ArrayList<vertex>());
					belongArr.get(minInd).add(verList[i][j]);
				}
			}
		}
		System.out.println(belongArr.size());
		for(ArrayList<vertex> a:belongArr.values()) {
			System.out.println(a.size());
		}
	}
}

class vertex {
	int i, j;
	int index;
	ArrayList<vertex> belongArray;

	public vertex(int i, int j) {
		this.i = i;
		this.j = j;
		this.index = 0;
	}
}