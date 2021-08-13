import java.util.*;
class Solution {
    public String solution(String new_id) {
        String answer = new_id.toLowerCase();
        answer = removeCharacter(answer);
        answer = removeDot(answer);
        if(answer.length() > 15)
            answer = answer.substring(0, 16);
        System.out.print(answer);
        return answer;
    }
    public String removeCharacter(String answer){
        String cstr = "~!@#$%^&*()=+[{]}:?,<>/";
        for(int i = 0;i<cstr.length();i++){
            String bc = Character.toString(cstr.charAt(i));
            answer = answer.replaceAll("\\"+bc, "");
        }
        cstr = "..";
        while(answer.contains(cstr)) {
            System.out.println(answer);
            answer = answer.replaceAll("\\.\\.", ".");
            System.out.println(answer);
        }
        return answer;
    }
    public String removeDot(String answer){
        while(answer.startsWith(".")){
            answer = answer.replaceFirst(".", "");
        }

        while(answer.endsWith(".") || answer.length() > 15){
            answer = answer.substring(0, answer.length()-1);
        }
        if(answer.equals("")){
            answer = "aaa";
        }
        String last = Character.toString(answer.charAt(answer.length() - 1));
        while(answer.length() < 3){
            answer += last;
        }
        return answer;
    }
}
