import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Main {
    public static void main(String[] args) {
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

        int i = 1; // 엘리베이터에서부터 세었을 때의 번호
        while (N >= H) {
            N -= H;
            i++;
        }
        roomNumber += (N*100);
        roomNumber += i;
        return roomNumber;
    }
}
