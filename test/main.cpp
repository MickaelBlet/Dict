#include <iostream>
#include <string>

struct A {
    int i;
    template<typename T>
    void to(const T& v) {
        std::cout << "other" << std::endl;
    }
};

struct B : public A {};

struct C : public A {
    void to(const std::string& v) {
        std::cout << "string" << std::endl;
    }
};

struct D : public A {
    void to(const double& v) {
        std::cout << "double" << std::endl;
    }
};

struct E : public virtual B, public virtual C, public virtual D {};

int main(int argc, char** argv) {
    (void)argc;
    (void)argv;
    C e;
    std::cout << sizeof(E) << std::endl;
    e.to(std::string("test"));
    e.A::to<int>(42);
    return 0;
}