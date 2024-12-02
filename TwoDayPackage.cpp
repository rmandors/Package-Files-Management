#include <string>
#include <stdexcept>
#include "TwoDayPackage.h"

TwoDayPackage::TwoDayPackage(std::string _id, std::string nm_s, std::string nm_r, std::string ad_s, std::string ad_r, 
                             std::string ct_s, std::string ct_r, std::string st_s, std::string st_r, int zc_s, int zc_r, 
                             double wg, double co, double ff) : Package(_id, nm_s, nm_r, ad_s, ad_r, ct_s, ct_r, st_s, 
                             st_r, zc_s, zc_r, wg, co){
     setFlatFeeForTwoDays(ff);
}

void TwoDayPackage::setFlatFeeForTwoDays(double ff){
     if(ff>0){
          flatFeeForTwoDays = ff;
     }
     else{
          throw std::invalid_argument("Invalid Flat Fee for two days");
     }
}

double TwoDayPackage::getFlatFeeForTwoDays() const{
     return flatFeeForTwoDays;
}

// Override the calculateCost method to include the flat fee for two days
double TwoDayPackage::calculateCost() const{
     return(Package::calculateCost() + flatFeeForTwoDays);	
}

// Override the print method to also display the flat fee for two days
void TwoDayPackage::print(std::ostream& out) const{
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
         << "\nFlat Fee for Two Days: " << getFlatFeeForTwoDays()
         << "\nShipping Cost: " << calculateCost()<<std::endl;
}

std::istream& operator>>(std::istream& in, TwoDayPackage& p){
        double twoDaysFlatFee;

        // Calls the base class operator>> to read common fields
        std::cin >> static_cast<Package&>(p);  

        // Reads the additional flat fee for two days
        std::cout << "Enter Flat Fee for Two Days: ";
        in >> twoDaysFlatFee;
        p.setFlatFeeForTwoDays(twoDaysFlatFee);

        return in;
}
