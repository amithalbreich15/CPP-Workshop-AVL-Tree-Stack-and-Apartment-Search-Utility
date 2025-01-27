
#include "AVL.h"

using std::cout;
using std::endl;
using std::cin;


AVL::AVL() : root_()
{

}

AVL::AVL(const AVL &other)
{
    root_ = copy_helper(other.root_, nullptr);
}

AVL::~AVL()
{
    delete_helper(root_);
}

AVL &AVL::operator=(const AVL &other_avl)
        {
    if (this == &other_avl)
    {
        return *this;
    }
    delete_helper(root_);
    root_ = copy_helper(other_avl.root_, nullptr);
    return *this;
}


AVL::AVL(std::vector<std::pair<double, double>> coordinates) : root_(nullptr)
{
    for (size_t i = 0; i < coordinates.size(); ++i) {
        insert(coordinates.at(i));
    }
}

void AVL::insert(const Apartment &apartment)
{
    insert_helper(root_, apartment, nullptr);
}

void AVL::erase(const Apartment &apartment)
{
    node * node_to_erase = tree_search(apartment, root_);
    erase_helper(node_to_erase);
    delete node_to_erase;
}

AVL::iterator AVL::begin()
{
    return {root_};
}

AVL::const_iterator AVL::begin() const
{
    return {root_};
}

AVL::const_iterator AVL::cbegin() const
{
    return {root_};
}

AVL::iterator AVL::end()
{
    return {nullptr};
}

AVL::const_iterator AVL::end() const
{
    return {nullptr};
}

AVL::const_iterator AVL::cend() const
{
    return {nullptr};
}

AVL::iterator AVL::find(const Apartment &data)
{
    node* found_node = tree_search(data,root_);
    iterator it(found_node);
    return it;
}

AVL::const_iterator AVL::find(const Apartment &data) const
{
    node* found_node = tree_search(data,root_);
    const_iterator it(found_node);
    return it;
}

std::ostream &operator<<(std::ostream &os, const AVL &avl)
{
    for (auto val: avl)
    {
        os << val << endl;
    }
    return os;
}


AVL::node *AVL::preorder_successor(AVL::node *cur) {
    // If left child exists, then it is preorder
    // successor.
    if (cur->left_)
        return cur->left_;

    // If left child does not exist and right child
    // exists, then it is preorder successor.
    if (cur->right_)
        return cur->right_;
    // If left child does not exist, then
    // travel up (using parent pointers)
    // until we reach a node which is left
    // child of its parent.
    node *parent = cur->parent_;
    while (parent != nullptr && parent->right_ == cur) {
        cur = cur->parent_;
        parent = parent->parent_;
    }

    // If we reached root, then the given
    // node has no preorder successor
    if (parent == nullptr)
        return nullptr;

    // If we reached the root which means we don't have a parent
    // we will need to go to the right child of root and continue from there
    // the tree travel.
    return parent->right_;
}

void AVL::delete_helper(node *cur)
{
    if (cur == nullptr)
        return;
    // Delete the leaves first then their parents and grandparents etc and
    // only at the end delete the root.
    delete_helper(cur->left_);
    delete_helper(cur->right_);
    delete cur;
}

int AVL::calculate_height(AVL::node *&cur) {
    if (cur)
    {
        if (cur->left_ && cur->right_)
        {
            if (cur->left_->height_ < cur->right_->height_)
            {
                return cur->right_->height_ + 1;
            } else
            {
                return cur->left_->height_ + 1;
            }
        }
        else if (cur->left_ && cur->right_ == nullptr)
        {
            return cur->left_->height_ + 1;
        }
        else if (cur->left_ == nullptr && cur->right_)
        {
            return cur->right_->height_ + 1;
        }
    }
    return 1;
}

int AVL::calculate_bf(AVL::node *&cur)
{
    if (cur)
    {
        if (cur->left_ && cur->right_)
        {
            return cur->left_->height_ - cur->right_->height_;
        }
        else if (cur->left_ && cur->right_ == nullptr)
        {
            return cur->left_->height_;
        }
        else if (cur->left_ == nullptr && cur->right_)
        {
            return -cur->right_->height_;
        }
    }
    return 0;
}


AVL::node *AVL::ll_rotation(AVL::node *cur)
{
    node *t;
    t = cur->left_;
    cur->left_ = t->right_;
    t->right_ = cur;
    return t;
}

AVL::node *AVL::rr_rotation(AVL::node *cur)
{
    node *t;
    t = cur->right_;
    cur->right_ = t->left_;
    t->left_ = cur;
    return t;
}

AVL::node *AVL::rl_rotation(AVL::node *cur)
{
    node *t;
    t = cur->right_;
    cur->right_ = ll_rotation(t);
    return rr_rotation(cur);
}

AVL::node *AVL::lr_rotation(AVL::node *cur)
{
    node *t;
    t = cur->left_;
    cur->left_ = rr_rotation(t);
    return ll_rotation(cur);
}

void
AVL::insert_helper(AVL::node *&cur, const Apartment &apartment, node *parent)
{
    if (!cur)
    {
        cur = new node(apartment,
                       nullptr, nullptr,
                       parent, calculate_bf(cur),
                       calculate_height(cur));
        return;
    }
    else
    {
        if (apartment < cur->data_)
        {
            insert_helper(cur->left_, apartment, cur);
            cur->height_ = calculate_height(cur);
            cur->bf_ = calculate_bf(cur);
            cur->parent_ = parent;
        }
        else
        {
            insert_helper(cur->right_, apartment, cur);
            cur->height_ = calculate_height(cur);
            cur->bf_ = calculate_bf(cur);
            cur->parent_ = parent;
        }
        node * old_cur = cur;
        cur = balance_tree(cur);
        if (old_cur->bf_ == 2 || old_cur->bf_ == - 2){
            fix_nodes_fields_downwards(cur, parent);
        }
    }
}

