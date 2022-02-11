#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> solution(vector<int> progresses, vector<int> speeds) {
    vector<int> answer;
    reverse(progresses.begin(), progresses.end());
    reverse(speeds.begin(), speeds.end());
    
    while(progresses.size() > 0){
        int count = 0;
        int workingDays = (100 - progresses.back()) / speeds.back();
        
        if((100 - progresses.back()) % speeds.back() != 0)
            workingDays++;
        
        for(int i = 0; i < progresses.size(); i++){
            progresses[i] = progresses[i] + (speeds[i] * workingDays);
        }
    
        while(progresses.back() >= 100 && progresses.size() > 0){
            count++;
            progresses.pop_back();
            speeds.pop_back();
        }
        answer.push_back(count);
    }
    return answer;
}
