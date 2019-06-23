#include <iostream>
#include <list>
#include <string>

#include "Page.h"

#define FRAME_SIZE 3

using namespace std;

list<Page> get_pages(string reference, const string& delimiter);
void subst_page_fifo(list<Page>& paging_frame, Page next_page, int frame_size);
void subst_page_sca(list<Page>& paging_frame, Page next_page, int frame_size);

int main() {
    // system characteristics
    string reference = "1,2,3,4,2,1,5,6,2,1,2,3,7,6,3,2,1,2,3,6,2,4,1,6,2,2,7,3,1,3,1,3,2,4,2,2,7,4,1,3";
    string delimiter = ",";

    // paging queue
    list<Page> paging_frame_fifo;
    list<Page> paging_frame_sca;

    // extract paging information from paging reference string
    list<Page> pages = get_pages(reference, delimiter);

    cout << "FIFO: " << endl;
    // fifo algorithm
    for (Page & page : pages) {
        subst_page_fifo(paging_frame_fifo, page, FRAME_SIZE);

        // print the result of the substitution
        cout << "[ ";
        for (Page & page_in_frame : paging_frame_fifo) {
            cout << page_in_frame.page << " ";
        }
        cout << "]" << endl;
    }
    cout << endl;

    cout << "Second-chance Algorithm" << endl;
    // second change algorithm
    for (Page & page : pages) {
        subst_page_sca(paging_frame_sca, page, FRAME_SIZE);

        // print the result of the substitution
        cout << "[ ";
        for (Page & page_in_frame : paging_frame_sca) {
            cout << page_in_frame.page << " (" << page_in_frame.ref_bit_up() << ") ";
        }
        cout << "]" << endl;
    }
    cout << endl;
}

list<Page> get_pages(string reference, const string& delimiter) {
    list<Page> pages;
    char* pEnd;

    // memory pages iteration
    int pos = 0;
    string token;
    while ((pos = reference.find(delimiter)) != string::npos) {
        token = reference.substr(0, pos);
        Page page(strtol(token.c_str(), &pEnd, 10));
        pages.push_back(page);
        reference.erase(0, pos + delimiter.length());
    }
    Page last_page(strtol(reference.c_str(), &pEnd, 10));
    pages.push_back(last_page);

    return pages;
}

void subst_page_fifo(list<Page>& paging_frame, const Page next_page, const int frame_size) {
    // verify whether this is a page fault
    bool page_fault = true;
    for (Page & page : paging_frame) {
        if (page.page == next_page.page)
            page_fault = false;
    }

    // if page fault, apply algorithm
    if (page_fault) {
        if (paging_frame.size() == frame_size)
            paging_frame.pop_front();
        Page page(next_page);
        paging_frame.push_back(page);
    }
}

void subst_page_sca(list<Page>& paging_frame, const Page next_page, const int frame_size) {
    // verify whether this is a page fault
    // if it isn't, toggle reference bit of page to 1
    bool page_fault = true;
    for (Page & page : paging_frame) {
        if (page.page == next_page.page) {
            page_fault = false;
            if (!page.ref_bit_up()) {
                page.toggle_bit();
            }
            break;
        }
    }

    // if page fault, apply algorithm
    Page page(next_page);
    if (page_fault) {
        // add page-fault-causing page value
        if (paging_frame.size() == frame_size) {
            for (Page & current_page : paging_frame) {
                if (!current_page.ref_bit_up()) {
                    paging_frame.remove(current_page);
                    break;
                } else {
                    current_page.toggle_bit();
                }
            }
        }

        // When all bits are referenced (1), it may happen that the push
        // might overflow on the frame size. In this case, revert back to
        // FIFO strategy.
        if (paging_frame.size() == frame_size)
            paging_frame.pop_front();
        paging_frame.push_back(page);
    }
}