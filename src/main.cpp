#include <iostream>

#include "ConverterJSON.h"
#include "SearchServer.h"

int main() {
    std::cout << "SearchEngine started" << std::endl;
    SearchServer search;
    ConverterJSON converter;
    RequestsDTO requests = RequestsDTO("requests.json");
    converter.putAnswers(search.searchAllRequests(requests.requests));

    return 0;
}
