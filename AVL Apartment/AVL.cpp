//
// Created by evy18 on 19/12/2021.
//

#include "AVL.h"
#include <vector>
#include <stack>

AVL::AVL() : root_(nullptr){}

AVL::AVL(const AVL &other) {
    create_avl(other);
}

AVL::node* AVL::node_to_copy(const node* to_copy, node* parent){
    if (to_copy == nullptr){
        return nullptr;
    }
    else{
        node* temp = new node(to_copy->get_data(), nullptr, nullptr,
                               parent,to_copy->left_high_,
                               to_copy->right_high_);
        if (to_copy->parent_->left_ == to_copy){
            parent->left_ = temp;
        }
        else{
            parent->right_ = temp;
        }
        temp->left_ = node_to_copy(to_copy->left_,temp);
        temp->right_ = node_to_copy(to_copy->right_,temp);
        return temp;
    }
}

void AVL::create_avl(const AVL &other){
    this->root_ = new node(other.get_root()->data_, nullptr, nullptr,
                           nullptr,other.get_root()->left_high_,other
                                   .get_root()->right_high_);
    root_->left_ = node_to_copy(other.get_root()->left_,root_);
    root_->right_ = node_to_copy(other.get_root()->right_,root_);
}

AVL& AVL::operator=(const AVL &other) {
    if (this != &other){
        delete_avl(this->root_);
        create_avl(other);
    }
    return (*this);
}

void AVL::delete_avl(node *cur) {
    if (cur == nullptr){
        return;
    }
    delete_avl(cur->left_);
    delete_avl(cur->right_);
    delete cur;
}
AVL::~AVL(){
    delete_avl(root_);
    root_ = nullptr;
}

AVL::AVL(std::vector<std::pair<double, double>> coordinates) : AVL() {
    for (const auto &pair: coordinates){
        Apartment my_apartment = Apartment(pair);
        insert(my_apartment);
        }
    }


void AVL::right_rotation(node* node){
    (node->left_)->parent_ = node->parent_;
    AVL::node* cur_parent = (node->left_)->parent_;
    AVL::node* z=(node->left_)->right_;
    (node->left_)->right_=node;
    (node->left_)->right_high_ = ((node->left_)->right_)->right_high_+1;
    node->parent_ = node->left_;
    (node->left_)= z;
    if (z == nullptr){
        node->left_high_ = 0;
    }
    else{
        z->parent_=node;
        node->left_high_ = z->left_high_+1;
    }
    if (cur_parent != nullptr){
        if (cur_parent->left_ == node){
            cur_parent->left_ = node->parent_;
        }
        else{
            cur_parent->right_ = node->parent_;
        }
    }
}

void AVL::left_rotation(node *node){
    (node->right_)->parent_ = node->parent_;
    AVL::node* cur_parent = (node->right_)->parent_;
    AVL::node* z = (node->right_)->left_;
    (node->right_)->left_ = node;
    (node->right_)->left_high_ = ((node->right_)->left_)->left_high_ +1;
    node->parent_ = node->right_;
    (node->right_) = z;
    if (z == nullptr){
        node->right_high_ = 0;
    }
    else{
        z->parent_=node;
        node->right_high_ = z->right_high_ +1;
    }
    if (cur_parent != nullptr){
        if (cur_parent->left_ == node){
            cur_parent->left_ = node->parent_;
        }
        else{
            cur_parent->right_ = node->parent_;
        }
    }
}

