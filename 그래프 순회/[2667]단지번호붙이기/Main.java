import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Queue;

public class Main {
    static BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

    public static void main(String arg[]) throws NumberFormatException, IOException {
        int N = Integer.parseInt(br.readLine());

        vertex[][] verTable = new vertex[N][N];
        ArrayList<vertex> verList = new ArrayList<vertex>();

        inputFunction(N, verTable, verList);
        mainFunciton(verTable, verList);
    }

    public static void mainFunciton(vertex[][] verTable, ArrayList<vertex> verList) {
        int size = 0;
        ArrayList<Integer> arrOfSize = new ArrayList<Integer>();

        Queue<vertex> queue = new LinkedList<vertex>();
        queue.add(verList.remove(0));
        while (!queue.isEmpty() || !verList.isEmpty()) {
            if (queue.isEmpty()) {
                arrOfSize.add(size);
                size = 0;
                queue.add(verList.remove(0));
            }
            vertex ver = queue.remove();
            if (ver.flag) {
                continue;
            }
            ver.flag = true;
            size++;

            ArrayList<edge> edges = ver.inciList;
            for (edge edg : edges) {
                if (edg.flag) {
                    continue;
                }
                edg.flag = true;
                vertex inciVer = edg.otherVertex(ver);
                verList.remove(inciVer);
                queue.add(inciVer);
            }
        }
        if (size != 0) {
            arrOfSize.add(size);
        }
        outputFunction(arrOfSize);
    }

    public static void inputFunction(int N, vertex[][] verTable, ArrayList<vertex> verList)
            throws NumberFormatException, IOException {

        // input
        for (int i = 0; i < N; i++) {
            String[] tmp = br.readLine().split("");
            for (int j = 0; j < N; j++) {
                int a = Integer.parseInt(tmp[j]);
                if (a == 1) {
                    vertex newVer = new vertex();

                    verList.add(newVer);
                    verTable[i][j] = newVer;

                    inputInciVerToList(i, j, verTable, newVer);
                }
            }
        }
    }

    public static void outputFunction(ArrayList<Integer> arr) {
        System.out.println(arr.size());
        arr.sort(null);
        for (int a : arr) {
            System.out.println(a);
        }
    }

    public static void inputInciVerToList(int i, int j, vertex[][] arr, vertex ver) {
        // 주위의 1인 vertex를 찾아 삽입
        vertex inciVer;
        edge newEdge;
        if (i > 0 && arr[i - 1][j] != null) {
            inciVer = arr[i - 1][j];

            newEdge = new edge(ver, inciVer);
            ver.addEdgeList(newEdge);
            inciVer.addEdgeList(newEdge);
        }
        if (j > 0 && arr[i][j - 1] != null) {
            inciVer = arr[i][j - 1];

            newEdge = new edge(ver, inciVer);
            ver.addEdgeList(newEdge);
            inciVer.addEdgeList(newEdge);
        }

    }
}

class vertex {
    boolean flag;
    // 방문 전 false
    // 방문 후 true
    ArrayList<edge> inciList;

    public vertex() {
        this.inciList = new ArrayList<edge>();
        this.flag = false;
    }

    public void addEdgeList(edge edg) {
        this.inciList.add(edg);
    }
}

class edge {
    vertex s, e;
    boolean flag;

    // 방문 전 false
    // 방문 후 true
    public edge() {
        this.s = null;
        this.e = null;
        flag = false;
    }

    public edge(vertex s, vertex e) {
        this.s = s;
        this.e = e;
        flag = false;
    }

    public vertex otherVertex(vertex ver) {
        if (ver.equals(s))
            return e;
        else if (ver.equals(e))
            return s;
        else
            return null;
    }
}