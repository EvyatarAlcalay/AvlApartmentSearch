//
// Created by rotem on 07/10/2021.
//

#ifndef _AVL_H_
#define _AVL_H_
#include <vector>
#include "Apartment.h"
#include <stack>
#define AFTER_INSERTION 1
#define AFTER_DELETION 2
#define AFTER_ROTATION 3

class AVL {
 public:
  /**
   * To manage the tree nodes, we use a nested struct. This struct contains
   * the apartment corresponding to the node, the left son and the right son
   * of the node, both of them node type themselves.
   */
  struct node {
      /**
       * Constructor - It can be expanded
       * @param data the corresponding apartment object
       * @param left child
       * @param right child
       */
      node (Apartment data, node *left, node *right,node *parent,int
      left_high, int right_high)
          : data_ (data), left_ (left), right_ (right),  parent_(parent),
          left_high_(left_high), right_high_(right_high)
      {}

      /**
       *
       * @return the left child of this node
       */
      node *get_left () const
      {
        return left_;
      }
      /**
       *
       * @return the right child of this node
       */
      node *get_right () const
      {
        return right_;
      }
      /**
     *
     * @return the const reference apartment of this node
     */
      const Apartment &get_data () const
      {
        return data_;
      }
      Apartment data_;
      node *left_, *right_;
      node *parent_;
      int left_high_;
      int right_high_;
  };

  /**
   * Constructor. Constructs an empty AVL tree
   */
  AVL ();
  /**
   * Copy constructor
   * @param other the AVL we will copy to this
   */
  AVL (const AVL &other);
  /**
   * A constructor that receives a vector of a pairs. Each such pair is an
   * apartment that will inserted to the tree. Insert can be used to insert
   * the apartments a vector of a pairs
   * @param coordinates the pairs we will initizlize the AVL with them
   */
  AVL (std::vector<std::pair<double, double>> coordinates);
  /**
   *
   * @param rhs the AVL tree i will
   * @return AVL the /// AVL
   */
  AVL& operator=(const AVL &other);
  /**
   * the destructor
   */
  ~AVL();
  /**
   *
   * @return the root node of this tree
   */
  node *get_root () const{
    return root_;
  }
  /**
   * The function inserts the new apartment into the tree so that it maintains
   * the legality of the tree.
   * @param apartment
   */
  void insert (const Apartment &apartment);
  /**
   * The function deletes the apartment from the tree (if it is in that tree)
   * so that it maintains the legality of the tree.
   * @param apartment
   */
  void erase (const Apartment &apartment);
  /**
   * The class should support forward iterator. Don't forget to define the
   * iterator traits and all the actions required to support a forward
   * iterator
   * The iterator will move in preorder.
   */
  class ConstIterator{
      node *cur;
      std::stack<node*> my_stack;
  public:
      /* iterator traits */
      typedef const Apartment value_type;
      typedef const Apartment &reference;
      typedef const Apartment *pointer;
      typedef std::forward_iterator_tag iterator_category;
      typedef std::ptrdiff_t difference_type;
      ConstIterator(node* cur);
      const reference operator* () const;
      pointer operator-> () const;
      ConstIterator &operator++();
      ConstIterator operator++(int);
      bool operator== (const ConstIterator &rhs) const;
      bool operator!= (const ConstIterator &rhs) const;
  };
  class Iterator{
      node *cur;
      std::stack<node*> my_stack;
      friend class ConstIterator;
  public:
      /* iterator traits */
      typedef Apartment value_type;
      typedef Apartment &reference;
      typedef Apartment *pointer;
      typedef std::forward_iterator_tag iterator_category;
      typedef std::ptrdiff_t difference_type;
      Iterator(node *cur);
      reference operator*();
      pointer operator-> ();
      Iterator &operator++();
      Iterator operator ++(int);
      bool operator== (const Iterator &rhs) const;
      bool operator!= (const Iterator &rhs) const;
  };
  using iterator = Iterator; // same as typedef Iterator iterator;
  using const_iterator = ConstIterator; //same as typedef ConstIterator
  // const_iterator;
  iterator begin ();
  const_iterator begin () const;
  const_iterator cbegin () const;
  iterator end ();
  const_iterator end () const;
  const_iterator cend () const;
  /**
   * The function returns an iterator to the item that corresponds to the item
   * we were looking for. If there is no such member, returns end ().
   * @param data apartment to search
   * @return iterator to the item that corresponds to the item
   * we were looking for. If there is no such member, returns end ().
   */
  iterator find (const Apartment &data);
  /**
   * The function returns an iterator to the item that corresponds to the item
   * we were looking for. If there is no such member, returns end ().
   * @param data apartment to search
   * @return iterator to the item that corresponds to the item
   * we were looking for. If there is no such member, returns end ().
   */
  const_iterator find (const Apartment &data) const;
  /**
   * Insertion operator, prints the apartment in the tree in preorder
   * traversal. Each apartmnet will be printed in the format: (x,y)\n
   * @param os reference to std::ostream
   * @param avl tree
   * @return os reference to std::ostream
   */
  friend std::ostream &operator<< (std::ostream &os, const AVL &avl);

private:
  node *root_;

  /**
   * a function which do a right rotation on the AVL
   * @param node the node we will do it the rotation
   */
  static void right_rotation(node* node);
  /**
   * a function which do a left rotation on the AVL
   * @param node the node we will do it the rotation
   */
  static void left_rotation(node *node);
  /**
   * after every operation we did, we will update the high of the AVL to be
   * correct
   * @param node the node we will start from it to update the high (we will
   * go up)
   * @param type
   */
  static void update_highs(node *node, int type);
  /**
   * a function which define when to do rotation
   * @param node the node from it there is a chance for rotation
   */
  void do_rotation(node *node);
  /**
   * define the rotations in case the left high > right high+1
   * @param node the node we will do on it the rotation
   */
  static void balance_factor_two(node *node);
  /**
   * define the rotations in case the left high < right high+1
   * @param node the node we will do on it the rotation
   */
  static void balance_factor_minus_two(node *node);
  /**
   * the purpose of this function is to define when in have to do rotation
   * (in case that the difference between left and right high is more than 1)
   * @param node the node we are searching for difference between his highs
   * @return the difference between the left high and right high of node
   */
  static int define_balance_factor(node *node);
  /**
   * the purpose of this function is to find the successor for a case i want
   * to erase a node with 2 children.
   * @param node the node we are looking for his successor
   * @return the successor
   */
  static node* find_successor(node *node);
  /**
   * a recursive function which get a root of AVL and destroy it
   * @param cur the root od the AVL
   */
  void delete_avl(node *cur);
  /**
   * this function is creating an AVL tree recursively
   * @param to_copy the new node we will want to copy
   * @param parent the parent of the node after its copy
   * @return the node we will copy. finally, we get an AVL tree
   */
  AVL::node* node_to_copy(const node* to_copy, node* parent);
  /**
   * this function is creating an AVL tree
   * @param other AVL tree we want to copy
   */
  void create_avl(const AVL &other);
  /**
   * a helper function to delete a node with left child
   * @param cur a node with a left child we want to delete
   */
  void delete_node_with_just_left_child(node *cur);
  /**
   * a helper function to delete a node with right child
   * @param cur a node with a right child we want to delete
   */
  void delete_node_with_just_right_child(node *cur);
};

#endif //_AVL_H_
