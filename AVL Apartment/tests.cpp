#include <iostream>
#include <vector>
#include "test_runner.h"
#include "Apartment.h"
#include "Stack.h"
#include "AVL.h"
#include "Find.h"
#include <algorithm>
//#include "Bonus.cpp"

using std::cin;
using std::cout;
using std::endl;
using std::size_t;
using std::string;


//----------------------------------------
//----------------------------------------
//----------------------------------------


void print_value(const AVL::node *pn) {
    cout << "(" << pn->get_data().get_x() << ","
         << pn->get_data().get_y() << ")";
    cout << endl;
}

void printBT(const std::string &prefix, const AVL::node *node, bool isLeft) {
    if (node != nullptr) {
        std::cout << prefix;

        std::cout << (isLeft ? "<-├──" : "->└──");

        print_value(node);

        // enter the next tree level - left and right branch
        printBT(prefix + (isLeft ? "  │   " : "    "), node->get_left(), true);
        printBT(prefix + (isLeft ? "  │   " : "    "), node->get_right(), false);
    }
}

void printBT(const AVL::node *node) {
    printBT("", node, false);
}

void print_avl(const AVL &avl) {
    cout << endl;
    printBT(avl.get_root());
    cout << endl;
}

//----------------------------------------
//----------------------------------------
//----------------------------------------

typedef std::pair<double, double> double_pair;

Apartment
create_apartment_and_insert(AVL &avl, const double_pair &coordinates) {
    Apartment apt(coordinates);
    avl.insert(apt);
    return apt;
}

bool test_apartment_sanity() {
    double_pair coordinates(123.321, 456.654);
    Apartment apartment(coordinates);

    return apartment.get_x() == coordinates.first &&
           apartment.get_y() == coordinates.second;
}

bool test_apartment_operator_lower_than() {
    std::vector<Apartment> apts{
            Apartment({0, 0}),  // distance: 47.42862
            Apartment({1, 0}),  // distance: 46.69106
            Apartment({7, 10}), // distance: 35.63766
            Apartment({10, 7}), // distance: 35.34677
    };

    for (size_t i = 0; i < apts.size(); i++) {
        if (apts[i] < apts[i]) {
            return false;
        }
        for (size_t j = 0; j < i; ++j) {
            if ((!(apts[i] < apts[j])) || (apts[j] < apts[i])) {
                return false;
            }
        }
    }

    return true;
}

bool test_apartment_operator_greater_than() {
    std::vector<Apartment> apts{
            Apartment({0, 0}),  // distance: 47.42862
            Apartment({1, 0}),  // distance: 46.69106
            Apartment({7, 10}), // distance: 35.63766
            Apartment({10, 7}), // distance: 35.34677
    };

    for (size_t i = 0; i < apts.size(); i++) {
        if (apts[i] > apts[i]) {
            return false;
        }

        for (size_t j = 0; j < i; ++j) {
            if ((apts[i] > apts[j]) || !(apts[j] > apts[i])) {
                return false;
            }
        }
    }

    return true;
}

bool test_apartment_operator_equal_given_equal_apartments() {
    const double x = 123;
    const double y = -123;

    std::vector<Apartment> apts{
            Apartment({x, y}),
            Apartment({x, y}),
            Apartment({x, y - (EPSILON / 2)}),
            Apartment({x - (EPSILON / 2), y}),
    };

    for (size_t i = 0; i < apts.size(); i++) {
        for (size_t j = 0; j <= i; ++j) {
            if (!(apts[i] == apts[j] && apts[j] == apts[i])) {
                return false;
            }
        }
    }

    return true;
}

bool test_apartment_operator_equal_given_unequal_apartments() {
    const double x = 123;
    const double y = -123;

    std::vector<Apartment> apts{
            Apartment({x, y}),
            Apartment({x, y - (2 * EPSILON)}),
            Apartment({x - (2 * EPSILON), y}),
    };

    for (size_t i = 0; i < apts.size(); i++) {
        for (size_t j = 0; j < i; ++j) {
            if (apts[i] == apts[j] && apts[j] == apts[i]) {
                return false;
            }
        }
    }

    return true;
}

bool test_stack_default_ctor() {
    Stack stack;
    return stack.empty() && stack.size() == 0;
}

bool test_stack_vector_ctor() {
    std::vector<double_pair> apts{
            {1, 2},
            {2, 3},
            {3, 4},
            {4, 5}};
    Stack stack(apts);

    return !stack.empty() && stack.size() == apts.size() &&
           stack.top() == Apartment(apts.back());
}

