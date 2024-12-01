#include "Package.h"
#include <stdexcept>

Package::Package(std::string _id, std::string nm_s, std::string nm_r, std::string ad_s, std::string ad_r, std::string ct_s,
	            std::string ct_r, std::string st_s, std::string st_r, int zc_s, int zc_r, double wg, double co){
     setID(_id);
     setSenderName(nm_s);
     setRecipientName(nm_r);
     setSenderAddress(ad_s);
     setRecipientAddress(ad_r);
     setSenderCity(ct_s);
     setRecipientCity(ct_r);
     setSenderState(st_s);
     setRecipientState(st_r);
     setSenderZipCode(zc_s);
     setRecipientZipCode(zc_r);
     setWeight(wg);
     setCostPerOunce(co);
}

void Package::setID(std::string _id){
     if(_id.length()>0 && _id.length()<=15){
          id = _id;
     }
     else{
          throw std::invalid_argument("Invalid ID");
     }
}

void Package::setSenderName(std::string nm_s){
     if(nm_s.length()>0 && nm_s.length()<=40){
          name_sender = nm_s;
     }
     else{
          throw std::invalid_argument("Invalid Sender Name");
     }
}

void Package::setRecipientName(std::string nm_r){
     if(nm_r.length()>0 && nm_r.length()<=40){
          name_recipient = nm_r;
     }
     else{
          throw std::invalid_argument("Invalid Recipient Name");
     }
}

void Package::setSenderAddress(std::string ad_s){
     if(ad_s.length()>0 && ad_s.length()<=50){
          address_sender = ad_s;
     }
     else{
          throw std::invalid_argument("Invalid Sender Address");
     }
}

void Package::setRecipientAddress(std::string ad_r){
     if(ad_r.length()>0 && ad_r.length()<=50){
          address_recipient = ad_r;
     }
     else{
          throw std::invalid_argument("Invalid Recipient Address");
     }
}

void Package::setSenderCity(std::string ct_s){
     if(ct_s.length()>0 && ct_s.length()<=30){
          city_sender = ct_s;
     }
     else{
          throw std::invalid_argument("Invalid Sender City");
     }
}

void Package::setRecipientCity(std::string ct_r){
     if(ct_r.length()>0 && ct_r.length()<=30){
          city_recipient = ct_r;
     }
     else{
          throw std::invalid_argument("Invalid Recipient City");
     }
}

void Package::setSenderState(std::string st_s){
     if(st_s.length()>0 && st_s.length()<=30){
          state_sender = st_s;
     }
     else{
          throw std::invalid_argument("Invalid Sender State");
     }
}

void Package::setRecipientState(std::string st_r){
     if(st_r.length()>0 && st_r.length()<=30){
          state_recipient = st_r;
     }
     else{
          throw std::invalid_argument("Invalid Recipient State");
     }
}

void Package::setSenderZipCode(int zc_s){
     if(zc_s>0 && zc_s<=999999){
          zipCode_sender = zc_s;
     }
     else{
          throw std::invalid_argument("Invalid Sender Zip Code");
     }
}

void Package::setRecipientZipCode(int zc_r){
     if(zc_r>0 && zc_r<=999999){
          zipCode_recipient = zc_r;
     }
     else{
          throw std::invalid_argument("Invalid Recipient Zip Code");
     }
}

void Package::setWeight(double wg){
     if(wg>0 && wg<=10000){
          weight = wg;
     }
     else{
          throw std::invalid_argument("Invalid Weight");
     }
}

void Package::setCostPerOunce(double co){
     if(co>0 && co<=500){
          costPerOunce = co;
     }
     else{
          throw std::invalid_argument("Invalid Cost per Once");
     }
}

std::string Package::getID() const{
     return id;
}

std::string Package::getSenderName() const{
     return name_sender;
}

std::string Package::getRecipientName() const{
     return name_recipient;
}

std::string Package::getSenderAddress() const{
     return address_sender;
}

