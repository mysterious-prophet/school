#ifndef TABLE
#define TABLE
    #include "../Abstract/Table.h"
#endif

#ifndef MEMORY
#define MEMORY
    #include <memory>
#endif

#ifndef DYNTREE
#define DYNTREE
    #include "DynTree.h"
#endif

#ifndef NYT_NODE_SIGN
#define NYT_NODE_SIGN 0x200
#endif

#ifndef NO_INF_SIGN
#define NO_INF_SIGN 0x300
#endif

#ifndef NOTHING
#define NOTHING -1
#endif
 
class Code;

class DynTable final : public Table
{
    public:

        explicit DynTable(DynTree& dtr);
        DynTable(const DynTable& dtb);
        DynTable(DynTable&& dtb);

        virtual std::vector<char> encrypt(const std::vector<char>&
                                          bytes_to_encrypt);

        DynTable& operator = (const DynTable& dtb);
        DynTable& operator = (DynTable&& dtb);

        virtual const Code& operator [] (unsigned int i) const;
        virtual ~DynTable();
        
    protected:

        DynTree * dyn_tree;
        std::shared_ptr<Code> ret_Code;
};
