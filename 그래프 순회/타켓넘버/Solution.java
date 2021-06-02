import java.util.*;

public class Solution {
    public int solution(int[] numbers, int target) {
        Stack<Number> stack = new Stack<Number>();
        stack.add(new Number(0, numbers[0]));
        stack.add(new Number(0, numbers[0] * -1));

        int N = numbers.length;
        int answer = 0;
        while (!stack.isEmpty()) {
            Number num = stack.pop();
            int sum = num.accumulateSum;
            int ind = num.index;

            if (ind + 1 >= N) {
                if (sum == target) {
                    answer++;
                }
                continue;
            }
            ind++;
            stack.add(new Number(ind, sum + numbers[ind]));
            stack.add(new Number(ind, sum - numbers[ind]));
        }
        return answer;
    }
}

class Number {
    int index;
    int accumulateSum;

    public Number(int index, int accumulateSum) {
        this.index = index;
        this.accumulateSum = accumulateSum;
    }
}