#ifndef __FLAT_PACK_H__
#define __FLAT_PACK_H__

#include "Vector.h"		// Get variable types

/*	OCTAGRAM (C) 2018 - All rights reserved. Users may examin			// --------------------
	the code of Flatpack library to further their acknowledgment. */	// --------------------

#define PLANAR_DOT_THRESHOLD	(static_cast<float>(0.1f))	// Threshold for planar projection


// Main library namespace for native structures and functions
namespace flatpack
{
	// This will contain one set of v* data
	struct vertex
	{
		v3	position;	// Vertex position
		v3	normal;		// Vertex normal

		// Default constructor
		inline vertex() : position(v3(0.0f)), normal(v3(0.0f)) {}

		// Initial constructor
		inline vertex(v3 p, v3 n)
		{
			position = p;	// Assign position
			normal = n;		// Assign normal
		}
	};

	// This will contain a triangle arbitary for uv segmentation
	struct triangle
	{
		v3	origin;		// The central position
		v3	normal;		// The direction vector
		v3	points[3];	// Three points for each corner

		// Default constructor
		inline triangle() : origin(v3(0.0f)), normal(v3(0.0f))
		{
			for (size_t i = 0; i < 4; i++)	// Iterate through each point
				points[i] = v3(0.0f);	// Initialise each point
		}

		// Initial constructor 0
		inline triangle(v3 p[3], v3 n) : origin(v3(0.0f))
		{
			assign(p, n);	// Assign data
		}

		// Initial constructor 1
		inline triangle(v3 p0, v3 p1, v3 p2, v3 n) : origin(v3(0.0f))
		{
			v3 ind[3] = { p0, p1, p2 };		// Create indirect array from values
			assign(ind, n);		// Assign indirect array to point array
		}

		// Assign values
		inline void assign(v3 x[3], v3 n)
		{
			for (size_t i = 0; i < 3; i++)	// Iterate through each point
				points[i] = x[i];	// Assign each point

			origin = calc_center({ x[0], x[1], x[2] });		// Calculate local origin
			normal = n;		// Assign normal
		}	
	};

	// This struct will contain the basic data for an oriented plane
	struct uv_plane
	{
	};

	// This will contain one group of v* data
	struct uv_element
	{
		uint16_t				id;		// Unique id
		std::vector<vertex>		vertices;	// List of v* data

		// Default constructor
		inline uv_element() : id(0) {}

		// Initial constructor
		inline uv_element(uint16_t i, std::vector<vertex> v)
		{
			id = i;			// Assign id
			vertices = v;	// Assign vertex positions
		}
	};

	// This will contain a heriarchal structure of uv elements
	struct uv_skeleton
	{
		std::vector<uv_element>	_uv_elements;	// A list of uv groups
	};

	// This function will split up uvs into seperate elements
	inline static std::vector<uv_element> split_uvs(std::vector<v3> &p, std::vector<v3> &n, std::vector<unsigned int> &i)
	{
		std::vector<uv_element> res;	// Resulting object

		// Step 1: Gather and store indexed vertex data
		int						current_id(-1);		// Current id value
		unsigned int			index(0);	// Index iterator
		std::vector<vertex>		vertices;	// A list of vertex data
		std::vector<triangle>	triangles;	// A list of triangle data
		std::vector<uv_plane>	uv_planes;	// A list of uv plane data

		for (index = 0; index != i.size(); index += 3)	// Iterate through each index
		{
			vertices.push_back(vertex(p[i[index]], n[i[index]]));		// Assign vertex 0 t i
			vertices.push_back(vertex(p[i[index + 1]], n[i[index + 1]]));		// Assign vertex 1 t i
			vertices.push_back(vertex(p[i[index + 2]], n[i[index + 2]]));		// Assign vertex 2 t i

			v3 normal_avg = calc_center({ vertices[index].normal, vertices[index + 1].normal, vertices[index + 2].normal });		// Calculate normal center
						
			triangles.push_back(triangle(p[i[index]], p[i[index + 1]], p[i[index + 2]], normal_avg));	// Assign triangle i
		}
		
		std::cout << "Dot " << triangles[1].normal.dot(triangles[0].normal) << "\n\n";

		// Step 2: Check for triangles that share similar normals
		res.push_back(uv_element(0, vertices));		// TEMP

		return res;		// Return result
	}

	// This function will uv unwrap vertex data
	inline static uv_skeleton uv_unwrap(std::vector<v3> &p, std::vector<v3> &n, std::vector<unsigned int> &i)
	{
		uv_skeleton res;	// Result object

		if (p.size() != n.size())	// If the size between both lists do not match
		{
			std::cerr << "Flatpack Error: Positions and normals are incorrectly indexed!\n";	// Print error
			return res;		// Return empty object
		}
		else if (i.size() % 3 != 0)		// Otherwise, if the index size is NOT in a multiple of three
		{
			std::cerr << "Flatpack Error: Index data is corrupt!\n";	// Print error
			return res;		// Return empty object
		}

		// Step 1: Split indexed vertex data

	}
}


#endif