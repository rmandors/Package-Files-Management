/*
2 Diciembre 2024
Proyecto Final
NRC: 1422
Diogo Coral - 00336376	
Raymond Portilla - 00335050
*/

#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <memory>
#include "Package.h"
#include "TwoDayPackage.h"
#include "OvernightPackage.h"
using namespace std;

void displayMenu();
void mapDataFromCSVfile(map<string, unique_ptr<Package>>&);
void displayMapData(map<string, unique_ptr<Package>>&);

int main(){
	map<string, unique_ptr<Package>> packages;
	char menuChoice;

	do{
		displayMenu();

		cout << "Your choice: ";
		cin >> menuChoice;

		switch (menuChoice){
			case '1':
				mapDataFromCSVfile(packages);
				break;
	
			case '2':
				displayMapData(packages);
				break;
			
			case '3':

				break;
			
			case '4':
			
				break;	
			
			case '5':
			
				break;

			case '6':
			
				break;

			case '7':
			
				break;
	
			case '8':
				cout << "Exiting..." <<endl ;
				break;
	
			default:
				cout << "Please enter a valid option!" << endl << endl;
				break;
		}

	}while(menuChoice != '8');

	return 0;
}

void displayMenu(){
	cout << "\t\t.:MENU:." << endl
		 << "[1] Load Packages Data from CSV file to a Map." << endl
	     << "[2] Display Packages Information from the Map." << endl
		 << "[3] Save Packages Data in a Binary File." << endl
		 << "[4] Empty Packages Map." << endl
		 << "[5] Load Packages Data from a Binary File to a Map." << endl
		 << "[6] Display Packages ordered by their Type." << endl 
		 << "[7] Display Packages ordered by their Shipping Cost." << endl
		 << "[8] Exit." << endl << endl;
}

void mapDataFromCSVfile(map<string, unique_ptr<Package>>& packages){
	ifstream file("initialData.csv", ios::in);
	if(!file){
		cerr << "File could not be opened." << endl;
		exit(EXIT_FAILURE);
	}

	string row;
	getline(file, row);

	while (getline(file, row)) {
        stringstream ss(row);

        string id, name_sender, name_recipient, address_sender, address_recipient, city_sender, 
		       city_recipient, state_sender, state_recipient, zipCode_senderStr, zipCode_recipientStr, 
			   weightStr, costPerOnceStr, flatFeeForTwoDaysStr, overnightFeePerOnceStr;

        getline(ss, id, ',');
        getline(ss, name_sender, ',');
        getline(ss, name_recipient, ',');
        getline(ss, address_sender, ',');
		getline(ss, address_recipient, ',');
		getline(ss, city_sender, ',');
		getline(ss, city_recipient, ',');
		getline(ss, state_sender, ',');
		getline(ss, state_recipient, ',');
		getline(ss, zipCode_senderStr, ',');
		getline(ss, zipCode_recipientStr, ',');
		getline(ss, weightStr, ',');
		getline(ss, costPerOnceStr, ',');
		getline(ss, flatFeeForTwoDaysStr, ',');
		getline(ss, overnightFeePerOnceStr, ',');

		int zipCode_sender = stoi(zipCode_senderStr);
		int zipCode_recipient = stoi(zipCode_recipientStr);
        double weight = stod(weightStr);
        double costPerOnce = stod(costPerOnceStr);
		double flatFeeForTwoDays = stod(flatFeeForTwoDaysStr);
		double overnightFeePerOnce = stod(overnightFeePerOnceStr);

		if(flatFeeForTwoDays == 0 && overnightFeePerOnce == 0)
        	packages[id] = make_unique<Package>(id, name_sender, name_recipient, address_sender, address_recipient, 
												city_sender, city_recipient, state_sender, state_recipient, zipCode_sender, 
												zipCode_recipient,weight, costPerOnce);
		else if(overnightFeePerOnce == 0)
			packages[id] = make_unique<TwoDayPackage>(id, name_sender, name_recipient, address_sender, address_recipient, 
			                   						  city_sender, city_recipient, state_sender, state_recipient, zipCode_sender, 
													  zipCode_recipient, weight, costPerOnce, flatFeeForTwoDays);
		else
		    packages[id] = make_unique<OvernightPackage>(id, name_sender, name_recipient, address_sender, address_recipient, 
													     city_sender, city_recipient, state_sender, state_recipient, zipCode_sender, 
													     zipCode_recipient, weight, costPerOnce, overnightFeePerOnce);
    }

	cout << "Data has been correctly loaded!" << endl << endl;
    file.close();
} 

void displayMapData(map<string, unique_ptr<Package>>& packages){
    double totalShippingCost = 0;
	
	for (const auto& [id, package] : packages) {
        cout << *package << endl;
		totalShippingCost += package->calculateCost();
    }

	cout << "Total Shipping Cost: " << totalShippingCost << endl << endl;
}