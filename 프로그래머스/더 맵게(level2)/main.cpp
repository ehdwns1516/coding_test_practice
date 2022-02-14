#include <string>
#include <vector>
#include <queue>

using namespace std;

int solution(vector<int> scoville, int K) {
    int answer = 0;
    priority_queue<int, vector<int>, greater<int>> minHeap;
    
    for(int i = 0; i < scoville.size(); i++){
        minHeap.push(scoville[i]);
    }
    
    while(minHeap.size() > 1) {
        int minFood = minHeap.top();
        if(minFood >= K)    break;
        minHeap.pop();
        int nextMinFood = minHeap.top();
        minHeap.pop();
        minHeap.push(minFood + (nextMinFood * 2));
        answer++;
    }
    
    if(minHeap.top() < K)
        answer = -1;
    
    return answer;
}
