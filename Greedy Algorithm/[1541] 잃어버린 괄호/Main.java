import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        String input = br.readLine();
        String[] term = input.split("-");
        System.out.println(AddFunction(term));
    }

    public static int AddFunction(String[] term) {
        int sum = 0;
        int i = 0;
        while (i < term.length) {
            int tmpSum = 0;
            if (!term[i].contains("+")) {
                tmpSum = Integer.parseInt(term[i]);
            } else {
                //split, replaceAll 등을 사용할 때 +, [, ], (, ) 등의 문자를
                //사용할 때는 \\를 앞에 붙여주어야 한다
                String[] tmpArr = term[i].split("\\+");
                for (String tmp : tmpArr) {
                    tmpSum += Integer.parseInt(tmp);
                }
            }
            sum = (i==0)?tmpSum:sum-tmpSum;
            i++;
        }
        return sum;
    }
}
