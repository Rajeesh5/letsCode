
#include<iostream>
#include<string>
#include<vector>
#include<list>
#include<set>
#include <sstream> 
#include<algorithm>

using namespace std;

class Block
{
public:

    // Reserver the vector, as many element required s_attributesPerBlock = 250
    Block() {} //: m_name("") { m_attributes.reserve(251); }
    Block(std::string name) :m_name(name) {}
    ~Block() { }

    std::string GetName() const{ return m_name; }
    void SetName(std::string name) { m_name = name; }

    void AddAttribute(std::string attribute) { m_attributes.push_back(attribute); }
    const std::vector<std::string>& GetAttributes() { return m_attributes; }

private:
    std::string m_name;
    std::vector<std::string> m_attributes;
};

class BlockPtrLess {

public:
    bool operator() (const Block* lsh, const Block* rhs) const{
        return (lsh->GetName() < rhs->GetName());
    }
};


class Graph {
     
public:


    void AddBlock(Block* block)
    {
        // Make sure we have a unique name for this block within the content of this Graph object.
        std::string uniqueName = GetUniqueBlockNameInGraph(block);
        block->SetName(uniqueName);

        // Add it to our collection of blocks.
        m_blocks.insert(block);
    }


    std::set<Block*, BlockPtrLess> GetBlocks() {
        return m_blocks;
    }

    std::list<Block*> GetBlocksWithAttribute(std::string attribute)
    {
        std::list<Block*> blocksWithAttribute;

        for (Block* b : m_blocks)
        {
            std::vector<std::string> attributes = b->GetAttributes();
            std::stable_sort(attributes.begin(), attributes.end());
            if (std::binary_search(attributes.begin(), attributes.end(), attribute)) {
                blocksWithAttribute.push_back(b);
            }

        }
        return blocksWithAttribute;
    }
private:

    // Determines if the specified blockName is already the name of a block in this Graph.
    bool BlockNameExistsInGraph(std::string blockName)
    {
        Block* tmp = new Block(blockName);
        return (m_blocks.find(tmp) != m_blocks.end());
    }

    // Generate a unique name for this block within the graph.
    // If there's no name collision, then the original Block name is returned.
    // If there is a name collision, then we will appends numbers to the name to make unique.
    // So if you call with a block named "a" and there's already a block named "a", then it will return "a1".
    // If there's already an "a1" then it will return "a2", and so on.
    std::string GetUniqueBlockNameInGraph(Block* block)
    {
        std::string originalName = block->GetName();
        std::string potentialName = block->GetName();

        unsigned int count = 0;
        
        bool foundUniqueName = false;
        while (foundUniqueName == false)
        {
            if (!BlockNameExistsInGraph(potentialName))
            {
                foundUniqueName = true;
            }
            else if (BlockNameExistsInGraph(potentialName))
            {
                std::ostringstream s;
                s << originalName << count;
                potentialName = s.str();
                count++;
            }
        }

        return potentialName;
    }
       
    std::set<Block*,BlockPtrLess> m_blocks;
};

int main() {

    //Animal->Animal1->Animal2->Birds->Birds1->Person


    Block* Blk1 = new Block();
    Blk1->SetName("Birds");
    Blk1->AddAttribute("Crow");
    Blk1->AddAttribute("Pigion");
    Blk1->AddAttribute("sparrow");
    Blk1->AddAttribute("Valture");

    Block *Blk2 = new Block();
    Blk2->SetName("Persons");
    Blk2->AddAttribute("Rajeev");
    Blk2->AddAttribute("Rohan");
    Blk2->AddAttribute("Dinesh");
    Blk2->AddAttribute("Kartik");


    Block *Blk3 = new Block();
    Blk3->SetName("Animal");
    Blk3->AddAttribute("Tiger");
    Blk3->AddAttribute("Loin");
    Blk3->AddAttribute("Monkey");
    Blk3->AddAttribute("Girraff");

    Block *Blk4 = new Block();
    Blk4->SetName("Animal");
    Blk4->AddAttribute("Tiger");
    Blk4->AddAttribute("Loin");
    Blk4->AddAttribute("Monkey");
    Blk4->AddAttribute("Girraff");
       

    Block* Blk5 = new Block();
    Blk5->SetName("Animal");
    Blk5->AddAttribute("Tiger");
    Blk5->AddAttribute("Loin");
    Blk5->AddAttribute("Monkey");
    Blk5->AddAttribute("Girraff");

    Block* Blk6 = new Block();
    Blk6->SetName("Birds");
    Blk6->AddAttribute("Crow");
    Blk6->AddAttribute("Pigion");
    Blk6->AddAttribute("sparrow");
    Blk6->AddAttribute("Valture");

    Graph Grp;

    Grp.AddBlock(Blk1);
    Grp.AddBlock(Blk2);
    Grp.AddBlock(Blk3);
    Grp.AddBlock(Blk4);
    Grp.AddBlock(Blk5);
    Grp.AddBlock(Blk6);


    std::set<Block*, BlockPtrLess> collection = Grp.GetBlocks();

    for (auto item : collection) {
        std::cout << item->GetName() << endl;;
    }


    std::list<Block*> blocksWithAttribute = Grp.GetBlocksWithAttribute("Tiger");

    cout << "\n----------------------------\n";


    for (auto item : blocksWithAttribute) {
        std::cout << item->GetName() << endl;;
    }



    return 0;

}