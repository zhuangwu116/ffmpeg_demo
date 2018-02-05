#include "Person.pb.h"
#include <iostream>
#include <fstream>

using namespace std;

void ListPeople(const mamage::AddressBook& address_book);
int main(int argc, char* argv[])
{
    if(2!=argc)
    {
        cerr<<"Usage: "<<argv[0] << "ADDRESS_BOOK_FILE" <<endl;
        return -1;
    }

    fstream in("ADDRESS_BOOK_FILE", ios::in | ios::binary);

    mamage::AddressBook address_book;
    if(!address_book.ParseFromIstream(&in))
    {
        cerr << "Parse Input File failed!"<<endl;
        return -1;
    }

    ListPeople(address_book);
    google::protobuf::ShutdownProtobufLibrary();
    return 0;
}

void ListPeople(const mamage::AddressBook& address_book)
{
    for(int i=0;i<address_book.person_size();i++)
    {
        const mamage::Person& person = address_book.person(i);
        cout<<"Person ID: "<<person.id();
        cout<<"Name: "<<person.name();
        cout<<"Email: "<<person.email();
        
        for(int j=0; j<person.phone_size();j++)
        {
            const mamage::Person::PhoneNumber& phone_number = person.phone(j);
            switch(phone_number.type())
            {
                case mamage::Person::MOBILE:
                    cout<< "Mobile phone #: ";
                    break;
                case mamage::Person::HOME:
                    cout<<" Home phone #: ";
                    break;
                case mamage::Person::WORK:
                    cout<< " Work phone #: ";
                    break;
            }
            cout <<phone_number.number()<<endl;
        }
    }
}
