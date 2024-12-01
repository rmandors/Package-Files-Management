#include <string>
#include <stdexcept>
#include "OvernightPackage.h"

OvernightPackage::OvernightPackage(std::string _id, std::string nm_s, std::string nm_r, std::string ad_s, std::string ad_r, 
                                   std::string ct_s, std::string ct_r, std::string st_s, std::string st_r, int zc_s, int zc_r, 
                                   double wg, double co, double of) : Package(_id, nm_s, nm_r, ad_s, ad_r, ct_s, ct_r, st_s, st_r, 
                                   zc_s, zc_r, wg, co){
     setOvernightFeePerOunce(of);
}

void OvernightPackage::setOvernightFeePerOunce(double of){
     if(of>0 && of<=100){
          overnightFeePerOunce = of;
     }
     else{
          throw std::invalid_argument("Invalid Overnight Fee per Once");
     }
}

double OvernightPackage::getOvernightFeePerOunce() const{
     return overnightFeePerOunce;
}

double OvernightPackage::calculateCost() const{
     double newCostPerOunce = getCostPerOunce() + getOvernightFeePerOunce(); 	
     return (newCostPerOunce * getWeight()); 	
}

void OvernightPackage::print(std::ostream& out) const{
     out << "ID: " << getID()
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
         << "\nOvernight Fee per Ounce: " << getOvernightFeePerOunce()
         << "\nShipping Cost: " << calculateCost()<<std::endl;
}

std::istream& operator>>(std::istream& in, OvernightPackage& p){
        double overnightFee;
        
        std::cin >> static_cast<Package&>(p);  

        std::cout << "Enter Overnight Fee per Ounce: ";
        in >> overnightFee;
        p.setOvernightFeePerOunce(overnightFee);

        return in;
}


