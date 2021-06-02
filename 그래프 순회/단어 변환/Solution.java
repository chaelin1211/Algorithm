import java.util.*;

class Solution {
    public int solution(String begin, String target, String[] words) {
        int answer = 0;
        Word[] wordsArr = makeGraph(begin, words);

        Queue<Word> queue = new LinkedList<Word>();
        queue.add(wordsArr[0]);
        int sizeOfQueue = queue.size();
        boolean targetVisited = false;
        while (!queue.isEmpty()) {
            if (sizeOfQueue == 0) {
                answer++;
                sizeOfQueue = queue.size();
            }

            Word word = queue.remove();
            sizeOfQueue--;

            if (word.flag) {
                continue;
            }
            word.flag = true;

            if (word.word.equals(target)) {
                return answer;
            }
            queue.addAll(word.inciList);
        }
        return 0;
    }

    public Word[] makeGraph(String begin, String[] words) {
        int N = words.length + 1;
        Word[] wordsArr = new Word[N];
        wordsArr[0] = new Word(begin); // first word: begin word
        for (int i = 1, j = 0; i < N; i++, j++) {
            wordsArr[i] = new Word(words[j]);
        }

        for (int i = 0; i < N - 1; i++) {
            String str1 = wordsArr[i].word;
            for (int j = i + 1; j < N; j++) {
                String str2 = wordsArr[j].word;
                if (checkWords(str1, str2)) {
                    wordsArr[i].addInciWord(wordsArr[j]);
                    wordsArr[j].addInciWord(wordsArr[i]);
                }
            }
        }
        return wordsArr;
    }

    public boolean checkWords(String str1, String str2) {
        int ans = 0;
        for (int i = 0; i < str1.length(); i++) {
            if (str1.charAt(i) != str2.charAt(i)) {
                ans++;
                if (ans > 1) {
                    return false;
                }
            }
        }
        return true;
    }
}

class Word {
    ArrayList<Word> inciList;
    String word;
    boolean flag;

    public Word(String word) {
        this.word = word;
        flag = false;
    }

    public void addInciWord(Word word) {
        if (inciList == null)
            inciList = new ArrayList<Word>();
        inciList.add(word);
    }
}