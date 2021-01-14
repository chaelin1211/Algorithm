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

        if (N >= K) {
            return N - K;
        }

        Queue<Integer> queue = new LinkedList<Integer>();
        HashMap<Integer, Boolean> flag = new HashMap<Integer, Boolean>();

        // 수빈이의 처음 위치
        queue.add(N);
        sizeOfQueue = queue.size();
        while (sizeOfQueue != 0 || !queue.isEmpty()) {
            if (sizeOfQueue == 0) {
                count++;
                sizeOfQueue = queue.size();
            }

            int num = queue.remove();
            sizeOfQueue--;

            if (num == K) {
                return count;
            }

            // 음수 제외
            if (num < 0)
                continue;

            // 이미 지나간 자리 제외
            if (flag.get(num) != null) {
                continue;
            }
            flag.put(num, true);

            if (num < K) {// 효율을 위한 범위 제한
                if (num * 2 > K) {
                    if (num * 2 - K < K - N) {
                        queue.add(num * 2);
                    }
                } else {
                    queue.add(num * 2);
                }
                queue.add(num + 1);
                queue.add(num - 1);
            }
            else {
                queue.add(num - 1);
            }
        }
        return count;
    }
}
