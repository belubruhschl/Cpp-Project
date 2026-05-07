#include <bits/stdc++.h>
using namespace std;

vector<string> validGuesses;
vector<string> answers;

void loadData(){
    ifstream file("validGuesses.txt");
    string temp;
    while(file>>temp){
        validGuesses.push_back(temp);
    }
    file.close();
    ifstream file2("answers.txt");
    while(file2>>temp){
        answers.push_back(temp);
    }
    file2.close();
    cout<<validGuesses[0]<<answers[0];/*debug*/
}

string hints(){
    return "Good Luck";
}

string getRandomWord() {
    if (answers.empty()) return "";

    // 1. 建立隨機數產生器 (使用 random_device 當種子)
    static random_device rd; 
    static mt19937 gen(rd()); 

    // 2. 定義範圍：從 0 到 vector 的最後一個索引
    uniform_int_distribution<> dis(0, answers.size() - 1);

    // 3. 取得隨機索引並回傳單字
    int randomIndex = dis(gen);
    return answers[randomIndex];
}

void intro(char s){
    if(s=='e'){
        cout << R"(
          =============================================
                     WELCOME TO WORDLE C++
          =============================================
            - Guess the 5-letter word in 6 tries.
            - Each guess must be in the word list.
            - Feedback will be given for each letter.
          =============================================
        )" << endl;
    }
    else{
        cout << "=====================================" << endl;
        cout << "      WELCOME TO WORDLE (中文版)      " << endl;
        cout << "=====================================" << endl;
        cout << " 1. 目標：猜出隱藏的 5 字母單字" << endl;
        cout << " 2. 機會：共有 6 次嘗試機會" << endl;
        cout << " 3. 提示：綠色(正確)、黃色(錯位)、灰色(無)" << endl;
        cout << "-------------------------------------" << endl;
        cout << "[系統] 已就緒，請開始輸入單字。" << endl;
    }
}

void wordle(){
    loadData();
    char s;
    cout<<"================================";
    cout<<"select a language: English(e) or Chinese(c)";
    cin>>s;
    intro(s);
    int chance=6;
    string answer=getRandomWord();
    vector<char> result;
    vector<vector<char>> output(6,vector<int>(5,'_'));
    // 定義字體顏色常數
    const string RESET  = "\033[0m";
    const string GREEN  = "\033[32m";  // 綠色字體
    const string YELLOW = "\033[33m";  // 黃色字體
    const string GRAY   = "\033[90m";  // 灰色字體
    while(chance>0){
        cout<<chance<<" attemps left, please enter a five letter word for your "<<7-chance<<"guess"<<endl;
        cout<<"If you need a hint, enter h";
        string guess;
        cin>>guess;
        if(guess=='h'){
            cout<<hints()<<"might be a good choice"<<endl;
            cout<<chance<<" attemps left, please enter a five letter word for your "<<7-chance<<"guess"<<endl;
            cin>>guess;
        }
        for (int i=0;i<5;i++){
            if(guess[i]==answer[i]){
                result.push_back(GREEN+guess[i]+RESET);
                continue;
            }
            for (int j=0;j<5;j++){
                if(answer[j]==guess[i]){
                    result.push_back(YELLOW+guess[i]+RESET);
                    break;
                }
                if(j==4){
                    result.push_back(GRAY+guess[i]+RESET);
                }
            }
        }/*result*/
        for(int i=0;i<5;i++){
            output[6-chance][i]=result[i];
        }
        cout<<"\033[2J\033[1;1H";
        intro(s);
        cout<<"============="<<endl;
        for(int i=0;i<6;i++){
            cout<<"= "
            for(int j=0;j<5;j++){
                cout<<output[i][j]<<" ";
            }
            cout<<"="<<endl;
        }
        cout<<"============="<<endl;
        cout<<"Nice Try!";
        chance--;
    }
}