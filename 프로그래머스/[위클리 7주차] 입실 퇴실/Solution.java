import java.util.*;
class Solution {
    public int[] solution(int[] enter, int[] leave) {
        int[] answer = new int[enter.length];
        ArrayList<Integer> list = new ArrayList<Integer>();
        int e = 0;
        int l = 0;
        int n = enter.length;
        while(e < n && l < n){
            if(list.contains(leave[l])){
                list.remove(Integer.valueOf(leave[l]));
                l++;
            }else{
                answer[enter[e]-1] += list.size();
                for(int r:list){
                    answer[r-1] ++;
                }
                list.add(enter[e]);
                e++;
            }
        }
        return answer;
    }
}
