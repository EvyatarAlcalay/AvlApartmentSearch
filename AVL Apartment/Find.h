//
// Created by rotem on 21/09/2021.
//

#ifndef _FIND_H_
#define _FIND_H_
#include "Apartment.h"
/**
 *  The function returns an iterator to the item that corresponds to the item
 * we were looking for. If there is no such member, returns end ().
 * @tparam InputIt
 * @param first
 * @param last
 * @param value
 * @return
 */
template<class InputIt>
InputIt find (InputIt first, InputIt last, const Apartment &value){
    while (first != last){
        if (*first == value){
            return first;
        }
        ++first;
    }
    return last;
}
#endif //_FIND_H_
