/*
 https://www.acmicpc.net/problem/2565
 전깃줄
 두 전봇대 A와 B 사이에 하나 둘씩 전깃줄을 추가하다 보니 전깃줄이 서로 교차하는 경우가 발생하였다. 합선의 위험이 있어 이들 중 몇 개의 전깃줄을 없애 전깃줄이 교차하지 않도록 만들려고 한다.

 예를 들어, < 그림 1 >과 같이 전깃줄이 연결되어 있는 경우 A의 1번 위치와 B의 8번 위치를 잇는 전깃줄, A의 3번 위치와 B의 9번 위치를 잇는 전깃줄, A의 4번 위치와 B의 1번 위치를 잇는 전깃줄을 없애면 남아있는 모든 전깃줄이 서로 교차하지 않게 된다.

 전깃줄이 전봇대에 연결되는 위치는 전봇대 위에서부터 차례대로 번호가 매겨진다. 전깃줄의 개수와 전깃줄들이 두 전봇대에 연결되는 위치의 번호가 주어질 때, 남아있는 모든 전깃줄이 서로 교차하지 않게 하기 위해 없애야 하는 전깃줄의 최소 개수를 구하는 프로그램을 작성하시오.
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    int N;
    cin >> N;
    int answer = 0;
    vector<vector<int>> connected;
    vector<int> arr;
    vector<int> dp(N, 1);
    
    
    for(int i = 0; i < N; i++){
        int A, B;
        cin >> A >> B;
        connected.push_back({A, B});
    }
    sort(connected.begin(), connected.end());

    for(int i = 0; i < N; i++){
        arr.push_back(connected[i][1]);
    }
    
    for(int i = 1; i < N; i++){
        for(int j = i - 1; j > -1; j--){
            if(arr[i] > arr[j])
                dp[i] = max({dp[j] + 1, dp[i]});
        }
        if(dp[i] > answer)
            answer = dp[i];
    }
    answer = N - answer;
    cout << answer;
}
