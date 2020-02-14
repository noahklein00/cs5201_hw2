// Programmer : Noah Klein
// Instructor : Price
// Class      : CS5201 Spring 2020
// Assignment : Homework 2 - Templated Interpolator
// Filename   : interpolator.hpp

#include "interpolator.h"

using namespace std;

int main()
{
	try{
		cout.precision(8);
		
		int firstRange;
		int secondRange;
		tuple<double, double> y_vals;
		
		cin >> firstRange;
		cin >> secondRange;
		
		Interpolator<double> set1(firstRange);
		Interpolator<double> set2(secondRange);
		
		cin >> set1;
		cin >> set2;
		
		y_vals = set1(1.707);
		cout << "1.707: " << get<0>(y_vals) << " " << get<1>(y_vals) << endl;
		y_vals = set2(1.707);
		cout << "1.707: " << get<0>(y_vals) << " " << get<1>(y_vals) << endl;	

		if(set1 > set2)
			cout << "0" << endl;
		if(set1 < set2)
			cout << "1" << endl;
		
		get<1>(set1[0.0]) = 1.47;
		get<2>(set1[0.0]) = -0.0234;
		
		y_vals = set1(0.03);
		cout << "0.03: " << get<0>(y_vals) << " " << get<1>(y_vals) << endl;
	}
	
	catch(IncrementErr e)
	{
		cerr << "ERROR!! Independent variable must be strictly increasing: "
			<< e.getIncrement() << endl;
	}
	
	catch(BoundErr e)
	{
		cerr << "ERROR!! Attempted access out of bounds: " << e.getBound()
			<< endl;
	}
	
	return 0;
}