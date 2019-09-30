#ifndef ARRAYINDEXOUTOFBOUNDSEXCEPTION_H
#define ARRAYINDEXOUTOFBOUNDSEXCEPTION_H

#include "Exception.h"
#include <sstream>
using namespace std;
class ArrayIndexOutOfBoundsException : public Exception {
public:
    ArrayIndexOutOfBoundsException(int index) {
    	string str1;
		stringstream sstr;
		sstr << index;
		sstr >> str1;
		string str2("ArrayIndexOutOfBoundsException:");
		str2.append(str1);
		_message = str2.c_str();
    }
    ArrayIndexOutOfBoundsException(const char *message) {
        _message = message;
    }

    virtual const char* message() {
        return _message;
    }
};

#endif
