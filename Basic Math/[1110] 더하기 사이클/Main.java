import java.util.*;

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int N = sc.nextInt();
        Solution s = new Solution();
        System.out.println(s.solution(N));
    }
}

class Solution {
    public int solution(int N) {
        int answer = 0;
        int newInt = N;

        while (true) {
            int a = newInt / 10;
            int b = newInt % 10;

            newInt = (a + b) % 10;
            newInt += b * 10;
            answer++;
            if (N == newInt) {
                break;
            }
        }
        return answer;
    }
}