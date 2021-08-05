class Solution {
    public int solution(int n, int[] lost, int[] reserve) {
        int answer = n;
        answer -= lost.length;
        boolean[] flags = new boolean[n + 1];
        
        lost = sortArray(lost);
        reserve = sortArray(reserve);
        for(int i:lost){
            flags[i] = true;
        }
        for(int i = 0; i < reserve.length ; i++){
            int num = reserve[i];
            if(flags[num]){
                flags[num] = false;
                answer ++;
                reserve[i] = -1;
            }
        }
        for(int i = 0; i < reserve.length ; i++ ){
            int j = reserve[i];
            if(j == -1) continue;
            if(flags[j]){
                flags[j] = false;
            }
            else if(j - 1 >= 1 && flags[j-1]){
                flags[j-1] = false;
            }
            else if(j + 1 <= MAX && flags[j+1]){
                flags[j+1] = false;
            }else{
                continue;
            }
            answer ++;
        }
        
        return answer;
    }
    
    public int[] sortArray(int[]arr){
        int n = arr.length;
        for(int i = 0;i<n-1;i++){
            for(int j=i+1;j<n;j++){
                int tmp = 0;
                if(arr[i] > arr[j]){
                    tmp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = tmp;
                }
            }
        }
        for(int i:arr){
            System.out.print(i+" ");
        }
        return arr;
    }
}
