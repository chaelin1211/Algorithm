import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.util.ArrayList;
import java.util.HashMap;

public class Main {

    public static void main(String arg[]) throws NumberFormatException, IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        String str = br.readLine();

        int M = Integer.parseInt(str.split(" ")[0]);
        int N = Integer.parseInt(str.split(" ")[1]);

        int numberOfZero = 0;
        int index;

        vertex[] verts = new vertex[N * M];

        // 현재 익어있는 토마토~
        ArrayList<Integer> vertexesOfOne = new ArrayList<Integer>();

        for (int i = 0; i < N; i++) {
            str = br.readLine();
            for (int j = 0; j < M; j++) {
                int tmp = Integer.parseInt(str.split(" ")[j]);
                index = i * M + j;

                verts[index] = new vertex(index, tmp);
                verts[index].incidentList = incidentList(i, j, N, M, verts);

                if (tmp == 1) {
                    vertexesOfOne.add(index);
                } else if (tmp == 0) {
                    numberOfZero++;
                }
            }
        }

        System.out.println(func(verts, vertexesOfOne, numberOfZero));
    }

    public static int func(vertex[] verts, ArrayList<Integer> vertexesOfOne, int numberOfZero) {
        int count = 0;
        int ind = 0;

        if (numberOfZero == 0) {
            return count;
        }
        // 한 레벨을 한 리스트에 넣고 다음 레벨은 다른 리스트에 넣어 레벨 간의 구별을 해주고자 함
        // 두 리스트를 번갈아 사용하고자 하였고 쉽게 이용하기 위해 리스트를 배열로 다시 구성
        ArrayList<Integer>[] ListToggle = new ArrayList[2];
        ListToggle[0] = vertexesOfOne;
        ListToggle[1] = new ArrayList<Integer>();

        while (!ListToggle[ind].isEmpty() && numberOfZero > 0) {
            vertex nowVer = verts[(int) ListToggle[ind].remove(0)];

            int[] incidentList = nowVer.incidentList;

            if (incidentList.length == 0) {
                continue;
            }

            ArrayList<Integer> tmpList = new ArrayList<Integer>();
            for (int i : incidentList) {
                vertex inciVer = verts[i];

                if (inciVer.number != 0)
                    continue;
                // 주위의 토마토가 익는 중~
                inciVer.number = 1;
                numberOfZero--;

                tmpList.add(inciVer.index);
            }

            if (ind == 0) {
            	if(ListToggle[1].size()==0) count++;
                ListToggle[1].addAll(tmpList);
            } else if (ind == 1) {
            	if(ListToggle[0].size()==0) count++;
                ListToggle[0].addAll(tmpList);
            }
            
            if (ListToggle[ind].isEmpty()) {
                if (ind == 0)
                    ind = 1;
                else
                    ind = 0;
            }
        }

        if (numberOfZero > 0) {
            count = -1;
        }
        return count;
    }

    public static int[] incidentList(int i, int j, int N, int M, vertex[] verts) {
    	int[] tmp = new int[4];
    	int k=0;
        int x;

        // 상
        if (i > 0) {
            x = (i - 1) * M + j;
            tmp[k++]=x;
        }

        // 하
        if (i < N - 1) {
            x = (i + 1) * M + j;
            tmp[k++]=x;
        }

        // 좌
        if (j > 0) {
            x = i * M + (j - 1);
            tmp[k++]=x;
        }

        // 우
        if (j < M - 1) {
            x = i * M + (j + 1);
            tmp[k++]=x;
        }
        return tmp;
    }
}

class vertex {
    int index;
    int number;
	int[] incidentList;

    public vertex() {
        this.index = 0;
        this.number = 0;
    }

    public vertex(int index, int number) {
        this.index = index;
        this.number = number;
    }
}
