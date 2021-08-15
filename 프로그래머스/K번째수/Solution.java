import java.util.*;
class Solution {
    public int[] solution(int[] array, int[][] commands) {
        int[] answer = new int[commands.length];
        int x = 0;
        for(int[]command:commands){
            int i = command[0]-1;
            int j = command[1];
            int c = command[2]-1;
            
            // index i ~ index j-1까지 복사
            int[] newArr = Arrays.copyOfRange(array, i, j);
            Arrays.sort(newArr);
            answer[x++] = newArr[c];
        }
        return answer;
    }
}
