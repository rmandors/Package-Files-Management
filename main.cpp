/*
2 Diciembre 2024
Proyecto Final
NRC: 1422
Diogo Coral - 00336376	
Raymond Portilla - 00335050
*/

#include "functions.h"
#include "Package.h"
#include "TwoDayPackage.h"
#include "OvernightPackage.h"
using namespace std;

int main(){
	map<string, Package*> packages; // Stores all packages with ID as the key
	char menuChoice; // Stores the user's menu selection

	do{
		displayMenu();

		cout << "Your choice: ";
		cin >> menuChoice;

		switch (menuChoice){
			case '1':{
				loadMapDataFromCSVfile(packages);
				break;
			}
	
			case '2':{
				displayMapData(packages);
				break;
			}
			
			case '3':{
				saveMapDataToBinaryFile(packages);
				break;
			}
			
			case '4':{
				loadMapDataFromBinaryFile(packages);
				break;
			}

			case '5':{
				displayPackagesByType(packages);
				break;
			}

			case '6':{
				displayPackagesByCost(packages);
				break;
			}

			case '7':{
				extractAndModifyPackage(packages);
				break;
			}

			case '8':{
				// Clear the map of packages and release memory
				for(auto& [id, package] : packages){
    				delete package;
				}
				packages.clear();
				cout << "The map has been emptied." << endl << endl;
				break;
			}

			case '9':{
				cout << "Exiting..." <<endl ;
				break;
			}

			default:{
				// Handle invalid user inputs
				cout << "Please enter a valid option!" << endl << endl;
				break;
			}
		}

	}while(menuChoice != '9');

	// Release memory before ending the program (in case the map was not cleared manually)
    for (auto& [id, package] : packages) {
       	delete package;
    }
    packages.clear();

	return 0;
}