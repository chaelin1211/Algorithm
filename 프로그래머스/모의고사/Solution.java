import java.util.*;
class Solution {
    public int[] solution(int[] answers) {
        int[][] stds = {
            {1, 2, 3, 4, 5}
            , {2, 1, 2, 3, 2, 4, 2, 5}
            , {3, 3, 1, 1, 2, 2, 4, 4, 5, 5}
        };
        
        int[] scores = new int[3];
        for(int i = 0 ; i < answers.length ; i++){
            for(int j = 0 ; j < stds.length; j++){
                int[] std = stds[j];
                if(std[i%std.length] == answers[i]){
                    scores[j] ++;
                }
            }
        }
        
        int max = Math.max(scores[0], Math.max(scores[1],scores[2]));
        
        ArrayList<Integer> list = new ArrayList<>();
        for(int i=0 ; i < scores.length ; i++){
            if(scores[i] == max){
                list.add(i+1);
            }
        }

        int[] answer = new int[list.size()];
        for(int i = 0;i<list.size();i++){
            answer[i] = list.get(i);
        }
        
        return answer;
    }
}
