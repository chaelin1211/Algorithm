import java.io.BufferedReader;

public class Main {
    public static void main(String[] args) {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int T = Integer.parseInt(br.readLine());
        int x, y;
        for (int i = 0; i < T; i++) {
            String input = br.readLine();
            x = input.split(" ")[0];
            y = input.split(" ")[1];
            System.out.println(function());
        }
    }
}
