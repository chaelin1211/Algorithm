import java.util.*;
class Solution {
    public String solution(String new_id) {
        String answer = new_id.toLowerCase();
        // 소문자, 숫자, -_. 제외 다 제거
        // . 두 개 이상 .으로 변경
        // 시작, 끝 . 제거
        answer = answer.replaceAll("[^a-z0-9-_.]", "")
                        .replaceAll("[.]{2,}", ".")
                        .replaceAll("^[.]|[.]$", "");
        System.out.println(answer);
        
        if(answer.length() > 15) {
            answer = answer.substring(0, 15)
                    .replaceAll("^[.]|[.]$", "");
        } else if(answer.equals("")){
            answer = "aaa";
        } else if(answer.length() < 3){
            String last = Character.toString(answer.charAt(answer.length() - 1));
            while(answer.length() < 3){
                answer += last;
            }
        }
        System.out.println(answer);

        return answer;
    }
}
