#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string filename, vector<string>& names, vector<int>& scores, vector<char>& grades){
    ifstream fin(filename);
    string line;
    while(getline(fin, line)){

        int colonPos = line.find(':');
        string name = line.substr(0, colonPos);
        string scoresPart = line.substr(colonPos + 1);

        int idx = 0;

        while(idx < (int)scoresPart.size() && scoresPart[idx] == ' ') idx++;
        string token;
        vector<int> sv;
        for(unsigned i = idx; i <= scoresPart.size(); i++){
            if(i == scoresPart.size() || scoresPart[i] == ' '){
                if(!token.empty()){
                    sv.push_back(atoi(token.c_str()));
                    token = "";
                }
            } else {
                token += scoresPart[i];
            }
        }
        int total = sv[0] + sv[1] + sv[2];
        names.push_back(name);
        scores.push_back(total);
        grades.push_back(score2grade(total));
    }
    fin.close();
}

void getCommand(string& command, string& key){
    cout << "Please input your command:\n";
    string line;
    getline(cin, line);
    int spacePos = line.find(' ');
    if(spacePos == (int)string::npos){
        command = line;
        key = "";
    } else {
        command = line.substr(0, spacePos);
        key = line.substr(spacePos + 1);
    }
}

void searchName(vector<string>& names, vector<int>& scores, vector<char>& grades, string key){
    cout << "---------------------------------\n";
    bool found = false;
    for(unsigned i = 0; i < names.size(); i++){
        if(toUpperStr(names[i]) == key){
            string displayName = names[i];
            cout << displayName << "'s score = " << scores[i] << "\n";
            cout << displayName << "'s grade = " << grades[i] << "\n";
            found = true;
            break;
        }
    }
    if(!found) cout << "Cannot found.\n";
    cout << "---------------------------------\n";
}

void searchGrade(vector<string>& names, vector<int>& scores, vector<char>& grades, string key){
    cout << "---------------------------------\n";
    bool found = false;
    char targetGrade = key[0];
    for(unsigned i = 0; i < names.size(); i++){
        if(grades[i] == targetGrade){
            cout << names[i] << " (" << scores[i] << ")\n";
            found = true;
        }
    }
    if(!found) cout << "Cannot found.\n";
    cout << "---------------------------------\n";
}


int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}
