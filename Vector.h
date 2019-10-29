#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <iostream>		// For debugging
#include <math.h>	// Math logic
#include <algorithm>	// Extra math logic
#include <vector>	// Dynamic arrays
#include <numeric>	// For mathmatical formulas

/* ----------------------------------------------------------------- Classes ----------------------------------------------------------------- */

// An abstract vector class
class v
{
protected:
	size_t	_size;	// Size of vector
	
public:
	std::vector<float> value;	// Vector value

	// Get the size of vector
	inline size_t comp_size()
	{
		return _size;	// Return size of vector
	}

	// Calculate length of vector
	inline virtual float length() { return 0.0f; }
	inline virtual float dot(v& that) { return 0.0f; }
	inline virtual void clamp_abs(float max) = 0;
	inline virtual void normalise() = 0;
};

// A class for storing a vector type with three components
class v3 : public v
{
public:
	// Default constructor
	inline v3()
	{
		_size = 3;	// Set vector size
		float a[] = { 0.0f, 0.0f, 0.0f };	// Set up raw array
		value.insert(value.begin(), a, a + _size);	// Insert values to container
	}

	// Initial constructor 0
	inline v3(float x, float y, float z)
	{
		_size = 3;	// Set vector size
		float a[] = { x, y, z };	// Set up raw array
		value.insert(value.begin(), a, a + _size);	// Insert values to container
	}

	// Initial constructor 1
	inline v3(float x)
	{
		_size = 3;	// Set vector size
		float a[] = { x, x, x };	// Set up raw array
		value.insert(value.begin(), a, a + _size);	// Insert values to container
	}

	// Additive lvalue operator overload
	inline v3 operator+(v3& that)
	{
		v3 res(0.0f);		// Resulting value
		for (unsigned int i = 0; i < _size; i++)	// For each component
			res.value[i] = value[i] + that.value[i];	// Calculate all component values

		return res;		// Return result
	}

	// Subtractive lvalue operator overload
	inline v3 operator-(v3& that)
	{
		v3 res(0.0f);		// Resulting value
		for (unsigned int i = 0; i < _size; i++)	// For each component
			res.value[i] = value[i] - that.value[i];	// Calculate all component values

		return res;		// Return result
	}

	// Multiplication lvalue operator overload
	inline v3 operator*(v3& that)
	{
		v3 res(0.0f);		// Resulting value
		for (unsigned int i = 0; i < _size; i++)	// For each component
			res.value[i] = value[i] * that.value[i];	// Calculate all component values

		return res;		// Return result
	}

	// Multiplication with double operator overload
	inline v3 operator*(float that)
	{
		v3 res;		// Resulting value
		for (unsigned int i = 0; i < _size; i++)	// For each component
			res.value[i] = value[i] * static_cast<float>(that);	// Calculate all component values

		return res;		// Return result
	}

	// Multiplication with double lvalue operator overload
	inline v3 operator*(float& that)
	{
		v3 res(0.0f);		// Resulting value
		for (unsigned int i = 0; i < _size; i++)	// For each component
			res.value[i] = value[i] * static_cast<float>(that);	// Calculate all component values

		return res;		// Return result
	}

	// Division lvalue operator overload
	inline v3 operator/(v3& that)
	{
		v3 res(0.0f);		// Resulting value
		for (unsigned int i = 0; i < _size; i++)	// For each component
			res.value[i] = value[i] / that.value[i];	// Calculate all component values

		return res;		// Return result
	}

	// Division with double operator overload
	inline v3 operator/(float that)
	{
		v3 res(0.0f);		// Resulting value
		for (unsigned int i = 0; i < _size; i++)	// For each component
			res.value[i] = value[i] / static_cast<float>(that);	// Calculate all component values

		return res;		// Return result
	}

	// Division with double lvalue operator overload
	inline v3 operator/(float& that)
	{
		v3 res(0.0f);		// Resulting value
		for (unsigned int i = 0; i < _size; i++)	// For each component
			res.value[i] = value[i] / static_cast<float>(that);	// Calculate all component values

		return res;		// Return result
	}

	// Calculate length of vector
	inline float length()
	{
		return sqrt((value[0] * value[0]) + (value[1] * value[1]) + (value[2] * value[2]));		// Calculate square root of each component multiplied by itself
	}

