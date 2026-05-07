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

void wordle(){
    loadData();
    template T;
    char s;
    cout<<"select a language: English(e) or Chinese(c)";
    cin>>s;
    if(s=='e'){
        cout<<"Welcome to Wordle!"<<endl<<"You have 6 attempts to guess the hidden 5-letter word."<<endl<<"Each guess must be a valid word from our vocabulary of 20,000 words."<<endl<<"After each guess, the color of the tiles will change to show how close your guess was to the word."<<endl;
    }
    else{
        cout<<"歡迎來到 Wordle！"<<endl<<"你有 6 次機會猜出隱藏的 5 個字母的單字。"<<endl<<"每次猜測的單字都必須是我們 20,000 個單字庫中的有效單字。"<<endl<<"每次猜測後，方塊的顏色都會改變，以顯示你的猜測與目標單字的接近程度。"<<endl;
    }
    int chance=6;
    while(chance>0){
        cout<<chance<<" attemps left, please enter a five letter word for your "<<7-chance<<"guess"<<endl;
        cout<<"If you need a hint, enter h";
        string guess;
        cin>>guess;
        if(guess=='h'){
            hints();
        }
        else{
            
        }
    }
}