bool test_stack_operations() {
    Stack stack;

    auto apt1 = Apartment({1, 2});
    auto apt2 = Apartment({4, 5});
    auto apt3 = Apartment({6, -9});
    auto apt4 = Apartment({8, 10});

    stack.push(apt1);
    bool result = stack.top() == apt1 && stack.size() == 1 && !stack.empty();
    stack.push(apt2);
    result = result && stack.top() == apt2 && stack.size() == 2 &&
             !stack.empty();
    stack.pop();
    result = result && stack.top() == apt1 && stack.size() == 1 &&
             !stack.empty();
    stack.push(apt3);
    stack.push(apt2);
    result = result && stack.top() == apt2 && stack.size() == 3 &&
             !stack.empty();
    stack.pop();
    result = result && stack.top() == apt3 && stack.size() == 2 &&
             !stack.empty();
    stack.top() = apt4;
    result = result && stack.top() == apt4 && stack.size() == 2 &&
             !stack.empty();
    stack.pop();
    stack.pop();
    result = result && stack.size() == 0 && stack.empty();

    return result;
}

bool test_stack_iterator() {
    auto apt1 = Apartment({1, 2});
    auto apt2 = Apartment({4, 5});
    auto apt3 = Apartment({6, -9});
    auto apt4 = Apartment({8, 10});

    std::vector<double_pair> coordinates{
            {apt1.get_x(), apt1.get_y()},
            {apt2.get_x(), apt2.get_y()},
            {apt3.get_x(), apt3.get_y()},
    };

    Stack stack(coordinates);

    size_t i = coordinates.size() - 1;
    for (const auto &apt: stack) {
        if (!(apt == Apartment(coordinates[i--]))) {
            return false;
        }
    }

    stack.push(apt4);
    coordinates.push_back({apt4.get_x(), apt4.get_y()});

    i = coordinates.size() - 1;
    for (const auto &apt: stack) {
        if (!(apt == Apartment(coordinates[i--]))) {
            return false;
        }
    }

    return true;
}

bool test_stack_const_iterator() {
    auto apt1 = Apartment({1, 2});
    auto apt2 = Apartment({4, 5});
    auto apt3 = Apartment({6, -9});
    auto apt4 = Apartment({8, 10});

    std::vector<double_pair> coordinates{
            {apt1.get_x(), apt1.get_y()},
            {apt2.get_x(), apt2.get_y()},
            {apt3.get_x(), apt3.get_y()},
    };

    Stack stack(coordinates);
    const Stack stack2 = stack;

    size_t i = coordinates.size() - 1;
    for (const auto &apt: stack2) {
        if (!(apt == Apartment(coordinates[i--]))) {
            return false;
        }
    }

    stack.push(apt4);
    coordinates.push_back({apt4.get_x(), apt4.get_y()});
    const Stack stack3 = stack;

    i = coordinates.size() - 1;
    for (const auto &apt: stack3) {
        if (!(apt == Apartment(coordinates[i--]))) {
            return false;
        }
    }

    return true;
}

bool test_avl_vector_ctor() {
    Apartment apt6({6, 6});
    Apartment apt7({7, 7});
    Apartment apt4({4, 4});
    Apartment apt8({8, 8});
    Apartment apt5({5, 5});
    Apartment apt2({2, 2});
    Apartment apt3({3, 3});
    Apartment apt1({1, 1});
    Apartment apt0({0, 0});

    std::vector<double_pair> coordinates{
            {apt6.get_x(), apt6.get_y()},
            {apt7.get_x(), apt7.get_y()},
            {apt4.get_x(), apt4.get_y()},
            {apt8.get_x(), apt8.get_y()},
            {apt5.get_x(), apt5.get_y()},
            {apt2.get_x(), apt2.get_y()},
            {apt3.get_x(), apt3.get_y()},
            {apt1.get_x(), apt1.get_y()},
            {apt0.get_x(), apt0.get_y()},
    };
    AVL avl(coordinates);

    AVL::node *root = avl.get_root();
    AVL::node *left = root->get_left();
    AVL::node *right = root->get_right();

    return root->get_data() == apt6
           && left->get_data() == apt7
           && right->get_data() == apt2
           && left->get_left()->get_data() == apt8
           && right->get_left()->get_data() == apt4
           && right->get_right()->get_data() == apt1
           && right->get_left()->get_left()->get_data() == apt5
           && right->get_left()->get_right()->get_data() == apt3
           && right->get_right()->get_right()->get_data() == apt0;

}

bool test_avl_simple_insert() {
    AVL avl;
    bool result = avl.get_root() == nullptr;

    Apartment apt1({1, 1}); // middle
    Apartment apt0({0, 0}); // farthest
    Apartment apt2({2, 2}); // closest

    avl.insert(apt1);
    result = result && avl.get_root()->get_data() == apt1
             && avl.get_root()->get_left() == nullptr
             && avl.get_root()->get_right() == nullptr;
    avl.insert(apt0); // goes right
    result = result
             && avl.get_root()->get_data() == apt1
             && avl.get_root()->get_left() == nullptr
             && avl.get_root()->get_right()->get_data() == apt0;
    avl.insert(apt2); // goes left
    result = result
             && avl.get_root()->get_data() == apt1
             && avl.get_root()->get_left()->get_data() == apt2
             && avl.get_root()->get_right()->get_data() == apt0;

    return result;
}

