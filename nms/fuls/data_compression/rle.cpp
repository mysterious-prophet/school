#include "rle.h"

rle::rle()
{

}

const string rle::encode(string text){
    int n = text.length();
    string result = "";
    for(int i = 0; i < n; i++){
        int occs = 1;

        while(i < n-1 && text[i] == text[i+1]){
            occs++;
            i++;
        }

        result.append(1, text[i]);
        result.append(to_string(occs));
    }

    return result;
}

const string rle::decode(string text){
    int n = text.length();
    string result = "";
    int i = 0;
    while(i<n){
        if((isdigit(text[i]))){
            int k = 1;
            while(k < n - i){
                if(!(isdigit(text[i+k]))){
                    break;
                }
                k++;
            }

            string occs_substr = text.substr(i, k);
            int occs = atoi(occs_substr.c_str());

            for(int j = 0; j < occs; j++){
                result.append(1, text[i+k-occs_substr.length()-1]);
            }

            i += occs_substr.length();
        }
        i++;
    }

    return result;
}
