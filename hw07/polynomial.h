#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H
#include <iostream>
#include <string>
#include <vector>


struct Node {
    Node(int, Node*);
    int coefficient;
    Node* next;
};


class Polynomial {
    friend std::ostream& operator<<(std::ostream&, const Polynomial&);
public:
    Polynomial();
    Polynomial(std::vector<int>);
    Polynomial(const Polynomial&);
    ~Polynomial();
    Polynomial& operator=(const Polynomial&);
    bool operator==(const Polynomial&);
    bool operator!= (const Polynomial&);
    Polynomial& operator +=(const Polynomial& rhs);
    Polynomial operator+(const Polynomial&) const;
    double evaluate(double);
private:
    int degree;
    Node* termOne;
};

void printReverse(std::ostream&, Node*, int);

#endif