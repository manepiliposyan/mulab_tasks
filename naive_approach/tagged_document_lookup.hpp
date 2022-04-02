#ifndef TAGGED_DOCUMENTS_LOOKUP
#define TAGGED_DOCUMENTS_LOOKUP

#include <iostream>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

namespace TaggedDocumentsLookup
{
// a few typedefs so that the code is prettier

// container for tags
typedef std::set<std::string> Tags;  
// container to be used to store the data
typedef std::unordered_map<std::string, Tags> Doc2TagMap;  

// iterator to the map
typedef Doc2TagMap::iterator Doc2TagMapIt;  
// const iterator to the map
typedef Doc2TagMap::const_iterator Doc2TagMapConstIt;               
 // iterator to the set of tags
typedef Tags::const_iterator TagsConstIt; 

// singletone class that keeps our data and carries out the searching operation
// singelton designe ensures that only one instance of the class is created
// in real-life project this would ensure that we can access the same data from
// anywhere in the programm once the map is filled
class TaggedDocuments
{
  public:
    // returns the single instance of the class
    static TaggedDocuments& instance();

  private:
    TaggedDocuments()
        : doc2TagMap_()
    {
    }
    // since c++ compiler always defines default and copy constructors and the
    // assignment operator, we need to define them manually in private so they
    // will not be accesable outside of the class this is needed for singleton 
    // design pattern
    TaggedDocuments(const TaggedDocuments&);
    void operator=(const TaggedDocuments&);

  public:
    // add new document to doc2TagMap_ container
    void insert(const std::string& tag, const std::string& document);

    // reporting found documents in a file so it is convinient to go through
    void streamOutDocuments(const Tags& tags) const;

    // for debuging purposes
    // streams out the whole doc2TagMap_ container and some information about it
    void dbgDump() const;

  private:
    // actual searching operation is done in this function
    void search(const Tags& tags, std::vector<std::string>& documents) const;

  private:
    // unordered_map from document name to set of tags
    // set and map ensure that there are no duplications in documents and
    // tags document -> {tag1, tag2,...}
    Doc2TagMap doc2TagMap_;
};


};  // namespace TaggedDocumentsLookup
#endif
