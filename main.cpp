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
	map<string, Package*> packages;
	char menuChoice;

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
				cout << "Exiting..." <<endl ;
				break;
			}

			default:{
				cout << "Please enter a valid option!" << endl << endl;
				break;
			}
		}

	}while(menuChoice != '8');

	return 0;
}