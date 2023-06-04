#include<string>
#include<memory>
#include<iostream>
#include "license.h"

using namespace std;

//CONSTRUCTOR
License::License (string new_name, unsigned int new_salary): name(new_name), salary(new_salary) {

    if (name.size() == 0 || salary == 0) throw runtime_error ("License Constructor failed");
    counter = 0;
}

//GET_GUILDNAME
string License::get_guildname() const {
    return name;
}

//GET_SALARY
unsigned int License::get_salary() const {
    return salary;
}

//VALID (used <= 3 times)
bool License::valid() const {
    return counter<= 3;
}

//USE (used if valid, else false)
bool License::use(){
    if (this->valid()) {
        counter++;
        return true;
    }
    return false;
}

//PRINT
ostream& License::print (ostream& o) const{
    o << "[License for " << name << ", Salary: " << salary << ", Used: " << counter << "]";
    return o;
}

//OPERATOR <<
ostream& operator<< (ostream& o, const License& prtlicense) {
    return prtlicense.print(o);
}
