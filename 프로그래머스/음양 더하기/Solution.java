class Solution {
    public int solution(int[] absolutes, boolean[] signs) {
        int answer = 0;
        int n = absolutes.length;
        for(int i = 0 ; i < n ; i++){
            int tmp = absolutes[i];
            if(!signs[i]){
                tmp *= -1;
            }
            answer += tmp;
        }
        return answer;
    }
}
