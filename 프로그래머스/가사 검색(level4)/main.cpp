/*
 https://programmers.co.kr/learn/courses/30/lessons/60060
 가사 검색
 문제 설명
 [본 문제는 정확성과 효율성 테스트 각각 점수가 있는 문제입니다.]

 친구들로부터 천재 프로그래머로 불리는 "프로도"는 음악을 하는 친구로부터 자신이 좋아하는 노래 가사에 사용된 단어들 중에 특정 키워드가 몇 개 포함되어 있는지 궁금하니 프로그램으로 개발해 달라는 제안을 받았습니다.
 그 제안 사항 중, 키워드는 와일드카드 문자중 하나인 '?'가 포함된 패턴 형태의 문자열을 뜻합니다. 와일드카드 문자인 '?'는 글자 하나를 의미하며, 어떤 문자에도 매치된다고 가정합니다. 예를 들어 "fro??"는 "frodo", "front", "frost" 등에 매치되지만 "frame", "frozen"에는 매치되지 않습니다.

 가사에 사용된 모든 단어들이 담긴 배열 words와 찾고자 하는 키워드가 담긴 배열 queries가 주어질 때, 각 키워드 별로 매치된 단어가 몇 개인지 순서대로 배열에 담아 반환하도록 solution 함수를 완성해 주세요.

 가사 단어 제한사항
 words의 길이(가사 단어의 개수)는 2 이상 100,000 이하입니다.
 각 가사 단어의 길이는 1 이상 10,000 이하로 빈 문자열인 경우는 없습니다.
 전체 가사 단어 길이의 합은 2 이상 1,000,000 이하입니다.
 가사에 동일 단어가 여러 번 나올 경우 중복을 제거하고 words에는 하나로만 제공됩니다.
 각 가사 단어는 오직 알파벳 소문자로만 구성되어 있으며, 특수문자나 숫자는 포함하지 않는 것으로 가정합니다.
 검색 키워드 제한사항
 queries의 길이(검색 키워드 개수)는 2 이상 100,000 이하입니다.
 각 검색 키워드의 길이는 1 이상 10,000 이하로 빈 문자열인 경우는 없습니다.
 전체 검색 키워드 길이의 합은 2 이상 1,000,000 이하입니다.
 검색 키워드는 중복될 수도 있습니다.
 각 검색 키워드는 오직 알파벳 소문자와 와일드카드 문자인 '?' 로만 구성되어 있으며, 특수문자나 숫자는 포함하지 않는 것으로 가정합니다.
 검색 키워드는 와일드카드 문자인 '?'가 하나 이상 포함돼 있으며, '?'는 각 검색 키워드의 접두사 아니면 접미사 중 하나로만 주어집니다.
 예를 들어 "??odo", "fro??", "?????"는 가능한 키워드입니다.
 반면에 "frodo"('?'가 없음), "fr?do"('?'가 중간에 있음), "?ro??"('?'가 양쪽에 있음)는 불가능한 키워드입니다.
 입출력 예
 words    queries    result
 ["frodo", "front", "frost", "frozen", "frame", "kakao"]    ["fro??", "????o", "fr???", "fro???", "pro?"]    [3, 2, 4, 1, 0]
 입출력 예에 대한 설명
 "fro??"는 "frodo", "front", "frost"에 매치되므로 3입니다.
 "????o"는 "frodo", "kakao"에 매치되므로 2입니다.
 "fr???"는 "frodo", "front", "frost", "frame"에 매치되므로 4입니다.
 "fro???"는 "frozen"에 매치되므로 1입니다.
 "pro?"는 매치되는 가사 단어가 없으므로 0 입니다.
 */

