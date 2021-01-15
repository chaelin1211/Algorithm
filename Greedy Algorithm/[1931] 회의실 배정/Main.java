import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;

public class Main {
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

		String input = br.readLine();
		int N = Integer.parseInt(input);

		ArrayList<schedule> scheduleArr = new ArrayList<schedule>();
		HashMap<Integer, Integer> numOfSchedule = new HashMap<Integer, Integer>();

		for (int i = 0; i < N; i++) {
			input = br.readLine();
			int a, b;

			a = Integer.parseInt(input.split(" ")[0]);
			b = Integer.parseInt(input.split(" ")[1]);

			scheduleArr.add(new schedule(a, b));
			if (numOfSchedule.get(a) == null)
				numOfSchedule.put(a, 1);
			else {
				int x = numOfSchedule.get(a);
				numOfSchedule.put(a, x + 1);
			}
		}
		System.out.println(function(scheduleArr, numOfSchedule));
	}

	public static int function(ArrayList<schedule> arr, HashMap<Integer, Integer> numOfSchedule) {
		int count = 0;

		if (arr.isEmpty())
			return 0;

		Collections.sort(arr);
		schedule beforeSchedule = arr.remove(0);
		int numOfImpossibleScheduleBefore = numOfImpossibleSchedule(beforeSchedule, numOfSchedule);
		schedule nowSchedule;
		while (!arr.isEmpty()) {
			nowSchedule = arr.remove(0);

			int numOfImpossibleScheduleNow = numOfImpossibleSchedule(nowSchedule, numOfSchedule);

			if (beforeSchedule.getEtime() < nowSchedule.getStime()) {
				count++;
				beforeSchedule = nowSchedule;
				numOfImpossibleScheduleBefore = numOfImpossibleScheduleNow;
				if(arr.isEmpty()) count++;
				continue;
			}

			numOfImpossibleScheduleNow++;

			if (numOfImpossibleScheduleBefore > numOfImpossibleScheduleNow) {
				beforeSchedule = nowSchedule;
				numOfImpossibleScheduleBefore = --numOfImpossibleScheduleNow;
			}else {
				int tmp = nowSchedule.getStime();
				numOfSchedule.put(tmp, numOfSchedule.get(tmp)-1);

				numOfImpossibleScheduleBefore--;
			}
		}
		return count;
	}

	public static int numOfImpossibleSchedule(schedule sch, HashMap<Integer, Integer> numOfSchedule) {
		int count = 0;
		int s = sch.getStime();
		int e = sch.getEtime();

		for (int i = s ; i < e; i++) {
			if (numOfSchedule.get(i) == null)
				continue;
			count += numOfSchedule.get(i);
		}

		return count-1;	//현재 스케줄도 개수에 포함되니 제외해줌
	}
}

class schedule implements Comparable<schedule> {
	private int sTime;
	private int eTime;

	public schedule(int sTime, int eTime) {
		this.sTime = sTime;
		this.eTime = eTime;
	}

	public int getStime() {
		return this.sTime;
	}

	public int getEtime() {
		return this.eTime;
	}

	public int compareTo(schedule s) {
		if (sTime > s.sTime)
			return 1;
		else if (sTime == s.sTime)
			return 0;
		else
			return -1;
	}
}