#ifndef ARCHIVER
#define ARCHIVER
    #include "../Abstract/Archiver.h" 
#endif

#ifndef STATTREE
#define STATTREE
    #include "../../headers/Stat/StatTree.h"
#endif

#ifndef STATTABLE
#define STATTABLE
    #include "../../headers/Stat/StatTable.h"
#endif

#ifndef FSTREAM
#define FSTREAM
    #include <fstream>
#endif

class StatArchiver final : public Archiver
{
    public:
        StatArchiver();

        virtual std::string arch(const std::string& nf_to_arch) const;

        virtual std::string unarch(const std::string& nf_to_unarch,
                                const std::string& Res_nf = "") const;

        virtual ~StatArchiver();
};
