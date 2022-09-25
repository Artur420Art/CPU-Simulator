#include "cpu.h"


void CPU::make()
{
    reg["r1"] = &r1;
    reg["r2"] = &r2;
    reg["r3"] = &r3;
    reg["r4"] = &r4;
    reg["r5"] = &r5;
    reg["r6"] = &r6;
    reg["r7"] = &r7;
    reg["r8"] = &r8;
    reg["r9"] = &r9;
    reg["r10"] = &r10;

    ins["mov"] = &CPU::mov;
    ins["div"] = &CPU::div;
    ins["add"] = &CPU::add;
    ins["mul"] = &CPU::mul;
    ins["sub"] = &CPU::sub;
    ins["and"] = &CPU::_and;
    ins["or"] = &CPU::_or;
    ins["xor"] = &CPU::_xor;
    ins["not"] = &CPU::_not;
    ins["jmp"] = &CPU::jmp;
    ins["cmp"] = &CPU::cmp;

    jmps["je"] = &CPU::equal;
    jmps["jne"] = &CPU::nequal;
    jmps["jz"] = &CPU::jzero;
    jmps["jnz"] = &CPU::jnzero;
    jmps["jge"] = &CPU::jge;
    jmps["jle"] = &CPU::jle;
    jmps["jl"] = &CPU::jl;
    jmps["jg"] = &CPU::jg;

}

void CPU::cut(std::string rhs) {
    std::string operation = "";
    std::string reg = "";
    std::string src = "";
    int line = 0;
    int index = rhs.find(' ');
    if (rhs.find(',') != -1) {
        rhs.erase(rhs.begin() + rhs.find(','));
    }
    if (rhs.find(':') != -1) {
        rhs.erase(rhs.begin() + rhs.find(':'));
        lable[rhs] = this->file.tellg();
        return;
    }
    if (index == -1)
    {
        operation = rhs;
    }
    int space = 0;
    for (int i = 0; i < rhs.size(); ++i)
    {
        if (rhs[i] == ' ')
        {
            ++space;
        }
    }
    if (space == 1)
    {
        for (int i = 0; i < rhs.size(); ++i)
        {
            if (rhs[i] == ' ')
            {
                operation += rhs.substr(0, i);
                rhs.erase(rhs.begin(), rhs.begin() + i + 1);
            }
        }
        reg += rhs;
        cmp_3 = reg;
    }
    if (space == 2)
    {                                      
        for (int i = 0; i < rhs.size(); ++i)
        {
            if (rhs[i] == ' ')
            {
                operation += rhs.substr(0, i);
                rhs.erase(rhs.begin(), rhs.begin() + i + 1);
                reg += rhs.substr(0, rhs.find(' '));
                rhs.erase(rhs.begin(), rhs.begin() + rhs.find(' ') + 1);
            }
        }
        src += rhs;
        
    }
    if (operation[0] == 'j' && operation[1] != 'm')
    {
        (this->*jmps[operation])(cmp_1, cmp_2);
    }
    else 
    {
        (this->*ins[operation])(reg, src);
    }
}

void CPU::get_assm() {
    get_lbl();
    std::string str1;
    file.open("assm.txt");
     if(file.is_open()) {
        while(getline(file, str1)) {
            if (str1 == "")
            {
                continue;
            }
            this->cut(str1);
        }
    } else {
        std::cout << "is not open";
    }
}
void CPU::get_lbl() {
    std::string lineer;
    this->file.open("assm.txt");
    if (this->file.is_open()) {
        while (!(this->file.eof())) {
            std::getline(this->file, lineer);
            if (lineer.find(':') != -1) {
                lineer.erase(lineer.begin() + lineer.find(':'));
                this->lable[lineer] = this->file.tellg();
            }
        }
    }
    this->file.close();
}

void CPU::mov(std::string& dest, std::string& src) {
 if (check_rg(dest)) {
   if(!check_rg(src) && is_number(src)) {
        *(reg[dest]) = stoi(src);
        return;
   }
   if (check_rg(src)) {
        *(reg[dest]) = *(reg[src]);
        return;
   }
}
    throw std::invalid_argument("Register is not found");
}
bool CPU::check_rg(std::string dest) {
    for(int i = 0; i < reg.size(); ++i) {
        if (reg.find(dest) == reg.end()) 
        {
             return false;
        }
    }
    return true;
}
bool CPU::is_number(std::string dest) {
    for(int i = 0; i < dest.size(); ++i) {
        if(!(dest[i] >= '0' && dest[i] <= '9')) {
            return false;
        }
    }
    return true;
}
void CPU::add(std::string& dest, std::string& src) {
    if (check_rg(dest)) {
        if(!check_rg(src) && is_number(src)) {
            *(reg[dest]) += stoi(src);
            return;
        }
        if (check_rg(src)) {
            *(reg[dest]) += *(reg[src]);
            return;
        } 
    }
    throw std::invalid_argument("Registr is not found");

}
void CPU::mul(std::string& dest, std::string& src) {
    if (check_rg(dest)) {

        if(!check_rg(src) && is_number(src)) {
            *(reg[dest]) *= stoi(src);
        }
        if (check_rg(src)) {
            *(reg[dest]) *= *(reg[src]);
        }
    }
    throw std::invalid_argument("Register is not found"); 
}
void CPU::_not(std::string& str, std::string& str1) {
     if (check_rg(str)) {
           *(reg[str]) = ~*(reg[str]);
            return;
        }
    throw std::logic_error("Eror");
}
void CPU::div(std::string& dest, std::string& src) {
    if (check_rg(dest))  {
        if(!check_rg(src) && is_number(src)) {
            *(reg[dest]) /= stoi(src);
        }
        if (check_rg(src)) {
            *(reg[dest]) /= *(reg[src]);
        }
    }
    throw std::invalid_argument("Register is not found");     
}
void CPU::sub(std::string& dest, std::string& src) {
    if(check_rg(dest)) {
        if(!check_rg(src) && is_number(src)) {
            *(reg[dest]) -= stoi(src);
        }
        if (check_rg(src)) {
            *(reg[dest]) -= *(reg[src]);
        }
    }
    throw std::invalid_argument("Register is not found");  
}
void CPU::_and(std::string& dest, std::string& src) {
    if (check_rg(dest)) {
        if (!check_rg(src) && is_number(src)) {
            *(reg[dest]) &= stoi(src);
            return;
        }
        if (check_rg(src)) {
            *(reg[dest]) &= *(reg[src]);
            return;
        }
    }
    throw std::logic_error("Error");

}
void CPU::_or(std::string& str, std::string& str1) {
     if (check_rg(str)) {
        if (!check_rg(str1) && is_number(str1)) {
            *(reg[str]) |= stoi(str1);
            return;
        }
        if (check_rg(str1)) {
            *(reg[str]) |= *(reg[str1]);
            return;
        }
    }
    throw std::logic_error("Eror");
}
void CPU::_xor(std::string& str, std::string& str1) {
     if (check_rg(str)) {
        if (!check_rg(str1) && is_number(str1)) {
            *(reg[str]) ^= stoi(str1);
            return;
        }
        if (check_rg(str1)) {
            *(reg[str]) ^= *(reg[str1]);
            return;
        }
    }
    throw std::logic_error("Eror");
}
void CPU::jmp(std::string& dest, std::string& src) {
    this->file.seekg(this->lable[dest]);
}