void AVL::update_highs(node *node, int type) {
    AVL::node* cur_son = node;
    AVL::node* cur = (node->parent_);
    while (cur != nullptr){
        if (cur->left_== cur_son){
            int max = cur_son->left_high_ > cur_son->right_high_ ?
                    cur_son->left_high_ : cur_son->right_high_;
            cur->left_high_ = max +1;
            if (type == AFTER_INSERTION){
                if (cur->left_high_ == cur->right_high_ || cur->left_high_ <
                                                           cur->right_high_ ){
                    break;
                }
            }
            else if(type == AFTER_DELETION){
                if (cur->left_high_ < cur->right_high_){
                    break;
                }
            }
        }
        else{
            int max = cur_son->left_high_ > cur_son->right_high_ ?
                    cur_son->left_high_ : cur_son->right_high_;
            cur->right_high_ = max +1;
            if (type == AFTER_INSERTION){
                if (cur->left_high_ == cur->right_high_ || cur->left_high_ >
                                                           cur->right_high_){
                    break;
                }
            }
            else if (type == AFTER_DELETION){
                if(cur->left_high_ > cur->right_high_){
                    break;
                }
            }
        }
        cur = cur->parent_;
        cur_son = cur_son->parent_;
    }
}

void AVL::do_rotation(node *node) {
    while (node != nullptr) {
        if (define_balance_factor(node) == 2) {
            balance_factor_two(node);
            if (node == root_) {
                root_ = node->parent_;
            }
        } else if (define_balance_factor(node) == -2) {
            balance_factor_minus_two(node);
            if (node == root_) {
                root_ = node->parent_;
            }
        }
        node = node->parent_;
    }
}

void AVL::balance_factor_two(node *node){
    if (define_balance_factor(node->get_left()) == 1 ||
            define_balance_factor(node->get_left()) == 0){
        //return LL
        right_rotation(node);
    }
    else if (define_balance_factor(node->get_left()) == -1){
        //return LR
        left_rotation(node->get_left());
        right_rotation(node);
    }
    update_highs(node->parent_,AFTER_ROTATION);
}

void AVL::balance_factor_minus_two(node *node){
    if (define_balance_factor(node->get_right()) == 1){
        //return RL
        right_rotation(node->get_right());
        left_rotation(node);
    }
    else if (define_balance_factor(node->get_right()) == -1 ||
    define_balance_factor(node->get_right()) == 0){
        //return RR
        left_rotation(node);
    }
    update_highs(node->parent_,AFTER_ROTATION);
}

int AVL::define_balance_factor(node *node) {
    return node->left_high_ - node->right_high_;
}

AVL::node* AVL::find_successor(node *node) {
    node = node->right_;
    while (node->left_ != nullptr){
        node = node->left_;
    }
    return node;
}

void AVL::insert (const Apartment &apartment) {
    //create a leaf with the given apartment
    node *node_to_insert = new node(apartment, nullptr, nullptr,
                                    nullptr, 0,0);
    //check if the AVL is empty
    if (this->root_ == nullptr) {
        this->root_ = node_to_insert;
    }
    //now the AVL is not empty
    else {
        node *cur = root_;
        //we will trip until we will find the correct place to put the node
        while (cur->get_left() != nullptr || cur->get_right() != nullptr) {
            if (cur->get_data() > apartment) {
                if (cur->get_left() == nullptr) {
                    break;
                }
                cur = cur->get_left();
            } else {
                if (cur->get_right() == nullptr) {
                    break;
                }
                cur = cur->get_right();
            }
        }
        //putting the node in the correct place
        node *prev_cur = cur;
        if (cur->get_data() > apartment) {
            cur->left_ = node_to_insert;
            cur = cur->get_left();
            cur->parent_ = prev_cur;
            (cur->parent_)->left_high_++;
            if ((cur->parent_)->left_high_ > (cur->parent_)->right_high_) {
                update_highs((cur->parent_), AFTER_INSERTION);
            }
        }
        else {
            cur->right_ = node_to_insert;
            cur = cur->get_right();
            cur->parent_ = prev_cur;
            (cur->parent_)->right_high_++;
            if ((cur->parent_)->left_high_ < (cur->parent_)->right_high_) {
                update_highs((cur->parent_), AFTER_INSERTION);
            }
            //now we will fix the tree if it's not good
        }
        do_rotation(prev_cur);
    }
}

