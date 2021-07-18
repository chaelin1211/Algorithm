import java.lang.Math;
class Solution {
    public int solution(int[] nums) {
        int answer = 0;
        int n = nums.length;
    
        int sum = 0;
        for(int i = 0;i < n-2 ; i++){
            sum += nums[i];
            for(int j = i+1 ; j < n-1 ; j++){
                sum += nums[j];
                for(int k = j+1 ; k < n; k++){
                    sum += nums[k];
                    if(isPrime(sum)){
                        answer++;
                        System.out.println(i+" "+j+" "+k);
                    }
                    sum -= nums[k];
                }
                sum -= nums[j];
            }
            sum -= nums[i];
        }
        
        return answer;
    }
    public static boolean isPrime(int num){
        double n = Math.sqrt(num);
        for(int i = 2; i <= n ; i++){
            if(num % i == 0){
                return false;
            }
        }
        return true;
    }
}

