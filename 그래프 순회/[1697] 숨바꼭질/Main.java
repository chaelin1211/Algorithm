import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.Queue;

public class Main {
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

		String tmp = br.readLine();
		int N = Integer.parseInt(tmp.split(" ")[0]);
		int K = Integer.parseInt(tmp.split(" ")[1]);

		System.out.println(function(N, K));
	}

	public static int function(int N, int K) {
		int count = 0;
		int sizeOfQueue = 0;

		Queue<Integer> queue = new LinkedList<Integer>();
		boolean[] flag = new boolean[100000];

		//수빈이의 처음 위치
		queue.add(N);
		sizeOfQueue = queue.size();
		while (sizeOfQueue!=0) {
			int num = queue.remove();
			sizeOfQueue--;
			
			if(num==K) {
				return count;
			}
			
			if (flag[num])
				continue;
			flag[num] = true;
			
			queue.add(num + 1);
			queue.add(num - 1);
			queue.add(num * 2);
			
			if(sizeOfQueue == 0) {
				count++;
				sizeOfQueue = queue.size();
			}
		}
		return count;
	}
}
