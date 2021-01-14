import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.Queue;

public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        int N = Integer.parseInt(br.readLine()); // 컴퓨터 수
        int M = Integer.parseInt(br.readLine()); // 연결 쌍의 수

        //1~N까지의 정점 존재
        int[] vers = new int[N + 1];

        //정점, 정점과 인전한 정점들
        HashMap<Integer, ArrayList<Integer>> edges = new HashMap<Integer, ArrayList<Integer>>();

        for (int i = 0; i < M; i++) {
            String tmp = br.readLine();
            int a = Integer.parseInt(tmp.split(" ")[0]);
            int b = Integer.parseInt(tmp.split(" ")[1]);

            vers[a] = 1;
            vers[b] = 1;

            if (edges.get(a) == null)
                edges.put(a, new ArrayList<Integer>());
            if (edges.get(b) == null)
                edges.put(b, new ArrayList<Integer>());

            edges.get(a).add(b);
            edges.get(b).add(a);
        }

        //BFS를 활용하기 위한 큐
        Queue<Integer> queue = new LinkedList<Integer>();
        queue.add(1);

        int com = 0;

        while (!queue.isEmpty()) {
            int ind = queue.remove();
            if(vers[ind]!=1) continue;
            com++;
            vers[ind] = 2;
            for (int a : edges.get(ind)) {
                if(vers[a]==1)
                    queue.add(a);
            }
        }
        System.out.println(com - 1);
    }
}
