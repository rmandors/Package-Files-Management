#include <iostream>
#include <string>

#ifndef PACKAGE_H
#define PACKAGE_H

class Package{
		friend std::ostream& operator<<(std::ostream&, const Package&);
		friend std::istream& operator>>(std::istream&, Package&);

    public:
        Package(std::string, std::string, std::string, std::string, std::string,
          	    std::string, std::string, std::string, std::string, int, int, double, double);

	  	virtual ~Package() = default;

	  	void setID(std::string);
	  	void setSenderName(std::string);
	  	void setRecipientName(std::string);
	  	void setSenderAddress(std::string);
	  	void setRecipientAddress(std::string);
	  	void setSenderCity(std::string);
	  	void setRecipientCity(std::string);
	  	void setSenderState(std::string);
		void setRecipientState(std::string);
  		void setSenderZipCode(int);
  		void setRecipientZipCode(int);
		void setWeight(double);
	  	void setCostPerOunce(double);

	  	std::string getID() const;
	  	std::string getSenderName() const;
	  	std::string getRecipientName() const;
	  	std::string getSenderAddress() const;
	  	std::string getRecipientAddress() const;
	  	std::string getSenderCity() const;
	  	std::string getRecipientCity() const;
	  	std::string getSenderState() const;
	  	std::string getRecipientState() const;
	  	int getSenderZipCode() const;
	  	int getRecipientZipCode() const;
	  	double getWeight() const;
	  	double getCostPerOunce() const;

	  	bool operator>(const Package&) const;
	  	bool operator>=(const Package&) const;
	  	bool operator==(const Package&) const;
	  	bool operator!=(const Package&) const;

	  	virtual double calculateCost() const;
		virtual void print(std::ostream&) const;
    
    private:
    	std::string id;
    	std::string name_sender;
    	std::string name_recipient;
	  	std::string address_sender;
	  	std::string address_recipient;
	  	std::string city_sender;
	  	std::string city_recipient;
	  	std::string state_sender;
	  	std::string state_recipient;
	  	int zipCode_sender;
	  	int zipCode_recipient;
    	double weight;
	  	double costPerOunce; 
};

#endif
