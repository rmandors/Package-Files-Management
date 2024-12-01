#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <map>
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