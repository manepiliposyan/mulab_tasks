#include "tagged_document_lookup.hpp"
#include <algorithm>
#include <fstream>

namespace TaggedDocumentsLookup
{

//////////////////////////////////////////////////////////////////////////////////////////
//                                              TaggedDocuments //
//////////////////////////////////////////////////////////////////////////////////////////

TaggedDocuments&
TaggedDocuments::instance()
{
    static TaggedDocuments instance;
    return instance;
}

// first try to find the provided document
// if it is not present in the map yet create a new element document -> {tag}
// and insert in map if the document has been already inserted then simply add
// tag to its set of tags time Complexity of find is O(1) on average.
void
TaggedDocuments::insert(const std::string& document, const std::string& tag)
{
    Doc2TagMapIt it = doc2TagMap_.find(document);

    // if document does not exist add new element to the map
    if (it == doc2TagMap_.end()) {
        Tags newTagSet;
        newTagSet.insert(tag);
        doc2TagMap_.insert(std::make_pair(document, newTagSet));
        return;
    }

    it->second.insert(tag).second;
}

// output file format:
// Searching for the following set of tags:
// {tag_1, tag_2, tag_3, .... tag_n}
//
// Found <k>(number of found documents) documents:
// 1. doc_1
// 2. doc_2
// .....
// k. doc_k
void
TaggedDocuments::streamOutDocuments(const Tags& tags) const
{
    std::vector<std::string> documents;
    std::cout << "Starting search...\n";

    search(tags, documents);

    std::cout << "Search ended\n";

    // create a file <found_documents.txt>
    std::ofstream out("found_documents.txt");

    out << "Searching for the following set of tags:\n{";
    
    TagsConstIt it = tags.begin();
    TagsConstIt end = tags.end();
    for (; it != end; ++it) {
        out << *it;
        // adding this check so that the line does not end with a comma
        // e.g. {tag_1, tag_2, ... tag_n, }
        if (it != --tags.end()) out << ", ";
    }
    out << "}\n";

    out << "\nFound " << documents.size() << " documents\n";
    
    for (size_t i = 0; i != documents.size(); ++i)
        out << i + 1 << ". " << documents[i] << std::endl;

    // close the stream
    out.close();
}

// collects found documents in an array(doing this since in real-life projects
// some file processing might be needed)
// we iterate over the whole map, complexity O(n)
// additionally iterate over each set of tags of each document,
// complexity of each iteration - O(k) (k-number of tags associated with the
// observed documet) 
// for each tag, the find function searches in the provided
// set, complexity O(logn), overall complexity O(n*k*logn)
void
TaggedDocuments::search(const Tags& tags,
                        std::vector<std::string>& documents) const
{
    Doc2TagMapConstIt it = doc2TagMap_.begin();
    Doc2TagMapConstIt end = doc2TagMap_.end();

     // iterator to the end of the provided set
    TagsConstIt tagsEnd = tags.end(); 

    for (; it != end; ++it) {
        TagsConstIt currSetIt = it->second.begin();
        TagsConstIt currSetEnd = it->second.end();
        for (; currSetIt != currSetEnd; ++currSetIt)
            if (tags.find(*currSetIt) == tagsEnd) break;

        // if the set of tags of the current document entierly lies in the set
        // of provided set of tags, than kepp the document name
        if (currSetIt == currSetEnd) documents.push_back(it->first);
    }
}

void
TaggedDocuments::dbgDump() const
{
    std::cout << "Number of elements: " << doc2TagMap_.size();
    Doc2TagMapConstIt it = doc2TagMap_.begin();
    Doc2TagMapConstIt end = doc2TagMap_.end();
    for (; it != end; ++it) {
        std::cout << "Document: " << it->first << std::endl;
        std::cout << "Number of tags: " << it->second.size() << std::endl;
        TagsConstIt currSetIt = it->second.begin();
        TagsConstIt currSetEnd = it->second.end();
        for (; currSetIt != currSetEnd; ++currSetIt)
            std::cout << " - " << *currSetIt << std::endl;
    }
}

};  // namespace TaggedDocumentsLookup
