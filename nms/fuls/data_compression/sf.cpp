#include "sf.h"

using namespace std;

sf::sf(){

}

const string sf::encode(string text){
    int i, n = text.length();
    float total = 0;
    string ch;
    node temp;

    num_symbols = getNumberSymbols(text);

    vector<float> x(num_symbols, 0);
    freqAnalysis(x, text, total, num_symbols);

    sortByProbability(num_symbols, p);

    for (i = 0; i < num_symbols; i++){
        p[i].top = -1;
    }

    calcCodes(0, num_symbols-1, p);

    string result = "";
    /*for(i = 0; i < n; i++){
        result.append(getCode(text[i]));
    }*/

    return result;
}

const string sf::decode(const string text){
    int n = text.length(), i = 0;
    string result = "";
    while(i < n){
        for(int j = 0; j < num_symbols; j++){
            string substr = text.substr(i, p[j].code.length());
            if(substr.compare(p[j].code) == 0){
                result.append(p[j].sym);
                i += p[j].code.length();
                break;
            }
        }
    }

    return result;
}

void sf::sortByProbability(int n, node *p){
    int i, j;
    node temp;
    for (j = 1; j <= n - 1; j++) {
        for (i = 0; i < n - 1; i++) {
            if ((p[i].pro) > (p[i + 1].pro)) {
                temp.pro = p[i].pro;
                temp.sym = p[i].sym;

                p[i].pro = p[i + 1].pro;
                p[i].sym = p[i + 1].sym;

                p[i + 1].pro = temp.pro;
                p[i + 1].sym = temp.sym;
            }
        }
    }
}

void sf::freqAnalysis(vector<float> &x, const string& text, float &total, int num_symbols){
    int i;
    int n = text.length();
    for(int i = 0; i < n; i++){
        x[int(text[i])-97]++;
    }

    for(i = 0; i < num_symbols; i++){
        x[i] = x[i] / n;
        p[i].pro = x[i];
        total += p[i].pro;
    }

    p[i].pro = 1 - total;
}

int sf::getNumberSymbols(string &text){
    vector<char> symbols(39);
    int count = 0, n = text.length();
    for(int i = 0; i < n; i++){
        if(find(symbols.begin(), symbols.end(), text[i]) == symbols.end()){
            symbols[count] = text[i];
            p[count].sym = text[i];
            count++;
        }
    }
    return count;
}

string sf::getCode(char ch){
    string code = "";
    int j = 0;
    for(int i = 0; i <  num_symbols; i++){
        if(tolower(p[i].sym[0]) == ch){
            j = i;
            break;
        }
    }
    for (int i = 0; i <= p[j].top; i++){
        code.append(to_string(p[j].arr[i]));
    }

    p[j].code = code;
    return code;
}

void sf::calcCodes(int l, int h, node *p){
    float pack1 = 0, pack2 = 0, diff1 = 0, diff2 = 0;
        int i, k, j;
        if ((l + 1) == h || l == h || l > h) {
            if (l == h || l > h)
                return;
            p[h].arr[++(p[h].top)] = 0;
            p[l].arr[++(p[l].top)] = 1;

            return;
        }
        else {
            for (i = l; i <= h - 1; i++){
                pack1 = pack1 + p[i].pro;
            }

            pack2 = pack2 + p[h].pro;
            diff1 = pack1 - pack2;
            if (diff1 < 0){
                diff1 = diff1 * -1;
            }
            j = 2;
            while (j != h - l + 1) {
                k = h - j;
                pack1 = pack2 = 0;
                for (i = l; i <= k; i++){
                    pack1 = pack1 + p[i].pro;
                }
                for (i = h; i > k; i--){
                    pack2 = pack2 + p[i].pro;
                }
                diff2 = pack1 - pack2;
                if (diff2 < 0){
                    diff2 = diff2 * -1;
                }
                if (diff2 >= diff1){
                    break;
                }
                diff1 = diff2;
                j++;
            }
            k++;
            for (i = l; i <= k; i++){
                p[i].arr[++(p[i].top)] = 1;
            }
            for (i = k + 1; i <= h; i++){
                p[i].arr[++(p[i].top)] = 0;
            }

            calcCodes(l, k, p);
            calcCodes(k + 1, h, p);
        }
}



