#include <string>
#include "Package.h"

#ifndef OVERNIGHTPACKAGE_H
#define OVERNIGHTPACKAGE_H

class OvernightPackage : public Package{
	public:
          OvernightPackage(std::string, std::string, std::string, std::string, std::string, 
          			       std::string, std::string, std::string, std::string, int, int, 
          			       double, double, double);
	
	  	void setOvernightFeePerOnce(double);
	  	double getOvernightFeePerOnce() const;

	  	double calculateCost() const override;

     private:
       	double overnightFeePerOnce; 
};

#endif