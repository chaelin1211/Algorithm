import java.io.BufferedReader;
import java.io.InputStreamReader;

public class Main {
    public static void main(String[] args) {

        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        
        int A, B, C;
        String input = br.readLine();

        // input
        // A: 노트북 개수에 상관없이 필요한 고정 비용
        // B: 노트북 한 개 생산하는 데 필요한 비용
        // C: 노트북 한 개 판매 가격
        A = Integer.parseInt(input.split(" ")[0]);
        B = Integer.parseInt(input.split(" ")[1]);
        C = Integer.parseInt(input.split(" ")[2]);

        
    }
}
