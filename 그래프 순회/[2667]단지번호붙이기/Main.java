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

        //vertex의 존재와 위치를 동시에 확인할 수 있도록 테이블의 형태로 저장
        vertex[][] verTable = new vertex[N][N];

        //1인 정점을 따로 리스트에 모아 관리
        ArrayList<vertex> verList = new ArrayList<vertex>();

        //자료를 입력 받아 저장
        inputFunction(N, verTable, verList);

        //저장된 자료로 단지를 구성
        mainFunciton(verTable, verList);
    }

    public static void mainFunciton(vertex[][] verTable, ArrayList<vertex> verList) {
        //저장된 자료로 단지를 구성

        int size = 0;   //각 단지의 주택 수
        ArrayList<Integer> arrOfSize = new ArrayList<Integer>();    //모든 단지의 주택 수를 저장할 ArrayList
        Queue<vertex> queue = new LinkedList<vertex>();             //BFS 순회를 위해 사용할 Queue

        queue.add(verList.remove(0));
        while (!queue.isEmpty() || !verList.isEmpty()) {
            if (queue.isEmpty()) {          //queue가 비었다는 것은 한 단지를 다 조사했다는 뜻 -> 다음 단지로 넘어감
                arrOfSize.add(size);        //조사한 단지의 주택 수 저장
                size = 0;
                queue.add(verList.remove(0));   //다음 단지로 넘어감   
            }
            vertex ver = queue.remove();

            //중복 조사 방지
            if (ver.flag) {     
                continue;
            }
            ver.flag = true;
            size++;

            ArrayList<edge> edges = ver.inciList;
            
            //한 주택의 인근 주택 조사
            for (edge edg : edges) {
                //이미 지나온 간선은 확인하지 않음
                if (edg.flag) {
                    continue;
                }
                edg.flag = true;
                vertex inciVer = edg.otherVertex(ver);  //한 간선에서 현재 정점의 반대편에 위치하는 정점 리턴
                verList.remove(inciVer);                
                queue.add(inciVer);
            }
        }
        //queue와 verList가 동시에 empty한 경우 이미 조사한 단지의 주택 수를 저장하지 못하고 끝날 수 있음
        //따로 저장해주는 로직
        if (size != 0) {
            arrOfSize.add(size);
        }
        outputFunction(arrOfSize);
    }

    public static void inputFunction(int N, vertex[][] verTable, ArrayList<vertex> verList)
            throws NumberFormatException, IOException {
        // input을 받아 자료를 Table과 List에 저장
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

    public static void outputFunction(ArrayList<Integer> arr) {
        System.out.println(arr.size());
        arr.sort(null);
        for (int a : arr) {
            System.out.println(a);
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