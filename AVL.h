#ifndef _AVL_H_
#define _AVL_H_

#include <vector>
#include "Apartment.h"
#include <iostream>

class AVL {
public:
    /**
     * To manage the tree nodes, we use a nested struct. This struct
     * contains the apartment corresponding to the node, the left son and
     * the right son of the node, both of them node type themselves.
     */
    struct node {
        /**
         * Constructor for node instance.
         * @param data the corresponding apartment object
         * @param left child
         * @param right child
         * @param parent pointer to parent node
         * @param bf balance factor of current node
         * @param height height of current node
         */
        node(Apartment data, node *left, node *right, node *parent,
             int bf, int height)
                : data_(data), left_(left), right_(right), parent_(parent),
                 bf_(bf), height_(height) {}

        /**
         *
         * @return the left child of this node
         */
        node *get_left() const {
            return left_;
        }

        /**
         *
         * @return the right child of this node
         */
        node *get_right() const {
            return right_;
        }

        /**
        *
        * @return the parent of this node
        */
        node *get_parent() const {
            return parent_;
        }

        /**
       *
       * @return the const reference apartment of this node
       */
        const Apartment &get_data() const {
            return data_;
        }

        /**
        *
        * @return the balance factor of this node
        */
        int get_bf() const {
            return bf_;
        }

        /**
        *
        * @return the height of this node
        */
        int get_height() const {
            return height_;
        }

        Apartment data_;
        node *left_, *right_, *parent_;
        int bf_;
        int height_;
    };
    /**
     * The class should support forward Iterator. Don't forget to define the
     * Iterator traits and all the actions required to support a forward
     * Iterator.
     * The Iterator will move in preorder.
     */
    class ConstIterator;
    class Iterator;
    class Iterator {
        node *cur;
        friend class ConstIterator;

    public:
        /**
       * Iterator traits:
       */
        typedef Apartment value_type;
        typedef Apartment &reference;
        typedef Apartment *pointer;
        typedef std::forward_iterator_tag iterator_category;
        typedef std::ptrdiff_t difference_type;

       /**
       * Constructor for iterator.
       */
        Iterator(node *cur) : cur(cur) {}

        /**
       * Pointer for data of the node (apartment).
       * @return Reference to data (apartment) of the current node.
       */
        pointer operator->() {
            return &cur->data_;
        }
        /**
       * Dereference for data of the node (apartment).
       * @return The actual data (apartment) of the current node.
       */
        reference operator*() {
            return cur->data_;
        }

        /**
      * Operator++ postfix for AVL iterator - advances the current node
      * to the next node in preorder traversal of the AVL Tree
      * and returns its data.
      * @return The data (Apartment) of the next node.
      */
        Iterator &operator++() {
            cur = preorder_successor(cur);
            return *this;
        }

        /**
      * Operator++ prefix for AVL iterator - advances the current node
      * to the next node in preorder traversal of the AVL Tree and
      * returns the previous node's data.
      * @return The data (Apartment) of the previous node.
      */
        Iterator operator++(int) {
            Iterator it = *this;
            cur = preorder_successor(cur);
            return it;
        }

        /**
      * Operator== for AVL iterator - checks if 2 iterators are equal.
      * @return true if this iterator and other iterator are equal to each
      * other ,false otherwise.
      */
        bool operator==(const Iterator &rhs) const {
            return cur == rhs.cur;
        }

        /**
     * Operator!= for AVL iterator - checks if 2 iterators are unequal.
     * @return true if this iterator and other iterator are unequal to each
     * other ,false otherwise.
     */
        bool operator!=(const Iterator &rhs) const {
            return !(rhs == *this);
        }
    };

    class ConstIterator {
        node *cur;
    public:
        /**
       * ConstIterator traits:
       */
        typedef const Apartment value_type;
        typedef const Apartment &reference;
        typedef const Apartment *pointer;
        typedef std::forward_iterator_tag iterator_category;
        typedef std::ptrdiff_t difference_type;

        /**
       * Constructor for ConstIterator.
       */
        ConstIterator(node *cur) : cur(cur) {}

        ConstIterator(const Iterator &it) : cur(it.cur) {}

        /**
       * Pointer for data of the node (apartment).
       * @return Reference to data (apartment) of the current node.
       */
        const Apartment *operator->() const
        {
            return &cur->data_;
        }

