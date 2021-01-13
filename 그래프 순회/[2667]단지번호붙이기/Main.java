import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Main {
    public static void main(String arg[]) throws NumberFormatException, IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        int N = Integer.parseInt(br.readLine());

        String[][] arr = new String[N][N];
        vertex[][] verList = new vertex[N][N];

        int idx = 1;

        // input
        for (int i = 0; i < N; i++) {
            String[] tmp = br.readLine().split("");
            arr[i] = tmp;
            for (int j = 0; j < N; j++) {
                if (arr[i][j] == "1") {
                    verList[i][j] = new vertex(i,j);
                    verList[i][j].index = idx++;

                    int minInd = verList[i][j].index;

                    if(i>0 && verList[i-1][j]!=null){
                        if(minInd>verList[i-1][j].index){
                            minInd = verList[i-1][j].index;
                        }else{
                            verList[i-1][j].index = minInd;
                        }
                    }
                    if(j>0 && verList[i][j-1]!=null){
                        if(minInd>verList[i][j-1].index){
                            minInd = verList[i][j-1].index;
                        }else{
                            verList[i][j-1].index = minInd;
                        }
                    }
                }
            }
        }
    }
}

class vertex {
    int i, j;
    int index;

    public vertex(int i, int j) {
        this.i = i;
        this.j = j;
        this.index = 0;
    }
}