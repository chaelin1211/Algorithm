import java.util.*;

public class Main {
	public static void main(String[] args) {
		String[][] tickets = { { "ICN", "SFO" }, { "ICN", "ATL" }, { "SFO", "ATL" }, { "ATL", "ICN" },
				{ "ATL", "SFO" } };
//		[['ICN','B'],['B','ICN'],['ICN','A'],['A','D'],['D','A']]
//				answer = ['ICN', 'B', 'ICN', 'A', 'D', 'A']
		Solution s = new Solution();

		System.out.println(s.solution(tickets));
	}
}

class Solution {
	String startPoint = "ICN";

	public String[] solution(String[][] tickets) {
		HashMap<String, Airport> hash = new HashMap<String, Airport>();
//		그래프 생성
		for (String[] ticket : tickets) {
			for (String ap : ticket) {
				if (hash.get(ap) == null) {
					hash.put(ap, new Airport(ap));
				}
			}
//			간선 추가
			Airport sAP = hash.get(ticket[0]);
			Airport eAP = hash.get(ticket[1]);
			sAP.addInciAp(eAP);
		}

//		오름차순을 위한 정렬
		for (Airport apo : hash.values()) {
			apo.sortInciAp();
		}

		Airport begin = hash.get(startPoint);
		return DFS(tickets.length, begin);
	}

	public String[] DFS(int N, Airport begin) {
		String[] visited = new String[N + 1];
		visited[0] = startPoint;
		rDFS(N, 1, begin, visited);
		return visited;
	}

	public int rDFS(int N, int cnt, Airport begin, String[] visited) {
		if (cnt == N+1) {
			return cnt;
		}

		for (Ticket edg : begin.inciList) {
			if (edg.flag) {
				continue;
			}
			edg.flag = true;
			visited[cnt] = edg.e.code;
			cnt = rDFS(N, cnt+1, edg.e, visited);

//			모든 항공권을 사용해야 하기 때문에 아닌 경로는 버린다
			if (cnt < N+1) {
				cnt--;
				edg.flag = false;
				continue;
			}
		}
		return cnt;
	}
}

// vertex
class Airport {
	String code;
	ArrayList<Ticket> inciList;

	public Airport(String code) {
		this.code = code;
		inciList = new ArrayList<Ticket>();
	}

	public void addInciAp(Airport ap) {
		inciList.add(new Ticket(this, ap));
	}

	public void sortInciAp() {
		if (inciList.size() > 1)
			Collections.sort(inciList);
	}

}

// edge
class Ticket implements Comparable<Ticket> {
	Airport s, e;
	boolean flag = false;

	public Ticket(Airport s, Airport e) {
		this.s = s;
		this.e = e;
	}

	@Override
	public int compareTo(Ticket o) {
		return this.e.code.compareTo(o.e.code);
	}
}