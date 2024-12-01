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
#include <algorithm>
#include <map>
#include <memory>
#include "Package.h"
#include "TwoDayPackage.h"
#include "OvernightPackage.h"
using namespace std;

void displayMenu();
void loadMapDataFromCSVfile(map<string, Package*>&);
void displayMapData(map<string, Package*>&);
void saveMapDataToBinaryFile(map<string, Package*>&);
void loadMapDataFromBinaryFile(map<string, Package*>&);
void displayPackagesByType(map<string, Package*>&);
void displayPackagesByCost(map<string, Package*>&);
void extractAndModifyPackage(map<string, Package*>&);

int main(){
	map<string, Package*> packages;
	char menuChoice;

	do{
		displayMenu();

		cout << "Your choice: ";
		cin >> menuChoice;

		switch (menuChoice){
			case '1':
				loadMapDataFromCSVfile(packages);
				break;
	
			case '2':
				displayMapData(packages);
				break;
			
			case '3':
				saveMapDataToBinaryFile(packages);
				break;
			
			case '4':
				for (auto& [id, package] : packages){
    				delete package;
				}
				packages.clear();
				cout << "The map has been emptied." << endl << endl;
				break;	
			
			case '5':
				loadMapDataFromBinaryFile(packages);
				break;

			case '6':
				displayPackagesByType(packages);
				break;

			case '7':
				displayPackagesByCost(packages);
				break;

			case '8':
				extractAndModifyPackage(packages);
				break;
	
			case '9':
				cout << "Exiting..." <<endl ;
				break;
	
			default:
				cout << "Please enter a valid option!" << endl << endl;
				break;
		}

	}while(menuChoice != '9');

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
		 << "[8] Extract and Modify a Package." << endl
		 << "[9] Exit." << endl << endl;
}

void loadMapDataFromCSVfile(map<string, Package*>& packages){
	if(packages.empty()){
		ifstream file("initialData.csv", ios::in);
		if(!file){
			cerr << "File could not be opened." << endl;
			exit(EXIT_FAILURE);
		}

		string row;
		getline(file, row);

		while(getline(file, row)) {
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
        		packages[id] = new Package(id, name_sender, name_recipient, address_sender, address_recipient, 
										   city_sender, city_recipient, state_sender, state_recipient, zipCode_sender, 
										   zipCode_recipient,weight, costPerOnce);
			else if(overnightFeePerOnce == 0)
				packages[id] = new TwoDayPackage(id, name_sender, name_recipient, address_sender, address_recipient, 
			                   					 city_sender, city_recipient, state_sender, state_recipient, zipCode_sender, 
												 zipCode_recipient, weight, costPerOnce, flatFeeForTwoDays);
			else
		    	packages[id] = new OvernightPackage(id, name_sender, name_recipient, address_sender, address_recipient, 
												   city_sender, city_recipient, state_sender, state_recipient, zipCode_sender, 
												   zipCode_recipient, weight, costPerOnce, overnightFeePerOnce);
    	}
	
		cout << "Data has been correctly loaded!" << endl << endl;
    	file.close();
	}
	else{
		cout << "The map already contains information. Empty the map, then try again!" << endl << endl;
	}
} 

void displayMapData(map<string, Package*>& packages){
	if(!packages.empty()){
    	double totalShippingCost = 0;
	
		for (const auto& [id, package] : packages) {
    		cout << endl << *package;
			totalShippingCost += package->calculateCost();
    	}

		cout << endl << "Total Shipping Cost: " << totalShippingCost << endl << endl;
	}
	else{
		cout << "The map is empty." <<endl << endl;
	}
}

void saveMapDataToBinaryFile(map<string, Package*>& packages){
	if(!packages.empty()){

	}
	else{
		cout << "The map is empty." << endl << endl;
	}	
}

void loadMapDataFromBinaryFile(map<string, Package*>& packages){
	if(packages.empty()){

	}
	else{
		cout << "The map already contains information. Empty the map, then try again!" << endl << endl;
	}
}

void displayPackagesByType(map<string, Package*>& packages){
    if(!packages.empty()){
        vector<Package*> packageType;
        vector<TwoDayPackage*> twoDayPackageType;
        vector<OvernightPackage*> overnightPackageType;

        for(const auto& [id, package] : packages){
            if(auto p = dynamic_cast<TwoDayPackage*>(package))
                twoDayPackageType.push_back(p); 
            else if(auto p = dynamic_cast<OvernightPackage*>(package))
                overnightPackageType.push_back(p); 
			else if(auto p = dynamic_cast<Package*>(package))
                packageType.push_back(p);
        }

        if(!packageType.empty()){
            cout << "\n.:Packages of Type 'Package':." << endl << endl;
            for(const auto& package : packageType){
                cout << *package << endl;
            }
        }

        if(!twoDayPackageType.empty()){
            cout << "\n.:Packages of Type 'TwoDayPackage':." << endl << endl;
            for(const auto& package : twoDayPackageType){
                cout << *package << endl;
            }
        }

        if(!overnightPackageType.empty()){
            cout << "\n.:Packages of Type 'OvernightPackage':." << endl << endl;
            for(const auto& package : overnightPackageType){
                cout << *package << endl;
            }
        }

        cout << endl;
    }
	else{
		cout << "The map is empty." <<endl << endl;
	}
}

void displayPackagesByCost(map<string, Package*>& packages){
   if (!packages.empty()) {
        vector<Package*> sortedPackages;

        for (auto& [id, package] : packages){
            sortedPackages.push_back(new Package(*package)); 
        }

        sort(sortedPackages.begin(), sortedPackages.end(), [](const Package* a, const Package* b){
            return a->calculateCost() > b->calculateCost();
        });

        for (auto& package : sortedPackages) {
            cout << endl << *package;
            delete package;  
        }

        cout << endl;;
    }
	else{
		cout << "The map is empty." <<endl << endl;
	}
}

void extractAndModifyPackage(map<string, Package*>& packages){
	int num, user_id;
	cout << "Enter the number of packages you want modify: ";
	cin >> num;
	
	for(int i=0; i<num; i++){

		cout << "Enter the id of the package you want to modify: ";
		cin >> user_id;
	}
}