void CPU::cmp(std::string& dest, std::string& src) {
        cmp_1 = dest;
        cmp_2 = src;
}

bool CPU::equal(std::string& dest, std::string& src) {
    if (check_rg(dest) && check_rg(src))
    {
        if((*reg[dest]) == (*reg[src]))
        {
           jmp(cmp_3, cmp_2);
        }
    }else if (check_rg(dest) && is_number(src)) {
         if((*reg[dest]) == stoi(src))
        {
           jmp(cmp_3, cmp_2);
        }
    }
    
    return false;
   
}
bool CPU::nequal(std::string& dest, std::string& src) {
  if (check_rg(dest) && check_rg(src))
    {
        if((*reg[dest]) != (*reg[src]))
        {
           jmp(cmp_3, cmp_2);
        }
    }else if (check_rg(dest) && is_number(src)) {
         if((*reg[dest]) != stoi(src))
        {
           jmp(cmp_3, cmp_2);
        }
    }
    return false;
   
}
bool CPU::jzero(std::string& dest, std::string& src) {
    if (check_rg(dest) && (check_rg(src) || is_number(src)) ) {
        if (*reg[dest] == 0) {
            jmp(cmp_3, cmp_2);
        }
    }
    return false;
}
bool CPU::jnzero(std::string& dest, std::string& src) {
    if (check_rg(dest) && (check_rg(src) || is_number(src)) ) {
        if (*reg[dest] != 0) {
            jmp(cmp_3, cmp_2);
        }
    }
    return false;
}
bool CPU::jle (std::string& dest, std::string& src) {
    if(check_rg(dest) && (check_rg(src) || is_number(src))) {
        if (is_number(src)) {
            if (*reg[dest] <= stoi(src)) {
                jmp(cmp_3, cmp_2);
            }
        }else if (check_rg(src)) {
            if (*reg[dest] <= *reg[src]) {
                jmp(cmp_3, cmp_2);
            }
        }
    }
    return false;
}
bool CPU::jge (std::string& dest, std::string& src) {
      if(check_rg(dest) && (check_rg(src) || is_number(src))) {
        if (is_number(src)) {
            if (*reg[dest] >= stoi(src)) {
                jmp(cmp_3, cmp_2);
            }
        }else if (check_rg(src)) {
            if (*reg[dest] >= *reg[src]) {
                jmp(cmp_3, cmp_2);
            }
        }
    }
    return false;
}
bool CPU::jg (std::string& dest, std::string&src) {
     if(check_rg(dest) && (check_rg(src) || is_number(src))) {
        if (is_number(src)) {
            if (*reg[dest] > stoi(src)) {
                jmp(cmp_3, cmp_2);
            }
        }else if (check_rg(src)) {
            if (*reg[dest] > *reg[src]) {
                jmp(cmp_3, cmp_2);
            }
        }
    }
    return false;
}
bool CPU::jl (std::string& dest, std::string&src) {
     if(check_rg(dest) && (check_rg(src) || is_number(src))) {
        if (is_number(src)) {
            if (*reg[dest] < stoi(src)) {
                jmp(cmp_3, cmp_2);
            }
        }else if (check_rg(src)) {
            if (*reg[dest] < *reg[src]) {
                jmp(cmp_3, cmp_2);
            }
        }
    }
    return false;
}
void CPU::print() {
   std::cout << "R1 " << r1 << std::endl;
   std::cout << "R2 " << r2 << std::endl;
   std::cout << "R3 " << r3 << std::endl;
   std::cout << "R4 " << r4 << std::endl;
   std::cout << "R5 " << r5 << std::endl;
   std::cout << "R6 " << r6 << std::endl;
   std::cout << "R7 " << r7 << std::endl;
   std::cout << "R8 " << r8 << std::endl;
   std::cout << "R9 " << r9 << std::endl;
//    std::cout << "lable " << lable["aOOT:"] << std::endl;

}
