/*
 https://programmers.co.kr/learn/courses/30/lessons/42861
 문제 설명
 n개의 섬 사이에 다리를 건설하는 비용(costs)이 주어질 때, 최소의 비용으로 모든 섬이 서로 통행 가능하도록 만들 때 필요한 최소 비용을 return 하도록 solution을 완성하세요.

 다리를 여러 번 건너더라도, 도달할 수만 있으면 통행 가능하다고 봅니다. 예를 들어 A 섬과 B 섬 사이에 다리가 있고, B 섬과 C 섬 사이에 다리가 있으면 A 섬과 C 섬은 서로 통행 가능합니다.

 제한사항

 섬의 개수 n은 1 이상 100 이하입니다.
 costs의 길이는 ((n-1) * n) / 2이하입니다.
 임의의 i에 대해, costs[i][0] 와 costs[i] [1]에는 다리가 연결되는 두 섬의 번호가 들어있고, costs[i] [2]에는 이 두 섬을 연결하는 다리를 건설할 때 드는 비용입니다.
 같은 연결은 두 번 주어지지 않습니다. 또한 순서가 바뀌더라도 같은 연결로 봅니다. 즉 0과 1 사이를 연결하는 비용이 주어졌을 때, 1과 0의 비용이 주어지지 않습니다.
 모든 섬 사이의 다리 건설 비용이 주어지지 않습니다. 이 경우, 두 섬 사이의 건설이 불가능한 것으로 봅니다.
 연결할 수 없는 섬은 주어지지 않습니다.
 
 입출력 예

 n    costs    return
 4    [[0,1,1],[0,2,2],[1,2,5],[1,3,1],[2,3,8]]    4
 
 */
#include <string>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

vector<int> check;

bool comp(vector<int> a, vector<int> b) {
    return a[2] < b[2];
}

int getRoot(int vertex) {
    if(check[vertex] == vertex)
        return vertex;
    return getRoot(check[vertex]);
}

bool isCycle(int vertex1, int vertex2){
    if(getRoot(vertex1) == getRoot(vertex2))
        return true;
    return false;
}

int makeBridge(vector<int> vertex){
    if(isCycle(vertex[0], vertex[1]))
       return 0;
    int vertex1 = getRoot(vertex[0]);
    int vertex2 = getRoot(vertex[1]);
    
    if(vertex1 < vertex2)
        check[vertex1] = vertex2;
    else
        check[vertex2] = vertex1;
    
    return vertex[2];
}

int solution(int n, vector<vector<int>> costs) {
    int answer = 0;
    int count = 1;
    sort(costs.begin(), costs.end(), comp);
    for(int i = 0; i < n; i++){
        check.push_back(i);
    }
    
    for(int i = 0; i < costs.size(); i++){
        if(count == n)
            break;
        int cost = makeBridge(costs[i]);
        if(cost != 0){
            answer += cost;
            count++;
        }
            
    }
    
    return answer;
}
