import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Collections;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Stack;

public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        String input = br.readLine();
        int T = Integer.parseInt(input.split(" ")[0]);
        for (int i = 0; i < T; i++) {
            int N = Integer.parseInt(br.readLine());
            ArrayList<Rank> rank = new ArrayList<Rank>();
            for (int j = 0; j < N; j++) {
                input = br.readLine();
                int a = Integer.parseInt(input.split(" ")[0]);
                int b = Integer.parseInt(input.split(" ")[1]);
                rank.add(new Rank(a, b));
            }
            System.out.println(function(rank));
        }
    }

    public static int function(ArrayList<Rank> ranks) {
        int count = 1;

        // 순위대로 정렬
        // 1차 등급은 비교할 필요 없어짐
        Collections.sort(ranks);

        int minRank = ranks.remove(0).r2;
        for (Rank p : ranks) {
            // 1차 순위가 높은 지원자들보다 2차 순위가 높아야 합격 가능
            if (minRank > p.r2) {
                count++;
                minRank = p.r2;
            }
        }
        return count;
    }
}

class Rank implements Comparable<Rank> {
    int r1, r2;

    public Rank(int r1, int r2) {
        this.r1 = r1;
        this.r2 = r2;
    }

    public int compareTo(Rank r) {
        if (this.r1 > r.r1) {
            return 1;
        } else {
            return -1;
        }
    }
}
