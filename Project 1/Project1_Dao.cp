/***************************************************************************
 * Name: Diem Dao
 * Email: ddao@email.sc.edu
 * Date/Time of Completion: 08/31/19 6:18 pm
 * 
 * Function: Starting point for C++ code.
 * 
 * Input: Program will ask for 5 numbers from the user. 
 * Output: The program will output the sum of those 5 numbers
 * 
 * Additional comments: 
 *                                                                         *
 ***************************************************************************/

#include <cstdlib>
#include <iostream>


using namespace std;


int main (int argc, char **argv)
{
	cout << "Hello World!" << endl; 

	bool go_on = true;
	while(go_on == true){
		cout << "Give me five numbers: "; 
		int a(0),b(0), c(0), d(0), e(0); 
		cin >> a >> b >> c >> d >> e; 
	
		int sum = a + b + c + d + e;
	
		if(sum > 0){
			cout << "The sum of the five numbers is: " << sum << endl;
		} else {
			break;
		}
		go_on = true;
	}
}
	
