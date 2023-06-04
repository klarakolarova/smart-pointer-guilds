#ifndef PERSON_H
#define PERSON_H
#include<string>
#include<memory>
#include<iostream>
#include<map>

class License;

using namespace std;

class Person{

    private:

    string name;
    unsigned int wealth;
    map<string, unique_ptr<License>> licenses;

    public:

    Person (string, unsigned int = 0); //Person(string name, unsigned int wealth = 0)
    virtual ~Person() = default;

    void work (string);
    virtual void work(unsigned int) = 0;
    void increase_wealth(unsigned int);
    string get_name() const;
    bool pay_fee(unsigned int);
    void receive_license(unique_ptr<License>);
    void transfer_license(string, shared_ptr<Person>);
    bool eligible(string) const;

    virtual ostream& print (ostream&) const;

};


class Worker: public Person {

    public:

    Worker(string, unsigned int = 0);

    void work (unsigned int);

    ostream& print(ostream& o) const;

};


class Superworker: public Person {

    private:
    unsigned int fee;

    public:

    Superworker(unsigned int, string, unsigned int = 0); //fee, name, wealth

    void work (unsigned int);

    ostream& print (ostream& o) const;
};


ostream& operator << (ostream&, const Person&);


#endif
