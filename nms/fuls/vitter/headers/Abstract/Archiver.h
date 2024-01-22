#ifndef STRING
#define STRING
    #include <string>
#endif

class Archiver
{
    public:

        class file_is_not_archive : public std::exception
        {
            public:

                explicit file_is_not_archive(const std::string& nof);
                virtual const char * what() const noexcept;
                const std::string& get_nof() const;
                virtual ~file_is_not_archive();

            protected:

                std::string _nof;
        };

        class cant_open_file_error : public std::exception
        {
            public:

                explicit cant_open_file_error(const std::string& nof);
                virtual const char * what() const noexcept;
                const std::string& get_nof() const;
                virtual ~cant_open_file_error();

            protected:

                std::string _nof;
        };

        class write_in_exist_file_error : public std::exception
        {
            public:

                explicit write_in_exist_file_error(const std::string& nof);
                virtual const char * what() const noexcept;
                const std::string& get_nof() const;
                virtual ~write_in_exist_file_error();

            protected:

                std::string _nof;
        };

        Archiver();
        virtual std::string arch(const std::string& nf_to_arch) const = 0;

        virtual std::string unarch(const std::string& nf_to_unarch,
                                const std::string& Res_nf = "") const = 0;

        virtual ~Archiver();
};
