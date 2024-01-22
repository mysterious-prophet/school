#ifndef STRING
#define STRING
    #include <string>
#endif

#ifndef NO_INF_SIGN
    #define NO_INF_SIGN 0x300
#endif

class Code
{
    public:

        Code(unsigned short Byte = static_cast<unsigned short>(NO_INF_SIGN),
             const std::size_t& b_Code = 0, unsigned int Length = 0);

        Code(const Code& cd);
        Code(Code&& cd);
        unsigned short get_byte() const;
        const std::size_t& get_code() const;
        unsigned int  get_length() const;
        void reset_byte(unsigned short Byte);
        void reset_code(const std::size_t& b_Code);
        void reset_length(unsigned int Length);
        Code& operator = (const Code& cd);
        Code& operator = (Code&& cd);
        ~Code();
        
    protected:

        unsigned short byte;
        std::size_t code;
        unsigned int length;
};
