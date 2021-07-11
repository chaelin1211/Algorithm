import java.util.*;
class Solution {
    public int solution(int n, int[][] edge) {
        int answer = 0;
        boolean[][] inciTable = new boolean[n+1][n+1];
        
        for(int[] e:edge){
            int v1 = e[0];
            int v2 = e[1];
            inciTable[v1][v2] = true;
            inciTable[v2][v1] = true;
        }
        
        
        Queue<Integer> queue = new LinkedList<Integer>();
        queue.add(1);
        
        answer = 1;
        int sizeOfQueue = 1;
        boolean[] flags = new boolean[n+1]; 
        // 큐에 삽입되었던 노드는 다시 삽입되지 않도록
        flags[1] = true;
        
        while(!queue.isEmpty()){
            if(sizeOfQueue == 0){
                sizeOfQueue = queue.size();
                if(queue.size() != 0){
                    answer = queue.size();
                }
            }
            
            int ver = queue.remove();
            sizeOfQueue --;
            for(int i = 1;i<=n;i++){
                if(inciTable[ver][i] && !flags[i]){
                    queue.add(i);
                    inciTable[ver][i] = false;
                    inciTable[i][ver] = false;
                    flags[i] = true;
                }
            }
        }
        return answer;
    }
}