void AVL::delete_node_with_just_left_child(node *cur){
    AVL::node* to_free = cur->left_;
    cur->data_ = to_free->data_;
    cur->right_high_ = to_free->right_high_;
    cur->left_high_ = to_free->left_high_;
    if (to_free->left_ != nullptr){
        (to_free->left_)->parent_ = cur;
    }
    cur->left_ = to_free->left_;
    if (to_free->right_ != nullptr){
        (to_free->right_)->parent_ = cur;
    }
    cur->right_ = to_free->right_;
    update_highs((cur), AFTER_DELETION);
    delete to_free;
}

void AVL::delete_node_with_just_right_child(node *cur){
    AVL::node* to_free = cur->right_;
    cur->data_ = to_free->data_;
    cur->right_high_ = to_free->right_high_;
    cur->data_ = cur->right_->data_;
    if (to_free->left_ != nullptr){
        (to_free->left_)->parent_ = cur;
    }
    cur->left_ = to_free->left_;
    if (to_free->right_ != nullptr){
        (to_free->right_)->parent_ = cur;
    }
    cur->right_ = to_free->right_;
    update_highs((cur->parent_), AFTER_DELETION);
    delete to_free;
}

void AVL::erase (const Apartment &apartment){
    if (root_ == nullptr){
        //don't do anything. just go out from the function
    }
    //the node I want to delete is the root
    else if (root_->get_data() == apartment){
        if (root_->get_left() == nullptr && root_->get_right() == nullptr){
            delete root_;
            root_ = nullptr;
        }
        else if (root_->get_left() == nullptr || root_->get_right() ==
        nullptr){
            if (root_->get_left()!= nullptr){
                delete_node_with_just_left_child(root_);
            }
            else{
                delete_node_with_just_right_child(root_);
            }
        }
        else{
            AVL::node* successor = find_successor(root_);
            Apartment data_to_insert = successor->get_data();
            erase(successor->get_data());
            root_->data_ = data_to_insert;
        }
    }
    else{
        //the node i want to delete is not the root
        node *cur = root_;
        //we will trip on the tree until we will find the node we have to
        // erase
        while (cur != nullptr){
            if (cur->get_data() > apartment){
                cur = cur->get_left();
            }
            else if (cur -> get_data() < apartment){
                cur = cur->get_right();
            }
            else if (cur -> get_data() == apartment){
                //after we found the node we have to delete, we will delete it
                //and try to keep the AVL tree balanced
                if (cur->get_left() == nullptr && cur->get_right() == nullptr)
                {
                    if ((cur->parent_)->right_==cur){
                        (cur->parent_)->right_ = nullptr;
                        (cur->parent_)->right_high_ --;
                        if ((cur->parent_)->right_high_ == (cur->parent_)
                                ->left_high_){
                            update_highs((cur->parent_), AFTER_DELETION);
                        }
                    }
                    else{
                        (cur->parent_)->left_ = nullptr;
                        (cur->parent_)->left_high_ --;
                        if ((cur->parent_)->right_high_ == (cur->parent_)
                                ->left_high_){
                            update_highs((cur->parent_), AFTER_DELETION);
                        }
                    }
                    do_rotation(cur->parent_);
                    delete cur;
                }
                else if(cur->get_left() == nullptr ||
                cur->get_right() == nullptr)
                {
                    if (cur->get_left() != nullptr){
                        //the node we delete have a left child
                        delete_node_with_just_left_child(cur);
                    }
                    else{
                        //the node we delete have a right child
                        delete_node_with_just_right_child(cur);
                    }
                    do_rotation(cur->parent_);
                }
                else{
                    //the node we delete have 2 children
                    AVL::node* successor = find_successor(cur);
                    Apartment data_to_insert = successor->get_data();
                    erase(successor->get_data());
                    cur->data_ = data_to_insert;
                }
                break;
            }
        }
    }
}

    AVL::Iterator::Iterator(node *cur): cur(cur){}

    AVL::Iterator::reference AVL::Iterator::operator* (){
        return cur->data_;
    }

    AVL::Iterator::pointer AVL::Iterator::operator-> (){
        return &cur->data_;
    }

    AVL::Iterator& AVL::Iterator::operator++(){
        if (cur->right_ != nullptr){
            my_stack.push(cur->right_);
        }
        if (cur->left_ != nullptr){
            my_stack.push(cur->left_);
        }
        cur = my_stack.top();
        my_stack.pop();
        if (my_stack.empty()){
            my_stack.push(nullptr);
        }
        return (*this);
    }

    AVL::Iterator AVL::Iterator::operator ++(int){
        Iterator it = (*this);
        if (cur->right_ != nullptr){
            my_stack.push(cur->right_);
        }
        if (cur->left_ != nullptr){
            my_stack.push(cur->left_);
        }
        cur = my_stack.top();
        my_stack.pop();
        if (my_stack.empty()){
            my_stack.push(nullptr);
        }
        return it;
    }

    bool AVL::Iterator::operator== (const Iterator &rhs) const{
        return cur == rhs.cur;
    }

    bool AVL::Iterator::operator!= (const Iterator &rhs) const{
        return !(rhs == *this);
    }

    AVL::ConstIterator::ConstIterator(node* cur) : cur(cur){}

    AVL::ConstIterator::reference AVL::ConstIterator::operator* ()
    const {
        return cur->data_;
    }

    AVL::ConstIterator::pointer AVL::ConstIterator::operator-> () const{
        return &cur->data_;
    }

    AVL::ConstIterator& AVL::ConstIterator::operator++(){
        if (cur->right_ != nullptr){
            my_stack.push(cur->right_);
        }
        if (cur->left_ != nullptr){
            my_stack.push(cur->left_);
        }
        cur = my_stack.top();
        my_stack.pop();
        if (my_stack.empty()){
            my_stack.push(nullptr);
        }
        return (*this);
    }

    AVL::ConstIterator AVL::ConstIterator::operator++(int){
        const_iterator it = *this;
        if (cur->right_ != nullptr){
            my_stack.push(cur->right_);
        }
        if (cur->left_ != nullptr){
            my_stack.push(cur->left_);
        }
        cur = my_stack.top();
        my_stack.pop();
        if (my_stack.empty()){
            my_stack.push(nullptr);
        }
        return it;
    }

    bool AVL::ConstIterator::operator== (const ConstIterator &rhs) const{
        return cur == rhs.cur;
    }

    bool AVL::ConstIterator::operator!= (const ConstIterator &rhs) const{
        return !(rhs == *this);
    }

