/*
This program is very simple. It contains two classes: Block and Graph.
- Graphs are responsible for ownership of a collection of Blocks.
- Blocks have two pieces of data: A name (std::string) and collection of (std::string) attributes.

This Graph class supports two operations:
1. Add a Block to the Graph (AddBlock)
- When a Block is added to a Graph, it cannot share a name with any Blocks already in the Graph. If the Block's name is
already elsewhere in the graph, its name will be modified to be unique. If the block's name is already unique, it must
not be changed.
- Calling AddBlock is resource acquisition. When it comes to data management, the Graph is the owner of the Block from
this point on.
2. Return a collection of every Block in the Graph that has a specified attribute (GetBlocksWithAttribute)
- Blocks can have any number of attributes.

There are functions below prefixed with Measure_. These _Measure functions exercise the two Graph operations previously
discussed. The goal of this exercise is to optimize the execution time of these functions:
- Measure_AddBlocks
- Measure_FindAttributesByBlock
- Measure_FindBlocksByAttribute

If you take a look at main() below, you'll see that it sends the execution time of these functions to stdout. Go ahead and
run the program as-is and it's obvious that the initial performance of these operations is very bad. If it doesn't build or
run, fix it so it does.

Goal: See how much better you can make it!

Here are the rules:
- The dynamic behavior of the code cannot change. Don't just write code to generate the expected output, expect your solution
to be tested on different datasets.
- You ARE NOT allowed to modify the Measure_ functions or main() except to make them compile and run.
- You ARE allowed to modify the Block and Graph classes. Feel free to change the API, data structures, etc. as long as you can
do so without requiring a modification of Measure_ functions or main().
- Feel free to use C++11/14/17 language features or any boost classes.
- Feel free to make any obvious, simple improvements generally.

When you're done, please send me three things:
- Your modified optgraph.cpp file. Please add a comment tagging where you've made changes.
- A copy/paste of the program output before and after you made your changes.
- A brief description of the changes that you made.

Bonus exercise:
Are there any problems that you see with this code that aren't related to performance optimization? Any obvious improvements
that jump out to you? Feel free to fix those issues as well, and be sure to include descriptions of what you fixed and why.

Good luck, and feel free to get in touch if you have any specific questions.
*/

#include <stdio.h>
#include <string>
#include <list>
#include <chrono>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <set>

class Block
{
public:
    // Better to reserve() the capacity of a vector. so that will prevent from   
    // un-nessery shifting of element while extending the vector size.
    // As of now I am living code as it is.
    Block() {}    
    ~Block() { }

    std::string GetName() const{ return m_name; }
    void SetName(std::string name) { m_name = name; }


    void AddAttribute(std::string attribute) { m_attributes.push_back(attribute); }


    // This is importance, instead of returning by value better to return by const refrence.
    // Why Refrence ??
    //    when we get an object from a container, the object is not the one that was in the container.
    //    When we add an object to a container, what goes into the container is a copy of the object 
    //    Copy in, copy out.That's the STL way.
    //
    //    suppose we have 1000 element in a vector (m_attributes), returning by value means copying   
    //    1000 element from one container to another. To prevent form this need to return by ref. 
    //
    // Why Const ??    
    //    because here we are returning internal handle/attribute of object by refrence, so it is 
    //    very easy to medify data from outside of function. Const privant data from accidentioanl modification. 
    //
    //    Note::      const_cast<vector<string>&>(m_attributes)   <- however by using this trick we and remove 
    //                                                               the constness and modify the data. 
    //
    const std::vector<std::string>& GetAttributes() const{ return m_attributes; }

private:
    std::string m_name;

    // Instread of list I am using vector here, if offers same time complexity as list offers
    // but consume less memory to compare to list (address of next node).
    // However we can sort on vector before and then use binary_search operation, this can reduce 
    // searching time O(n) to O(logn).
    std::vector<std::string> m_attributes;
};


// Custom comerator for set of Block*, key element of set is Block name.
class BlockPtrLess {
public:
    bool operator() (const Block* lsh, const Block* rhs) const {
        return (lsh->GetName() < rhs->GetName());
    }
};

class Graph
{

public:

    // Adds the passed block to this graph. Potentially renames the block prior to insertion to guarantee
    // each block in the graph has a unique name.

    void DeleteBlock(Block* blk) {
        delete blk;
    }

    void AddBlock(Block* block)
    {
        // Make sure we have a unique name for this block within the content of this Graph object.
        // Now seraching offres in log(n) time.
        std::string uniqueName = GetUniqueBlockNameInGraph(block);

  

        block->SetName(uniqueName);

        // Add it to our collection of blocks.
        // Now insertion offres in log(n) time where as list offes in O(1) time.
        m_blocks.insert(block);
    }

