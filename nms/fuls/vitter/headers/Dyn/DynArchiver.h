#ifndef FSTREAM
#define FSTREAM
    #include <fstream>
#endif

#ifndef MEMORY
#define MEMORY
    #include <memory>
#endif

#ifndef VECTOR
#define VECTOR
    #include <vector>
#endif

#ifndef ARCHIVER
#define ARCHIVER
    #include "../Abstract/Archiver.h"
#endif

#ifndef DYNTREE
#define DYNTREE
    #include "DynTree.h"
#endif

#ifndef DYNTABLE
#define DYNTABLE
    #include "DynTable.h"
#endif

class DynArchiver final : public Archiver
{
    public:
        DynArchiver();
        virtual std::string arch(const std::string& nf_to_arch) const;

        virtual std::string unarch(const std::string& nf_to_unarch,
                                const std::string& Res_nf = "") const;

        virtual ~DynArchiver();
};