bool test_avl_insert_LL_root_imbalance() {
    AVL avl;

    Apartment apt0 = create_apartment_and_insert(avl, {0, 0});
    Apartment apt1 = create_apartment_and_insert(avl, {1, 1});
    Apartment apt_1 = create_apartment_and_insert(avl, {-1, -1});
    Apartment apt05 = create_apartment_and_insert(avl, {0.5, 0.5});
    Apartment apt2 = create_apartment_and_insert(avl, {2, 2});
    Apartment apt3({3, 3});

    // before rotation
    AVL::node *root = avl.get_root();
    AVL::node *left = root->get_left();
    AVL::node *right = root->get_right();

    bool result = root->get_data() == apt0
                  && left->get_data() == apt1
                  && right->get_data() == apt_1
                  && left->get_left()->get_data() == apt2
                  && left->get_right()->get_data() == apt05;

    avl.insert(apt3);
    // after rotation

    root = avl.get_root();
    left = root->get_left();
    right = root->get_right();

    return result
           && root->get_data() == apt1
           && left->get_data() == apt2
           && right->get_data() == apt0
           && left->get_left()->get_data() == apt3
           && right->get_left()->get_data() == apt05
           && right->get_right()->get_data() == apt_1;
}

bool test_avl_insert_LL_inner_left_node_imbalance() {
    AVL avl;

    Apartment apt_2 = create_apartment_and_insert(avl, {-2, -2});
    Apartment apt0 = create_apartment_and_insert(avl, {0, 0});
    Apartment apt_3 = create_apartment_and_insert(avl, {-3, -3});
    Apartment apt1 = create_apartment_and_insert(avl, {1, 1});
    Apartment apt_1 = create_apartment_and_insert(avl, {-1, -1});
    Apartment apt_4 = create_apartment_and_insert(avl, {-4, -4});
    Apartment apt2 = create_apartment_and_insert(avl, {2, 2});
    Apartment apt05 = create_apartment_and_insert(avl, {0.5, 0.5});
    Apartment apt3 = create_apartment_and_insert(avl, {3, 3});

    AVL::node *root = avl.get_root();
    AVL::node *left = root->get_left();
    AVL::node *right = root->get_right();

    return root->get_data() == apt_2
           && left->get_data() == apt1
           && right->get_data() == apt_3
           && left->get_left()->get_data() == apt2
           && left->get_right()->get_data() == apt0
           && right->get_right()->get_data() == apt_4
           && left->get_left()->get_left()->get_data() == apt3
           && left->get_right()->get_left()->get_data() == apt05
           && left->get_right()->get_right()->get_data() == apt_1;
}

bool test_avl_insert_LL_inner_right_node_imbalance() {
    AVL avl;

    Apartment apt2 = create_apartment_and_insert(avl, {2, 2});
    Apartment apt3 = create_apartment_and_insert(avl, {3, 3});
    Apartment apt_1 = create_apartment_and_insert(avl, {-1, -1});
    Apartment apt4 = create_apartment_and_insert(avl, {4, 4});
    Apartment apt0 = create_apartment_and_insert(avl, {0, 0});
    Apartment apt_2 = create_apartment_and_insert(avl, {-2, -2});
    Apartment apt1 = create_apartment_and_insert(avl, {1, 1});
    Apartment apt_05 = create_apartment_and_insert(avl, {-0.5, -0.5});
    Apartment apt15 = create_apartment_and_insert(avl, {1.5, 1.5});

    AVL::node *root = avl.get_root();
    AVL::node *left = root->get_left();
    AVL::node *right = root->get_right();

    return root->get_data() == apt2
           && left->get_data() == apt3
           && right->get_data() == apt0
           && left->get_left()->get_data() == apt4
           && right->get_left()->get_data() == apt1
           && right->get_left()->get_left()->get_data() == apt15
           && right->get_right()->get_data() == apt_1
           && right->get_right()->get_left()->get_data() == apt_05
           && right->get_right()->get_right()->get_data() == apt_2;
}


