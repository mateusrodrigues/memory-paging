#include <iostream>
#include <list>
#include <queue>
#include <string>

#define FRAME_SIZE 3

using namespace std;

list<int> get_pages(string reference, const string& delimiter);
void subst_page_fifo(list<int>& paging_frame, int next_page, int frame_size);

int main() {
    // system characteristics
    string reference = "1,2,3,4,2,1,5,6,2,1,2,3,7,6,3,2,1,2,3,6,2,4,1,6,2,2,7,3,1,3,1,3,2,4,2,2,7,4,1,3";
    string delimiter = ",";

    // paging queue
    list<int> paging_frame;

    // extract paging information from paging reference string
    list<int> pages = get_pages(reference, delimiter);

    for (int & page : pages) {
        subst_page_fifo(paging_frame, page, FRAME_SIZE);

        cout << "[ ";
        for (int & page_in_frame : paging_frame) {
            cout << page_in_frame << " ";
        }
        cout << "]" << endl;
    }
}

list<int> get_pages(string reference, const string& delimiter) {
    list<int> pages;
    char* pEnd;

    // memory pages iteration
    int pos = 0;
    string token;
    while ((pos = reference.find(delimiter)) != string::npos) {
        token = reference.substr(0, pos);
        pages.push_back(strtol(token.c_str(), &pEnd, 10));
        reference.erase(0, pos + delimiter.length());
    }
    pages.push_back(strtol(reference.c_str(), &pEnd, 10));

    return pages;
}

void subst_page_fifo(list<int>& paging_frame, const int next_page, const int frame_size) {
    // verify whether page already exists in page frame
    bool needs_removal = true;
    for (int & page : paging_frame) {
        if (page == next_page)
            needs_removal = false;
    }

    if (needs_removal) {
        if (paging_frame.size() == frame_size)
            paging_frame.pop_front();
        paging_frame.push_back(next_page);
    }
}