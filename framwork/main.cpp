/*
 * @Author: xbybshd
 * @Date: 2020-03-09 18:06:40
 * @Last Modified by: xbybshd
 * @Last Modified time: 2020-11-07 22:47:39
 */
#include <bits/stdc++.h>

using namespace std;
ifstream fcin(".\\input.txt", ifstream::in);
ofstream fcout(".\\output.txt", ofstream::out);


#include <utility>
#include <string>
#include <iostream>
class Person
{
private:
    std::string name;
public:
    // generic constructor for passed initial name:
    template<typename STR>
    explicit Person(STR&& n) : name(std::forward<STR>(n)) {
        std::cout << "TMPL-CONSTR for '" << name << "'\n";
    }
    // copy and move constructor:
    Person(Person const& p) : name(p.name) {
        std::cout << "COPY-CONSTR Person '" << name << "'\n";
    }
    Person(Person&& p) : name(std::move(p.name)) {
        std::cout << "MOVE-CONSTR Person '" << name << "'\n";
    }
};

int main()
{
    std::string s = "sname";
    Person p1(s); // init with string object => calls TMPL-CONSTR
    Person p2("tmp"); // init with string literal => calls TMPL-CONSTR
    Person p3(p1); // ERROR

    fcin.close();
    fcout.close();


    return 0;
}