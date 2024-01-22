#ifndef ARCHIVER
#define ARCHIVER
    #include "../../headers/Abstract/Archiver.h" 
#endif

Archiver::Archiver() {}

Archiver::~Archiver() {}

Archiver::file_is_not_archive::file_is_not_archive(const std::string& nof) :
    _nof(nof) {}

const char * Archiver::file_is_not_archive::what() const noexcept {

    return "File is not archive";
}

const std::string& Archiver::file_is_not_archive::get_nof() const {

    return _nof;
}

Archiver::file_is_not_archive::~file_is_not_archive() {}

Archiver::cant_open_file_error::cant_open_file_error(const std::string& nof) :
    _nof(nof) {}

const char * Archiver::cant_open_file_error::what() const noexcept {

    return "Can't open file";
}

const std::string& Archiver::cant_open_file_error::get_nof() const {

    return _nof;
}

Archiver::cant_open_file_error::~cant_open_file_error() {}

Archiver::write_in_exist_file_error::write_in_exist_file_error(const std::string& nof) :
    _nof(nof) {}

const char * Archiver::write_in_exist_file_error::what() const noexcept {

    return "File already exist";
}

const std::string& Archiver::write_in_exist_file_error::get_nof() const {

    return _nof;
}

Archiver::write_in_exist_file_error::~write_in_exist_file_error() {}
