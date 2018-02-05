#include "Person.pb.h"
#include <fstream>
#include <iostream>

using namespace std;

void PromptForAddress(mamage::Person*);

int main(int argc, char* argv[])
{
    GOOGLE_PROTOBUF_VERIFY_VERSION;
    if(2!=argc)
    {
        cerr <<"Usage: "<<argv[0]<<" ADDRESS_BOOK_FILE" <<endl;
        return -1;
    }

    mamage::AddressBook address_book;

/*    fstream in("ADDRESS_BOOK_FILE",ios::binary | ios::in);
    if(!in)
    {
        cerr<<"open file ADDRESS_BOOK_FILE failed!\n";
        return -1;
    }
    if(!address_book.ParseFromIstream(&in))
    {
        cerr <<"Parse File ADDRESS_BOOK_FILE failed!\n";
        return -1;
    }

    in.close();*/

    PromptForAddress(address_book.add_person());

    fstream out("ADDRESS_BOOK_FILE", ios::binary | ios::out | ios::trunc);

    if(!address_book.SerializeToOstream(&out))
    {
        cerr << "Failed to Write Address Book!\n";
        return -1;
    }
    google::protobuf::ShutdownProtobufLibrary();
    return 0;
}


void PromptForAddress(mamage::Person* person)
{
    cout<<"Enter a Person ID number:";
    int id;
    cin>>id;
    person->set_id(id);
    cin.ignore(256,'\n');
    cout<<"Enter name: ";
    getline(cin,*person->mutable_name());

    cout<<"Enter email address (blank for none): ";

    string email;
    getline(cin,email);
    if(!email.empty())
    {
        person->set_email(email);
    }
    while(true)
    {
        cout<<"Enter a phone number (or leave blank to finish): ";
        string number;
        getline(cin,number);
        if(number.empty())
            break;
        mamage::Person::PhoneNumber* phone_number = person->add_phone();

        phone_number->set_number(number);
        cout<<"Is this a mobile, home, or work phone? ";

        string type;
        getline(cin,type);
        if(type == "mobile")
            phone_number->set_type(mamage::Person::MOBILE);
        else if(type=="home")
            phone_number->set_type(mamage::Person::HOME);
        else if(type=="work")
            phone_number->set_type(mamage::Person::WORK);
        else
        {
            cout<< "Unknown phone type. Using default." << endl;
            phone_number->set_type(mamage::Person::HOME);
        }
    }

}
