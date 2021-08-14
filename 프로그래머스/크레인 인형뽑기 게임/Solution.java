import java.util.*;

class Solution {
    public int solution(int[][] board, int[] moves) {
        int answer = 0;
        Stack<Integer> basket = new Stack<Integer>();
        for(int i:moves){
            i--;
            int j = -1;
            while(++j < board.length && board[j][i] == 0){}
            if(j >= board.length || board[j][i] == 0){
                continue;
            }
            if(basket.size() == 0 || basket.peek() != board[j][i]){
                basket.push(board[j][i]);
                board[j][i] = 0;
            }
            else if(basket.size() > 0 && basket.peek() == board[j][i]){
                board[j][i] = 0;
                basket.pop();
                answer+=2;
            }
        }
        return answer;
    }
}
