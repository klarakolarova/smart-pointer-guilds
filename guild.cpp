#include<string>
#include<memory>
#include<vector>
#include<iostream>
#include<algorithm>
#include<map>
#include "guild.h"
#include "license.h"
#include "person.h"


using namespace std;

//CONSTRUCTOR
Guild::Guild (string new_name, unsigned int new_fee, unsigned int new_salary, const vector<shared_ptr<Person>>& new_members): name(new_name), fee(new_fee), salary(new_salary), members({}) {

    if (name.size() == 0 || fee == 0 || salary == 0) throw runtime_error ("Guild constructor failed");
    //check for duplicates in members
    for (const auto& member: new_members) {
        if (members.count(member->get_name()) != 0) throw runtime_error ("Guild constructor - member multiplicity");
        else members[member->get_name()] = member;
    }
}


//ADD_MEMBER
bool Guild::add_member(shared_ptr<Person> p) {
    if (members.count(p->get_name()) != 0) return false;
    members[p->get_name()] = p; return true;
}

//REMOVE_MEMBER
bool Guild::remove_member(string n){
    if (members.count(n) == 0) return false;
    members.erase(n); return true;
}

//GRANT_LICENSE
void Guild::grant_license(string n){

    if (members.count(n) == 0) throw runtime_error ("grant_licence failed, this person is not a member");

    auto person = (members.find(n))->second; //shared pointer to person

    if (person->pay_fee(this->fee) == false) throw runtime_error ("license cannot be granted, unsufficient wealth");

    person->receive_license(make_unique<License>(this->name, this->salary));

}

//OFFER_JOB
bool Guild::offer_job(shared_ptr<Person> p) const{

    //members work for 2x salary
    if (members.count(p->get_name()) == 1) {
        p->work(2* this->salary);
        return true;
    }

    else {
        if (p->eligible(this->name) == false) return false; //non-members without license return false
        else{
            p->work(this->name);  //non-members work for guild
            return true;
        }
    }
}


//PRINT
ostream& Guild::print(ostream& o) const {
    o<< "[" << name << ", License fee: " << fee << ", Job salary: " << salary << ", {";

    bool first = true;
    for (auto it = members.begin(); it != members.end(); it++) {
      if (first) first = false;
      else o<< ", ";

      o<<it->first;
    }

    o<< "}]";
    return o;
}


//OPERATOR <<
ostream& operator << (ostream& o, const Guild& prt_guild) {
    return prt_guild.print(o);
}
