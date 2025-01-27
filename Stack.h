#ifndef _STACK_H_
#define _STACK_H_

#define STACK_EMPTY_ERROR "Error: The stack of apartments is empty!\n"

#include "Apartment.h"
#include <utility>
#include <vector>
#include <iterator>

using std::vector;

class Stack {
private:
    vector<Apartment> apartments;
public:
    /**
     * Default constructor, constructs an empty stack
     */
    Stack();

    /**
     * Constructor that gets vector of pairs, and pushes them
     * as apartments to the stack, when the first pair is pushed first.
     * @param coordinates vector of pairs
     */
    Stack(std::vector<std::pair<double, double>> coordinates);

    /**
     * Pushes an apartment to the top of the stack
     * @param apartment
     */
    void push(const Apartment &apartment);

    /**
     * A method that deletes the item from the top of the stack.
     * Calling this method with an empty stack will throw an out of
     * range exception with an informative message of your choice.
     */
    void pop();

    /**
    *A method that returns true if the stack is empty and otherwise false.
    */
    bool empty() const;

    /**
    *A method that returns how many items are inside the stack.
    */
    size_t size() const;

    /**
     * Method that return the item from the top of the stack,
     * but do not remove it from it.
     * Calling this method with an empty stack will throw an out of range
     * exception with an informative message of your choice.
     * @return refernce to the top most item
     */
    Apartment &top();

    /**
     * Method that return the item from the top of the stack, but do
     * not remove it from it.
     * Calling this method with an empty stack will throw an out of range
     * exception with an informative message of your choice.
     * @return copy to the top most item
     */
    Apartment top() const;

    /**
     * The stack should support the Iterator (at least a forward Iterator)
     * so that the item at the top of the stack is the first item.
     */

    /**
     * Define the iterator of Stack as reverse_iterator of vector so it will
     * preform in LIFO order (Stack).
     */
    typedef std::vector<Apartment>::reverse_iterator iterator;

    /**
    * Define the const_iterator of Stack as reverse_iterator of vector
    * so it will preform in LIFO order (Stack).
    */
    typedef std::vector<Apartment>::const_reverse_iterator const_iterator;


    /**
     * All definitions for begin() and end() of the Stack iterator
     * and const_iterator kinds of iterators.
     */
    iterator begin() { return apartments.rbegin(); }

    const_iterator begin() const { return apartments.crbegin(); }

    const_iterator cbegin() const { return apartments.crbegin(); }

    iterator end()
    { return apartments.rend(); }

    const_iterator end() const
    { return apartments.crend(); }

    const_iterator cend() const
    { return apartments.crend(); }
};

#endif //_STACK_H_
