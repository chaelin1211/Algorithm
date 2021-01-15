import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        String input = br.readLine();
        int N = Integer.parseInt(input);

        HashMap<Integer, ArrayList<schedule>> hash = new HashMap<Integer, ArrayList<schedule>>();

        for (int i = 0; i < N; i++) {
            input = br.readLine();
            int a, b;
            a = Integer.parseInt(input.split(" ")[0]);
            b = Integer.parseInt(input.split(" ")[1]);
            if(hash.get(a)==null){
                hash.put(a, new ArrayList<schedule>());
            }
            hash.get(a).add(new schedule(a, b));
        }
        System.out.println(function(hash));
    }

    public static int function(HashMap<Integer, ArrayList<schedule>> hash) {
        int i = A[A.length - 1];
        int count = 0;

        while (K != 0) {
            if (K < A[i]) {
                i--;
                continue;
            }
            K -= A[i];
            count++;
        }
        return count;
    }
}

class schedule {
    int sTime;
    int eTime;
    int mTime; // meeting time

    public schedule(int sTime, int eTime) {
        this.sTime = sTime;
        this.eTime = eTime;
        this.mTime = this.eTime - this.sTime;
    }
}