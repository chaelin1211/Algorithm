import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Stack;

public class Main {
    public static void main(String[] args) throws NumberFormatException, IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int T = Integer.parseInt(br.readLine());
        int x, y;
        for (int i = 0; i < T; i++) {
            String input = br.readLine();
            x = Integer.parseInt(input.split(" ")[0]);
            y = Integer.parseInt(input.split(" ")[1]);
            System.out.println(function(x, y));
        }
    }

    public static int function(int x, int y) {
        int answer = 0;
        int i = x; // 현재 위치
        int[] term = new int[3]; // 가능한 이동 반경
        Stack<Integer> location = new Stack<Integer>(); // 위치
        Stack<Integer> termList = new Stack<Integer>();
        
        // 초기값 추가
        int k = 0;
        location.add(x);
        termList.add(k);
        
        while (i < y) {
            k = termList.peek();
            term[0] = k + 1;
            term[1] = k;
            term[2] = k - 1;

            k = -1;
            for (int tmp : term) {
                if (i + tmp < y || (i+tmp == y && tmp ==1)) {
                    k = tmp;
                    break;
                }
            }
            if (k <= 0) { // 가능한 이동 범위가 없음
                termList.add(termList.pop() - 1);
            }else if(i+k == y && k != 1){   //마지막 이동은 1이어야 한다
                termList.add(termList.pop() - 1);
            }else{
                i+=k;             
                location.add(i);
                termList.add(k);   
            }
        }
        answer = location.size()-1;
        return answer;
    }
}
