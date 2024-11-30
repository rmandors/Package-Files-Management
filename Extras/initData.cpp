#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

int main(){
    ofstream dataFile("InitialData.csv", ios::out); 

    if (!dataFile) {
        cerr << "File could not be opened." << endl;
        exit(EXIT_FAILURE);
    }

    // Write table headers
    dataFile << "id,name_sender,name_recipient,address_sender,address_recipient,city_sender,"
             << "city_recipient,state_sender,state_recipient,zipCode_sender,zipCode_recipient,"
             << "weight,costPerOnce,flatFeeForTwoDays,overnightFeePerOnce" << endl;

    // Fill table data
    dataFile << "000001,Juan Montalvo,Leonardo Picasso,Av. El Inca,Av. Eloy Alfaro,"
             << "Quito,Quito,Pichincha,Pichincha,120180,120160,150,2,0,0" << endl

             << "000006,Sarah Ackerman,Amy Winehouse,Av. Juan de la Roca,Av. Simon Bolivar,"
             << "Ibarra,Ibarra,Imbabura,Imbabura,100150,100130,200,2,50,0" << endl

             << "000002,Juan Montalvo,Leonardo Picasso,Av. El Inca,Av. Eloy Alfaro,"
             << "Quito,Quito,Pichincha,Pichincha,120180,120160,150,2,0,0" << endl

             << "000007,Sarah Ackerman,Amy Winehouse,Av. Juan de la Roca,Av. Simon Bolivar,"
             << "Ibarra,Ibarra,Imbabura,Imbabura,100150,100130,200,2,50,0" << endl

             << "000011,Pedro Cifuentes,Jose Delgado,Av. 25 de Julio,Av. Olmedo,"
             << "Guayaquil,Guayaquil,Guayas,Guayas,110060,110090,175,2,0,1" << endl

             << "000012,Pedro Cifuentes,Jose Delgado,Av. 25 de Julio,Av. Olmedo,"
             << "Guayaquil,Guayaquil,Guayas,Guayas,110060,110090,175,2,0,1" << endl

             << "000003,Juan Montalvo,Leonardo Picasso,Av. El Inca,Av. Eloy Alfaro,"
             << "Quito,Quito,Pichincha,Pichincha,120180,120160,150,2,0,0" << endl

             << "000013,Pedro Cifuentes,Jose Delgado,Av. 25 de Julio,Av. Olmedo,"
             << "Guayaquil,Guayaquil,Guayas,Guayas,110060,110090,175,2,0,1" << endl

             << "000004,Juan Montalvo,Leonardo Picasso,Av. El Inca,Av. Eloy Alfaro,"
             << "Quito,Quito,Pichincha,Pichincha,120180,120160,150,2,0,0" << endl

             << "000008,Sarah Ackerman,Amy Winehouse,Av. Juan de la Roca,Av. Simon Bolivar,"
             << "Ibarra,Ibarra,Imbabura,Imbabura,100150,100130,200,2,50,0" << endl

             << "000009,Sarah Ackerman,Amy Winehouse,Av. Juan de la Roca,Av. Simon Bolivar,"
             << "Ibarra,Ibarra,Imbabura,Imbabura,100150,100130,200,2,50,0" << endl

             << "000014,Pedro Cifuentes,Jose Delgado,Av. 25 de Julio,Av. Olmedo,"
             << "Guayaquil,Guayaquil,Guayas,Guayas,110060,110090,175,2,0,1" << endl

             << "000005,Juan Montalvo,Leonardo Picasso,Av. El Inca,Av. Eloy Alfaro,"
             << "Quito,Quito,Pichincha,Pichincha,120180,120160,150,2,0,0" << endl

             << "000015,Pedro Cifuentes,Jose Delgado,Av. 25 de Julio,Av. Olmedo,"
             << "Guayaquil,Guayaquil,Guayas,Guayas,110060,110090,175,2,0,1" << endl

             << "000010,Sarah Ackerman,Amy Winehouse,Av. Juan de la Roca,Av. Simon Bolivar,"
             << "Ibarra,Ibarra,Imbabura,Imbabura,100150,100130,200,2,50,0" << endl;

    dataFile.close();

    return 0;
}