	// Calculate dot product between another vector
	inline float dot(v& that)
	{
		return static_cast<float>(std::inner_product(std::begin(this->value), std::end(this->value), std::begin(that.value), 0.0f));
	}

	// Calculate clamp to absolute value
	inline void clamp_abs(float max)
	{
		if (max <= 0)	// Check if max is equal or less than zero
		{
			for (unsigned int i = 0; i < _size; i++)	// Iterate through each component
				value[i] = 0.0f;	// Set each component value to zero

			return;		// Return as normal
		}
		else if ((value[0] + value[1] + value[2]) == 0.0f)		// If the magnitude is equal to zero
			return;		// Return as normal

		auto m = std::min({ value[0], value[1], value[2] });	// Get min value from all components

		if (m < 0)	// If min value is less than zero
		{
			float m_abs = std::abs(m);	// Convert to absolute value

			for (unsigned int i = 0; i < _size; i++)	// Iterate through each component
				value[i] += m_abs;	// Offset lowest value to zero
		}

		float ratio = max / std::max({ value[0], value[1], value[2] });		// Get aspect from 0 - max

		for (unsigned int i = 0; i < _size; i++)	// Iterate through each component
			value[i] *= ratio;	// Assign ratio to max
	}

	// Calculate normalisation of vector
	inline void normalise()
	{
		clamp_abs(1.0f);	// Clamp from zero to one
	}
};

// Struct for comparing vector size
struct greater_v3
{
	// Main operator overload
	bool const operator()(v3& a, v3& b) const
	{
		return (a.length() < b.length());		// Return greater comparison
	}
};

// Struct for comparing vector size
struct less_v3
{
	// Main operator overload
	bool const operator()(v3& a, v3& b) const
	{
		return (a.length() > b.length());		// Return less comparison
	}
};

// Struct for returning lowest vector component value
struct lowest_comp_v3
{
	// Main operator overload
	bool const operator()(v3& a, v3& b) const
	{
		float aa = a.value[0];		// Get first for a
		float bb = b.value[0];		// Get first for b

		for (unsigned int i = 1; i < a.comp_size(); i++)	// Iterate through each component
		{
			if (aa > a.value[i])	// If first a is greater than comparison
				aa = a.value[i];	// Assign comparison to first a

			if (bb > b.value[i])	// If first b is greater than comparison
				bb = b.value[i];	// Assign comparison to first b
		}

		return (aa < bb);	// Return lowest comparison
	}
};


/* ----------------------------------------------------------------- Global functions ----------------------------------------------------------------- */

// Return min float value
inline static float min_f(std::vector<float> x)
{
	float res = x[0];	// Get first element
	for (unsigned int i = 0; i < x.size(); i++)		// Iterate through each value
		if (res > x[i])		// If first is greater than comparison
			res = x[i];		// Assign comparison to first

	return res;		// Return result
}

// Return max float value
inline static float max_f(std::vector<float> x)
{
	float res = x[0];	// Get first element
	for (unsigned int i = 0; i < x.size(); i++)		// Iterate through each value
		if (res < x[i])		// If first is less than comparison
			res = x[i];		// Assign comparison to first

	return res;		// Return result
}

// Sort an array of vectors - with "lh" being ascendence / descendence
inline static void sort_v3(std::vector<v3> &x, bool lh)
{
	!lh ? std::sort(x.begin(), x.end(), greater_v3()) : std::sort(x.begin(), x.end(), less_v3());	// Sort from min to max
}

// Calculate cross product between two vectors
inline static v3 cross_v3(v3 a, v3 b)
{
	v3 res(0.0f);	// Resulting object

	res.value[0] = a.value[1] * b.value[2] - a.value[2] * b.value[1];	// Calculate x
	res.value[1] = a.value[0] * b.value[2] - a.value[2] * b.value[0];	// Calculate y
	res.value[2] = a.value[0] * b.value[1] - a.value[1] * b.value[0];	// Calculate z

	return res;		// Return result
}

