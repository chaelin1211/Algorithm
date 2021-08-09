package 프로그래머스.상호평가;

class Solution {
    public String solution(int[][] scores) {
        String answer = "";
        int num = scores.length;
        for (int i = 0; i < num; i++) {
            int min = findMin(scores, i);
            int max = findMax(scores, i);
            float avg = findSum(scores, i);
            if (scores[i][i] == min || scores[i][i] == max) {
                avg -= scores[i][i];
                avg /= (num - 1);
            } else {
                avg /= num;
            }
            System.out.println(min + " " + max + " " + avg + " " + getGrade(avg));
            answer += getGrade(avg);
        }
        return answer;
    }

    public char getGrade(float score) {
        if (score >= 90)
            return 'A';
        if (score >= 80)
            return 'B';
        if (score >= 70)
            return 'C';
        if (score >= 50)
            return 'D';
        return 'F';
    }

    public int findMin(int[][] scores, int i) {
        int min = 101;
        boolean[] flags = new boolean[101];
        for (int j = 0; j < scores.length; j++) {
            int s = scores[j][i];
            if (i != j && s == scores[i][i]) {
                return -1;
            }
            if (flags[s])
                continue;
            flags[s] = true;
            min = min > s ? s : min;
        }
        return min;
    }

    public int findMax(int[][] scores, int i) {
        int max = -1;
        boolean[] flags = new boolean[101];
        for (int j = 0; j < scores.length; j++) {
            int s = scores[j][i];
            if (i != j && s == scores[i][i]) {
                return -1;
            }
            if (flags[s])
                continue;
            flags[s] = true;
            max = max < s ? s : max;
        }
        return max;
    }

    public int findSum(int[][] scores, int i) {
        int sum = 0;
        for (int j = 0; j < scores.length; j++) {
            sum += scores[j][i];
        }
        return sum;
    }
}