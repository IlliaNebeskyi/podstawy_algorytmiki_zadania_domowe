#include <iostream>
#include <vector>
#include <string>

using namespace std;

int makeHash(string w, int p, int offset);
int updateHash(int hash, char s_prev, char s_next, int off, int p, int exp);
int pow(int p, int exp);

vector<int> KRPatternMatch(string pattern, string text, int p, int off);

int makeHashModular(string w, int LP);
int updateHashModular(int hash, char s_prev, char s_next, int p, int exp, int LP);
vector<vector<int>> KRMultiplePatternMatch(vector<string> patterns, string text, int p, int off);

int main()
{
    const int p = 256;
    int old_hash = makeHash("ABAB", 2, 'A');
    int new_hash = updateHash(old_hash, 'A', 'A', 'A', 2, 3);
    cout << old_hash << " " << new_hash << endl;
    string textt = "ABABAGALAMAGABA";
    string patternn = "BA";
    vector<int> foundPatt = KRPatternMatch(patternn, textt, 2, 'A');
    for (int i : foundPatt) {
        cout << i << " ";
    }
    cout << endl;

    vector<string> patterrns = { "BA", "GA", "AB" };
    vector<vector<int>> foundPattModular = KRMultiplePatternMatch(patterrns, textt, p, 907);

    for (vector<int> pattVect : foundPattModular) {
        for (int i : pattVect) {
            cout << i << " ";
        }
        cout << endl;
    }
    cout << endl;
    return 0;
}

int makeHash(string w, int p, int offset) {
    int result = 0;
    int p_power = 1;
    for (int i = w.length() - 1; i >= 0; i--) {
        result += ((int)w[i] - offset) * p_power;
        p_power *= p;
    }
    return result;
}

int updateHash(int hash, char s_prev, char s_next, int off, int p, int exp) {
    hash -= ((int)s_prev - off) * pow(p, exp);
    hash *= p;
    hash += (int)s_next - off;
    return hash;
}

int pow(int p, int exp) {
    int result = 1;
    for (int i = 0; i < exp; i++)
        result *= p;
    return result;
}

vector<int> KRPatternMatch(string pattern, string text, int p, int off) {
    vector<int> result;
    int hashP = 0;
    int hashT = 0;
    hashP = makeHash(pattern, p, off);
    hashT = makeHash(text.substr(0, pattern.length()), p, off);

    for (int j = 0, i = pattern.length(); i <= text.length(); i++) {
        if (hashP == hashT) {
            int k;
            for (k = 0; k < pattern.length() && pattern[k] == text.substr(j, pattern.length())[k]; k++);
            if (k == pattern.length())
                result.push_back(j);
        }
        if (i < text.length())
            hashT = updateHash(hashT, text[j], text[i], off, p, pattern.length() - 1);
        j++;
    }
    return result;
}

int makeHashModular(string w, int LP) {
    int result = 0;
    int p_power = 1;
    const int p = 256;
    for (int i = w.length() - 1; i >= 0; i--) {
        int product = (((int)w[i] % LP) * (p_power % LP)) % LP;
        result = (result + product) % LP;
        p_power = ((p_power) * (p % LP)) % LP;
    }
    return result;
}

int updateHashModular(int hash, char s_prev, char s_next, int p, int exp, int LP) {
    hash -= ((((int)s_prev) % LP) * (pow(p, exp) % LP)) % LP;
    hash = ((hash % LP) * (p % LP)) % LP;
    hash = (hash + (int)s_next % LP) % LP;
    return hash;
}

vector<vector<int>> KRMultiplePatternMatch(vector<string> patterns, string text, int p, int LP) {
    vector<vector<int>> result;
    for (int i = 0; i < patterns.size(); i++) {
        result.push_back(vector<int>());
    }
    vector<int> hashesP;
    for (string patt : patterns)
        hashesP.push_back(makeHashModular(patt, LP));
    int hashT = 0;
    hashT = makeHashModular(text.substr(0, patterns[0].length()), LP);

    for (int j = 0, i = patterns[0].length(); i <= text.length(); i++) {
        for (int l = 0; l < patterns.size(); l++) {
            if (hashesP[l] == hashT) {
                int k;
                for (k = 0; k < patterns[0].length() && patterns[l][k] == text.substr(j, patterns[0].length())[k]; k++);
                if (k == patterns[0].length())
                    result[l].push_back(j);
            }
        }
        
        if (i < text.length())
            hashT = updateHashModular(hashT, text[j], text[i], p, patterns[0].length() - 1, LP);
        j++;
    }

    return result;


}
