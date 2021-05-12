import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Stack;
import java.util.StringTokenizer;

public class Main {
    public static void main(String[] arg) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String input = br.readLine();
        StringTokenizer stk = new StringTokenizer(input);
        int N = Integer.parseInt(stk.nextToken());
        int[] arr = new int[N + 1];

        int i = 1;
        input = br.readLine();
        stk = new StringTokenizer(input);
        while (stk.hasMoreTokens()) {
            arr[i++] = Integer.parseInt(stk.nextToken());
        }

        input = br.readLine();
        stk = new StringTokenizer(input);
        int K = Integer.parseInt(stk.nextToken());
        int[][] terms = new int[K][2];
        for (i = 0; i < K; i++) {
            input = br.readLine();
            stk = new StringTokenizer(input);
            terms[i][0] = Integer.parseInt(stk.nextToken());
            terms[i][1] = Integer.parseInt(stk.nextToken());
        }
        Solution sol = new Solution(N, arr);
        sol.solution(terms);
        sol.printArr();
    }
}

class Solution {
    int N;
    int[] arr;
    Sort sort;

    public Solution(int N, int[] arr) {
        this.N = N;
        this.arr = arr;
        sort = new Sort(arr);
    }

    public void printArr() {
        for (int i = 1; i < arr.length; i++) {
            System.out.print(arr[i] + " ");
        }
        System.out.println();
    }

    public void solution(int[][] terms) {
        Stack<Order> stack = new Stack<Order>();
        int beforOrder = -1;
        // 명령 필터링
        for (int i = terms.length - 1; i >= 0; i--) {
            int A = terms[i][0];
            int B = terms[i][1];
            // DESC order
            if (beforOrder < B) {
                // flag: false (DESC)이면 이전 명령 pop
                if (!stack.isEmpty() && !stack.peek().flag) {
                    stack.pop();
                }
                stack.add(new Order(B, false));
                beforOrder = B;
            }
            // ASC order
            if (beforOrder < A) {
                // flag: true (ASC)이면 이전 명령 pop
                if (!stack.isEmpty() && stack.peek().flag) {
                    stack.pop();
                }
                stack.add(new Order(A, true));
                beforOrder = A;
            }
        }
        int s = 1;
        int e = 1;
        // 정렬 수행
        if (!stack.isEmpty()) {
            e = stack.peek().x;
            sort.sortAsc(e);
        }

        Stack<Integer> arrStack = new Stack<Integer>();
        while (!stack.isEmpty()) {
            Order order = stack.pop();
            int term;
            if (!stack.isEmpty()) {
                Order next = stack.peek();
                term = order.x - next.x;
            } else {
                term = order.x;
            }
            if (order.flag) {
                // ASC
                for (int i = 0; i < term; i++) {
                    arrStack.add(arr[e--]);
                }
            } else {
                // DESC
                for (int i = 0; i < term; i++) {
                    arrStack.add(arr[s++]);
                }
            }
        }
        // 원본 배열과 합치는 과정
        int i = 1;
        while (!arrStack.isEmpty()) {
            arr[i++] = arrStack.pop();
        }
    }
}

class Sort {
    int[] arr;

    public Sort(int[] arr) {
        this.arr = arr;
    }

    public void sortAsc(int x) {
        // inPlaceHeapSort
        buildHeap(1, x);
        int e = x;
        while (e >= 2) {
            int tmp = arr[e];
            arr[e--] = arr[1];
            arr[1] = tmp;

            downHeap(1, e);
        }
    }

    public void buildHeap(int i, int x) {
        if (i > x) {
            return;
        }
        buildHeap(i * 2, x);
        buildHeap(i * 2 + 1, x);
        downHeap(i, x);
    }

    public void downHeap(int i, int x) {
        int ind;
        if (i * 2 > x) {
            return;
        }
        ind = i * 2;
        if (i * 2 + 1 <= x) {
            ind = arr[i * 2] > arr[i * 2 + 1] ? i * 2 : i * 2 + 1;
        }

        if (arr[i] < arr[ind]) {
            int tmp = arr[i];
            arr[i] = arr[ind];
            arr[ind] = tmp;
        }
        downHeap(ind, x);
    }
}

class Order {
    boolean flag; // true: ACS, false: DESC
    int x;

    public Order(int x, boolean flag) {
        this.x = x;
        this.flag = flag;
    }
}