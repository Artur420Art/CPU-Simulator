#include <iostream>
#include <map>
#include <fstream>
#include <vector>
#include <string>

class CPU {
private:
    typedef void(CPU::*chlp) (std::string&, std::string&);
    typedef bool(CPU::*ghlp) (std::string&, std::string&);
    std::ifstream file;
    std::map<std::string, int*>reg;
    std::map<std::string, chlp> ins;
    std::map<std::string, int> lable;
    std::map<std::string, ghlp> jmps;
    int r1;
    int r2;
    int r3;
    int r4;
    int r5;
    int r6;
    int r7;
    int r8;
    int r9;
    int r10;
    std::string cmp_1;
    std::string cmp_2;
    std::string cmp_3;
public:
    void mov(std::string& str, std::string& str1);
    void add(std::string& str, std::string& str1);
    void mul(std::string& str, std::string& str1);
    void sub(std::string& str, std::string& str1);
    void div(std::string& str, std::string& str1);
    void _and(std::string& str, std::string& str1);
    void _or(std::string& str, std::string& str1);
    void _xor(std::string& str, std::string& str1);
    void _not(std::string& str, std::string& str1);
    void jmp(std::string& str, std::string& str1);
    void cmp(std::string& str, std::string& str1);
    bool equal(std::string& str, std::string& str1);
    bool nequal(std::string& str, std::string& str1);
    bool jzero(std::string& str, std::string& str1);
    bool jnzero(std::string& str, std::string& str1);
    bool jle(std::string& str, std::string& str1);
    bool jl(std::string& str, std::string& str1);
    bool jge(std::string& str, std::string& str1);
    bool jg(std::string& str, std::string& str1);
    void cut(std::string rhs);
    void make();
    void get_assm();
    bool check_rg(std::string);
    bool is_number(std::string);
    void print();
    
public:
    CPU () : r1{}, r2{}, r3{}, r4{}, r5{}, r6{}, r7{}, r8{}, r9{}, r10{}
    { make();}
};