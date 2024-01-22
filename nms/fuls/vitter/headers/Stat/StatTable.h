#ifndef TABLE
#define TABLE
    #include "../Abstract/Table.h" 
#endif

#ifndef STATTREE
#define STATTREE
    #include "StatTree.h"
#endif

#ifndef STATNODE
#define STATNODE
    #include "StatNode.h"
#endif

#ifndef MEMORY
#define MEMORY
    #include <memory>
#endif

class StatTree;

class StatTable final : public Table
{
    public:

        // constructors
        explicit StatTable(StatTree& tree);
        StatTable(const StatTable& stb);
        StatTable(StatTable&& stb);

        virtual std::vector<char> encrypt(const std::vector<char>&
                                          bytes_to_encrypt);

        virtual const Code& operator [] (unsigned int i) const; // EXCEPTION //

        StatTable& operator = (const StatTable& stb);
        StatTable& operator = (StatTable&& stb);

        virtual ~StatTable();

    protected:
        
        void rec_make_table(const std::shared_ptr<const StatNode>& stn,
                            std::size_t code, unsigned int length);

        std::shared_ptr<Code[]> table;
        bool bad_state;
};
