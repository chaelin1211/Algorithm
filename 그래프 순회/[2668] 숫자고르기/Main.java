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
		ArrayList<Integer> tmpList = new ArrayList<Integer>();
		Vertex ver = null;

		while (key <= N + 1) {
			while (ver == null) {
				ver = hash.get(key++);
				tmpList.clear();
			}
			if (ver.flag) {
				if (tmpList.contains(ver.key)) {
					if (verList.contains(ver.key)) {
                        // cycle end
						ver = hash.get(key++);
						tmpList.clear();
					} else {
						// cycle ing
						verList.add(ver.key);
						ver = hash.get(ver.value);
					}
				} else {
					// cycle은 아니나 이전에 방문된적 있는 경로
					ver = hash.get(key++);
					tmpList.clear();
				}
			} else {
				// 최초 방문
				ver.flag = true;
				tmpList.add(ver.key);
				ver = hash.get(ver.value);
			}
		}
		verList.sort(null);
		return verList;
	}
}

class Vertex {
	int key;
	int value;
	boolean flag;

	public Vertex(int key, int value) {
		this.key = key;
		this.value = value;
		this.flag = false;
	}
}
