//
// Created by ronl on 11/29/2022.
//

#ifndef WET1_EXCEPTION_H
#define WET1_EXCEPTION_H

#include <stdexcept>
#include <exception>
#include <memory>
#include <iostream>



class  keyAlreadyTaken : public std::exception {
public:
    const char * what () const noexcept override {
        return "The key is in use";
    }
};

class  keyDoesntExist : public std::exception {
public:
    const char * what () const noexcept override {
        return "There is not such key";
    }
};

class  RankIsNotInRange : public std::exception {
public:
    const char * what () const noexcept override {
        return "Rank is not in range";
    }
};




#endif //WET1_EXCEPTION_H