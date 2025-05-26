//agassinoa20@gmail.com
#ifndef GRAPH_EXCEPTIONS_HPP
#define GRAPH_EXCEPTIONS_HPP

class SimpleException {
public:
    const char* msg;
    explicit SimpleException(const char* m) : msg(m) {}
};

#endif