        /**
       * Dereference for data of the node (apartment).
       * @return The actual data (apartment) of the current node.
       */
        Apartment operator*() const {
            return cur->data_;
        }

        /**
     * Operator++ postfix for AVL ConstIterator - advances the current node
     * to the next node in preorder traversal of the AVL Tree
     * and returns its data.
     * @return The data (Apartment) of the next node.
     */
        ConstIterator &operator++() {
            cur = preorder_successor(cur);
            return *this;
        }

        /**
     * Operator++ prefix for AVL ConstIterator - advances the current node
     * to the next node in preorder traversal of the AVL Tree and
     * returns the previous node's data.
     * @return The data (Apartment) of the previous node.
     */
        ConstIterator operator++(int) {
            ConstIterator it = *this;
            cur = preorder_successor(cur);
            return it;
        }

        /**
     * Operator== for AVL ConstIterator - checks if 2 ConstIterators are equal.
     * @return true if this ConstIterator and other ConstIterator
     * are equal to each other ,false otherwise.
     */
        bool operator==(const ConstIterator &rhs) const {
            return cur == rhs.cur;
        }

        /**
     * Operator!= for AVL ConstIterator- checks if 2 ConstIterator are unequal.
     * @return true if this ConstIterator and other ConstIterator
     * are unequal to each other ,false otherwise.
     */
        bool operator!=(const ConstIterator &rhs) const {
            return !(rhs == *this);
        }
    };

    /**
       * typedefs - aliases for Iterator and ConstIterator:
       */
    using iterator = Iterator; // same as typedef Iterator Iterator;
    using const_iterator = ConstIterator;

    /**
     * Constructor. Constructs an empty AVL tree
     */
    AVL();

    /**
     * Copy constructor
     * @param other
     */
    AVL(const AVL &other);

    /**
     * A constructor that receives a vector of pairs. Each such pair is an
     * apartment that will inserted to the tree.
     * Insert can be used to insert the apartments as vector of pairs.
     * @param coordinates
     */
    AVL(std::vector<std::pair<double, double>> coordinates);

    /**
    * Destructor for AVL instance.
    * @param coordinates
    */
    ~AVL();

    /**
     * Assignment operator for AVL instance.
     * Assigns other AVL to this AVL Tree.
     * @param other_avl The other AVL Tree instance.
     */
    AVL &operator=(const AVL &other_avl);

    /**
     *
     * @return the root node of this tree
     */
    node *get_root() const {
        return root_;
    }

    /**
     * The function inserts the new apartment into the
     * tree so that it maintains the legality of the tree.
     * @param apartment
     */
    void insert(const Apartment &apartment);

    /**
     * The function deletes the apartment from the tree
     * (if it is in that tree) so that it maintains
     * the legality of the tree.
     * @param apartment
     */
    void erase(const Apartment &apartment);

    /**
     * All definitions for begin() and end() of the Stack iterator
     * and const_iterator kinds of iterators.
     */
    iterator begin ();

    const_iterator begin () const;

    const_iterator cbegin() const;

    iterator end();

    const_iterator end() const;

    const_iterator cend() const;

    /**
     * The function returns an Iterator to the item that corresponds
     * to the item
     * we were looking for. If there is no such member, returns end ().
     * @param data apartment to search
     * @return Iterator to the item that corresponds to the item
     * we were looking for. If there is no such member, returns end ().
     */
    iterator find(const Apartment &data);

    /**
     * The function returns an Iterator to the item that corresponds
     * to the item
     * we were looking for. If there is no such member, returns end ().
     * @param data apartment to search
     * @return Iterator to the item that corresponds to the item
     * we were looking for. If there is no such member, returns end ().
     */
    const_iterator find(const Apartment &data) const;

    /**
     * Insertion operator, prints the apartment in the
     * tree in preorder traversal.
     * Each apartmnet will be printed in the format: (x,y)\n
     * @param os reference to std::ostream
     * @param avl tree
     * @return os reference to std::ostream
     */
    friend std::ostream &operator<<(std::ostream &os, const AVL &avl);

private:
    node *root_;

    /**
     * Returns the preorder successor of the current node in the AVL.
     * Helper function for iterator.
     * @param cur current node in preorder traversal.
     * @return preorder successor of the cur node in the AVL.
     */
    static node *preorder_successor(node *cur);

