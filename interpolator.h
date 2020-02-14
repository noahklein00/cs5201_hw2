/*! \file
 *
 * Definitions for the Interpolator, IncrementErr, and BoundErr objects. \n
 * Programmer: Noah Klein \n
 * Class: CS5201 \n
 * Assignment: Homework 2 \n
 */
	
#ifndef INTERPOLATOR_H
#define INTERPOLATOR_H

#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>

using namespace std;

//! Interpolator class.
/*!
 * This class uses a vector of tuples of type T to store data points 
 * from a function. The purpose of the class is to be able to linearly
 * interpolate for both sets of dependent variables.
 */
template <typename T>
class Interpolator
{
	private:
		vector<tuple<T, T, T>> m_vector; /*!< A std::vector of type std::tuple 
				that is filled with 3 T objects. \n
				The c++ <vector>, <tuple>, and <algorithm> libraries are needed
				for this variable. */
		int m_data; ///< An integer that stores the size of the vector.
	public:
	
		/*! \brief Default constructor.
		 *	
		 * Description: Creates an empty vector of tuples of type T and sets
		 *		the size to the default of 20.
		 * \post An Interpolator object is declared with an empty vector and
		 *		sets m_data to 20.
		 */
		Interpolator();
		
		/*! \brief Constructor.
		 *
		 * Description: Copies the passed vector into the new Interpolator
		 *		object and sets the size equal to the size of the copied
		 *		vector. \n
		 * \param copy_vector is the vector to be copied.
		 * \post An Interpolator object is declared with a vector equal to the
		 *		one passed and m_data equals the size of the passed vector.
		 */
		Interpolator(const vector<tuple<T, T, T>> copy_vector);
		
		/*! \brief Constructor.
		 *
		 * Description: Creates an empty vector of tuples of type T and sets
		 *		the size to the value passed to the constructor.
		 * \param num_data is the integer m_data is set as.
		 * \pre num_data must be > 0.
		 * \post An Interpolator object is declared with m_data equal to 
		 *		num_data and with an empty vector of tuples of type T.
		 * \throws A BoundErr object if the user tries to declare a vector
		 * 		of a negative size.
		 */
		Interpolator(const int num_data);
		
		/*! \brief Copy constructor.
		 *
		 * Description: Copies the Interpolator passed to the function.
		 * \param cpy_intr is an Interpolator object to be copied.
		 * \post An Interpolator object is declared with member variables equal
		 *		to the member variables of the Interpolator passed to the
		 *		function.
		 */
		Interpolator(const Interpolator & cpy_intr);
		
		/*! \brief = operator overload.
	     *	
		 * Description: Sets the interpolator on the left of the operator equal
		 *		to the interpolator on the right of the operator.
		 * \param rhs is an Interpolator object that *this will be set equal
		 *		to.
		 * \return The new Interpolator set equal to the parameter is returned.
		 * \pre Needs an Interpolator object of type T declared.
		 * \post The calling object is now equal to the object passed.
		 */
		Interpolator<T> operator=(const Interpolator<T> & rhs) const;
		
		/*! \brief [] operator overload - const.
		 *
		 * Description: Finds the "independent variable" that is <= the index.
		 * \param index is the independent variable to be searched for.
		 * \return Returns a copy of the tuple pointed to in the vector.
		 * \pre The <, >, and <= operators need to be defined for type T.
		 * \post Returns a const tuple that is a copy of the one searched for
		 *		in the function.
		 * \throws A BoundErr object if the user tries to access an index
		 * 		that is out of range.
		 */
		const tuple<T, T, T> operator[](const T index) const;
		
		/*! \brief [] operator overload.
		 *
		 * Description: Finds the "independent variable" that is <= the index.
		 * \param index is the independent variable to be searched for.
		 * \return Returns a reference to the tuple pointed to in the vector.
		 * \pre The <, >, and <= operators need to be defined for type T.
		 * \post Returns a reference to the tuple in the vector that was
		 *		searched for in the function.
		 * \throws A BoundErr object if the user tries to access an index
		 * 		that is out of range.
		 */
		tuple<T, T, T> & operator[](const T index);
		
		/*! \brief () operator overload.
		 *
		 * Description: Performs linear interpolation for the two sets of
		 *		dependent variables stored in the Interpolator for the 
		 *		value passed in index.
		 * \param index is the independent variable that undergoes linear
		 *		interpolation.
		 * \return Returns a tuple that stores the dependent values of the 
		 * 		number that was passed to be interpolated.
		 * \pre The =, !=, +, and - operators need to be defined for type T.
		 * \post Returns a tuple that stores the interpolated values of the 
		 *		index that was passed.
		 */
		tuple<T, T> operator()(const T index);
		
