import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;

public class Main {
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

		String input = br.readLine();
		int N = Integer.parseInt(input);

		HashMap<Integer, ArrayList<schedule>> hash = new HashMap<Integer, ArrayList<schedule>>();

		for (int i = 0; i < N; i++) {
			input = br.readLine();
			int a, b;

			a = Integer.parseInt(input.split(" ")[0]);
			b = Integer.parseInt(input.split(" ")[1]);

			if (hash.get(b - a) == null) {
				hash.put(b - a, new ArrayList<schedule>());
			}
			hash.get(b - a).add(new schedule(a, b));
		}
		System.out.println(function(hash));
	}

	public static int function(HashMap<Integer, ArrayList<schedule>> hash) {
	
	}
}

class schedule implements Comparable<schedule> {
	private int sTime;
	private int eTime;

	public schedule(int sTime, int eTime) {
		this.sTime = sTime;
		this.eTime = eTime;
	}

	public int getStime() {
		return this.sTime;
	}

	public int getEtime() {
		return this.eTime;
	}

	public int compareTo(schedule s) {
		if (sTime > s.sTime)
			return 1;
		else if (sTime == s.sTime)
			return 0;
		else
			return -1;
	}
}