bool test_avl_insert_RR_root_imbalance() {
    AVL avl;

    Apartment apt0 = create_apartment_and_insert(avl, {0, 0});
    Apartment apt1 = create_apartment_and_insert(avl, {1, 1});
    Apartment apt_1 = create_apartment_and_insert(avl, {-1, -1});
    Apartment apt_05 = create_apartment_and_insert(avl, {-0.5, -0.5});
    Apartment apt_2 = create_apartment_and_insert(avl, {-2, -2});
    Apartment apt_3({-3, -3});

    // before rotation
    AVL::node *root = avl.get_root();
    AVL::node *left = root->get_left();
    AVL::node *right = root->get_right();

    bool result = root->get_data() == apt0
                  && left->get_data() == apt1
                  && right->get_data() == apt_1
                  && right->get_right()->get_data() == apt_2
                  && right->get_left()->get_data() == apt_05;

    avl.insert(apt_3);
    // after rotation

    root = avl.get_root();
    left = root->get_left();
    right = root->get_right();

    return result
           && root->get_data() == apt_1
           && left->get_data() == apt0
           && right->get_data() == apt_2
           && left->get_left()->get_data() == apt1
           && left->get_right()->get_data() == apt_05
           && right->get_right()->get_data() == apt_3;
}

bool test_avl_insert_RR_inner_right_node_imbalance() {
    AVL avl;

    Apartment apt6 = create_apartment_and_insert(avl, {6, 6});
    Apartment apt7 = create_apartment_and_insert(avl, {7, 7});
    Apartment apt4 = create_apartment_and_insert(avl, {4, 4});
    Apartment apt8 = create_apartment_and_insert(avl, {8, 8});
    Apartment apt5 = create_apartment_and_insert(avl, {5, 5});
    Apartment apt2 = create_apartment_and_insert(avl, {2, 2});
    Apartment apt3 = create_apartment_and_insert(avl, {3, 3});
    Apartment apt1 = create_apartment_and_insert(avl, {1, 1});
    Apartment apt0 = create_apartment_and_insert(avl, {0, 0});

    AVL::node *root = avl.get_root();
    AVL::node *left = root->get_left();
    AVL::node *right = root->get_right();

    return root->get_data() == apt6
           && left->get_data() == apt7
           && right->get_data() == apt2
           && left->get_left()->get_data() == apt8
           && right->get_left()->get_data() == apt4
           && right->get_right()->get_data() == apt1
           && right->get_left()->get_left()->get_data() == apt5
           && right->get_left()->get_right()->get_data() == apt3
           && right->get_right()->get_right()->get_data() == apt0;
}


bool test_avl_insert_RR_inner_left_node_imbalance() {
    AVL avl;

    Apartment apt2 = create_apartment_and_insert(avl, {2, 2});
    Apartment apt7 = create_apartment_and_insert(avl, {7, 7});
    Apartment apt1 = create_apartment_and_insert(avl, {1, 1});
    Apartment apt8 = create_apartment_and_insert(avl, {8, 8});
    Apartment apt5 = create_apartment_and_insert(avl, {5, 5});
    Apartment apt0 = create_apartment_and_insert(avl, {0, 0});
    Apartment apt6 = create_apartment_and_insert(avl, {6, 6});
    Apartment apt4 = create_apartment_and_insert(avl, {4, 4});
    Apartment apt3 = create_apartment_and_insert(avl, {3, 3});

    AVL::node *root = avl.get_root();
    AVL::node *left = root->get_left();
    AVL::node *right = root->get_right();

    return root->get_data() == apt2
           && left->get_data() == apt5
           && right->get_data() == apt1
           && left->get_left()->get_data() == apt7
           && left->get_right()->get_data() == apt4
           && right->get_right()->get_data() == apt0
           && left->get_left()->get_left()->get_data() == apt8
           && left->get_left()->get_right()->get_data() == apt6
           && left->get_right()->get_right()->get_data() == apt3;
}

bool test_avl_insert_LR_imbalance() {
    AVL avl;

    Apartment apt1 = create_apartment_and_insert(avl, {1, 1});
    Apartment apt3 = create_apartment_and_insert(avl, {3, 3});
    Apartment apt2 = create_apartment_and_insert(avl, {2, 2});

    return avl.get_root()->get_data() == apt2
           && avl.get_root()->get_left()->get_data() == apt3
           && avl.get_root()->get_right()->get_data() == apt1;
}

bool test_avl_insert_RL_imbalance() {
    AVL avl;

    Apartment apt3 = create_apartment_and_insert(avl, {3, 3});
    Apartment apt1 = create_apartment_and_insert(avl, {1, 1});
    Apartment apt2 = create_apartment_and_insert(avl, {2, 2});

    return avl.get_root()->get_data() == apt2
           && avl.get_root()->get_left()->get_data() == apt3
           && avl.get_root()->get_right()->get_data() == apt1;
}

bool test_avl_erase_no_children() {
    AVL avl;

    Apartment apt1 = create_apartment_and_insert(avl, {1, 1}); // middle
    Apartment apt0 = create_apartment_and_insert(avl, {0, 0}); // right
    Apartment apt2 = create_apartment_and_insert(avl, {2, 2}); // left

    avl.erase(apt0); // erase right
    bool result = avl.get_root()->get_data() == apt1
                  && avl.get_root()->get_left()->get_data() == apt2
                  && avl.get_root()->get_right() == nullptr;

    avl.erase(apt2); // erase left
    result = result && avl.get_root()->get_data() == apt1
             && avl.get_root()->get_left() == nullptr
             && avl.get_root()->get_right() == nullptr;

    avl.erase(apt1);
    result = result && avl.get_root() == nullptr;

    return result;
}

