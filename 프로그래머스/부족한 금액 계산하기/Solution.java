class Solution {
    public long solution(int price, int money, int count) {
        long answer = 0;
        answer = count * (count + 1) / 2;
        answer *= price;
        answer -= money;
        return answer>0 ? answer : 0;
    }
}

// class Solution   {
//     public long solution(int price, int money, int count) {
//         long answer = 0;
//         answer = (long)(count * (count + 1) / 2) * price;
//         answer -= money;
//         return answer>0 ? answer : 0;
//     }
// }