std::string Package::getRecipientAddress() const{
     return address_recipient;
}

std::string Package::getSenderCity() const{
     return city_sender;
}

std::string Package::getRecipientCity() const{
     return city_recipient;
}

std::string Package::getSenderState() const{
     return state_sender;
}

std::string Package::getRecipientState() const{
     return state_recipient;
}
	 
int Package::getSenderZipCode() const{
     return zipCode_sender;
}

int Package::getRecipientZipCode() const{
     return zipCode_recipient;
}

double Package::getWeight() const{
     return weight;
}

double Package::getCostPerOunce() const{
     return costPerOunce;
}

double Package::calculateCost() const{
     return (getWeight() * getCostPerOunce());
}

bool Package::operator>(const Package& right) const{
    return calculateCost() > right.calculateCost();
}

bool Package::operator>=(const Package& right) const{
     return calculateCost() >= right.calculateCost();
}

bool Package::operator==(const Package& right) const{ 
     return calculateCost() == right.calculateCost();
}

bool Package::operator!=(const Package& right) const{
     return calculateCost() != right.calculateCost();  
}

std::ostream& operator<<(std::ostream& out, const Package& p){
     p.print(out);
     return out;
}

void Package::print(std::ostream& out) const{
     out << "ID: "<< getID()
         << "\nSender Name: " << getSenderName()
         << "\nRecipient Name: " << getRecipientName()
         << "\nSender Address: " << getSenderAddress()
         << "\nRecipient Address: " << getRecipientAddress()
         << "\nSender City: " << getSenderCity()
         << "\nRecipient City: " << getRecipientCity()
         << "\nSender State: " << getSenderState()
         << "\nRecipient State: " << getRecipientState()
         << "\nSender ZIP Code: " << getSenderZipCode()
         << "\nRecipient ZIP Code: " << getRecipientZipCode()
         << "\nWeight: " << getWeight()
         << "\nCost per Once: " << getCostPerOunce()
         << "\nShipping Cost: " << calculateCost()<<std::endl;
}

std::istream& operator>>(std::istream& in, Package& p){
     std::string id, senderName, recipientName, senderAddress, recipientAddress,
            senderCity, recipientCity, senderState, recipientState;
     int senderZipCode, recipientZipCode;
     double weight, costPerOunce;
     
     std::cout << "Enter ID: ";
     in >> id;
     p.setID(id);
     in.ignore(); 

     std::cout << "Enter Sender Name: ";
     std::getline(in, senderName);
     p.setSenderName(senderName);

     std::cout << "Enter Recipient Name: ";
     std::getline(in, recipientName);
     p.setRecipientName(recipientName);

     std::cout << "Enter Sender Address: ";
     std::getline(in, senderAddress);
     p.setSenderAddress(senderAddress);

     std::cout << "Enter Recipient Address: ";
     std::getline(in, recipientAddress);
     p.setRecipientAddress(recipientAddress);

     std::cout << "Enter Sender City: ";
     std::getline(in, senderCity);
     p.setSenderCity(senderCity);

     std::cout << "Enter Recipient City: ";
     std::getline(in, recipientCity);
     p.setRecipientCity(recipientCity);

     std::cout << "Enter Sender State: ";
     std::getline(in, senderState);
     p.setSenderState(senderState);

     std::cout << "Enter Recipient State: ";
     std::getline(in, recipientState);
     p.setRecipientState(recipientState);

     std::cout << "Enter Sender ZIP Code: ";
     in >> senderZipCode;
     p.setSenderZipCode(senderZipCode);

     std::cout << "Enter Recipient ZIP Code: ";
     in >> recipientZipCode;
     p.setRecipientZipCode(recipientZipCode);

     std::cout << "Enter Weight: ";
     in >> weight;
     p.setWeight(weight);

     std::cout << "Enter Cost per Ounce: ";
     in >> costPerOunce;
     p.setCostPerOunce(costPerOunce);

     return in;
}