bool test_avl_erase_has_right_child_only() {
    AVL avl;

    Apartment apt2 = create_apartment_and_insert(avl, {2, 2}); // middle
    Apartment apt1 = create_apartment_and_insert(avl, {1, 1}); // right
    Apartment apt3 = create_apartment_and_insert(avl, {3, 3}); // left
    Apartment apt0 = create_apartment_and_insert(avl, {0, 0}); // right right

    avl.erase(apt1);

    return avl.get_root()->get_data() == apt2
           && avl.get_root()->get_left()->get_data() == apt3
           && avl.get_root()->get_right()
           && avl.get_root()->get_right()->get_data() == apt0;
}

bool test_avl_erase_has_left_child_only() {
    AVL avl;

    Apartment apt2 = create_apartment_and_insert(avl, {2, 2}); // middle
    Apartment apt1 = create_apartment_and_insert(avl, {1, 1}); // right
    Apartment apt3 = create_apartment_and_insert(avl, {3, 3}); // left
    Apartment apt4 = create_apartment_and_insert(avl, {4, 4}); // left left

    avl.erase(apt3);

    return avl.get_root()->get_data() == apt2
           && avl.get_root()->get_right()->get_data() == apt1
           && avl.get_root()->get_left()
           && avl.get_root()->get_left()->get_data() == apt4;
}

bool test_avl_erase_has_two_children() {
    AVL avl;

    Apartment apt4 = create_apartment_and_insert(avl, {4, 4});
    Apartment apt8 = create_apartment_and_insert(avl, {8, 8});
    Apartment apt2 = create_apartment_and_insert(avl, {2, 2});
    Apartment apt9 = create_apartment_and_insert(avl, {9, 9});
    Apartment apt6 = create_apartment_and_insert(avl, {6, 6});
    Apartment apt1 = create_apartment_and_insert(avl, {1, 1});
    Apartment apt3 = create_apartment_and_insert(avl, {3, 3});
    Apartment apt7 = create_apartment_and_insert(avl, {7, 7});

    avl.erase(apt8);

    AVL::node *root = avl.get_root();
    AVL::node *left = root->get_left();
    AVL::node *right = root->get_right();

    return root->get_data() == apt4
           && left->get_data() == apt7
           && right->get_data() == apt2
           && left->get_left()->get_data() == apt9
           && left->get_right()->get_data() == apt6
           && right->get_left()->get_data() == apt3
           && right->get_right()->get_data() == apt1;
}

bool test_avl_erase_multiple_imbalances() {
    // the example from DAST, the minuses are because as the
    // x and y's are getting larger they are closer to the feelbox and
    // therefore getting smaller in our tree
    AVL avl;

    Apartment apt13 = create_apartment_and_insert(avl, {-13, -13});
    Apartment apt8 = create_apartment_and_insert(avl, {-8, -8});
    Apartment apt18 = create_apartment_and_insert(avl, {-18, -18});
    Apartment apt5 = create_apartment_and_insert(avl, {-5, -5});
    Apartment apt11 = create_apartment_and_insert(avl, {-11, -11});
    Apartment apt16 = create_apartment_and_insert(avl, {-16, -16});
    Apartment apt20 = create_apartment_and_insert(avl, {-20, -20});
    Apartment apt3 = create_apartment_and_insert(avl, {-3, -3});
    Apartment apt7 = create_apartment_and_insert(avl, {-7, -7});
    Apartment apt10 = create_apartment_and_insert(avl, {-10, -10});
    Apartment apt12 = create_apartment_and_insert(avl, {-12, -12});
    Apartment apt15 = create_apartment_and_insert(avl, {-15, -15});
    Apartment apt17 = create_apartment_and_insert(avl, {-17, -17});
    Apartment apt19 = create_apartment_and_insert(avl, {-19, -19});
    Apartment apt2 = create_apartment_and_insert(avl, {-2, -2});
    Apartment apt4 = create_apartment_and_insert(avl, {-4, -4});
    Apartment apt6 = create_apartment_and_insert(avl, {-6, -6});
    Apartment apt9 = create_apartment_and_insert(avl, {-9, -9});
    Apartment apt14 = create_apartment_and_insert(avl, {-14, -14});
    Apartment apt1 = create_apartment_and_insert(avl, {-1, -1});

    avl.erase(apt19);

    AVL::node *left_left = avl.get_root()->get_left()->get_left();
    AVL::node *left_right = avl.get_root()->get_left()->get_right();
    AVL::node *right_right = avl.get_root()->get_right()->get_right();
    AVL::node *right_left = avl.get_root()->get_right()->get_left();


    return avl.get_root()->get_data() == apt8
           && avl.get_root()->get_left()->get_data() == apt5
           && avl.get_root()->get_right()->get_data() == apt13
           && left_left->get_data() == apt3
           && left_right->get_data() == apt7
           && right_left->get_data() == apt11
           && right_right->get_data() == apt16
           && left_left->get_left()->get_data() == apt2
           && left_left->get_right()->get_data() == apt4
           && left_right->get_left()->get_data() == apt6
           && right_left->get_left()->get_data() == apt10
           && right_left->get_right()->get_data() == apt12
           && right_right->get_left()->get_data() == apt15
           && right_right->get_right()->get_data() == apt18
           && left_left->get_left()->get_left()->get_data() == apt1
           && right_left->get_left()->get_left()->get_data() == apt9
           && right_right->get_left()->get_left()->get_data() == apt14
           && right_right->get_right()->get_left()->get_data() == apt17
           && right_right->get_right()->get_right()->get_data() == apt20;
}

