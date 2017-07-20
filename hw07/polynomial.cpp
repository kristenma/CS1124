#include <math.h>
#include "Polynomial.h"
using namespace std;

Node::Node(int coefficient, Node* next = nullptr) : coefficient(coefficient), next(next) {}

Polynomial::Polynomial() : termOne(nullptr) {}

Polynomial::Polynomial(vector<int> coefficients) : termOne(new Node(coefficients[coefficients.size() - 1])), degree(coefficients.size()-1) {
    Node* temp = termOne;
    
    //link list of ints together
    for (int i = coefficients.size() - 2; i >= 0; --i) {
        temp->next = new Node(coefficients[i]);
        temp = temp->next;
    }
}

//copy constructor
Polynomial::Polynomial(const Polynomial& aPolynomial) {
    //copy the degree
    degree = aPolynomial.degree;
    
    //copy the first term
    Node* polynomialTemp = aPolynomial.termOne->next;
    termOne = new Node(aPolynomial.termOne->coefficient);
    
    //copy the linked list after first term
    Node* temp = termOne;
    while (polynomialTemp) {
        temp->next = new Node(polynomialTemp->coefficient);
        temp = temp->next;
        polynomialTemp = polynomialTemp->next;
    }
}

//destructor
Polynomial::~Polynomial() {
    //while first term is not null, delete each term in linked list
    while (termOne != nullptr) {
        Node* temp = termOne;
        termOne = termOne->next;
        delete temp;
    }
}

//assignment operator
Polynomial& Polynomial::operator=(const Polynomial& aPolynomial) {
    
    //if polynomials are not equal to each other, delete each term in linked list
    if (this != &aPolynomial) {
        while (termOne != nullptr) {
            Node* temp = termOne;
            termOne = termOne->next;
            delete temp;
        }
        
        //copy the degree
        degree = aPolynomial.degree;
        //copy the first term
        Node* polynomialTemp = aPolynomial.termOne->next;
        termOne = new Node(aPolynomial.termOne->coefficient);
        
        //copy the linked list after first term
        Node* temp = termOne;
        while (polynomialTemp) {
            temp->next = new Node(polynomialTemp->coefficient);
            temp = temp->next;
            polynomialTemp = polynomialTemp->next;
        }
    }
    return *this;
}

//equality test
bool Polynomial::operator==(const Polynomial& rhs) {
    //if degrees of each polynomial are equal to each other
    if (degree == rhs.degree) {
        Node* rhsTemp = rhs.termOne;
        Node* lhsTemp = termOne;
        
        while (rhsTemp && lhsTemp) {
            //if coefficients of any term are not equal to each other return false
            //if equal, bump until end and return true
            if (rhsTemp->coefficient != lhsTemp->coefficient) {
                return false;
            }
            rhsTemp = rhsTemp->next;
            lhsTemp = lhsTemp->next;
        }
        return true;
    }
    //if degrees of each polynomial are not equal to each other return false
    else {
        return false;
    }
}

bool Polynomial::operator!= (const Polynomial& rhs) {
    return !(*this == rhs);
}

Polynomial& Polynomial::operator +=(const Polynomial& rhs) {
    Node* lhsTerm = termOne;
    Node* rhsTerm = rhs.termOne;
    Node* prevTerm = termOne;
    
    //while first node exists for both polynomials, add coefficient to base term, initiate new term and bump
    while (lhsTerm && rhsTerm) {
        lhsTerm->coefficient += rhsTerm->coefficient;
        prevTerm = lhsTerm;
        lhsTerm = lhsTerm->next;
        rhsTerm = rhsTerm->next;
    }
    
    //while second polynomial is greater than first, create new terms and bump
    lhsTerm = prevTerm;
    while (rhsTerm) {
        lhsTerm->next = new Node(rhsTerm->coefficient);
        rhsTerm = rhsTerm->next;
        lhsTerm = lhsTerm->next;
    }
    return *this;
}

Polynomial Polynomial::operator+(const Polynomial& rhs) const {
    //create a copy of polynomial so we don't change it
    Polynomial aPolynomial(*this);
    
    //add polynomials
    aPolynomial += rhs;
    return aPolynomial;
}

double Polynomial::evaluate(double x) {
    Node* temp = termOne->next;
    double result = termOne->coefficient;
    int exponent = 1;
    while (temp) {
        result += temp->coefficient * pow(x, exponent);
        temp = temp->next;
        exponent++;
    }
    return result;
}

void printReverse(ostream& os, Node* aNode, int degree) {
    if (aNode) {
        printReverse(os, aNode->next, degree+1);
        if (degree == 1) {
            os << aNode->coefficient << "x";
            os << " + ";
        }
        else if (degree == 0)
        {
            os << aNode->coefficient;
        }
        else
        {
            os << aNode->coefficient << "x^" << degree;
            os << " + ";
        }
    }
}

ostream& operator<<(ostream& os, const Polynomial& aPolynomial) {
    printReverse(os,aPolynomial.termOne, 0);
    return os;
}