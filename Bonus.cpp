#include <vector>
#include <cstddef>
#include <unordered_set>
#include <string>
#include <chrono>
#include <iostream>
#include <ostream>
#include <fstream>
#include "Apartment.h"
#include "AVL.h"
#include "Stack.h"
#include <sstream>
#include "Find.h"
#include "MesureTimeHelper.h"

#define X_COORD 31.81428051893798
#define Y_COORD 35.18577781093502
#define FILE_100 "apartments100.txt"
#define FILE_1000 "apartments1000.txt"
#define FILE_10000 "apartments10000.txt"
#define TIME_FOR_100_APARTMENTS "100 Apartments time measurements:"
#define TIME_FOR_1000_APARTMENTS "1000 Apartments time measurements:"
#define TIME_FOR_10000_APARTMENTS "10000 Apartments time measurements:"
#define STACK_INSERT_TIME "Stack insert time: "
#define STACK_TEMPLATE_TIME "Stack Template find time: "
#define AVL_INSERT_TIME "AVL insert time: "
#define AVL_TEMPLATE_ITER_TIME "AVL Template find time: "
#define AVL_BUILT_IN_ITER_TIME "AVL built in iterator find time: "
#define UNORDERED_SET_TIME "Unordered set insert time: "
#define SET_TEMPLATE_ITER_TIME "Unordered set Template find time: "
#define SET_BUILT_IN_ITER_TIME "Unordered set built in find time: "

using std::cout;
using std::endl;

/**
* inserts the apartments to unordered set.
* @param apartments_vec vector of pairs of doubles includes the coordinates
* of all the apartments.
* @param apartments_set The apartments unordered set of Apartments.
*/
void insert_unordered_set(const vector<std::pair<double, double>>&
apartments_vec, std::unordered_set<Apartment, MyHashFunction> &apartments_set);

/**
* Measure times of insertion, and template find of stack class.
* @param apartments_vec vector of pairs of doubles includes the coordinates
* of all the apartments.
* @param x The apartment to find.
*/
void stack_measures(const vector<std::pair<double, double>> &apartments_vec,
                    const Apartment &x);
/**
* Measure times of insertion,template find and built-in find of AVL class.
* @param apartments_vec vector of pairs of doubles includes the coordinates
* of all the apartments.
* @param x The apartment to find.
*/
void avl_measure(const vector<std::pair<double, double>> &apartments_vec,
                 const Apartment &x);
/**
* Measure times of insertion,template find and built-in find of STL unordered
* set class.
* @param apartments_vec vector of pairs of doubles includes the coordinates
* of all the apartments.
* @param apartments_set The apartments unordered set of Apartments.
* @param x The apartment to find.
*/
void unordered_set_measure(
        const vector<std::pair<double, double>> &apartments_vec,
        std::unordered_set<Apartment, MyHashFunction>
                &apartments_unordered_set, const Apartment &x);

void insert_unordered_set(const vector<std::pair<double, double>>
&apartments_vec, std::unordered_set<Apartment, MyHashFunction> &apartments_set)
{
    for (auto val: apartments_set)
    {
        apartments_set.insert(val);
    }
}

void stack_measures(const vector<std::pair<double, double>> &apartments_vec
        , const Apartment &x)
{
    auto time1 = std::chrono::high_resolution_clock::now();
    Stack stack_100(apartments_vec);
    auto time2 = std::chrono::high_resolution_clock::now();
    std::cout << STACK_INSERT_TIME << std::chrono::duration_cast<std
    ::chrono::nanoseconds>(time2-time1).count() << std::endl;
    auto t1 = std::chrono::high_resolution_clock::now();
    find(stack_100.begin(),stack_100.end(),x);
    auto t2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count();
    std::cout << STACK_TEMPLATE_TIME << std::chrono::
    duration_cast<std::chrono::nanoseconds>(t2-t1).count() << std::endl;
    cout << endl;
}