bool test_avl_erase_not_in_tree() {
    AVL avl;

    Apartment apt1({1, 1});
    Apartment apt2({2, 2});

    avl.erase(apt1);
    bool result = avl.get_root() == nullptr;

    avl.insert(apt1);
    avl.erase(apt2);
    result = result && avl.get_root() && avl.get_root()->get_data() == apt1;

    avl.insert(apt2);
    avl.erase(apt2);
    avl.erase(apt2);
    result = result && avl.get_root() && avl.get_root()->get_data() == apt1;

    avl.erase(apt1);
    result = result && avl.get_root() == nullptr;

    avl.erase(apt1);
    result = result && avl.get_root() == nullptr;

    return result;
}

bool test_avl_iterator_range_based() {
    AVL avl;

    Apartment apt5 = create_apartment_and_insert(avl, {5, 5});
    Apartment apt7 = create_apartment_and_insert(avl, {7, 7});
    Apartment apt3 = create_apartment_and_insert(avl, {3, 3});
    Apartment apt8 = create_apartment_and_insert(avl, {8, 8});
    Apartment apt6 = create_apartment_and_insert(avl, {6, 6});
    Apartment apt4 = create_apartment_and_insert(avl, {4, 4});
    Apartment apt2 = create_apartment_and_insert(avl, {2, 2});

    std::vector<Apartment> expected{
            apt5,
            apt7,
            apt8,
            apt6,
            apt3,
            apt4,
            apt2
    };

    int i = 0;
    for (auto apartment: avl) {
        if (!(apartment == expected[i])) {
            return false;
        }
        i++;
    }

    return true;
}

bool test_avl_iterator_postfix() {
    AVL avl;

    Apartment apt5 = create_apartment_and_insert(avl, {5, 5});
    Apartment apt7 = create_apartment_and_insert(avl, {7, 7});
    Apartment apt3 = create_apartment_and_insert(avl, {3, 3});
    Apartment apt8 = create_apartment_and_insert(avl, {8, 8});
    Apartment apt6 = create_apartment_and_insert(avl, {6, 6});
    Apartment apt4 = create_apartment_and_insert(avl, {4, 4});
    Apartment apt2 = create_apartment_and_insert(avl, {2, 2});

    std::vector<Apartment> expected{
            apt5,
            apt7,
            apt8,
            apt6,
            apt3,
            apt4,
            apt2
    };

    auto it = avl.begin();
    for (auto &apt: expected) {
        if (!(*(it++) == apt)) {
            return false;
        }
    }

    return true;
}

bool test_avl_iterator_prefix() {
    AVL avl;

    create_apartment_and_insert(avl, {5, 5});
    Apartment apt7 = create_apartment_and_insert(avl, {7, 7});
    Apartment apt3 = create_apartment_and_insert(avl, {3, 3});
    Apartment apt8 = create_apartment_and_insert(avl, {8, 8});
    Apartment apt6 = create_apartment_and_insert(avl, {6, 6});
    Apartment apt4 = create_apartment_and_insert(avl, {4, 4});
    Apartment apt2 = create_apartment_and_insert(avl, {2, 2});

    std::vector<Apartment> expected{
//            apt5, omitted on purpose, we skip the first one
            apt7,
            apt8,
            apt6,
            apt3,
            apt4,
            apt2
    };

    auto it = avl.begin();
    for (auto &apt: expected) {
        if (!(*(++it) == apt)) {
            return false;
        }
    }

    return true;
}


