#include <iostream>
#include <time.h>
#include <cstdlib>
#include <cmath>

using namespace std;

class RNG{
protected:
    unsigned long Max;
public:
    virtual unsigned long X(){return 0;}
};

class C_Rand : public RNG{
public:
    C_Rand(){
        Max = RAND_MAX;
        srand(static_cast<unsigned>(time(nullptr)));
    }

    unsigned long X() {return rand() % Max;}
};


class IBM_Rand: public RNG{
private:
    const unsigned int modular = pow(2,31);

public:
    unsigned int s = static_cast<unsigned>(time(nullptr)); // s = 1; kontrola

    IBM_Rand(){
        Max = modular - 1; //maximalni hodnota je pow(2,31) - 1
    }

    unsigned long X(){
        s = (65539 * s) % Max;
        return s;
    }
};

class MWC_Rand:public RNG{
private:
    const unsigned int modular = pow(2,16);

public:  
    unsigned int c = 0;
    unsigned int s = static_cast<unsigned>(time(nullptr));

    MWC_Rand(){
        Max = modular - 1; //max hodnota je pow(2,16) - 1
    }

    unsigned long X(){
        c = (36969*s+c) / modular;
        s = ((36969*s+c) % Max);

        return s;
    }
};

int main(){
    C_Rand rand1;
    IBM_Rand rand2;
    MWC_Rand rand3;

    cout << "Cisla vygenerovana pomoci C Rand: \n";
    for(int i=0; i<100; i++){
        cout << i << ". " <<rand1.X() << endl;
    }

    cout << "Cisla vygenerovana pomoci IBM Rand: \n";
    for(int i=0; i<100; i++){
        cout << i << ". " << rand2.X() << endl;
    }

    cout << "Cisla vygenerovana pomoci MWC Rand: \n";
    for(int i = 0; i<100; i++){
        cout << i << ". " << rand3.X() << endl;
    }

    return 0;
}
