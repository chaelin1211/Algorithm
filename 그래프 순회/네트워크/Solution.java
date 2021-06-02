import java.util.Stack;

public class Solution {
    public int solution(int N, int[][] computers) {
        int answer = 0;
        boolean[] visited = new boolean[N];
        Stack<Integer> stack = new Stack<Integer>();

        for (int i = 0; i < N; i++) {
            stack.add(i);
        }

        while (!stack.isEmpty()) {
            int number = stack.pop();

            if (!visited[number]) {
                answer++;
                visited[number] = true;
            }

            for (int i = 0; i < N; i++) {
                if (computers[number][i] == 1 && number != i && !visited[i]) {
                    stack.add(i);
                    visited[i] = true;
                }
            }
        }
        return answer;
    }
}