#include <iostream>
#include <stack>
#include <vector>
#include <set> 
#include <map>
using namespace std;

// 坑点：会出现内存溢出和时间溢出 

// vector<word> -> map<word, times>
map<string, int> vectorToMap(vector<string>& oldWords) {
    map<string, int> words;
    for (int i = 0; i < oldWords.size(); i++) {
        auto it = words.find(oldWords[i]);
        // 第一次出现 
        if (it == words.end())
            words.insert(map<string, int>::value_type(oldWords[i], 1));
        // 再次出现，出现次数+1 
        else  it->second++;
    }
    
    return words;
} 

// index储存的是还未匹配words的下标值
// nowPos代表当前words已经匹配到s中的nowPos位 
bool matchWordsRecur(set<int>* beginPos, vector<int>& wordsLength, map<int, int> index, int nowPos) {
    // 若words全部匹配成功，返回true 
    if (index.empty())  return true;
    
    //cout << "    BeginPos:" << nowPos << endl;
    
    int i = 0;
    for (auto it = index.begin(); it != index.end(); it++) {
        int wordIndex = it->first;
        //cout << "  WordIndex:" << wordIndex << endl;
        // 如果当前word正好可以接到nowPos的位置，在index中删掉该word，并继续递归 
        if (beginPos[wordIndex].find(nowPos) != beginPos[wordIndex].end()) {
            map<int, int> newIndex = index;
            
            // 判断剩余次数，如果为1，删除此项
            if (it->second > 1)  newIndex[wordIndex]--;
            else  newIndex.erase(wordIndex);
            if (matchWordsRecur(beginPos, wordsLength, newIndex, nowPos + wordsLength[wordIndex]))
                return true;
        }
    }
    
    return false;
}

vector<int> findSubstring(string s, vector<string>& words) {
    map<string, int> newWords;              // 统计相同字符串出现的次数，int为对应出现的次数 
    newWords = vectorToMap(words);
    
    vector<int> returnPos;                  // 储存返回值的vector 
    vector<int> wordsLength;                // 储存words字符的长度 
    map<int, int> index;                    // 第一个int为递归时剩余word的下标，第二个int为该word剩余多少个 
    int wordsSumLength = 0;                 // 字符串总长度和 
    set<int> beginPos[newWords.size()];     // 每个set储存对应words在父串中出现的起始位置， 
                                            // 用set会快些 
    
    
    int i = 0;
    for (auto it = newWords.begin(); it != newWords.end(); i++, it++) {
        string word = it->first;
        int times = it->second;
        //cout << word << ":\n";
        //cout << "times:" << times << endl;
        
        // 记录word的长度和下标
        wordsLength.push_back(word.size());
        wordsSumLength += word.size() * times;
        index.insert(map<int, int>::value_type(i, times));
        
        int position = s.find(word, 0);
        
        // 将words[i]在父串出现的所有初始位置都记录下来
        // 记录值保存在beginPos[i] 
        while (position != string::npos) {
            //cout << " Pos:" << position << endl;
            beginPos[i].insert(position);
            position = s.find(word, position + 1);
        }
        
    } 
    
    
    // 每个位置开始都存在可能 
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
