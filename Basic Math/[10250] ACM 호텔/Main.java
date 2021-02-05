import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Main {
    public static void main(String[] args) throws NumberFormatException, IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        int T = Integer.parseInt(br.readLine());
        int H, W, N;
        for (int i = 0; i < T; i++) {
            String input = br.readLine();
            H = Integer.parseInt(input.split(" ")[0]);
            W = Integer.parseInt(input.split(" ")[1]);
            N = Integer.parseInt(input.split(" ")[2]);
            System.out.println(function(H, W, N));
        }
    }

    public static int function(int H, int W, int N) {
        int roomNumber = 0;

        int i = 1;      // 엘리베이터에서부터 세었을 때의 번호
        while (N > H) {
            N -= H;     // N은 층수를 가리키게 된다.    
            i++;
        }
        
        // 저층부터 고층 순으로 엘리베이터에 가까운 방을 배정하기 때문에
        // N번 째 배정될 때 N = aH + b라면 b층의 a+1번 째 방에 배정되는 것이다.

        roomNumber += (N * 100);
        roomNumber += i;
        return roomNumber;
    }
    // public static int function(int H, int W, int N) {
	// 	int roomNumber = 0;

	// 	int a, b;

	// 	// 저층부터 고층 순으로 엘리베이터에 가까운 방을 배정하기 때문에
	// 	// N번 째 배정될 때 N = aH + b라면 b층의 a+1번 째 방에 배정되는 것이다.

	// 	a = N / H;
	// 	a++;
		
	// 	b = N % H;

	// 	// b는 무조건 1 이상이어야 한다.
	// 	// N = H인 경우에 b가 0이 될 수 있으므로 a에서 1을 빼고 b에 H를 더하므로써 해결 
	// 	if(b == 0) {
	// 		a--;
	// 		b += H;
	// 	}

	// 	roomNumber = (b * 100) + a;
	// 	return roomNumber;
	// }
}
