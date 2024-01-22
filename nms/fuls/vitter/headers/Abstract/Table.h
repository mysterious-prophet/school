#ifndef CODE
#define CODE
    #include "../Code.h"
#endif

#ifndef VECTOR
#define VECTOR
    #include <vector>
#endif

#ifndef STDEXCEPT
#define STDEXCEPT
    #include <stdexcept>
#endif

class Table
{
    public:

        std::pair<char, unsigned int> get_rest_of_encrypt();

        virtual std::vector<char> encrypt(const std::vector<char>&
                                          bytes_to_encrypt) = 0;

        virtual const Code& operator [] (unsigned int i) const = 0 ;
        virtual ~Table();

    protected:

        Table();
        Table(const Table& tb);
        Table(Table&& tb);

        void write_code(const Code& cd, std::vector<char>& encrypted);
        Table& operator = (const Table& tb) = delete;
        Table& operator = (Table&& tb) = delete;
        std::pair<char, unsigned int> outp_byte;
};
