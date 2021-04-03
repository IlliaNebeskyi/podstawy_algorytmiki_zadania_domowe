#include <iostream>
#include <vector>

using namespace std;

vector<int> naivePatternMatch(string pattern, string text);

vector<int> BMPatternMatch(string pattern, string text, vector<int> shiftTable, unsigned char startChar);
vector<int> makeShiftTable(string pattern, string text, unsigned char &startChar);

vector<int> KMPPatternMatch(string pattern, string text, vector<int> matchTable);
vector<int> makeMatchTable(string pattern);

string replace(string text, string deletedPattern, string replacingPattern, vector<int> matchTable);

int main()
{
    string menu = "\nMenu:\n"
                  "1. enter string and pattern\n"
                  "2. naive pattern match\n"
                  "3. BM pattern match\n"
                  "4. KMP pattern match\n"
                  "5. replace pattern with given string\n"
                  "6. show string and pattern\n"
                  "0. end\n"
                  "choose option: ";

    int ans = 1;
    string usrString;
    string pattern;
    string replacePattern;
    vector<int> result;
    vector<int> shiftTable;
    vector<int> matchTable;

    while (ans){
        cout << menu;
        cin >> ans;
        cin.ignore();
        switch(ans){
            case 1:
                cout << "enter string: ";
                getline(cin, usrString);
                cout << "enter pattern: ";
                getline(cin, pattern);
                cout << endl;
                break;
            case 2:
                result = naivePatternMatch(pattern, usrString);
                cout << "pattern(s) found (using naive matching) at following indices:" << endl;
                for (int i = 0; i < result.size(); i++){
                    cout << result[i] << " ";
                }
                cout << endl;
                break;
            case 3:
                unsigned char startchar;
                shiftTable = makeShiftTable(pattern, usrString, startchar);
                result = BMPatternMatch(pattern, usrString, shiftTable, startchar);
                cout << "pattern(s) found (using BM matching) at following indices:" << endl;
                for (int i = 0; i < result.size(); i++){
                    cout << result[i] << " ";
                }
                cout << endl;
                break;
            case 4:
                matchTable = makeMatchTable(pattern);
                result = KMPPatternMatch(pattern, usrString, matchTable);
                cout << "pattern(s) found (using KMP matching) at following indeces:" << endl;
                for (int i = 0; i < result.size(); i++){
                    cout << result[i] << " ";
                }
                cout << endl;
                break;
            case 5:
                cout << "enter replacingPattern:" << endl;
                getline(cin, replacePattern);
                cout << endl;
                matchTable = makeMatchTable(pattern);
                usrString = replace(usrString, pattern, replacePattern, matchTable);
                cout << "resulting string:" << endl << usrString << endl;
                break;
            case 6:
                for (int i = 0; i < usrString.length(); i++){
                    cout << usrString[i];
                }
                cout << endl;
                for (int i = 0; i < pattern.length(); i++){
                    cout << pattern[i];
                }
                cout << endl;
                break;
            default:
                break;

        }
    }
    return 0;
}


vector<int> naivePatternMatch(string pattern, string text){
    vector<int> result;
    for (int i = 0; i <= text.length() - pattern.length(); i++){
        int j;
        for (j = 0; text[i+j] == pattern[j] && j < pattern.length(); j++){}
        if (j == pattern.length())
            result.push_back(i);
    }
    return result;
}

vector<int> BMPatternMatch(string pattern, string text, vector<int> shiftTable, unsigned char startChar){
    int n_start = (int) startChar;
    vector<int> result;
    int j;
    for (int i = 0; i <= text.length() - pattern.length();){
        for (j = pattern.length() - 1; pattern[j]==text[i+j] && j > -1; j--){}
        if (j == -1){
            cout << i << endl;
            result.push_back(i);
            i++;
        } else {
            i += max(1, j-shiftTable[text[i+j]-n_start]);
        }
    }
    return result;
}

vector<int> makeShiftTable(string pattern, string text, unsigned char &startChar){
    unsigned char beginn = text[0], endd = text[0];
    for (int i = 1; i < text.length(); i++){
        if (text[i] > endd){
            endd = text[i];
        } else if (text[i] < beginn){
            beginn = text[i];
        }
    }
    vector<int> p;
    for (int i = 0; i <= endd - beginn; i++){
        p.push_back(-1);
    }
    for (int i = 0; i < pattern.length(); i++){
        p[pattern[i] - beginn] = i;
    }
    startChar = beginn;
    return p;
}


vector<int> KMPPatternMatch(string pattern, string text, vector<int> matchTable){
    vector<int> result;
    int j = 0;

    for (int i = 0; i < text.length() - pattern.length() + 1;){
        for (;pattern[j] == text[i+j] && j < pattern.length(); j++) {
        }

        if (j == pattern.length())
            result.push_back(i);

        i += max(1, j - matchTable[j]);
        j = matchTable[j];
    }

    return result;
}


vector<int> makeMatchTable(string pattern){
    vector<int> result;
    for (int i = 0; i <= pattern.length(); i++){
        result.push_back(0);
    }
    int t = 0;
    for (int i = 1; i < pattern.length(); i++){
        for (; pattern[t] != pattern[i] && t > 0;){
            t = result[t];
        }
        if (pattern[t] == pattern[i]){
            t++;
        }
        result[i+1] = t;
    }

    return result;
}

string replace(string text, string deletedPattern, string replacingPattern, vector<int> matchTable){
    string resultStr;
    int beg = 0;

    int j = 0;

    for (int i = 0; i < text.length() - deletedPattern.length() + 1;){
        for (;deletedPattern[j] == text[i+j] && j < deletedPattern.length(); j++) {
        }

        if (j == deletedPattern.length()){
            resultStr += text.substr(beg, i-beg) + replacingPattern;
            beg = i + deletedPattern.length(); // NOLINT(cppcoreguidelines-narrowing-conversions)
            i += deletedPattern.length(); // NOLINT(cppcoreguidelines-narrowing-conversions)
            j = 0;
            continue;
        }

        i += max(1, j - matchTable[j]);
        j = matchTable[j];
    }
    resultStr += text.substr(beg, text.length()-beg);

    return  resultStr;
}
