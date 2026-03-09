//
// Created by linad on 07.03.2026.
//

#ifndef SEARCHENGINE_INDEXER_H
#define SEARCHENGINE_INDEXER_H
#pragma once
#include <map>
#include <set>
#include <string>

#include "Document.h"


class Indexer {
public:
    std::map<std::string, std::vector<std::pair<int, int> > > index;

    void addDocument(const Document &doc) {
        for (auto it = doc.text.begin(); it != doc.text.end(); ++it) {
            index[it->first]
                    .emplace_back(
                        doc.docid, it->second
                    );
        }
    }

    nlohmann::json toJson() {
        nlohmann::json j;
        for (auto it = index.begin(); it != index.end(); ++it) {
            j.emplace(it->first, it->second);
        }
        return j;
    }

    nlohmann::json pairToJson(std::pair<int, int> pair) {
        nlohmann::json j;
        j[pair.first] = pair.second;
        return j;
    }

    std::string toString() {
        return toJson().dump(4);
    }
};


#endif //SEARCHENGINE_INDEXER_H
