#include <time.h>
#include <iostream>
#include <sstream>

#include "tagged_document_lookup.hpp"

int main()
{
    // instance of our class
    TaggedDocumentsLookup::TaggedDocuments& instance =
        TaggedDocumentsLookup::TaggedDocuments::instance();
        
    // initialize random seed (this is used by rand() function for generateing
    // pseudo-random number)
    srand(time(NULL));

    // start generating data and fill the container
    // generate 1000000 documents
    const unsigned numberOfDocs = 1000000;
    for (unsigned i = 0; i < numberOfDocs; ++i) {
        // randomly choose a number in [2, 7] for generting associated tags
        int tagCount = (rand() % 7) + 2;

        // construct document names: doc_{i}
        std::stringstream document;
        document << "doc_" << i;

        // generate set of tags for doc_{i}
        for (int i = 0; i <= tagCount; ++i) {
            // generate random number in [1, 100]
            int random = rand() % 100 + 1;
            std::stringstream ss;
            // construct tag name: tag_{random}
            ss << "tag_" << random;
            instance.insert(document.str(), ss.str());
        }
    }
    // end generating data and fill the container

    // start generatin set of tags for testing
    std::set<std::string> tags;
    int numberOfTags = rand() % (40 - 10) + 10;
    for (int i = 0; i <= numberOfTags; ++i) {
        int tagNumber = rand() % 100 + 1;
        std::stringstream ss;
        ss << "tag_" << tagNumber;
        tags.insert(ss.str());
    }
    // end generatin set of tags for testing

    // search for documents
    // see results in found_documents.txt
    instance.streamOutDocuments(tags);
}
