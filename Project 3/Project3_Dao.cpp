/***************************************************************************
 * Name: Diem Dao
 * Email: ddao@email.sc.edu
 *
 * Function: karatsuba
 *
 * Additional comments:
 *                                                                         *
 ***************************************************************************/

#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;
using std::vector;


// ------------------- "pencil and paper" algorithm (brute force)------------------------
vector<int> pencilAndPaper(vector<int> number1, vector<int> number2){
	//adding '0' if the numbers are not the same size
	if(number1.size() < number2.size()) {
		for(int i = number1.size(); i<number2.size(); i++) {
			number1.insert(number1.begin(),0);
		}
	}
	else {
		for(int i = number2.size(); i<number1.size();i++) {
			number2.insert(number2.begin(),0);
		}
	}

	int carry = 0;
	int index_num1 = 0;
	int index_num2 = 0;
	int size_n1 = number1.size();
	int size_n2 = number2.size();
	int total_size = size_n1 + size_n2;
	vector<int> total(total_size, 0);
	// vector<int> total = max(size_n1, size_n2);

	// Check to see if numbers filled properlly.
	// cout << "num1 test: " << endl;
	// for (int i = 0; i < number1.size(); ++i) {
	// 	cout << number1.at(i);
	// }
	// cout << endl;
	//
	// cout << "num2 test: " << endl;
	// for (int i = 0; i < number2.size(); ++i) {
	// 	cout << number2.at(i);
	// }
	// cout << endl;

	// reading from right to left
	for(int i = number1.size()-1;  i >= 0; i--) {
		carry = 0;
		int store_1 = number1[i];
		index_num2 = 0;

		for(int j = number2.size()-1;  j >= 0; j--) {
				int store_2 = number2[j];
				// cout << "store_2: " << store_2 << endl;
				// cout << "store_1: " << store_1 << endl;
				int sum = (store_1*store_2) + total[index_num1 + index_num2] + carry;
				// cout << "sum: " << sum << endl;
				carry = sum/10;
				// cout << "carry sum/10: " << carry << endl;
				total[index_num1 + index_num2] = sum % 10;
				index_num2++;
				// cout << "number1[i]: "<< number1[i] << endl;
		}
		// cout << endl;

		if(carry > 0){
			total[index_num1 + index_num2] = total[index_num1 + index_num2] + carry;
		}
		index_num1++;
	}

	int i = total.size() - 1;
	while(i >= 0 && total[i] == 0)
	i--;
	// return result vector
	vector<int> v;
	while( i >= 0)
			v.push_back(total[i--]);
	return v;
}

// ---------------- Add vector method ----------------------------------
vector<int> addV(vector<int> number1, vector<int> number2){

	//adding '0' if the numbers are not the same size
	if(number1.size() < number2.size()) {
		for(int i = number1.size(); i<number2.size(); i++) {
			number1.insert(number1.begin(),0);
		}
	}
	else {
		for(int i = number2.size(); i<number1.size();i++) {
			number2.insert(number2.begin(),0);
		}
	}

	int carry = 0;
	int sum = 0;
	int num = 0;
	vector<int> total;

	for(int i = number1.size()-1;  i >= 0; i--) {
			sum = number1[i] + number2[i] + carry;
			// cout << "sum: " << sum << endl;
			carry = sum/10;
			// cout << "carry sum/10: " << carry << endl;
			num = sum % 10;
			total.push_back(num);
		}
		if(carry > 0){
			total.push_back(carry);
	}

	int i = total.size() - 1;
	while(i >= 0 && total[i] == 0)
	i--;
	// return result vector
	vector<int> v;
	while( i >= 0)
			v.push_back(total[i--]);
	return v;
}

// ------------------- Subtract vector method ------------------------
vector<int> subtractV(vector<int> number1, vector<int> number2){
	//adding '0' if the numbers are not the same size
	if(number1.size() < number2.size()) {
		for(int i = number1.size(); i<number2.size(); i++) {
			number1.insert(number1.begin(),0);
		}
	}
	else {
		for(int i = number2.size(); i<number1.size();i++) {
			number2.insert(number2.begin(),0);
		}
	}

	int diff = 0;
	vector<int> result;
	for(int i = number1.size()-1;  i >= 0; i--) {
		diff = number1[i] - number2[i];
		if(diff >= 0){
			result.push_back(diff);
		}
		else{
			// borrow from the previous column
			int j = i - 1;
			while (j >= 0) {
				number1[j] = (number1[j] - 1) % 10;
				if (number1[j] != '9')
					break;
				else
					j--;
			}
			result.push_back(diff+10);
		}
	}

	int i = result.size() - 1;

	while(i >= 0 && result[i] == 0)
	i--;

	// cout << endl;
	// return result vector
	vector<int> v;
	while( i >= 0)
			v.push_back(result[i--]);
	return v;

}

