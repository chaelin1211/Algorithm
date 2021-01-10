import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.LinkedList;
import java.util.Queue;

public class Main {
	public static void main(String arg[]) {
		int n=4;
		int [][] nationality = {{1,2},{2,3},{1,3}};
		int answer=0;

		int[] studentArr = new int[n+1];		//각 학생의 국가 번호를 저장하는 배열
		int[] nationArr = new int[n+1];		//각 국가별 학생 수를 저장하는 배열
											//국가 번호가 1부터 시작하니 index 0은 공석
		int nNum=1;	//국가 번호
					//같은 국가를 가진 학생은 같은 번호를 가지게 된다.
		
		int numberOfStudent=0;
		for(int[] arr:nationality) {
			int i = arr[0];
			int j = arr[1];
			int tmp=0;
			
			if(studentArr[j]!=0&&studentArr[i]!=0){
				continue;
			}
			
			if(studentArr[i]!=0) {
				tmp = studentArr[i];
				nationArr[tmp]++;
				
				studentArr[j] = tmp;
				numberOfStudent++;
			}else if(studentArr[j]!=0) {
				//studentArr[i] = 0임
				tmp = studentArr[j];
				nationArr[tmp]++;
				
				studentArr[i] = tmp;
				numberOfStudent++;
			}else {
				//studentArr[i] = 0
				//studentArr[j] = 0
				
				nationArr[nNum]+=2;
				
				studentArr[i] = nNum;
				studentArr[j] = nNum++;
				numberOfStudent+=2;
			}
		}
		
		while(numberOfStudent<n) {
			studentArr[numberOfStudent++] = nNum;	//학생 정보 추가
			nationArr[nNum++]++;					//국가 배열 정보 추가
		}
		
		for(int i=0;i<n-1;i++) {
			for(int j=i+1;j<n;j++) {
				answer += nationArr[i]*nationArr[j];
			}
        }
        System.out.println(answer);
	}
}