AVL::node *AVL::copy_helper(node *cur, node *parent)
{
    if (!cur)
    {
        return nullptr;
    }
    node *node_copy =
            new node(cur->data_, nullptr, nullptr, parent, cur->bf_,
                               cur->height_);
    node_copy->left_ = copy_helper(cur->left_, node_copy);
    node_copy->right_ = copy_helper(cur->right_, node_copy);
    return node_copy;
}


AVL::node *AVL::tree_minimum(AVL::node *cur)
{
    while (cur->left_ != nullptr)
    {
        cur = cur->left_;
    }
    return cur;
}

void AVL::fix_nodes_fields_downwards(node *cur, node *parent)
{
    if (cur == nullptr)
    {
        return;
    }
    fix_nodes_fields_downwards(cur->left_, cur);
    fix_nodes_fields_downwards(cur->right_, cur);
    cur->height_ = calculate_height(cur);
    cur->bf_ = calculate_bf(cur);
    cur->parent_ = parent;
}

void AVL::transplant(node *cur, node *replace_cur)
{
    if (!cur->parent_)
    {
        root_ = replace_cur;
    }
    else if (cur == cur->parent_->left_)
    {
        cur->parent_->left_ = replace_cur;
    }
    else
    {
        cur->parent_->right_ = replace_cur;
    }
    if (replace_cur != nullptr)
    {
        replace_cur->parent_ = cur->parent_;
    }
}

void AVL::erase_helper(node *cur)
{
    if (cur)
    {
        if (!cur->left_)
        {
            transplant(cur, cur->right_);
        }
        else if (!cur->right_)
        {
            transplant(cur, cur->left_);
        }
        else
        {
            node* min_right = tree_minimum(cur->right_);
            if (min_right->parent_ != cur)
            {
                transplant(min_right,min_right->right_);
                min_right->right_ = cur->right_;
                min_right->right_->parent_ = min_right;
            }
            transplant(cur, min_right);
            min_right->left_ = cur->left_;
            min_right->left_->parent_ = min_right;
        }
        fix_all_affected_nodes(cur);
        node* unbalanced = unbalanced_node(cur);
        if (unbalanced == root_)
            // if root is unbalanced no need to while just fix root itself.
        {
            root_ = balance_tree(root_);
            return;
        }
        // find all imbalances after erasing the node and check for further
        // imbalances up to the root.
        while ( unbalanced != nullptr)
        {
            node * unbalanced_parent = unbalanced->parent_;
            node * balanced_sub_tree = balance_tree(unbalanced);
            // Connect the new balanced right subtree to its new father
            if (unbalanced == unbalanced_parent->right_)
            {
                unbalanced_parent->right_ = balanced_sub_tree;
                balanced_sub_tree->parent_ = unbalanced_parent;
            }
            // Connect the new balanced left subtree to its new father
            if (unbalanced == unbalanced_parent->left_)
            {
                unbalanced_parent->left_ = balanced_sub_tree;
                balanced_sub_tree->parent_ = unbalanced_parent;
            }
            // fix fields for affected nodes
            fix_all_affected_nodes(cur);
            // balance the whole tree
            root_ = balance_tree(root_);
            // re-fix fields for affected nodes
            fix_all_affected_nodes(cur);
            // update new parent
            cur = cur->parent_;
            // update new unbalanced to check if the parent has bf violation
            unbalanced = unbalanced_node(cur);
        }
    }
}

void AVL::fix_all_affected_nodes(AVL::node *cur)
{
    if (cur->parent_ && cur->parent_->parent_)
    {
        fix_nodes_fields_downwards(cur->parent_, cur->parent_->parent_);
        fix_nodes_fields_upwards(cur->parent_, cur->parent_->parent_);
    }
    else
    {
        fix_nodes_fields_downwards(root_, nullptr);
    }
}

AVL::node* AVL::balance_tree(AVL::node *cur) {
    if (calculate_bf(cur) == 2 && calculate_bf(cur->left_) == 1)
    {
        cur = ll_rotation(cur); // Left-Left Rotate
    }
    else if (calculate_bf(cur) == -2 && calculate_bf(cur->right_) == -1)
    {
        cur = rr_rotation(cur); // Right-Right Rotate
    }
    else if (calculate_bf(cur) == -2 && calculate_bf(cur->right_) == 1)
    {
        cur = rl_rotation(cur); // Right-Left Rotate
    }
    else if (calculate_bf(cur) == 2 && calculate_bf(cur->left_) == -1)
    {
        cur = lr_rotation(cur); // Left-Right Rotate
    }
    return cur;
}

AVL::node *
AVL::tree_search(const Apartment &apartment, node *search_node) const
{
    if (search_node == nullptr || apartment == search_node->data_)
    {
        return search_node;
    }
    if (apartment < search_node->data_){
        return tree_search(apartment, search_node->left_);
    }
    else
    {
    return tree_search(apartment, search_node->right_);
    }
}

AVL::node *AVL::unbalanced_node(node * start_node)
{
    if (start_node->bf_ == 2 || start_node->bf_ == -2)
    {
        return start_node;
    }
    if (start_node->parent_ == nullptr)
    {
        return nullptr;
    }
    return unbalanced_node(start_node->parent_);
}

void AVL::fix_nodes_fields_upwards(AVL::node *cur, AVL::node *parent)
{
    if (cur->parent_ == nullptr)
        return;
    cur->height_ = calculate_height(cur);
    cur->bf_ = calculate_bf(cur);
    cur->parent_ = parent;
    fix_nodes_fields_upwards(cur->parent_, cur->parent_->parent_);
}
