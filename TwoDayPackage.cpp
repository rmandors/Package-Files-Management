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
     if(ff>0 && ff<=100){
          flatFeeForTwoDays = ff;
     }
     else{
          throw std::invalid_argument("Invalid Flat Fee for two days");
     }
}

double TwoDayPackage::getFlatFeeForTwoDays() const{
     return flatFeeForTwoDays;
}

double TwoDayPackage::calculateCost() const{
     return(Package::calculateCost() + flatFeeForTwoDays);	
}


