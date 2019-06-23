//
// Created by mateus on 6/23/19.
//

#include "Page.h"

Page::Page(int page) {
    this->page = page;
    this->ref_bit = 0;
}

void Page::toggle_bit() {
    this->ref_bit = !this->ref_bit;
}

bool Page::ref_bit_up() {
    return this->ref_bit;
}

bool Page::operator==(const Page& otherPage) {
    return (this->page == otherPage.page);
}
