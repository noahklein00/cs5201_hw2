// Programmer : Noah Klein
// Instructor : Price
// Class      : CS5201 Spring 2020
// Assignment : Homework 2 - Templated Interpolator
// Filename   : interpolator.hpp

#include "interpolator.h"

using namespace std;

template <typename T>
Interpolator<T>::Interpolator()
{
	vector<tuple<T, T, T>> m_vector;
	int m_data = 20;  //defaults to 20
} 

template <typename T>
Interpolator<T>::Interpolator(const vector<tuple<T, T, T>> copy_vector)
{
	vector<tuple<T, T, T>> m_vector;
	m_data = copy_vector.size(); //sets the size of the new Interpolator to 
								 //the size of the copy_vector
	
	for(auto itr = copy_vector.begin(); itr != copy_vector.end(); itr++)
		this -> m_vector.push_back(*itr); //adds each element one by one to 
										  //the new vector
}

template <typename T>
Interpolator<T>::Interpolator(const int num_data)
{
	if(num_data < 0) throw BoundErr(num_data);
	m_data = num_data; //sets the size of the data set able to be stored
	vector<tuple<T, T, T>> m_vector;
}

template <typename T>
Interpolator<T>::Interpolator(const Interpolator & cpy_intr)
{
	m_data = cpy_intr.m_data;
	m_vector.clear();
	for(auto itr = cpy_intr.m_vector.begin(); itr != cpy_intr.m_vector.end(); itr++)
		this -> m_vector.push_back(*itr);
}

template <typename T>
Interpolator<T> Interpolator<T>::operator=(const Interpolator<T> & rhs) const
{
	m_data = rhs.m_data;
	m_vector.clear(); //empties the vector first
	for(auto itr = rhs.m_vector.begin(); itr != rhs.m_vector.end(); itr++)
		this -> m_vector.push_back(*itr); //refills the vector
	return *this;
}

// operator== must be defined for type T
//needs to check if the value corresponds to the last element and handle exception
template <typename T>
const tuple<T, T, T> Interpolator<T>::operator[](const T index) const
{
	int counter = 0;
	typename vector<tuple<T, T, T>>::const_iterator itr = this -> m_vector.begin();

	if((m_data > 1) && (index < get<0>(*m_vector.rbegin())) && (index > get<0>(*m_vector.begin())))
	{	
		while(get<0>(*itr) <= index)
		{
			counter++;
			advance(itr, 1);
		}
	}
	else
		throw BoundErr(index);
	
	return m_vector.at(counter - 1);
}

template <typename T>
tuple<T, T, T> & Interpolator<T>::operator[](const T index)
{
	int counter = 0;
	typename vector<tuple<T, T, T>>::iterator itr = this -> m_vector.begin();

	if((m_data > 1) && (index <= get<0>(*m_vector.rbegin())) && (index >= get<0>(*m_vector.begin())))
	{	
		while(get<0>(*itr) <= index)
		{
			counter++;
			advance(itr, 1);
		}
	}
	else
		throw BoundErr(index);
	
	return m_vector.at(counter - 1);
}

//needs to be passed an IV that is in the vector
template <typename T>
tuple<T, T> Interpolator<T>::operator()(const T index)
{
	tuple<T, T> new_tuple;
	tuple<T, T, T> first_set;
	tuple<T, T, T> second_set;
	typename vector<tuple<T, T, T>>::iterator itr = this -> m_vector.begin();
	
	T bound_check = get<0>((*this)[index]); //sets up a checker for the while loop
										   //instead of accessing it every iteration

	while(get<0>(*itr) != bound_check)
		advance(itr, 1);
	
	first_set = *itr;	
	advance(itr, 1);
	second_set = *itr;
	
	get<0>(new_tuple) = get<1>(first_set) + ((get<1>(second_set) - get<1>(first_set))
		/ (get<0>(second_set) - get<0>(first_set))) * (index - get<0>(first_set));
		
	get<1>(new_tuple) = get<2>(first_set) + ((get<2>(second_set) - get<2>(first_set))
		/ (get<0>(second_set) - get<0>(first_set))) * (index - get<0>(first_set));
	return new_tuple;
}

template <typename T>
std::ostream & operator << (ostream & out, const Interpolator<T> & rhs)
{	
	for(auto itr = rhs.m_vector.begin(); itr != rhs.m_vector.end(); itr++)
	{
		out << get<0>(*itr) << ": " << get<1>(*itr) << ", "
			<< get<2>(*itr) << endl;
	}
	return out;
}

template <typename T>
std::istream & operator >> (istream & in, Interpolator<T> & rhs)
{
	tuple<T, T, T> inserter;
	T previous;
	T current;
	
	rhs.m_vector.clear();
	
	for(int i = 0; i < rhs.m_data; i++)
	{
		in >> get<0>(inserter);
		in >> get<1>(inserter);
		in >> get<2>(inserter);
		
		rhs.m_vector.push_back(inserter);
		
		if(i == 0)
			previous = get<0>(inserter);
		else
		{
			current = get<0>(inserter);
			if(current <= previous) throw IncrementErr(current);
			previous = current;
		}
	}
	return in;
}		

template <typename T>
double Interpolator<T>::operator~() const
{
	double span = (get<0>(*m_vector.rbegin()) - get<0>(*m_vector.begin()));
	return span;
}

template <typename T>
bool Interpolator<T>::operator<(const Interpolator<T> & rhs) const
{
	bool relation = false;
	if(~*this < ~rhs)
		relation = true;
	return relation;
}

template <typename T>
bool Interpolator<T>::operator>(const Interpolator<T> & rhs) const
{
	bool relation = false;
	if(~*this > ~rhs)
		relation = true;
	return relation;
}

template <typename T>
bool Interpolator<T>::operator==(const Interpolator<T> & rhs) const
{
	bool relation = false;
	if(~*this == ~rhs)
		relation = true;
	return relation;
}

template <typename T>
bool Interpolator<T>::operator!=(const Interpolator<T> & rhs) const
{
	bool relation = false;
	if(~*this != ~rhs)
		relation = true;
	return relation;
}

IncrementErr::IncrementErr(const double i)
{
	m_iv = i;
}

double IncrementErr::getIncrement() const
{
	return m_iv;
}

BoundErr::BoundErr(const double i)
{
	m_iv = i;
}

double BoundErr::getBound() const
{
	return m_iv;
}