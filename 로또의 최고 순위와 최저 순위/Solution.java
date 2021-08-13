class Solution {
    public int[] solution(int[] lottos, int[] win_nums) {
        boolean[] flagsLottos = new boolean[46];
        boolean[] flagsWinNums = new boolean[46];
        int[] grade = {6, 6, 5, 4 ,3 ,2 ,1};
        int max = 0, min = 0;
        int zero = 0;
        for(int i : lottos){
            flagsLottos[i] = true;
            if(i == 0) zero++;
        }
        for(int i : win_nums){
            flagsWinNums[i] = true;
            if (flagsLottos[i]) {
                min++;
            }
        }
        max = min + zero;

        int[] answer = {grade[max], grade[min]};
        return answer;
    }
}
