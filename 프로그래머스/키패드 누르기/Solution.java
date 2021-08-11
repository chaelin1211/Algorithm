
class Solution {
    public String solution(int[] numbers, String hand) {
        String answer = "";
        // set location of fingers
        int[] rFinger = {3, 2};
        int[] lFinger = {3, 0};
        
        // set location of numbers
        int[][] numberLoc = new int[10][2];
        numberLoc[0][0] = 3;
        numberLoc[0][1] = 1;
        for(int i = 0, k = 1 ; i < 3 ; i++){
            for(int j = 0 ; j < 3 ; j++, k++){
                numberLoc[k][0] = i;
                numberLoc[k][1] = j;
            }
        }
        
        // push the key
        char mainHand = (char)(hand.charAt(0) + ('A' - 'a'));
        for(int n:numbers){
            char c;
            if(numberLoc[n][1] == 0){
                c = 'L';
            }else if(numberLoc[n][1] == 2){
                c = 'R';
            }else{
                int r = getDistance(numberLoc[n], rFinger);
                int l = getDistance(numberLoc[n], lFinger);
                c = (r > l? 'L' : (r == l ? mainHand : 'R'));
            }
            
            if(c == 'L'){
                lFinger = numberLoc[n];
            }else{
                rFinger = numberLoc[n];
            }
            answer += c;
        }
        return answer;
    }
    
    public int getDistance(int[]A, int[]B){
        int x = A[0] - B[0];
        int y = A[1] - B[1];
        return Math.abs(x) + Math.abs(y);
    }
}