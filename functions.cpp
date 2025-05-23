#include "functions.h"
using namespace std;

void displayMenu(){
	cout << "------------O------------ MENU ------------O------------" << endl
		 << "[1] Load Packages Data from a CSV file." << endl
	     << "[2] Display Packages Information." << endl
		 << "[3] Save Packages Data in a Binary File." << endl
		 << "[4] Load Packages Data from a Binary File." << endl
		 << "[5] Display Packages ordered by their Type." << endl 
		 << "[6] Display Packages ordered by their Shipping Cost." << endl
		 << "[7] Extract and Modify a Package." << endl
		 << "[8] Empty Packages Map." << endl
		 << "[9] Exit." << endl
		 << "------------O-----------------------------O------------" << endl << endl;
}

void loadMapDataFromCSVfile(map<string, Package*>& packages){
	if(!packages.empty()){
		for (auto& [id, package] : packages){
    		delete package; // Free allocated memory for each Package
		}
		packages.clear(); // Remove all entries from the map
	}
		
	// Open the CSV file for reading	
	ifstream file("initialData.csv", ios::in);
	if(!file){
		cerr << "File could not be opened." << endl;
		exit(EXIT_FAILURE); // Terminate program on failure
	}

	string row;
	getline(file, row); // Read and skip the first line (assumed to be headers)

	// Process each row in the CSV file
	while(getline(file, row)) {
       	stringstream ss(row);
       	string id, name_sender, name_recipient, address_sender, address_recipient, city_sender, 
		           city_recipient, state_sender, state_recipient, zipCode_senderStr, zipCode_recipientStr, 
			       weightStr, costPerOunceStr, flatFeeForTwoDaysStr, overnightFeePerOunceStr;

		// Extract CSV values separated by commas
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

        // Convert string values to numeric types
		int zipCode_sender = stoi(zipCode_senderStr);
		int zipCode_recipient = stoi(zipCode_recipientStr);
       	double weight = stod(weightStr);
       	double costPerOunce = stod(costPerOunceStr);
		double flatFeeForTwoDays = stod(flatFeeForTwoDaysStr);
		double overnightFeePerOunce = stod(overnightFeePerOunceStr);

        // Create the appropriate Package type based on fee values
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

void displayMapData(map<string, Package*>& packages){
	// Check if the map is not empty, this will be done in most other functions
	if(!packages.empty()){
    	double totalShippingCost = 0;
	
		// Iterate through each package in the map
		for (const auto& [id, package] : packages) {
    		cout << endl << *package; // Print package details (operator<< is overloaded)
			totalShippingCost += package->calculateCost(); // Add shipping cost of the current package
    	}

		cout << endl << "Total Shipping Cost: " << totalShippingCost << endl << endl;
	}
	else{
		cout << "The map is empty." <<endl << endl; // If the map is empty, notify the user
	}
}

void saveMapDataToBinaryFile(map<string, Package*>& packages){
    if(!packages.empty()){
		// Open the binary file for writing
        ofstream outFile("InitialData.dat", ios::binary);
        if(!outFile){  
            cerr << "File could not be opened." << endl;
            exit(EXIT_FAILURE);
        }

        auto writeString = [&outFile](const string& str){
            size_t length = str.size(); // Get the string length
            outFile.write(reinterpret_cast<char*>(&length), sizeof(length));  
            outFile.write(str.c_str(), length); //Write the string data
        };

		// Iterate through each package in the map
        for (const auto& [id, package] : packages){
            // Write the ID of the package
			size_t idLength = id.size();  
            outFile.write(reinterpret_cast<char*>(&idLength), sizeof(idLength));  
            outFile.write(id.c_str(), idLength);  

			// Write package details as strings
            writeString(package->getSenderName());
            writeString(package->getRecipientName());
            writeString(package->getSenderAddress());
            writeString(package->getRecipientAddress());
            writeString(package->getSenderCity());
            writeString(package->getRecipientCity());
            writeString(package->getSenderState());
            writeString(package->getRecipientState());

			// Write ZIP codes as integers
            int zipCode_sender = package->getSenderZipCode();
            int zipCode_recipient = package->getRecipientZipCode();
            outFile.write(reinterpret_cast<char*>(&zipCode_sender), sizeof(zipCode_sender));  
            outFile.write(reinterpret_cast<char*>(&zipCode_recipient), sizeof(zipCode_recipient));  
            
            // Write weight and cost per ounce as doubles
			double weight = package->getWeight();
            double costPerOunce = package->getCostPerOunce();
            outFile.write(reinterpret_cast<char*>(&weight), sizeof(weight));  
            outFile.write(reinterpret_cast<char*>(&costPerOunce), sizeof(costPerOunce));  

            // Write specific fees depending on the package type
			double flatFeeForTwoDays = 0.0;
            double overnightFeePerOunce = 0.0;

			// Check if the package is a TwoDayPackage or OvernightPackage
            if (auto p2d = dynamic_cast<TwoDayPackage*>(package)) {
                flatFeeForTwoDays = p2d->getFlatFeeForTwoDays();
            } 
            else if (auto p1d = dynamic_cast<OvernightPackage*>(package)) {
                overnightFeePerOunce = p1d->getOvernightFeePerOunce();
            }

			// Write additional fees to the binary file
            outFile.write(reinterpret_cast<char*>(&flatFeeForTwoDays), sizeof(flatFeeForTwoDays));
            outFile.write(reinterpret_cast<char*>(&overnightFeePerOunce), sizeof(overnightFeePerOunce));
        }

        outFile.close();
        cout << "Data has been successfully saved to binary file." << endl << endl;
    } 
	else{
        cout << "The map is empty." << endl << endl;
    }
}

void loadMapDataFromBinaryFile(map<string, Package*>& packages) {
    // Clear the map and free memory of existing Package objects
	if(!packages.empty()){
		for (auto& [id, package] : packages){
    		delete package;
		}
		packages.clear();
    }

	// Open the binary file for reading
    ifstream inFile("InitialData.dat", ios::binary);  
    if(!inFile){
        cerr << "File could not be opened." << endl;
        return;
    }

    auto readString = [&inFile](string& str){
        size_t length = 0;
        if(!inFile.read(reinterpret_cast<char*>(&length), sizeof(length))){
            str = "";
            return false; // Return false if reading failed
        }

        const size_t MAX_STRING_LENGTH = 1024;  
        if(length == 0 || length > MAX_STRING_LENGTH){ // Validate string length
            cerr << "Invalid string length: " << length << endl;
            str = "corrupt_data";

            inFile.seekg(length, ios::cur); // Skip invalid string
            return false;
        }

        str.resize(length); // Resize string buffer
        if(!inFile.read(&str[0], length)){ //Read string data
            cerr << "Failed to read string of length " << length << endl;
            str = "corrupt_data";
            return false;
        }

        return true; //Successfully read string
    };

    try{
        while(inFile){ // Read package ID length and validate
            size_t idLength = 0;
            if(!inFile.read(reinterpret_cast<char*>(&idLength), sizeof(idLength))) break;

            if(idLength == 0 || idLength > 100){  // Check for invalid ID length
                cerr << "Invalid ID length: " << idLength << endl;
                break;
            }

			// Read the package ID
            string id(idLength, '\0');
            if (!inFile.read(&id[0], idLength)) break;

            string name_sender, name_recipient, address_sender, address_recipient;
            string city_sender, city_recipient, state_sender, state_recipient;
            int zipCode_sender = 0, zipCode_recipient = 0;
            double weight = 0.0, costPerOunce = 0.0;

			// Read string fields and validate
            bool readSuccess = true;
            readSuccess &= readString(name_sender);
            readSuccess &= readString(name_recipient);
            readSuccess &= readString(address_sender);
            readSuccess &= readString(address_recipient);
            readSuccess &= readString(city_sender);
            readSuccess &= readString(city_recipient);
            readSuccess &= readString(state_sender);
            readSuccess &= readString(state_recipient);

            if(!readSuccess){ // Handle string reading errors
                cerr << "Error reading strings for package ID: " << id << endl;
                continue;
            }

			// Read numeric fields and validate
            if(!inFile.read(reinterpret_cast<char*>(&zipCode_sender), sizeof(zipCode_sender)) ||
               !inFile.read(reinterpret_cast<char*>(&zipCode_recipient), sizeof(zipCode_recipient)) ||
               !inFile.read(reinterpret_cast<char*>(&weight), sizeof(weight)) ||
               !inFile.read(reinterpret_cast<char*>(&costPerOunce), sizeof(costPerOunce))){
				cerr << "Error reading numeric values for package ID: " << id << endl;
                break;
            }

			// Read package-specific fees
            double flatFeeForTwoDays = 0.0;
            double overnightFeePerOunce = 0.0;

            if(inFile.read(reinterpret_cast<char*>(&flatFeeForTwoDays), sizeof(flatFeeForTwoDays)) &&
               inFile.read(reinterpret_cast<char*>(&overnightFeePerOunce), sizeof(overnightFeePerOunce))){
                
				// Create the appropriate package type
                Package* newPackage = nullptr;
                if(flatFeeForTwoDays == 0.0 && overnightFeePerOunce == 0.0){
                    newPackage = new Package(id, name_sender, name_recipient, address_sender, address_recipient,
                                             city_sender, city_recipient, state_sender, state_recipient,
                                             zipCode_sender, zipCode_recipient, weight, costPerOunce);
                } 
				else if(overnightFeePerOunce == 0.0){
                    newPackage = new TwoDayPackage(id, name_sender, name_recipient, address_sender, address_recipient,
                                                   city_sender, city_recipient, state_sender, state_recipient,
                                                   zipCode_sender, zipCode_recipient, weight, costPerOunce,
                                                   flatFeeForTwoDays);
                } 
				else{
                    newPackage = new OvernightPackage(id, name_sender, name_recipient, address_sender, address_recipient,
                                                      city_sender, city_recipient, state_sender, state_recipient,
                                                      zipCode_sender, zipCode_recipient, weight, costPerOunce,
                                                      overnightFeePerOunce);
                }

                if(newPackage){
                    packages[id] = newPackage; // Add package to the map
                }
            }
        }

        inFile.close();
        cout << "Data has been successfully loaded from binary file!" << endl << endl;
    }
    catch(const std::exception& e){
        cerr << "Exception occurred while reading file: " << e.what() << endl;
    }
}

void displayPackagesByType(map<string, Package*>& packages){
    if(!packages.empty()){
		// Vectors to store packages by type
        vector<Package*> packageType;
        vector<TwoDayPackage*> twoDayPackageType;
        vector<OvernightPackage*> overnightPackageType;

		// Classify packages based on their type
        for(const auto& [id, package] : packages){
            if(auto p = dynamic_cast<TwoDayPackage*>(package))
                twoDayPackageType.push_back(p); 
            else if(auto p = dynamic_cast<OvernightPackage*>(package))
                overnightPackageType.push_back(p); 
			else if(auto p = dynamic_cast<Package*>(package))
                packageType.push_back(p);
        }

        // Display standard packages
        if(!packageType.empty()){
            cout << "\n.:Packages of Type 'Package':." << endl << endl;
            for(const auto& package : packageType){
                cout << *package << endl;
            }
        }

		// Display TwoDayPackage objects	
        if(!twoDayPackageType.empty()){
            cout << "\n.:Packages of Type 'TwoDayPackage':." << endl << endl;
            for(const auto& package : twoDayPackageType){
                cout << *package << endl;
            }
        }

		// Display OvernightPackage objects
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
   if(!packages.empty()){
		// Vector to hold copies of packages for sorting
        vector<Package*> sortedPackages;

		// Create deep copies of the packages and store them in the vector
        for(auto& [id, package] : packages){
            sortedPackages.push_back(new Package(*package)); 
        }

        // Sort the packages by cost using a lambda comparator
        sort(sortedPackages.begin(), sortedPackages.end(), [](const Package* a, const Package* b){
            return *a > *b; // Operator> is overloaded for cost comparison
        });

		// Display sorted packages
        for(auto& package : sortedPackages){
            cout << endl << *package;
            delete package;  
        }

        cout << endl;
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

		// Loop until the desired number of packages is modified
        while(counter <= num){
            string user_id;
            cout << "(" << counter << "/" << num << ") Enter the ID of the package you want to modify: ";
            cin >> user_id;
			cout << endl;

            auto it = packages.find(user_id); // Search for the package by ID
            if(it != packages.end()){
				counter++; // Increment the modification counter
                Package* package = it->second;
                cout << "Package found: " << endl << endl;
                cout << *package << endl; // Display package details

				do{
					// Display modification options
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

					// Additional options for derived package types
                	if(dynamic_cast<TwoDayPackage*>(package))
                    	cout << "[13] Flat Fee for Two-Day Package." << endl;
                	else if(dynamic_cast<OvernightPackage*>(package)) 
                    	cout << "[13] Overnight Fee per Ounce." << endl;

					cout << endl << "Your choice: ";
                	cin >> choice;

					// Handle user input for modifying fields
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

						// Handle TwoDayPackage or OvernightPackage specific modifications
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

					if(choice == 0) break; // Exit modification loop
                	cout << "Package updated successfully!" << endl << endl;
                	cout << *package << endl; // Display updated package

				}while(choice != 0); // Continue until user chooses to exit modification
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