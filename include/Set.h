//
// Created by algo on 07/04/2021.
//

#ifndef SETEXERCISE_SET_H
#define SETEXERCISE_SET_H

#include <iostream>
#include <memory>
using namespace std;

struct Data {
    double data;
    string key;
    Data * next;
    Data(const string &key, double data);
};

class Set {
private:
    Data *head;

    Data *searchKeyComponent(const string &key) const;

public:
    // Methods
    Set();

    Set(const Set &toCopySet);

    ~Set();

    int add(const string &key, double data);

    int remove(const string &key);

    bool isInSet(const string &key, double &data) const;

    double sumSet() const;

    int totWeight() const;

    void printSet() const;

    // Static methods
    static int myHashFunction(const string &key);

    // Operators methods
    bool operator==(const Set &s) const;

    bool operator<(const Set &s) const;

    bool operator>(const Set &s) const;

    Set operator-(const Set &s) const;

    Set operator|(const Set &s) const;

    Set operator&(const Set &s) const;

    Set &operator=(const Set &s);
};

#endif //SETEXERCISE_SET_H