// ------------------- Karatsuba Algorithm ------------------------
vector<int> karatsuba(vector<int> number1, vector<int> number2) {
	//adding '0' if the numbers are not the same size
	if(number1.size() < number2.size()) {
		for(int i = number1.size(); i<number2.size(); i++) {
			number1.insert(number1.begin(),0);
		}
	}
	else {
		for(int i = number2.size(); i<number1.size();i++) {
			number2.insert(number2.begin(),0);
		}
	}

	int n = max(number1.size(), number2.size()); // the length

	// if one digit
	if (n == 1)
      return pencilAndPaper(number1, number2);

	// cout << "n: " << n << endl;  // m = 4
	int m = n/2;
	// cout << "m: " << m << endl;  // m = 2

	vector<int> x_H, x_L, y_H, y_L;

	// set of x_H
	for (int i = 0; i < (number1.size() - m); i++) {
		x_H.push_back(number1.at(i));
	}

	// set of x_L
	for (int i = (number1.size() - m); i < number1.size(); i++) {
		x_L.push_back(number1.at(i));
	}

	// set of y_H
	for (int i = 0; i < (number2.size() - m); ++i) {
		y_H.push_back(number2.at(i));
	}

	// set of y_L
	for (int i = number2.size() - m; i < number2.size(); ++i) {
		y_L.push_back(number2.at(i));
	}

	// step 1
	vector<int> step1 = karatsuba(x_H, y_H);
	// cout << "step1: ";
	// for (int i = 0; i < step1.size(); ++i) {
	// 	cout << step1.at(i);
	// }
	// cout << endl;


	// step 2
	vector<int> step2 = karatsuba(x_L, y_L);
	// cout << "step2: ";
	// for (int i = 0; i < step2.size(); ++i) {
	// 	cout << step2.at(i);
	// }
	// cout << endl;

	// step 3
	vector<int> x_result = addV(x_H, x_L);
	vector<int> y_result = addV(y_H, y_L);

	// step 3
	vector<int> step3 = karatsuba(x_result, y_result);

	// step 4
	vector<int> step4;
	step4 = subtractV(step3, addV(step2,step1));


	// Get the 10^n and 10^n/2 part
	vector<int> TenM2 = {1, 0};
	vector<int> TenM1 = {1, 0};
	vector<int> ten_vector = {1, 0};
	int m2 = 2 * m;
	int m1 = m;

	for (int i = 1; i < m2; ++i) {
		TenM2 = pencilAndPaper(TenM2, ten_vector);
	}
	for (int i = 1; i < m1; ++i) {
		TenM1 = pencilAndPaper(TenM1, ten_vector);
	}

	// final multiplication
	vector<int> result_2 = pencilAndPaper(TenM2, step1);
	vector<int> result_1 = pencilAndPaper(TenM1, step4);
	vector<int> final_answer;

	final_answer = addV(result_2, result_1);
	final_answer = addV(final_answer, step2);

	return final_answer;
}

// ------------------- main ---------------------------------------

int main (int argc, char **argv)
{
	char c_num;
	vector<int> number1, number2;

	//Read in number 1
	while(cin >> c_num && c_num != '*')
	{
		number1.push_back((int)c_num - 48);
	}

	//Read in number 2
	while(cin >> c_num)
	{
		number2.push_back((int)c_num - 48);
		if(cin.peek() == '\n') break;
	}

	//Check to see if numbers filled properlly.
	for(int i = 0; i < number1.size(); i++)
	{
		cout << number1[i] << " ";
	}
	cout << endl;

	for(int i = 0; i < number2.size(); i++)
	{
		cout << number2[i] << " ";
	}
	cout << endl;


	vector<int> pencil_And_Paper;
	pencil_And_Paper = pencilAndPaper(number1, number2);

  cout << "B: ";
  for (int i = 0; i < pencil_And_Paper.size(); ++i) {
    cout << pencil_And_Paper.at(i);
  }
  cout << endl;

	// testing adding and substracting methods
	// vector<int> adding;
	// adding = addV(number1, number2);
	// cout << "adding: ";
  // for (int i = 0; i < adding.size(); ++i) {
  //   cout << adding.at(i);
  // }
  // cout << endl;
	//
	// vector<int> subtraction;
	// subtraction = subtractV(number1, number2);
	// cout << "substracting: ";
	// for (int i = 0; i < subtraction.size(); ++i) {
	// 	cout << subtraction.at(i);
	// }
	// cout << endl;

	cout << "K: ";
	vector<int> karatsuba_alg = karatsuba(number1, number2);
  for (int i = 0; i < karatsuba_alg.size(); ++i) {
    cout << karatsuba_alg.at(i);
  }
  cout << endl;
}
