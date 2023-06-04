#ifndef GUILD_H
#define GUILD_H
#include<string>
#include<memory>
#include<vector>
#include<iostream>
#include<map>

class Person;
class License;

using namespace std;

class Guild{

    private:

    string name;
    unsigned int fee;
    unsigned int salary;
    map<string, shared_ptr<Person>> members;

    public:

    //Guild(string name, unsigned int fee, unsigned int salary, vector<shared_ptr<Person>>& members = {})
    Guild (string, unsigned int, unsigned int, const vector<shared_ptr<Person>>& = {});

    bool add_member(shared_ptr<Person>);
    bool remove_member(string);
    void grant_license(string);
    bool offer_job(shared_ptr<Person>) const;

    ostream& print(ostream&) const;

};

ostream& operator << (ostream&, const Guild&);



#endif
