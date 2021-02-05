import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Main {
    public static void main(String[] args) throws NumberFormatException, IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int N = Integer.parseInt(br.readLine());

        System.out.println(function(N));
    }

    public static int function(int N) {
        // input: 방의 번호
        // output: 1번 방으로부터 거리
        int level = 1; // 1번방을 중심으로 주위 방은 같은 level
                       // 같은 level의 방은 1번 방까지의 거리가 같다
        if (N == 1) {
            return level;
        }

        level += 1; // level은 1번 방을 포함해서 계산한다.

        int i = 2; // i는 각 level에서 가장 작은 방의 번호이다.
                   // level이 x일 때, 방의 개수는 6*(x-1)개이다. (육각형이기 때문!)
                   // 즉 각 level의 방 번호 범위는? i <= N < i+((level-1)*6)
        while (true) {
            if (i <= N && N < i + ((level - 1) * 6)) {
                return level;
            } else {
                i += ((level - 1) * 6);
                level++;
            }
        }
    }
}
