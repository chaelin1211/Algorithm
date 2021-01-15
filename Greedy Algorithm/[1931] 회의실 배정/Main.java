import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.Stack;

public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        String input = br.readLine();
        int N = Integer.parseInt(input);

        ArrayList<schedule> scheduleArr = new ArrayList<schedule>();

        for (int i = 0; i < N; i++) {
            input = br.readLine();
            int a, b;

            a = Integer.parseInt(input.split(" ")[0]);
            b = Integer.parseInt(input.split(" ")[1]);

            scheduleArr.add(new schedule(a, b));
        }
        System.out.println(function(scheduleArr));
    }

    public static int function(ArrayList<schedule> arr) {
        if (arr.isEmpty())
            return 0;

        Collections.sort(arr);

        // 확정된 스케줄을 저자하는 스택
        Stack<schedule> stack = new Stack<schedule>();
        stack.add(arr.remove(0));

        while (!arr.isEmpty()) {
            schedule nowSchedule = arr.remove(0);
            schedule beforeSchedule = stack.pop();

            if (nowSchedule.getStime() < beforeSchedule.getEtime()) {
                //스케줄이 겹치는 경우 앞에 위치한 스케줄 확정
                stack.push(beforeSchedule);
            } else {
                stack.push(beforeSchedule);
                stack.push(nowSchedule);
            }
        }

        return stack.size();
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
        // 우선적으로 끝나는 시간을 비교
        if (this.getEtime() > s.getEtime()) {
            return 1;
        } else if (this.getEtime() == s.getEtime()) {
            // 2차적으로 시작 시간 비교
            if (this.getStime() > s.getStime()) {
                return 1;
            } else
                return -1;
        } else {
            return -1;
        }
    }
}