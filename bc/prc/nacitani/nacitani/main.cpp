#include <iostream>
#include <cstdio>
#include <algorithm> //sort
#include <vector> //pouziva vectory
#include <cmath> //floor a ceil

using namespace std;

#define FILEIN "input.txt" //input file
#define FILEOUT "output.txt" //output file results

int max(vector<int> cisla){
    int max = cisla[0];
    for(vector<int>::iterator it = cisla.begin(); it<cisla.end(); it++){
        if(max<*it)
            max = *it;
    }
    return max;
}

int min(vector<int> cisla){
    int min = cisla[0];
    for(vector<int>::iterator it = cisla.begin(); it<cisla.end(); it++){
        if(min>*it)
            min = *it;
    }
    return min;
}

float prumer(vector<int> cisla){
    float prumer;
    for(vector<int>::iterator it = cisla.begin(); it<cisla.end(); it++){
        prumer += *it;
    }
    prumer = prumer/cisla.size(); //aritmeticky prumer
    return prumer;
}

float median(vector<int> cisla){
    float median;
    if(cisla.size() % 2 == 0){ //pokud sudy pocet cisel tak je median prumer dvou prostrednich cisel
        median = (cisla[(cisla.size()/2)-1]+cisla[(cisla.size()/2)])/2;
    }
    else{//jinak median prostredni cislo
        median = cisla[cisla.size()/2];
    }
    return median;
}

int main(){
    FILE *input = fopen(FILEIN,"r"); //cteni ze souboru
    if(input == nullptr){
        cout << "Nelze nacist soubor\n";
    }
    else{
        FILE *output = fopen(FILEOUT,"w+"); //zapis do souboru
        vector<int> cisla;

        int hexnumber;
        while(!feof(input)){
            fscanf(input, "%x", &hexnumber);
            cisla.push_back(hexnumber);
        }
        fclose(input);

        fprintf(output, "Data nactena ze souboru %s: \n", FILEIN);
        for(vector<int>::iterator it = cisla.begin(); it<cisla.end(); it++){
            fprintf(output, "%i ", *it);
        }

        sort(cisla.begin(),cisla.end());
        fprintf(output, "\nPo serazeni dat min to max: \n");
        for(vector<int>::iterator it = cisla.begin(); it<cisla.end();it++){
            fprintf(output, "%i ", *it);
        }

        fprintf(output, "\nMaximum: %i\nMinimum: %i\nPrumer: %.2f\nMedian: %.1f\n",
                max(cisla),min(cisla),prumer(cisla), median(cisla));

    }
    return 0;
}
