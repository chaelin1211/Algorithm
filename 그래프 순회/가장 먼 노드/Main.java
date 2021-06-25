import java.util.*;
class Solution {
    public int solution(int n, int[][] edge) {
        int answer = 0;
        HashMap<Integer, ArrayList<Integer>> hash = new HashMap<Integer, ArrayList<Integer>>();
        
        for(int i = 1; i<=n;i++){
            hash.put(i, new ArrayList<Integer>());    
        }
        
        for(int[]e:edge){
            int ver1 = e[0];
            int ver2 = e[1];
            hash.get(ver1).add(ver2);
            hash.get(ver2).add(ver1);
        }
        
        boolean[] flags = new boolean[n+1];
        Queue<Integer> queue = new LinkedList<Integer>();
        queue.add(1);
        int sizeOfQueue = 1;
        while(!queue.isEmpty()){
            if(sizeOfQueue == 0){
                answer = queue.size();
                sizeOfQueue = queue.size();
            }
            int ver = queue.remove();
            sizeOfQueue--;
            if(flags[ver]){
                answer--;
                continue;
            }
            flags[ver] = true;
            ArrayList<Integer> inciList = hash.get(ver);
            for(int v:inciList){
                if(flags[v]){
                    continue;
                }
                queue.add(v);
            }
        }
        return answer;
    }
}
