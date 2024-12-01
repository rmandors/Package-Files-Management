#include "functions.h"
using namespace std;

void displayMenu(){
	cout << "\t\t    .:MENU:." << endl
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
			       weightStr, costPerOunceStr, flatFeeForTwoDaysStr, overnightFeePerOunceStr;

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
			getline(ss, costPerOunceStr, ',');
			getline(ss, flatFeeForTwoDaysStr, ',');
			getline(ss, overnightFeePerOunceStr, ',');

			int zipCode_sender = stoi(zipCode_senderStr);
			int zipCode_recipient = stoi(zipCode_recipientStr);
        	double weight = stod(weightStr);
        	double costPerOunce = stod(costPerOunceStr);
			double flatFeeForTwoDays = stod(flatFeeForTwoDaysStr);
			double overnightFeePerOunce = stod(overnightFeePerOunceStr);

			if(flatFeeForTwoDays == 0 && overnightFeePerOunce == 0)
        		packages[id] = new Package(id, name_sender, name_recipient, address_sender, address_recipient, 
										   city_sender, city_recipient, state_sender, state_recipient, zipCode_sender, 
										   zipCode_recipient,weight, costPerOunce);
			else if(overnightFeePerOunce == 0)
				packages[id] = new TwoDayPackage(id, name_sender, name_recipient, address_sender, address_recipient, 
			                   					 city_sender, city_recipient, state_sender, state_recipient, zipCode_sender, 
												 zipCode_recipient, weight, costPerOunce, flatFeeForTwoDays);
			else
		    	packages[id] = new OvernightPackage(id, name_sender, name_recipient, address_sender, address_recipient, 
												   city_sender, city_recipient, state_sender, state_recipient, zipCode_sender, 
												   zipCode_recipient, weight, costPerOunce, overnightFeePerOunce);
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
    if(!packages.empty()){
        int num, choice = -1, counter = 1;

        cout << "Enter the number of packages you want to modify: ";
        cin >> num;

        while(counter <= num){
            string user_id;
            cout << "(" << counter << "/" << num << ") Enter the ID of the package you want to modify: ";
            cin >> user_id;
			cout << endl;

            auto it = packages.find(user_id);
            if(it != packages.end()){
				counter++;
                Package* package = it->second;
                cout << "Package found: " << endl << endl;
                cout << *package << endl;

				do{
                	cout << "Select the field to modify: " << endl
					 	 << " [0] None." << endl
                	 	 << " [1] Sender Name." << endl
                	 	 << " [2] Recipient Name." << endl
					 	 << " [3] Sender Address." << endl
                	 	 << " [4] Recipient Address." << endl
					 	 << " [5] Sender City." << endl
                	 	 << " [6] Recipient City." << endl
					 	 << " [7] Sender State." << endl
                	 	 << " [8] Recipient State." << endl
					 	 << " [9] Sender ZIP Code. " << endl
                	 	 << "[10] Recipient ZIP Code." << endl
					 	 << "[11] Weight." << endl
                	 	 << "[12] Cost per Ounce." << endl;

                	if(dynamic_cast<TwoDayPackage*>(package))
                    	cout << "[13] Flat Fee for Two-Day Package." << endl;
                	else if(dynamic_cast<OvernightPackage*>(package)) 
                    	cout << "[13] Overnight Fee per Ounce." << endl;

					cout << endl << "Your choice: ";
                	cin >> choice;

                	switch(choice){
						case 0:
							cout << endl;
							break;

                    	case 1:{
                        	string newName;
                        	cout << "Enter new Sender Name: ";
                        	cin.ignore();
                        	getline(cin, newName);
                        	package->setSenderName(newName);
                        	break;                
						}

                    	case 2:{
                        	string newName;
                        	cout << "Enter new Recipient Name: ";
                        	cin.ignore();
                        	getline(cin, newName);
                        	package->setRecipientName(newName);
                        	break;
						}

                    	case 3:{
                        	string newAddress;
                        	cout << "Enter new Sender Address: ";
                        	cin.ignore();
                        	getline(cin, newAddress);
                        	package->setSenderAddress(newAddress);
                        	break;  
						}              

                    	case 4:{ 
                        	string newAddress;
                        	cout << "Enter new Recipient Address: ";
                        	cin.ignore();
                        	getline(cin, newAddress);
                        	package->setRecipientAddress(newAddress);
                        	break;
						}

                    	case 5:{
                        	string newCity;
                        	cout << "Enter new Sender City: ";
                        	cin.ignore();
                        	getline(cin, newCity);
                        	package->setSenderCity(newCity);
                        	break; 
						}               

                    	case 6:{
                        	string newCity;
                        	cout << "Enter new Recipient City: ";
                        	cin.ignore();
                        	getline(cin, newCity);
                        	package->setRecipientCity(newCity);
                        	break;
						}
						
						case 7:{
                        	string newState;
                        	cout << "Enter new Sender State: ";
                        	cin.ignore();
                        	getline(cin, newState);
                        	package->setSenderState(newState);
                        	break;                
						}

                    	case 8:{
                        	string newState;
                        	cout << "Enter new Recipient State: ";
                        	cin.ignore();
                        	getline(cin, newState);
                        	package->setRecipientState(newState);
                        	break;
						}

						case 9:{
                        	int newZipCode;
                        	cout << "Enter new Sender ZIP Code: ";
                        	cin >> newZipCode;
                        	package->setSenderZipCode(newZipCode);
                        	break;                
						}

                    	case 10:{ 
                        	int newZipCode;
                        	cout << "Enter new Recipient ZIP Code: ";
                        	cin >> newZipCode;
                        	package->setRecipientZipCode(newZipCode);
                        	break;
						}

                    	case 11:{
                        	double newWeight;
                        	cout << "Enter new Weight: ";
                        	cin >> newWeight;
                        	package->setWeight(newWeight);
                        	break;
						}

                    	case 12:{
                        	double newCost;
                        	cout << "Enter new Cost per Ounce: ";
                        	cin >> newCost;
                        	package->setCostPerOunce(newCost);
                        	break;
						}

                    	case 13:{ 
							if(auto twoDayPackage = dynamic_cast<TwoDayPackage*>(package)){
                            	double newFlatFee;
                            	cout << "Enter new Flat Fee for Two-Day Package: ";
                            	cin >> newFlatFee;
                            	twoDayPackage->setFlatFeeForTwoDays(newFlatFee);
                        	} 
							else if(auto overnightPackage = dynamic_cast<OvernightPackage*>(package)){
                            	double newOvernightFee;
                            	cout << "Enter new Overnight Fee per Ounce: ";
                            	cin >> newOvernightFee;
                            	overnightPackage->setOvernightFeePerOunce(newOvernightFee);
                        	} 
							else{
                            	cout << "Invalid option for this package type." << endl;
                        	}
                        	break;
						}

                    	default:{
                        	cout << "Invalid option." << endl;
                        	break;
						}
                	}

					if(choice == 0) break;
                	cout << "Package updated successfully!" << endl << endl;
                	cout << *package << endl;

				}while(choice != 0);
            } 
			else{
                cout << "Package with ID " << user_id << " was not found." << endl;
            }
        }
    } 
	else{
        cout << "The map is empty." << endl << endl;
    }
}
