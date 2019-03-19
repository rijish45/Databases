#include "exerciser.h"

void exercise(connection *C)
{


  cout << "Testing query 1" << endl; 
  query1(C,1, 35, 40,
	   0, 0, 0,
	   1, 0, 100,
	   0, 0, 0,
	   0, 0, 0,
	   0, 0, 0);
  cout << endl;
  query1(C,1, 0, 40,
	   1, 0, 40,
	   0, 0, 0,
	   0, 0, 0,
	   1, 20, 0,
	   0, 0, 0);
  cout << endl;
  query1(C,0, 0, 0,
	   1, 0, 40,
	   1, 0, 40,
	   0, 0, 0,
	   1, 20, 0,
	   0, 0, 0);
  cout << endl;

   
cout << "Testing query 2" << endl;
query2(C, "Red");
cout << endl;
query2(C, "Orange");
cout << endl;
query2(C, "Green");
cout << endl;
 

cout << "Testing query 3" << endl;
query3(C, "NCSU");
cout << endl;
query3(C,"Duke");
cout << endl;
query3(C, "Clemson");
cout << endl;

 

cout << "Testing query 4" << endl; 
query4(C, "NC", "LightBlue");
cout << endl;
query4(C, "NY", "Orange");
cout << endl;
 


cout << "Testing query 5" << endl;
query5(C, 5);
cout << endl;
query5(C, 9);
cout << endl;
query5(C, 12);
cout << endl;

}
