#include<string>
#include<memory>
#include<iostream>
#include<map>
#include "person.h"
#include "license.h"


using namespace std;


//CLASS PERSON ///////////////////////////////////////////////////////////////////////

  Person::Person (string new_name, unsigned int new_wealth): name(new_name), wealth(new_wealth), licenses() {
          if (name.size() == 0) throw runtime_error ("Person constructor failed");
  }


  //WORK(string)
  void Person::work (string guild) {

    if (licenses.count(guild) == 0) throw runtime_error ("work failed, no license with this guildname");

    else if (licenses.find(guild)->second->valid()) {
      licenses.find(guild)->second->use();
      work((licenses.find(guild)->second)->get_salary()); //work(unsigned int)
     }
    else throw runtime_error("work failed, license is invalid");

  }


    //INCREASE WEALTH (setter)
    void Person::increase_wealth(unsigned int i) {
        wealth += i;
    }

    //GET_NAME
    string Person::get_name() const {
        return name;
    }

   //PAY_FEE (person must have enough money and fee can't be 0)
    bool Person::pay_fee(unsigned int i){
        if (i==0 || i> wealth) return false;
        wealth -= i;
        return true;
    }

    // RECEIVE_LICENSE (adds new license or replaces old one)
    void Person::receive_license(unique_ptr<License> l){

        if (licenses.count(l->get_guildname()) == 1) {
            licenses.erase(l->get_guildname());
        }

        licenses[l->get_guildname()] = move(l);
    }

    //TRANSFER LICENSE
    void Person::transfer_license(string l, shared_ptr<Person> p){

        if (licenses.count(l) == 0) throw runtime_error ("transfer not possible, source-person doesnt own such license");

         if (p->get_name() != this->get_name()) {
         p->licenses[l] = move(licenses.find(l)->second);
         licenses.erase(l);
         }
    }

    //ELIGIBLE (true if person owns valid license named l)
    bool Person::eligible(string l) const {
        if (licenses.count(l) == 0) return false;
        return (licenses.find(l)->second)->valid();
    }


    //PRINT
    ostream& Person::print(ostream& o) const {

        o<< name << ", " << wealth << " Coins, {";

        bool first = true;
        for(auto it = licenses.begin(); it != licenses.end(); it++) {
            if (first == true) first = false;
            else cout<<", ";

            it->second->print(o);
        }

        o<<"}]";
        return o;
    }

////////////////////////////////////////////////////////////////////////////////////////////

//CLASS WORKER //////////////////////////////////////////////////////////////////////////////////

    Worker::Worker(string new_name, unsigned int new_wealth): Person(new_name, new_wealth) {
    }


   //WORK
    void Worker::work (unsigned int i){
        Person::increase_wealth(i);
    }

    //PRINT
    ostream& Worker::print (ostream& o) const {
        o<< "[Worker ";
        Person::print(o);
        return o;
    }

////////////////////////////////////////////////////////////////////////////////////////

//CLASS SUPERWORKER ///////////////////////////////////////////////////////////////////

    Superworker::Superworker(unsigned int new_fee, string new_name, unsigned int new_wealth): Person(new_name, new_wealth){
      fee = new_fee;
    }

    //WORK
    void Superworker::work (unsigned int i) {
        Person::increase_wealth(i+fee);
    }

    //PRINT
    ostream& Superworker::print(ostream& o) const {
        o<<"[Superworker ";
        Person::print(o);
        return o;
    }

//////////////////////////////////////////////////////////////////////////////////////


//OPERATOR <<
ostream& operator << (ostream& o, const Person& prtperson) {
    return prtperson.print(o);
}
