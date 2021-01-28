import java.io.BufferedInputStream;
import java.io.InputStream;
import java.util.ArrayList;
import java.util.Queue;

public class Main {
    public static void main(String[] args) {
        BufferedInputStream br = new BufferedInputStream(new InputStream(System.in));
        int N = Integer.parseInt(br.readLine()); // 정점 개수
        Vertex[] Vers = new Vertex[N];
        int[][] possiblePath = new int[N][N];

        // input incidentTable
        // set vertexes
        for (int i = 0; i < N; i++) {
            String input = br.readLine();
            for (int j = 0; j < N; j++) {
                if (Integer.parseInt(input.split(" ")[j]) == 1) {
                    vers[i].addIncidentList(vers[j]);
                }
            }
        }

        possiblePath = function(vers, N);
    }

    public int[][] function(Vertex[] vers, int N) {
        int[][] possiblePath = new int[N][N];
        for (int i = 0; i < N; i++) {
            Vertex ver = vers[i];

            Queue<Vertex> incidentList = new LinkedList<Vertex>();
            incidentList.addAll(ver.getIncidentList());
            while (!incidentList.isEmpty()) {
                Vertex tmpVer = incidentList.remove(0);

                // 중복 순회 방지
                if (possiblePath[i][tmpVer.getI()] == 0) {
                    possiblePath[i][tmpVer.getI()] = 1;
                    possiblePath[tmpVer.getI()][i] = 1;
                    queue.addAll(tmpVer.getIncidentList());
                }
            }

        }
        return possiblePath;
    }
}

class Vertex {
    private int i;
    private Queue<Vertex> incidentVertex;

    public Vertex(int i) {
        this.i = i;
        this.incidentVertex = new LinkedList<Vertex>();
    }

    public int getI() {
        return this.i;
    }

    public Queue<Vertex> getIncidentList() {
        return this.incidentVertex;
    }

    public void addIncidentList(Vertex ver) {
        this.incidentVertex.add(ver);
    }
}