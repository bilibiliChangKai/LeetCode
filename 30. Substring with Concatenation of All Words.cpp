#include <iostream>
#include <stack>
#include <vector>
#include <set> 
#include <map>
using namespace std;

// �ӵ㣺������ڴ������ʱ����� 

// vector<word> -> map<word, times>
map<string, int> vectorToMap(vector<string>& oldWords) {
    map<string, int> words;
    for (int i = 0; i < oldWords.size(); i++) {
        auto it = words.find(oldWords[i]);
        // ��һ�γ��� 
        if (it == words.end())
            words.insert(map<string, int>::value_type(oldWords[i], 1));
        // �ٴγ��֣����ִ���+1 
        else  it->second++;
    }
    
    return words;
} 

// index������ǻ�δƥ��words���±�ֵ
// nowPos����ǰwords�Ѿ�ƥ�䵽s�е�nowPosλ 
bool matchWordsRecur(set<int>* beginPos, vector<int>& wordsLength, map<int, int> index, int nowPos) {
    // ��wordsȫ��ƥ��ɹ�������true 
    if (index.empty())  return true;
    
    //cout << "    BeginPos:" << nowPos << endl;
    
    int i = 0;
    for (auto it = index.begin(); it != index.end(); it++) {
        int wordIndex = it->first;
        //cout << "  WordIndex:" << wordIndex << endl;
        // �����ǰword���ÿ��Խӵ�nowPos��λ�ã���index��ɾ����word���������ݹ� 
        if (beginPos[wordIndex].find(nowPos) != beginPos[wordIndex].end()) {
            map<int, int> newIndex = index;
            
            // �ж�ʣ����������Ϊ1��ɾ������
            if (it->second > 1)  newIndex[wordIndex]--;
            else  newIndex.erase(wordIndex);
            if (matchWordsRecur(beginPos, wordsLength, newIndex, nowPos + wordsLength[wordIndex]))
                return true;
        }
    }
    
    return false;
}

vector<int> findSubstring(string s, vector<string>& words) {
    map<string, int> newWords;              // ͳ����ͬ�ַ������ֵĴ�����intΪ��Ӧ���ֵĴ��� 
    newWords = vectorToMap(words);
    
    vector<int> returnPos;                  // ���淵��ֵ��vector 
    vector<int> wordsLength;                // ����words�ַ��ĳ��� 
    map<int, int> index;                    // ��һ��intΪ�ݹ�ʱʣ��word���±꣬�ڶ���intΪ��wordʣ����ٸ� 
    int wordsSumLength = 0;                 // �ַ����ܳ��Ⱥ� 
    set<int> beginPos[newWords.size()];     // ÿ��set�����Ӧwords�ڸ����г��ֵ���ʼλ�ã� 
                                            // ��set���Щ 
    
    
    int i = 0;
    for (auto it = newWords.begin(); it != newWords.end(); i++, it++) {
        string word = it->first;
        int times = it->second;
        //cout << word << ":\n";
        //cout << "times:" << times << endl;
        
        // ��¼word�ĳ��Ⱥ��±�
        wordsLength.push_back(word.size());
        wordsSumLength += word.size() * times;
        index.insert(map<int, int>::value_type(i, times));
        
        int position = s.find(word, 0);
        
        // ��words[i]�ڸ������ֵ����г�ʼλ�ö���¼����
        // ��¼ֵ������beginPos[i] 
        while (position != string::npos) {
            //cout << " Pos:" << position << endl;
            beginPos[i].insert(position);
            position = s.find(word, position + 1);
        }
        
    } 
    
    
    // ÿ��λ�ÿ�ʼ�����ڿ��� 
    for (int i = 0; i < s.size() - wordsSumLength + 1; i++)
        if (matchWordsRecur(beginPos, wordsLength, index, i))
            returnPos.push_back(i);
    
    return returnPos;
}

void addTestData(string& s, vector<string>& words) {
    string data[100] = {
        "word",
        "good",
        "best",
        "good"};
    int num = 4;
    
    s = "wordgoodgoodgoodbestword";
    
    for (int i = 0; i < num; i++)
        words.push_back(data[i]);
}

void showOutput(vector<int> output) {
    for (int i = 0; i < output.size(); i++)
        cout << output[i] << " ";
    cout << endl;
}

int main() {
    string s;
    vector<string> words;
    addTestData(s, words);
    showOutput(findSubstring(s, words));
}
