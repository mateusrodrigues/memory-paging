//
// Created by mateus on 6/23/19.
//

#ifndef PROJECT_SO_2_PAGE_H
#define PROJECT_SO_2_PAGE_H


class Page {

private:
    int ref_bit;

public:
    int page;

    explicit Page(int page);
    void toggle_bit();
    bool ref_bit_up();

    bool operator==(const Page& otherPage);
};


#endif //PROJECT_SO_2_PAGE_H
