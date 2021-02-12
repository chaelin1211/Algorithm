import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Main {
	public static void main(String[] args) throws NumberFormatException, IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int T = Integer.parseInt(br.readLine());
		long x, y;                  // 0 ~ 2^-31 범위
		for (int i = 0; i < T; i++) {
			String input = br.readLine();
			x = Integer.parseInt(input.split(" ")[0]);
			y = Integer.parseInt(input.split(" ")[1]);
			System.out.println(function(x, y));
		}
	}

	public static long function(long x, long y) {
		long answer = 0;
		long distance = y - x;
        
		long maxSpeed = (long) Math.sqrt(distance);     // 최대 거리는 거리의 제곱근 이하의 가장 큰 정수
		answer = 2 * maxSpeed - 1;                      // 최대 거리를 기준으로 거리의 목록이 대칭이라고 할 때 이동 거리 (이상적인 경우)
                                                        // ex) 121, 12321, 1234321

		distance -= maxSpeed*maxSpeed;                  // 최대 거리 제곱은 위의 예제(이상적인 경우)의 경우 거리 

        // 초기 distance가 정수의 제곱 사이일 때 (이상적이지 않은 경우) ex) 23: 16과 25 사이
		answer += (distance/maxSpeed);
        if(distance % maxSpeed != 0 ){ 
            answer++;
        }                
    
        // 최대 거리 이상으로 이동할 수 없음 (그 이상으로 이동하면 마지막에 1로 끝낼 수 없음 -> 때문에 최대 거리 이하로만 이동 가능)
        
        // 이상적인 경우 외에 추가로 이동이 필요한 case  -  추가 이동 거리 r
        // 최대거리 이하 이동거리는 한 번의 이동으로 이동할 수 있음 - 이상적인 경우에 이동을 추가해주면 됨
        // ex) 121 -> 1221 or 1211
        // r을 가기위해 필요한 추가 이동은 r/최대거리이고 추가적으로 r%최대거리가 0이 아니면 +1

		return answer;
	}
}