// Calculate clamp to absolute value
inline void clamp_abs_v3(v3& x, float max)
{
	if (max <= 0)	// Check if max is equal or less than zero
	{
		std::cout << "FlatPack Error: clamp_abs only takes number greater than zero!\n";	// Print error
		return;		// Return as normal
	}
	else if ((x.value[0] + x.value[1] + x.value[2]) == 0.0f)		// If the magnitude is equal to zero
		return;		// Return as normal

	auto m = std::min({ x.value[0], x.value[1], x.value[2] });	// Get min value from all components

	if (m < 0)	// If min value is less than zero
	{
		float m_abs = std::abs(m);	// Convert to absolute value

		for (unsigned int i = 0; i < x.comp_size(); i++)	// Iterate through each component
			x.value[i] += m_abs;	// Offset lowest value to zero
	}

	float ratio = max / std::max({ x.value[0], x.value[1], x.value[2] });		// Get aspect from 0 - max

	for (unsigned int i = 0; i < x.comp_size(); i++)	// Iterate through each component
		x.value[i] *= ratio;	// Assign ratio to max
}

// Calculate normalisation of vector
inline void normalise_v3(v3& x)
{
	clamp_abs_v3(x, 1.0f);	// Clamp from zero to one
}

// Clamp an array of vectors
inline static void clamp_array_v3(std::vector<v3> &x, float max)
{	
	if (max <= 0)	// Check if max is equal or less than zero
	{
		for (unsigned int i = 0; i < x.size(); i++)	// Iterate through each vector
			for (unsigned int j = 0; j < 3; j++)	// Iterate through each compoent
				x[i].value[j] = 0.0f;	// Set each component value to zero

		return;		// Return as normal
	}
	else if (x.size() <= 1)		// If there isn't enough elements to compare
	{
		std::cout << "FlatPack Error: clamp_abs only takes multiple elements for comparison!\n";	// Print error
		return;		// Return as normal
	}

	std::vector <float> comp;	// A list for comparing component values

	sort_v3(x, 0);	// Sort vector list to ascend

	v3 ol = *std::min_element(&x[0], &x[0] + x.size(), lowest_comp_v3());	// Get vector with min size
	for (unsigned int i = 0; i < 3; i++)	// Iterate through each component
		comp.push_back(ol.value[i]);	// Assign component values

	float m = min_f(comp);	// Get min component value

	if (m < 0)		// If min component value is less than zero
	{
		for (unsigned int i = 0; i < x.size(); i++)		// Iterate through each vector
			for (unsigned int j = 0; j < 3; j++)	// Iterate through each component
				x[i].value[j] += std::abs(m);	// Offset min value to zero
	}
	
	comp.resize(0);		// Clear list for calculating ratio
	sort_v3(x, 1);	// Sort vector list to descend

	v3 oh = *std::max_element(&x[0], &x[0] + x.size(), greater_v3());	// Get vector with max size
	for (unsigned int i = 0; i < 3; i++)	// Iterate through each component
		comp.push_back(oh.value[i]);	// Assign component values
	
	float r = max / max_f(comp);	// Get max vector component value
	
	for (unsigned int i = 0; i < x.size(); i++)		// Iterate through each vector
		for (unsigned int j = 0; j < 3; j++)	// Iterate through each component
			x[i].value[j] *= r;	// Multiply each component value with ratio

	sort_v3(x, 0);	// Resort vector list to ascend
}

// Normalise an array of vectors
inline static void normalise_array_v3(std::vector<v3> &x)
{
	clamp_array_v3(x, 1.0f);	// Clamp all vector values to one
}

// This function will calculate the center point of a list of points
inline static v3 calc_center(std::vector<v3> p)
{
	v3 res(0.0f);	// Initialise resulting value

	std::vector<float> x;	// List of x values
	std::vector<float> y;	// List of y values
	std::vector<float> z;	// List of z values

	for (unsigned int i = 0; i < p.size(); i++)		// Iterate through each point
	{
		x.push_back(p[i].value[0]);		// Store x values
		y.push_back(p[i].value[1]);		// Store y values
		z.push_back(p[i].value[2]);		// Store z values
	}

	res = v3(	(min_f(x) + max_f(x)) / 2.0f,		// Calculate center for x
				(min_f(y) + max_f(y)) / 2.0f,		// Calculate center for y
				(min_f(z) + max_f(z)) / 2.0f);		// Calculate center for z

	return res;		// Return the resulting value
}

#endif