		/*! \brief << operator overload.
	 	 *
		 * Description: Outputs the Interpolator in the correct format.
		 * \param rhs is the Interpolator object to be output.
		 * \param out allows the output stream to be modified.
		 * \return The modified output stream.
		 * \pre The << operator must be defined for type T.
		 * \post The contents of the Interpolator are printed to the 
				output stream.
		 */
		template <typename U>
		friend ostream& operator << (ostream& out, const Interpolator<U>& rhs);
		
		/*! \brief >> operator overload.
		 *
		 * Description: Allows the user to input data into the Interpolator.
		 * \param rhs is the Interpolator that store the input.
		 * \param in allows the input stream to be modified.
		 * \return The modified input stream.
		 * \pre The >> operator must be defined for type T and the user must
		 * 		know the correct format for inputting the variables.
		 * \post Stores the inputted variables in the correct spots in the 
		 *		Interpolator and overrides any previously stored data.
		 * \throws An IncrementErr object if the user tries to enter 
		 * 		independent variables that are not strictly increasing.
		 */
		template <typename U>
		friend istream& operator >> (istream& in, Interpolator<U>& rhs);
		
		/*! \brief ~ operator overload.
	     *	
		 * Description: Calculates the span of the Interpolator.
		 * \return A double that represents the span of the vector.
		 * \post Returns a double that stores the span of the "independent 
		 * 		variables" of the Interpolator object.
		 */
		double operator~() const;
		
		/*! \brief < operator overload.
	 	 * 
		 * Description: Checks if the calling Interpolator is < the right
		 *		side.
		 * \return A bool that represents the comparison.
		 * \pre The < operator needs to be defined for type T.
		 * \post Returns a bool to represent the comparison.
		 */
		bool operator<(const Interpolator<T> & rhs) const;
		
		/*! \brief > operator overload.
		 *
		 * Description: Checks if the calling Interpolator is > the right
		 *		side.
		 * \return A bool that represents the comparison.
		 * \pre The > operator needs to be defined for type T.
		 * \post Returns a bool to represent the comparison.
		 */
		bool operator>(const Interpolator<T> & rhs) const;
		
		/*! \brief == operator overload.
		 *
		 * Description: checks if the calling Interpolator is == the right
		 *		side.
		 * \return A bool that represents the comparison.
		 * \pre The == operator needs to be defined for type T.
		 * \post Returns a bool to represent the comparison.
		 */
		bool operator==(const Interpolator<T> & rhs) const;
		
		/*! \brief != operator overload.
		 *
		 * Description: checks if the calling Interpolator is != the right
		 *		side.
		 * \return A bool that represents the comparison.
		 * \pre The != operator needs to be defined for type T.
		 * \post Returns a bool to represent the comparison.
		 */
		bool operator!=(const Interpolator<T> & rhs) const;
};

/*! \brief << operator overload.
 *
 * Description: Outputs the Interpolator in the correct format.
 * \param rhs is the Interpolator object to be output.
 * \param out allows the output stream to be modified.
 * \return The modified output stream.
 * \pre The << operator must be defined for type T.
 * \post The contents of the Interpolator are printed to the 
		output stream.
 */
template <typename T>
std::ostream & operator << (ostream & out, const Interpolator<T> & rhs);

/*! \brief >> operator overload.
 *
 * Description: Allows the user to input data into the Interpolator.
 * \param rhs is the Interpolator that store the input.
 * \param in allows the input stream to be modified.
 * \return The modified input stream.
 * \pre The >> operator must be defined for type T and the user must
 * 		know the correct format for inputting the variables.
 * \post Stores the inputted variables in the correct spots in the 
 *		Interpolator and overrides any previously stored data.
 */
template <typename T>
std::istream & operator >> (istream & in, Interpolator<T> & rhs);

//! IncrementErr class
/*! The purpose of this class is to be able to give a more accurate 
 * description of the errors occuring during the running of the 
 * program.
 */
class IncrementErr
{
	private:
		double m_iv;
	public:
	
		/*! \brief Constructor.
		 *		
		 * Description: constructs the object and sets its member
		 *		variable = i \n
		 * \pre N/A \n
		 * \post Creates an IncrementErr object with member m_iv = i \n
		 */
		IncrementErr(const double i);
		
		/*! \brief Accessor.
		 *
		 * Description: accessor for the member variable \n
		 * \pre N/A \n
		 * \post returns the value of m_iv \n
		 */
		double getIncrement() const;
};

//! BoundErr class
/*! The purpose of this class is to be able to give a more accurate 
 * description of the errors occuring during the running of the 
 * program.
 */
class BoundErr
{
	private:
		double m_iv;
	public:
	
		/*! \brief Constructor.
		 *		
		 * Description: constructs the object and sets its member 
		 *		variable = i \n
		 * \pre N/A \n
		 * \post Creates an BoundErr object with member m_iv = i \n
		 */
		BoundErr(const double i);
		
		/*! \brief Accessor.
		 * 
		 * Description: accessor for the member variable \n
		 * \pre N/A \n
		 * \post returns the value of m_iv \n
		 */
		double getBound() const;
};

#include "interpolator.hpp"
#endif