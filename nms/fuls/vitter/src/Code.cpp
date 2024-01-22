#ifndef CODE
#define CODE
    #include "../headers/Code.h" 
#endif

Code::Code(unsigned short Byte, const std::size_t& b_Code, unsigned int Length) :
byte(Byte), code(b_Code), length(Length) {}

Code::Code(const Code& cd) :
byte(cd.byte), code(cd.code), length(cd.length) {}

Code::Code(Code&& cd) :
byte(cd.byte), code(std::move(cd.code)), length(cd.length) {

    cd.byte = static_cast<unsigned short>(NO_INF_SIGN);
    cd.length = 0;
}

unsigned short Code::get_byte() const {

    return byte;
}

const std::size_t& Code::get_code() const {

    return code;
}

unsigned int Code::get_length() const {

    return length;
}

void Code::reset_byte(unsigned short Byte) {

    if ((Byte <= 0x0FF) || ((Byte == 0x100)
        || (Byte == 0x200) || (Byte == 0x300))) {

        byte = Byte;

    } else {

        byte = NO_INF_SIGN;
    }
}

void Code::reset_code(const std::size_t& b_Code) {

    code = b_Code;
}

void Code::reset_length(unsigned int Length) {

    length = Length;
}

Code& Code::operator = (const Code& cd) {

    if(this == &cd){
        return * this;
    } else {
        byte = cd.byte;
        code = cd.code;
        length = cd.length;
        return * this;
    }
}

Code& Code::operator = (Code&& cd) {

    if(this == &cd){
        return * this;
    } else {
        byte = cd.byte;
        cd.byte = static_cast<unsigned short>(NO_INF_SIGN);
        code = std::move(cd.code);
        length = cd.length;
        cd.length = 0;
        return * this;
    }
}

Code::~Code() {}
