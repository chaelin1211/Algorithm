import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Collections;

// 여러 개의 로프를 병렬로 연결하면 각각의 로프에 걸리는 중량을 나눌 수 있다.
// k개의 로프를 사용하여 중량이 w인 물체를 들어올릴 때,각각의 로프에는 모두 고르게 
// w/k 만큼의 중량이 걸리게 된다.
// 각 로프들에 대한 정보가 주어졌을 때,이 로프들을 이용하여 들어올릴 수 있는 물체의
//  최대 중량을 구해내는 프로그램을 작성하시오.모든 로프를 사용해야 할 필요는 없으며,
// 임의로 몇 개의 로프를 골라서 사용해도 된다.

public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        String input = br.readLine();
        int N = Integer.parseInt(input.split(" ")[0]);
        ArrayList<Integer> ropes = new ArrayList<Integer>();

        for (int i = 0; i < N; i++) {
            input = br.readLine();
            ropes.add(Integer.parseInt(input.split(" ")[0]));
        }

        System.out.println(function(N, ropes));
    }

    public static int function(int N, ArrayList<Integer> ropes) {
        // 큰 순으로 정렬
        Collections.sort(ropes, Collections.reverseOrder());
        int weight = 0;
        int i = 0;

        weight += ropes.remove(0);
        i++;

        while (!ropes.isEmpty()) {
            int tmp = ropes.remove(0);
            i++;
            if (tmp * i > weight) {
                weight = tmp * i;
            }
        }
        return weight;
    }
}