//#include <string>
//#include <vector>
//#include <unordered_map>
//#include <algorithm>
//#include <iostream>
//
//using namespace std;
//
//int findCount(vector<string> words, string queries){
//    if(!words.size())
//        return 0;
//    int index = 0;
//    for( ; index < queries.size(); index++){
//        if(queries[index] == '?')
//            break;
//    }
//    if(index == 0)
//        return words.size();
//
//    string key_word = queries.substr(0, index);
//
//    int low = 0;
//    for(; low < words.size(); low++){
//        if(words[low].substr(0, index) == key_word){
//            break;
//        }
//
//    }
//    int start = low;
//    int high = words.size();
//    while(low + 1 < high){
//        int mid = (low + high) / 2;
//        if(words[mid].substr(0, index) != key_word)
//            high = mid;
//        else
//            low = mid;
//    }
//    return high - start;
//}
//
//
//
//vector<int> solution(vector<string> words, vector<string> queries) {
//    vector<int> answer;
//    unordered_map<string, int> queries_count;
//    if(queries.size() > 1000){ //쿼리 개수가 많을 때는 hash가 유리하다. 하지만 쿼리 개수가 적고 단어의 개수가 많다면 불리하다.
//        for(int i = 0 ; i < words.size(); i++){
//        string word = words[i];
//        queries_count[word]++;
//        queries_count[string(words[i].size(), '?')]++;
//            for(int j = 1; j < word.size(); j++){
//                string front = (string(j, '?')) + word.substr(j);
//                string back = word.substr(0, j) + (string(word.size() - j, '?'));
//                queries_count[front]++;
//                queries_count[back]++;
//            }
//        }
//        for(int i = 0 ; i < queries.size(); i++){
//            answer.push_back(queries_count[queries[i]]);
//        }
//    }
//    else{
//        unordered_map<int, vector<string>> div_size_words;
//        unordered_map<int, vector<string>> div_size_words_reverse;
//        for(int i = 0; i < words.size(); i++){
//            string temp = words[i];
//            int size = temp.size();
//            div_size_words[size].push_back(temp);
//            reverse(temp.begin(), temp.end());
//            div_size_words_reverse[size].push_back(temp);
//        }
//
//        for(auto iter = div_size_words.begin(); iter != div_size_words.end(); iter++){
//            sort(iter->second.begin(), iter->second.end());
//        }
//
//        for(auto iter = div_size_words_reverse.begin(); iter != div_size_words_reverse.end(); iter++){
//            sort(iter->second.begin(), iter->second.end());
//        }
//
//        for(int i = 0; i < queries.size(); i++){
//            if(queries[i][0] == '?'){
//                reverse(queries[i].begin(), queries[i].end());
//                int result = findCount(div_size_words_reverse[queries[i].size()], queries[i]);
//                answer.push_back(result);
//            }
//            else{
//                int result = findCount(div_size_words[queries[i].size()], queries[i]);
//                answer.push_back(result);
//            }
//        }
//    }
//
//    return answer;
//}


// 이분 탐색으로만 풀이
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool comp(string a, string b){
    if(a.size() == b.size()){
        return a <= b;
    }
    return a.size() <= b.size();
}

vector<int> solution(vector<string> words, vector<string> queries) {
    vector<int> answer;
    vector<string> reverse_words;
    
    for(string word : words){
        reverse(word.begin(), word.end());
        reverse_words.push_back(word);
    }
    sort(reverse_words.begin(), reverse_words.end(), comp);
    sort(words.begin(), words.end(), comp);
    
    for(string query : queries){
        if(query[0] == '?'){
            string temp_start = query;
            reverse(temp_start.begin(), temp_start.end());
            string temp_end = temp_start;
            for(int i = temp_start.size() - 1; i > -1; i--){
                if(temp_start[i] == '?')
                    temp_start[i] = 'a';
                else
                    break;
            }
            for(int i = temp_end.size() - 1; i > -1; i--){
                if(temp_end[i] == '?')
                    temp_end[i] = 'z';
                else
                    break;
            }
            
            int start_low = -1;
            int start_high = reverse_words.size();
            while(start_low + 1 < start_high){
                int mid = (start_low + start_high) / 2;
                if(!comp(reverse_words[mid], temp_start))
                    start_high = mid;
                else
                    start_low = mid;
            }
            
            int end_low = -1;
            int end_high = reverse_words.size();
            while(end_low + 1 < end_high){
                int mid = (end_low + end_high) / 2;
                if(!comp(reverse_words[mid], temp_end))
                    end_high = mid;
                else
                    end_low = mid;
            }
            answer.push_back(((end_low + 1) - (start_low + 1)));
        }
        else{
            string temp_start = query;
            string temp_end = temp_start;
            for(int i = temp_start.size() - 1; i > -1; i--){
                if(temp_start[i] == '?')
                    temp_start[i] = 'a';
                else
                    break;
            }
            for(int i = temp_end.size() - 1; i > -1; i--){
                if(temp_end[i] == '?')
                    temp_end[i] = 'z';
                else
                    break;
            }
            
            int start_low = -1;
            int start_high = words.size();
            while(start_low + 1 < start_high){
                int mid = (start_low + start_high) / 2;
                if(!comp(words[mid], temp_start))
                    start_high = mid;
                else
                    start_low = mid;
            }
            
            int end_low = -1;
            int end_high = words.size();
            while(end_low + 1 < end_high){
                int mid = (end_low + end_high) / 2;
                if(!comp(words[mid], temp_end))
                    end_high = mid;
                else
                    end_low = mid;
            }
            answer.push_back(((end_low + 1) - (start_low + 1)));
        }
    }
    return answer;
}
