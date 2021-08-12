class Solution {
    public int solution(int[] nums) {
        int answer = 0;
        int n = nums.length;
        int max = n/2;
        
        boolean[] flags = new boolean[200001];
        for(int i:nums){
            if(!flags[i]){
                answer++;
            }else continue;
            flags[i] = true;
        }
        return Math.min(answer, max);
    }
}