AVL::iterator AVL::begin() {
    return {root_};
}

AVL::const_iterator AVL::begin() const {
    return {root_};
}

AVL::const_iterator AVL::cbegin() const {
    return {root_};
}

AVL::iterator AVL::end() {
    return {nullptr};
}

AVL::const_iterator AVL::end() const {
    return {nullptr};
}

AVL::const_iterator AVL::cend() const {
    return {nullptr};
}

AVL::iterator AVL::find(const Apartment &data) {
    AVL::node* cur = root_;
    while (cur->get_left() != nullptr || cur->get_right() != nullptr){
        if (cur->get_data() == data){
            return {cur};
        }
        else if (cur->get_data() > data){
            cur = cur->get_left();
        }
        else if (cur -> get_data() < data){
            cur = cur->get_right();
        }
    }
    return end();
}

AVL::const_iterator AVL::find(const Apartment &data) const {
    AVL::node* cur = root_;
    while (cur->get_left() != nullptr || cur->get_right() != nullptr){
        if (cur->get_data() == data){
            return {cur};
        }
        else if (cur->get_data() > data){
            cur = cur->get_left();
        }
        else if (cur -> get_data() < data){
            cur = cur->get_right();
        }
    }
    return end();
}

std::ostream &operator<< (std::ostream &os, const AVL &avl){
    for (auto apartment : avl){
        os << apartment;
    }
    return os;
}
