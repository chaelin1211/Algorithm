import java.io.BufferedInputStream;
import java.io.InputStream;

public class Main {
    public static void main(String[] args) {
        BufferedInputStream br = new BufferedInputStream(new InputStream(System.in));
        int N = Integer.parseInt(br.readLine());        //정점 개수
        int[][] incidentArray = new int[N][N];
        
        //input incidentTable
        for(int i=0;i<N;i++){
            String input = br.readLine();
            for(int j=0;j<N;j++){
                incidentArray[i][j] = Integer.parseInt(input.split(" ")[j]);
            }
        }
    }
}
