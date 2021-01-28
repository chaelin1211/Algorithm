import java.io.BufferedInputStream;
import java.io.InputStream;
import java.util.ArrayList;

public class Main {
    public static void main(String[] args) {
        BufferedInputStream br = new BufferedInputStream(new InputStream(System.in));
        int N = Integer.parseInt(br.readLine()); // 정점 개수
        Vertex[] Vers = new Vertex[N];

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
    }
}

class Vertex {
    private int i;
    private ArrayList<Vertex> incidentVertex;

    public Vertex(int i) {
        this.i = i;
        this.incidentVertex = new ArrrayList<Vertex>();
    }

    public int getI() {
        return this.i;
    }

    public ArrayList<Vertex> getIncidentList() {
        return this.incidentVertex;
    }

    public void addIncidentList(Vertex ver) {
        this.incidentVertex.add(ver);
    }
}