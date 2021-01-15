import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;

public class Main {
	public static void main(String[] args) throws NumberFormatException, IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int N = Integer.parseInt(br.readLine());

		String P = br.readLine();
		ArrayList<Integer> arr = new ArrayList<Integer>();

		for (int i = 0; i < N; i++) {
			arr.add(Integer.parseInt(P.split(" ")[i]));
		}

		System.out.println(function(N, arr));
	}

	public static int function(int N, ArrayList<Integer> arr) {
		int nowTime = 0;
		int sum = 0;
        int beforeWait = 0;
        
        //적은 시간 순으로 정렬하기 위한 sort
        arr.sort(null);
        
		while (!arr.isEmpty()) {
			nowTime = arr.remove(0);
			
			sum += beforeWait + nowTime;
			
			beforeWait += nowTime;
		}

		return sum;
	}
}
