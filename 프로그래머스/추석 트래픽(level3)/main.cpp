/*
 https://programmers.co.kr/learn/courses/30/lessons/17676
 문제 설명
 추석 트래픽
 이번 추석에도 시스템 장애가 없는 명절을 보내고 싶은 어피치는 서버를 증설해야 할지 고민이다. 장애 대비용 서버 증설 여부를 결정하기 위해 작년 추석 기간인 9월 15일 로그 데이터를 분석한 후 초당 최대 처리량을 계산해보기로 했다. 초당 최대 처리량은 요청의 응답 완료 여부에 관계없이 임의 시간부터 1초(=1,000밀리초)간 처리하는 요청의 최대 개수를 의미한다.

 입력 형식
 solution 함수에 전달되는 lines 배열은 N(1 ≦ N ≦ 2,000)개의 로그 문자열로 되어 있으며, 각 로그 문자열마다 요청에 대한 응답완료시간 S와 처리시간 T가 공백으로 구분되어 있다.
 응답완료시간 S는 작년 추석인 2016년 9월 15일만 포함하여 고정 길이 2016-09-15 hh:mm:ss.sss 형식으로 되어 있다.
 처리시간 T는 0.1s, 0.312s, 2s 와 같이 최대 소수점 셋째 자리까지 기록하며 뒤에는 초 단위를 의미하는 s로 끝난다.
 예를 들어, 로그 문자열 2016-09-15 03:10:33.020 0.011s은 "2016년 9월 15일 오전 3시 10분 33.010초"부터 "2016년 9월 15일 오전 3시 10분 33.020초"까지 "0.011초" 동안 처리된 요청을 의미한다. (처리시간은 시작시간과 끝시간을 포함)
 서버에는 타임아웃이 3초로 적용되어 있기 때문에 처리시간은 0.001 ≦ T ≦ 3.000이다.
 lines 배열은 응답완료시간 S를 기준으로 오름차순 정렬되어 있다.
 출력 형식
 solution 함수에서는 로그 데이터 lines 배열에 대해 초당 최대 처리량을 리턴한다.
 입출력 예제
 예제1
 입력: [
 "2016-09-15 01:00:04.001 2.0s",
 "2016-09-15 01:00:07.000 2s"
 ]

 출력: 1

 예제2
 입력: [
 "2016-09-15 01:00:04.002 2.0s",
 "2016-09-15 01:00:07.000 2s"
 ]

 출력: 2

 설명: 처리시간은 시작시간과 끝시간을 포함하므로
 첫 번째 로그는 01:00:02.003 ~ 01:00:04.002에서 2초 동안 처리되었으며,
 두 번째 로그는 01:00:05.001 ~ 01:00:07.000에서 2초 동안 처리된다.
 따라서, 첫 번째 로그가 끝나는 시점과 두 번째 로그가 시작하는 시점의 구간인 01:00:04.002 ~ 01:00:05.001 1초 동안 최대 2개가 된다.

 예제3
 입력: [
 "2016-09-15 20:59:57.421 0.351s",
 "2016-09-15 20:59:58.233 1.181s",
 "2016-09-15 20:59:58.299 0.8s",
 "2016-09-15 20:59:58.688 1.041s",
 "2016-09-15 20:59:59.591 1.412s",
 "2016-09-15 21:00:00.464 1.466s",
 "2016-09-15 21:00:00.741 1.581s",
 "2016-09-15 21:00:00.748 2.31s",
 "2016-09-15 21:00:00.966 0.381s",
 "2016-09-15 21:00:02.066 2.62s"
 ]

 출력: 7
 */
#include <string>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int solution(vector<string> lines) {
    int answer = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> waiting;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> processing;
    vector<vector<int>> time;
    for(int i = 0; i < lines.size(); i++){
        string temp = "";
        vector<int> time_temp;
        for(int j = 11; j < lines[i].size(); j++){
            if(lines[i][j] == ':'){
                time_temp.push_back(stoi(temp));
                temp = "";
                continue;
            }
            else if(lines[i][j] == '.'){
                time_temp.push_back(stoi(temp));
                temp = "";
                continue;
            }
            else if(lines[i][j] == ' '){
                time_temp.push_back(stoi(temp));
                temp = "";
                continue;
            }
            if(j == lines[i].size() - 1){
                if(j == 25){
                    time_temp.push_back(stoi(temp));
                    continue;
                }
                if(temp.size() == 1){
                    time_temp.push_back(stoi(temp) * 100);
                }
                else if(temp.size() == 2){
                    time_temp.push_back(stoi(temp) * 10);
                }
                else{
                    time_temp.push_back(stoi(temp));
                }
            }
            temp += lines[i][j];
        }
        time.push_back(time_temp);
    }
    for(int i = 0; i < time.size() ;i++){
        int milli_time = 0;
        int time_taken = 0;
        milli_time += time[i][0] * 60 * 60 * 1000;
        milli_time += time[i][1] * 60 * 1000;
        milli_time += time[i][2] * 1000;
        milli_time += time[i][3];
        time_taken += time[i][4] * 1000;
        time_taken += time[i][5];
        waiting.push({milli_time - time_taken + 1, milli_time });
    }
    int max = 0;
    while(!waiting.empty() or !processing.empty()){
        int start = waiting.top().first - 1000;
        if(waiting.empty()){
            break;
        }
        while(!processing.empty() and processing.top().first <= start){
            processing.pop();
            answer--;
        }
        start += 1000;
        while(!waiting.empty() and waiting.top().first <= start){
            processing.push({waiting.top().second, waiting.top().first});
            waiting.pop();
            answer++;
        }
        if(max < answer)
            max = answer;
    }
    answer = max;
    return answer;
}
