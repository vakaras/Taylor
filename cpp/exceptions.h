#ifndef TAYLOR_CPP_EXCEPTIONS
#define TAYLOR_CPP_EXCEPTIONS

#include <exception>
#include <cstring>

class Exception: public std::exception {

// Attributes.

private:

  char *msg;

// Methods:

public:

  Exception(const char *_msg) {
    msg = new char[strlen(_msg)+1];
    strcpy(msg, _msg);
    }
  
  virtual const char *what() const throw() {
    return msg;
    }
  
  };

class OverflowException: public Exception {

// Methods:

public:

  OverflowException(): 
    Exception("Too small precision to hold this value.") {
    }

  OverflowException(const char *_msg): Exception(_msg) {
    }

  };

#endif
