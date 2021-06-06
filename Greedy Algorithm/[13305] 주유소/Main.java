import java.util.*;

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int N = sc.nextInt();
        long[] distances = new long[N - 1];
        for (int i = 0; i < N - 1; i++) {
            distances[i] = sc.nextInt();
        }
        long[] prices = new long[N];
        for (int i = 0; i < N; i++) {
            prices[i] = sc.nextInt();
        }

        Solution s = new Solution();
        System.out.println(s.solution(N, distances, prices));
    }
}

class Solution {
    public long solution(int N, long[] distances, long[] prices) {
        long answer = 0;
        int i = 0, j = 0;
        long minPrice = prices[0];

        while (i < N - 1) {
            if (minPrice > prices[j]) {
                minPrice = prices[j];
            }
            answer += distances[i] * minPrice;
            j++;
            i++;
        }
        return answer;
    }
}