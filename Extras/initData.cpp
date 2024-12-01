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
    dataFile << "0001,Juan Montalvo,Leonardo Picasso,Av. El Inca,Av. Eloy Alfaro,"
             << "Quito,Quito,Pichincha,Pichincha,120180,120160,150,3,0,0" << endl

             << "0002,Sarah Ackerman,Amy Winehouse,Av. Juan de la Roca,Av. Simon Bolivar,"
             << "Ibarra,Ibarra,Imbabura,Imbabura,100150,100130,200,2,50,0" << endl

             << "0003,Pedro Cifuentes,Jose Delgado,Av. 25 de Julio,Av. Olmedo,"
             << "Guayaquil,Guayaquil,Guayas,Guayas,110060,110090,175,4,0,1" << endl
             
             << "0004,Emma Johnson,Liam Smith,Av. Rivadavia 72 y Calle San Juan,Calle 7 de Octubre 200 y Av. Flores,"
             << "Cuenca,Guayaquil,Azuay,Guayas,170102,070150,23,3,0,2" << endl

             << "0005,Juan Rodriguez,Maria Garcia,Av. Libertad 123 y Calle 5 de Mayo,Av. Victoria 145 y Calle 3 de Febrero,"
             << "Ambato,Loja,Tungurahua,Loja,090101,120101,46,2,70,0" << endl
             
             << "0006,Carlos Martinez,Ana Lopez,Calle 1 de Mayo 45 y Av. San Martin,Calle 5 de Julio 303 y Av. Santa Rosa,"
             << "Machala,Manta,El Oro,Manabi,110101,110150,146,5,0,0" << endl

             << "0007,Jose Perez,Laura Sanchez,Calle 10 y Av. de la Paz 678,Av. del Sol 567 y Calle Primavera,"
             << "Riobamba,Esmeraldas,Chimborazo,Esmeraldas,180150,180101,78,3,30,0" << endl

             << "0008,Luis Gonzalez,Carmen Rivera,Av. Constitución 56 y Calle 6 de Agosto,Calle 15 de Agosto 400 y Av. Río Claro,"
             << "Ibarra,Ambato,Imbabura,Tungurahua,070150,040150,93,4,0,0" << endl

             << "0009,Miguel Fernandez,Isabel Diaz,Calle 25 de Julio 12 y Av. Bolívar,Av. del Oeste 87 y Calle 13 de Enero,"
             << "Portoviejo,Durán,Manabi,Guayas,130150,190101,103,3,90,0" << endl

             << "0010,Pablo Torres,Teresa Ramirez,Av. Independencia 789 y Calle 9 de Octubre,Av. Paz y Bien 123 y Calle San José,"
             << "Latacunga,Babahoyo,Cotopaxi,Los Rios,060150,240101,169,4,0,2" << endl

             << "0011,Andres Gonzalez,Patricia Morales,Calle 14 de Septiembre 98 y Av. Norte,Av. Libertad 45 y Calle 10 de Enero,"
             << "Tena,Zamora,Napo,Zamora,100101,230101,111,5,0,0" << endl

             << "0012,Roberto Herrera,Lucia Gomez,Calle Larga 456 y Av. La Esperanza,Calle 4 de Julio 123 y Av. Central,"
             << "Cañar,Macas,Cañar,Morona Santiago,030101,010101,92,2,20,0" << endl

             << "0013,Fernando Alvarez,Rosa Martinez,Av. Sur 321 y Calle Nueva 45,Av. Norte 678 y Calle 7 de Marzo,"
             << "Salinas,Loja,Santa Elena,Loja,130101,080101,120,3,0,2" << endl

             << "0014,Alejandro Jimenez,Marta Vargas,Calle 20 de Noviembre 33 y Av. Central,Calle 5 de Octubre 200 y Av. Sol,"
             << "Machachi,Cuenca,Pichincha,Azuay,090201,060101,66,5,0,0" << endl

             << "0015,Diogo Coral,Raymond Portilla,Av. Inca y Valdivia,Av. Rivadavia y jardines,"
             << "Quito,Quito,Pichincha,Pichincha,050101,110150,48,4,0,1" << endl;


    dataFile.close();

    return 0;
}
