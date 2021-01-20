import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;

public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String input = br.readLine();
        int T = Integer.parseInt(input.split(" ")[0]);
        for (int i = 0; i < T; i++) {
            input = br.readLine();
            int N = Integer.parseInt(input.split(" ")[0]);
            int M = Integer.parseInt(input.split(" ")[1]);
            int K = Integer.parseInt(input.split(" ")[2]);

            ArrayList<Vertex> arr = new ArrayList<Vertex>();
            for (int j = 0; j < K; j++) {
                input = br.readLine();
                int a = Integer.parseInt(input.split(" ")[0]);
                int b = Integer.parseInt(input.split(" ")[1]);
                arr.add(new Vertex(a, b));
            }
            System.out.println(function(N, M, arr));
        }
    }

    public static int function(int N, int M, ArrayList<Vertex> arr) {
        int larva = 0;
        // i, j
        // i순 오름차순 정렬 -> j순 오름차순 정렬
        // 메소드 컨퍼런스 이용
        Comparator<Vertex> reversedComparator = Comparator.comparing(Vertex::getJ).reversed();
        arr.sort(Comparator.comparing(Vertex::getI).thenComparing(reversedComparator));
        return larva;
    }
}

class Vertex {
    int i, j;
    boolean flag;

    // false: fresh
    // true: visited
    public int getI() {
        return this.i;
    }

    public int getJ() {
        return this.J;
    }

    public Vertex(int i, int j) {
        this.i = i;
        this.j = j;
        this.flag = false;
    }
}