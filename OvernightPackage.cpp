#include <string>
#include <stdexcept>
#include "OvernightPackage.h"

OvernightPackage::OvernightPackage(std::string _id, std::string nm_s, std::string nm_r, std::string ad_s, std::string ad_r, 
                                   std::string ct_s, std::string ct_r, std::string st_s, std::string st_r, int zc_s, int zc_r, 
                                   double wg, double co, double of) : Package(_id, nm_s, nm_r, ad_s, ad_r, ct_s, ct_r, st_s, st_r, 
                                   zc_s, zc_r, wg, co){
     setOvernightFeePerOnce(of);
}

void OvernightPackage::setOvernightFeePerOnce(double of){
     if(of>0 && of<=100){
          overnightFeePerOnce = of;
     }
     else{
          throw std::invalid_argument("Invalid Overnight Fee per Once");
     }
}

double OvernightPackage::getOvernightFeePerOnce() const{
     return overnightFeePerOnce;
}

double OvernightPackage::calculateCost() const{
     double newCostPerOnce = getCostPerOnce() + getOvernightFeePerOnce(); 	
     return (newCostPerOnce * getWeight()); 	
}