bool test_avl_const_iterator_range_based() {
    AVL avl;

    Apartment apt5 = create_apartment_and_insert(avl, {5, 5});
    Apartment apt7 = create_apartment_and_insert(avl, {7, 7});
    Apartment apt3 = create_apartment_and_insert(avl, {3, 3});
    Apartment apt8 = create_apartment_and_insert(avl, {8, 8});
    Apartment apt6 = create_apartment_and_insert(avl, {6, 6});
    Apartment apt4 = create_apartment_and_insert(avl, {4, 4});
    Apartment apt2 = create_apartment_and_insert(avl, {2, 2});

    const AVL const_avl = avl;

    std::vector<Apartment> expected{
            apt5,
            apt7,
            apt8,
            apt6,
            apt3,
            apt4,
            apt2
    };

    int i = 0;
    for (auto apartment: const_avl) {
        if (!(apartment == expected[i])) {
            return false;
        }
        i++;
    }

    return true;
}

bool test_avl_const_iterator_postfix() {
    AVL avl;

    Apartment apt5 = create_apartment_and_insert(avl, {5, 5});
    Apartment apt7 = create_apartment_and_insert(avl, {7, 7});
    Apartment apt3 = create_apartment_and_insert(avl, {3, 3});
    Apartment apt8 = create_apartment_and_insert(avl, {8, 8});
    Apartment apt6 = create_apartment_and_insert(avl, {6, 6});
    Apartment apt4 = create_apartment_and_insert(avl, {4, 4});
    Apartment apt2 = create_apartment_and_insert(avl, {2, 2});

    const AVL const_avl = avl;

    std::vector<Apartment> expected{
            apt5,
            apt7,
            apt8,
            apt6,
            apt3,
            apt4,
            apt2
    };

    auto it = const_avl.begin();
    for (auto &apt: expected) {
        if (!(*(it++) == apt)) {
            return false;
        }
    }

    return true;
}

bool test_avl_const_iterator_prefix() {
    AVL avl;

    create_apartment_and_insert(avl, {5, 5});
    Apartment apt7 = create_apartment_and_insert(avl, {7, 7});
    Apartment apt3 = create_apartment_and_insert(avl, {3, 3});
    Apartment apt8 = create_apartment_and_insert(avl, {8, 8});
    Apartment apt6 = create_apartment_and_insert(avl, {6, 6});
    Apartment apt4 = create_apartment_and_insert(avl, {4, 4});
    Apartment apt2 = create_apartment_and_insert(avl, {2, 2});

    const AVL const_avl = avl;

    std::vector<Apartment> expected{
//            apt5, omitted on purpose, we skip the first one
            apt7,
            apt8,
            apt6,
            apt3,
            apt4,
            apt2
    };

    auto it = const_avl.begin();
    for (auto &apt: expected) {
        if (!(*(++it) == apt)) {
            return false;
        }
    }

    return true;
}

bool test_avl_find() {
    std::vector<double_pair> coordinates{
            {5, 5},
            {7, 7},
            {3, 3},
            {8, 8},
            {6, 6},
            {4, 4},
            {2, 2},
    };

    std::vector<Apartment> sorted_apartments{
            Apartment({5, 5}),
            Apartment({7, 7}),
            Apartment({8, 8}),
            Apartment({6, 6}),
            Apartment({3, 3}),
            Apartment({4, 4}),
            Apartment({2, 2}),
    };

    AVL avl(coordinates);
    for (auto coordinate: coordinates) {
        const Apartment apt(coordinate);
        auto it = avl.find(apt);
        if (!(*it == apt)) {
            return false;
        }

        auto sorted_iter = std::find(sorted_apartments.begin(),
                                     sorted_apartments.end(), apt);
        sorted_iter++;

        if (sorted_iter != sorted_apartments.end()) {
            if (!(*(++it) == *sorted_iter)) {
                return false;
            }
        } else {
            if (++it != avl.end()) {
                return false;
            }
        }
    }

    return true;
}

bool test_avl_find_not_in_tree() {
    AVL avl({{5, 5},
             {7, 7},
             {3, 3},
             {8, 8},
             {6, 6},
             {4, 4},
             {2, 2},});

    const Apartment apt1 = Apartment({-1, -1});
    const Apartment apt2 = Apartment({7, 7});

    bool result = avl.find(apt1) == avl.end();
    avl.erase(apt2);

    return result && avl.find(apt2) == avl.end();
}


bool test_avl_const_find() {
    std::vector<double_pair> coordinates{
            {5, 5},
            {7, 7},
            {3, 3},
            {8, 8},
            {6, 6},
            {4, 4},
            {2, 2},
    };

    std::vector<Apartment> sorted_apartments{
            Apartment({5, 5}),
            Apartment({7, 7}),
            Apartment({8, 8}),
            Apartment({6, 6}),
            Apartment({3, 3}),
            Apartment({4, 4}),
            Apartment({2, 2}),
    };

    const AVL avl(coordinates);
    for (auto coordinate: coordinates) {
        const Apartment apt(coordinate);
        auto it = avl.find(apt);
        if (!(*it == apt)) {
            return false;
        }

        auto sorted_iter = std::find(sorted_apartments.begin(),
                                     sorted_apartments.end(), apt);
        sorted_iter++;

        if (sorted_iter != sorted_apartments.end()) {
            if (!(*(++it) == *sorted_iter)) {
                return false;
            }
        } else {
            if (++it != avl.end()) {
                return false;
            }
        }
    }

    return true;
}