    /**
     * Helper function for insert function - recursively inserts the node with
     * given data and balances it. Also corrects the fields after insertion
     * and balance of the AVL.
     * @param cur Current node in preorder traversal.
     * @param apartment Apartment data to insert for current node.
     * @param parent Pointer to the parent of the current node.
     */
    void insert_helper(node *& cur, const Apartment &apartment, node* parent);

    /**
     * Left_Left rotation of the unbalanced node.
     * @param cur Current node that its balance factor was violated e.g. equals
     * 2 or -2.
     */
    static node *ll_rotation(node *cur);

    /**
     * Right-Right rotation of the unbalanced node.
     * @param cur Current node that its balance factor was violated e.g. equals
     * 2 or -2.
     */
    static node *rr_rotation(node *cur);

    /**
     * Right-Left rotation of the unbalanced nodes in the AVL.
     * @param cur Current node that its balance factor was violated e.g. equals
     * 2 or -2.
     */
    static node *rl_rotation(node *cur);

    /**
    * Left-Right rotation of the unbalanced nodes in the AVL.
    * @param cur Current node that its balance factor was violated e.g. equals
    * 2 or -2.
    */
    static node *lr_rotation(node *cur);

    /**
    * Finds the minimum value (Apartment) in the AVL Tree.
    * @param cur The current node to start searching minimum from.
    */
    static node* tree_minimum(node* cur);

    /**
    * Recursive helper function to fix heights, parents and balance factor
    * of the given subtree.
    * @param cur The current node to start fixing from.
    * @param parent The current node's parent - updated with the recursion.
    */
    void fix_nodes_fields_downwards(node* cur, node* parent);


    /**
    * Recursive helper function to fix heights, parents and balance factor
    * of ancestors (parents and grand parents etc) of current node.
    * @param cur The current node to start fixing from.
    * @param parent The current node's parent - updated with the recursion.
    */
    void fix_nodes_fields_upwards(node* cur, node* parent);
    /**
    * Calculates the height of a given node.
    * @param cur The current node to calculate its height.
    */
    static int calculate_height(node*& cur);

    /**
    * Calculates the balance factor (bf) of a given node.
    * @param cur The current node to calculate its bf.
    */
    static int calculate_bf(node*& cur);

    /**
    * Helper function to copy new dynamically allocated nodes - copies all
    * nodes data,bf,height,pointers and returns the copied root with all
    * pointer to nodes and the nodes' data.
    * @param cur The current node.
    * @param parent The current node's parent - updated with the recursion.
    */
    node* copy_helper(node* cur, node* parent);

    /**
    * Helper function for destructor - delete new dynamically allocated nodes
    * with recursion - first delete the leaves, then the father, grandfather
    * etc and all the way to the root.
    * @param cur The current node.
    */
    void delete_helper(node * cur);

    /**
    * Transplants the node to delete with a replaced node that is suppose to
    * be instead of this node - changes the pointers of the substitute  node so
    * the substitute node will be place insted of the deleted node.
    * @param cur The current node.
    * @param replace_cur the substitute node that will be exchanged with the
    * erased node.
    */
    void transplant(node* cur, node *replace_cur);

    /**
    * Helper function to for erase function - erases the node with the given
    * data and balances it. Also corrects the fields after erasing the node
    * and balances the AVL all the way to the root.
    * @param cur The current node.
    */
    void erase_helper(node *cur);

    /**
    * Helper function for erase function and find function - Finds the node
    * that we want to find in the tree
    * @param apartment The apartment (data) of the node we would like to find.
    * @param search_node The pointer to the node to find.
    * @return The node that we want to find in the AVL tree.
    */
    node * tree_search(const Apartment &apartment, node *search_node) const;

    /**
    * Helper function for erase/insert to balance the AVL Tree (or subtree)
    * if its balance factor was violated.
    * @param cur The current node to check if its balance factor was violated.
    */
    static node* balance_tree(node *cur);


    /**
    * Helper function for erase function - finds the unbalanced node after
    * a node was erased (with bf 2 or -2) - climbs up all the
    * way up to the root - we will need to preform  at most O(log(h))
    * balances after erasing a node.
    * @param start_node The current node to check if its balance factor
     * was violated.
    */
    node* unbalanced_node(node * start_node);

    /**
    * Recursive helper function to fix heights, parents and balance factor
    * of ancestors (parents and grand parents etc) of current node and also
    * all the descendants (subtree of cur).
    * @param cur The current node to start fixing from.
    */
    void fix_all_affected_nodes(node *cur);
};

#endif //_AVL_H_