void avl_measure(const vector<std::pair<double, double>> &apartments_vec,
                 const Apartment &x)
{
    auto t3 = std::chrono::high_resolution_clock::now();
    AVL avl_100(apartments_vec);
    auto t4 = std::chrono::high_resolution_clock::now();
    std::cout <<  AVL_INSERT_TIME << std::chrono::
    duration_cast<std::chrono::nanoseconds>(t4-t3).count() << std::endl;
    auto t5 = std::chrono::high_resolution_clock::now();
    find(avl_100.begin(),avl_100.end(),x);
    auto t6 = std::chrono::high_resolution_clock::now();
    std::chrono::duration_cast<std::chrono::nanoseconds>(t6-t5).count();
    std::cout <<  AVL_TEMPLATE_ITER_TIME << std::chrono::
    duration_cast<std::chrono::nanoseconds>(t6-t5).count() << std::endl;
    auto time3 = std::chrono::high_resolution_clock::now();
    avl_100.find(x);
    auto time4 = std::chrono::high_resolution_clock::now();
    std::chrono::duration_cast<std::chrono::nanoseconds>(time4-time3).count();
    std::cout << AVL_BUILT_IN_ITER_TIME <<  std::chrono::
    duration_cast<std::chrono::nanoseconds>(time4-time3).count() << std::endl;
    cout << endl;
}

void unordered_set_measure(const vector<std::pair<double, double>>
        &apartments_vec, std::unordered_set<Apartment, MyHashFunction>
                &apartments_unordered_set, const Apartment &x)
                {
    auto t7 = std::chrono::high_resolution_clock::now();
                    insert_unordered_set(apartments_vec,
                                         apartments_unordered_set);
    auto t8 = std::chrono::high_resolution_clock::now();
    std::cout <<  UNORDERED_SET_TIME << std::chrono::
    duration_cast<std::chrono::nanoseconds>(t8-t7).count() << std::endl;
    auto t9 = std::chrono::high_resolution_clock::now();
    find(apartments_unordered_set.begin(), apartments_unordered_set.end(), x);
    auto t10 = std::chrono::high_resolution_clock::now();
    std::chrono::duration_cast<std::chrono::nanoseconds>(t10-t9).count();
    std::cout <<  SET_TEMPLATE_ITER_TIME << std::chrono::
    duration_cast<std::chrono::nanoseconds>(t10-t9).count() << std::endl;
    auto t11 = std::chrono::high_resolution_clock::now();
    apartments_unordered_set.find(x);
    auto t12 = std::chrono::high_resolution_clock::now();
    std::cout <<  SET_BUILT_IN_ITER_TIME << std::chrono::
    duration_cast<std::chrono::nanoseconds>(t12-t11).count() << std::endl;
    cout << endl;
}

void run_single_file(const std::vector<std::pair<double,double>>
& apartments_vec, const Apartment &x)
{
    stack_measures(apartments_vec, x);
    avl_measure(apartments_vec, x);
    std::unordered_set<Apartment, MyHashFunction> apartments_unordered_set;
    unordered_set_measure(apartments_vec, apartments_unordered_set, x);
    cout << endl;
}

void run_all_files()
{
    double x_coord = X_COORD;
    double y_coord = Y_COORD;
    const Apartment x(std::pair<double, double>{x_coord,y_coord});
    std::string file_100 =  FILE_100;
    std::string file_1000 =  FILE_1000;
    std::string file_10000 =  FILE_10000;
    std::vector<std::pair<double,double>> apartments100
    = xy_from_file(file_100);
    std::vector<std::pair<double,double>> apartments1000
    = xy_from_file(file_1000);
    std::vector<std::pair<double,double>> apartments10000
    = xy_from_file(file_10000);
    cout << TIME_FOR_100_APARTMENTS << endl;
    run_single_file(apartments100, x);
    cout << TIME_FOR_1000_APARTMENTS << endl;
    run_single_file(apartments1000, x);
    cout << TIME_FOR_10000_APARTMENTS << endl;
    run_single_file(apartments10000, x);
}