    ~Graph() {
        std::set<Block*, BlockPtrLess> m_blocks;

        for_each(m_blocks.begin(), m_blocks.end(), DeleteBlock);



    }

    // Here it is fine to return by value, because set has pointers of Block. 
    std::set<Block*, BlockPtrLess> GetBlocks() {
        return m_blocks;
    }

    std::list<Block*> GetBlocksWithAttribute(std::string attribute)
    {
        std::list<Block*> blocksWithAttribute;
        for (Block* b : m_blocks)
        {
            const std::vector<std::string>& attributes = b->GetAttributes();
            if (std::find(attributes.begin(), attributes.end(), attribute)!=attributes.end()) {
                blocksWithAttribute.push_back(b);
            }
        }
        return blocksWithAttribute;
    }

private:

    // Determines if the specified blockName is already the name of a block in this Graph.
    bool BlockNameExistsInGraph(std::string blockName)
    {
        Block* tmp = new Block();
        tmp->SetName(blockName);     
        
        bool ans = (m_blocks.find(tmp) != m_blocks.end());
        delete tmp;
        return ans;

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

private:

    // Here is our collection of blocks in this graph.

    // Insted of list now we have set with custom comparator BlockPtrLess.
    // set keep data in sorted order and offers serach search capabitity in O(logn) time
    // However it demands more memory to implement banlanced binary serach tree kind of
    // struture.

    std::set<Block*, BlockPtrLess> m_blocks;
};


/// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
/// DO NOT MODIFY ANY CODE BELOW THIS POINT
/// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

static const int s_blockQuantity = 1000;
static const int s_attributesPerBlock = 250;

static const int s_distinctAttributes = 300;
static const int s_distinctBlockNames = 10;
static std::string s_blockBaseName("blockNameBase_");
static std::string s_attrBaseName("attributeBase_");

static std::vector<std::string> s_attrs;
static std::vector<std::string> s_blockNames;

void createBlockNames() {
    std::ostringstream s;
    for (int i = 0; i < s_distinctBlockNames; ++i) {
        s << s_blockBaseName;
        s_blockNames.push_back(s.str());
    }
}

void createAttrNames() {
    for (int i = 0; i < s_distinctAttributes; ++i) {
        std::ostringstream s;
        s << s_attrBaseName << i;
        s_attrs.push_back(s.str());
    }
}

std::chrono::milliseconds Measure_AddBlocks(Graph& graph)
{
    auto start = std::chrono::system_clock::now();
    int blockNameNum = 0;
    int attrNum = 0;

    for (int i = 0; i < s_blockQuantity; ++i)
    {
        blockNameNum = ++blockNameNum % s_distinctBlockNames;

        Block* b = new Block;
        b->SetName(s_blockNames[blockNameNum]);
        for (int j = 0; j < s_attributesPerBlock; ++j)
        {
            attrNum = ++attrNum % s_distinctAttributes;
            b->AddAttribute(s_attrs[attrNum]);
        }
        graph.AddBlock(b);
    }
    auto end = std::chrono::system_clock::now();

    // Post-measurement verification

    return std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
}

std::chrono::milliseconds Measure_FindAttributesByBlock(Graph& graph)
{
    auto start = std::chrono::system_clock::now();
    int compareLength = s_attrBaseName.length();

    for (auto block : graph.GetBlocks()) {
        for (const auto& attr : block->GetAttributes()) {
            assert(attr.compare(0, compareLength, s_attrBaseName) == 0);
        }
    }

    auto end = std::chrono::system_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
}

std::chrono::milliseconds Measure_FindBlocksByAttribute(Graph& graph)
{
    auto start = std::chrono::system_clock::now();
    int compareLength = s_blockBaseName.length();

    for (const auto& attr : s_attrs) {
        for (auto block : graph.GetBlocksWithAttribute(attr)) {
            assert(block->GetName().compare(0, compareLength, s_blockBaseName) == 0);
        }
    }
    auto end = std::chrono::system_clock::now();

    return std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
}

int main(int argc, char* argv[])
{
    Graph graph;
    createBlockNames();
    createAttrNames();

    auto timeAddBlocks = Measure_AddBlocks(graph);
    std::cout << "Measure_AddBlocks took: " << timeAddBlocks.count() << "ms.\n";

    auto timeFindAttributesByBlock = Measure_FindAttributesByBlock(graph);
    std::cout << "Measure_FindAttributesByBlock took: " << timeFindAttributesByBlock.count() << "ms.\n";

    auto timeFindBocksByAttribute = Measure_FindBlocksByAttribute(graph);
    std::cout << "Measure_FindBlocksByAttribute took: " << timeFindBocksByAttribute.count() << "ms.\n";

    std::getchar();
    return 0;
}
