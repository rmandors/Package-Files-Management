#include <string>
#include "Package.h"

#ifndef TWODAYPACKAGE_H
#define TWODAYPACKAGE_H

class TwoDayPackage : public Package{
	 public:
        TwoDayPackage(std::string, std::string, std::string, std::string, std::string, 
          		      std::string, std::string, std::string, std::string, int, int, double, 
          		      double, double);
	  
	  	void setFlatFeeForTwoDays(double);
	  	double getFlatFeeForTwoDays() const;
	  
	  	double calculateCost() const override;
		void print(std::ostream&) const override;

     private:
          double flatFeeForTwoDays; 
};

#endif