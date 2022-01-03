import java.util.*;

class Solution {
    public int solution(int[] numbers) {
        int answer = 0;
        boolean[] numberFlag = new boolean[10];

        for (int i : numbers) {
            numberFlag[i] = true;
        }

        for (int i = 1; i < 10; i++) {
            if (!numberFlag[i]) {
                answer += i;
            }
        }

        return answer;
    }
}