bool test_avl_const_find_not_in_tree() {
    const AVL avl({{5, 5},
                   {7, 7},
                   {3, 3},
                   {8, 8},
                   {6, 6},
                   {4, 4},
                   {2, 2}});

    const Apartment apt1 = Apartment({-1, -1});
    return avl.find(apt1) == avl.end();
}

bool test_find_avl() {
    AVL avl;

    Apartment apt5 = create_apartment_and_insert(avl, {5, 5});
    Apartment apt7 = create_apartment_and_insert(avl, {7, 7});
    Apartment apt3 = create_apartment_and_insert(avl, {3, 3});
    Apartment apt8 = create_apartment_and_insert(avl, {8, 8});
    create_apartment_and_insert(avl, {6, 6});
    create_apartment_and_insert(avl, {4, 4});
    create_apartment_and_insert(avl, {2, 2});
    Apartment apt9({2, 2}); // not in the tree

    std::vector<Apartment> sorted_apartments{
            Apartment({5, 5}),
            Apartment({7, 7}),
            Apartment({8, 8}),
            Apartment({6, 6}),
            Apartment({3, 3}),
            Apartment({4, 4}),
            Apartment({2, 2}),
    };

    auto it7 = find(avl.begin(), avl.end(), apt7);
    bool result = *it7 == apt7;

    auto it3 = find(it7, avl.end(), apt3);
    result = result && *it3 == apt3;

    auto it8 = find(it3, avl.end(), apt8);
    result = result && it8 == avl.end();

    auto it5 = find(avl.begin(), it7, apt5);
    result = result && *it5 == apt5;

    auto it9 = find(avl.begin(), it7, apt9);
    result = result && it9 == it7;

    return result;
}


int main() {
    std::vector<TestInfo> apartment_tests = {
            TEST_CASE(test_apartment_sanity),
            TEST_CASE(test_apartment_operator_lower_than),
            TEST_CASE(test_apartment_operator_greater_than),
            TEST_CASE(test_apartment_operator_equal_given_equal_apartments),
            TEST_CASE(test_apartment_operator_equal_given_unequal_apartments),
    };

    std::vector<TestInfo> stack_tests = {
            TEST_CASE(test_stack_default_ctor),
            TEST_CASE(test_stack_vector_ctor),
            TEST_CASE(test_stack_operations),
            TEST_CASE(test_stack_iterator),
            TEST_CASE(test_stack_const_iterator),
    };

    std::vector<TestInfo> avl_tests = {
            TEST_CASE(test_avl_vector_ctor),
            TEST_CASE(test_avl_simple_insert),
            TEST_CASE(test_avl_insert_LL_root_imbalance),
            TEST_CASE(test_avl_insert_LL_inner_left_node_imbalance),
            TEST_CASE(test_avl_insert_LL_inner_right_node_imbalance),
            TEST_CASE(test_avl_insert_RR_root_imbalance),
            TEST_CASE(test_avl_insert_RR_inner_right_node_imbalance),
            TEST_CASE(test_avl_insert_RR_inner_left_node_imbalance),
            TEST_CASE(test_avl_insert_LR_imbalance),
            TEST_CASE(test_avl_insert_RL_imbalance),
            TEST_CASE(test_avl_erase_no_children),
            TEST_CASE(test_avl_erase_has_right_child_only),
            TEST_CASE(test_avl_erase_has_left_child_only),
            TEST_CASE(test_avl_erase_has_two_children),
            TEST_CASE(test_avl_erase_multiple_imbalances),
            TEST_CASE(test_avl_erase_not_in_tree),
            TEST_CASE(test_avl_iterator_range_based),
            TEST_CASE(test_avl_iterator_postfix),
            TEST_CASE(test_avl_iterator_prefix),
            TEST_CASE(test_avl_const_iterator_range_based),
            TEST_CASE(test_avl_const_iterator_postfix),
            TEST_CASE(test_avl_const_iterator_prefix),
            TEST_CASE(test_avl_find),
            TEST_CASE(test_avl_const_find),
            TEST_CASE(test_avl_find_not_in_tree),
            TEST_CASE(test_avl_const_find_not_in_tree),
    };

    std::vector<TestInfo> find_tests = {
            TEST_CASE(test_find_avl),
    };


    std::vector<TestSuite> test_suites{
            {"Apartment", apartment_tests},
            {"Stack",     stack_tests},
            {"AVL",       avl_tests},
            {"Find",      find_tests},
    };

    run_test_suites(test_suites);
}
