import java.util.*;

public class Main {
    static String[] answers = { "NO", "YES" };

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int T = sc.nextInt();
        Solution s = new Solution();
        for (int i = 0; i < T; i++) {
            int N = sc.nextInt();
            sc.nextLine();
            ArrayList<String> input = new ArrayList<String>();
            for (int j = 0; j < N; j++) {
                input.add(sc.nextLine());
            }
            System.out.println(answers[s.solution(N, input)]);
        }
        sc.close();
    }
}

class Solution {
    public int solution(int N, ArrayList<String> input) {
        int answer = 1;
        Collections.sort(input);

        for (int i = 1; i < N; i++) {
            String str1 = input.get(i - 1);
            String str2 = input.get(i);

            int len1 = str1.length();
            int len2 = str2.length();

            if (len1 <= len2 && str1.equals(str2.substring(0, len1))) {
                answer = 0;
                break;
            }
        }
        return answer;
    }
}