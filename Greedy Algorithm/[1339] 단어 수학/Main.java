import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;

public class Main {
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

		String input = br.readLine();
		int N = Integer.parseInt(input);
		String[] words = new String[N];
		for (int i = 0; i < N; i++) {
			words[i] = br.readLine();
		}
		System.out.println(function(words));
	}

	public static int function(String[] words) {
		int answer = 0;
		int index = 'Z' + 1;
		int[] Alph = new int[index];
		ArrayList<Integer> arr = new ArrayList<Integer>();

		int i = 1;
		while (true) {
			int count = 0;
			for (String str : words) {
				int idx = str.length() - i;
				if (idx < 0) {
					count++;
					continue;
				}
				char Al = str.charAt(idx);
				if(Alph[Al] == 0) arr.add((int) Al);
				Alph[Al] += (int) Math.pow(10, i - 1);
			}
			i++;
			if (count == words.length) {
				break;
			}
		}
		
		Collections.sort(arr, new Comparator<Integer>() {
			@Override
			public int compare(Integer o1, Integer o2) {
				return Alph[o2] - Alph[o1];
			}
			
		});
		
		i=9;
		for(int x:arr) {
			answer += (i*Alph[x]);
			i--;
		}
		
		return answer;
	}
}

class Alphabet implements Comparable<Alphabet> {
	int firstIndex;
	int count;
	char Alph;

	public Alphabet(char Alph, int firstIndex) {
		this.Alph = Alph;
		this.firstIndex = firstIndex;
		this.count = 0;
	}

	@Override
	public int compareTo(Alphabet o) {
		if (this.firstIndex < o.firstIndex) {
			return 1;
		} else if (this.firstIndex == o.firstIndex) {
			if (this.count > o.count) {
				return 1;
			}
		}
		return -1;
	}
}
