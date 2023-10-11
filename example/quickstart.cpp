#include <iostream>

#include "blet/dict.h"

int main(int, char**) {
    /*
    ** generate
    */
    std::vector<double> vDouble;
    vDouble.reserve(3);
    vDouble.push_back(0.42);
    vDouble.push_back(-0.42);
    vDouble.push_back(42);

    std::map<std::string, std::string> mStr;
    mStr["key1"] = "value1";
    mStr["key2"] = "value2";

    blet::Dict dict;
    dict["foo"] = "bar";
    dict["array"][0] = "foo";
    dict["array"][1] = "bar";
    dict["vector"].newArray(vDouble);
    dict["object"]["foo"] = "bar";
    dict["map_object"] = mStr;
    dict["boolean"] = true;
    dict["number"] = 24;
    dict["null"].newNull();
    dict["self"] = dict;

    std::cout << "foo: " << dict["foo"] << '\n';
    std::cout << "array: " << '\n';
    std::cout << "  0: " << dict["array"][0] << '\n';
    std::cout << "  1: " << dict["array"][1] << '\n';
    std::cout << "vector: " << '\n';
    std::cout << "  0: " << dict["vector"][0] << '\n';
    std::cout << "  1: " << dict["vector"][1] << '\n';
    std::cout << "  2: " << dict["vector"][2] << '\n';
    std::cout << "object: " << '\n';
    std::cout << "  foo: " << dict["object"]["foo"] << '\n';
    std::cout << "map_object: " << '\n';
    std::cout << "  key1: " << dict["map_object"]["key1"] << '\n';
    std::cout << "  key2: " << dict["map_object"]["key2"] << '\n';
    std::cout << "boolean: " << dict["boolean"] << '\n';
    std::cout << "number: " << dict["number"] << '\n';
    std::cout << "null: " << dict["null"] << '\n';
    std::cout << "self: " << '\n';
    std::cout << "  foo: " << dict["self"]["foo"] << '\n';
    std::cout << "  array: " << '\n';
    std::cout << "    0: " << dict["self"]["array"][0] << '\n';
    std::cout << "    1: " << dict["self"]["array"][1] << '\n';
    std::cout << "  vector: " << '\n';
    std::cout << "    0: " << dict["self"]["vector"][0] << '\n';
    std::cout << "    1: " << dict["self"]["vector"][1] << '\n';
    std::cout << "    2: " << dict["self"]["vector"][2] << '\n';
    std::cout << "  object: " << '\n';
    std::cout << "    foo: " << dict["self"]["object"]["foo"] << '\n';
    std::cout << "  map_object: " << '\n';
    std::cout << "    key1: " << dict["self"]["map_object"]["key1"] << '\n';
    std::cout << "    key2: " << dict["self"]["map_object"]["key2"] << '\n';
    std::cout << "  boolean: " << dict["self"]["boolean"] << '\n';
    std::cout << "  number: " << dict["self"]["number"] << '\n';
    std::cout << "  null: " << dict["self"]["null"] << '\n';
}