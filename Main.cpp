#include "FlatPack.h"	// Main directory

// The main protocal (Debugging purposes)
int main(int** argc, char** argv)
{
	std::vector<flatpack::uv_element> mesh;
	std::vector<v3>	points;
	std::vector<v3> normals;
	std::vector<unsigned int> indices;

	v3 p[4] = { v3(1.0f, 1.0f, 0.0f),
				v3(-1.0f, 1.0f, 0.0f), 
				v3(1.0f, -1.0f, 0.0f), 
				v3(-1.0f, -1.0f, 0.0f) };

	unsigned int i[6] = { 0, 1, 2, 2, 1, 3 };

	
	//for (size_t i = 0; i < 3; i++)
	normals.push_back(v3(0.0f, 0.0f, 1.0f));
	normals.push_back(v3(0.0f, 0.0f, 1.0f));
	normals.push_back(v3(0.0f, 0.0f, 1.0f));
	normals.push_back(v3(0.52f, 1.0f, 0.2f));

	points.insert(points.begin(), p, p + 4);
	indices.insert(indices.begin(), i, i + 6);

	
	mesh = flatpack::split_uvs(points, normals, indices);

	for (unsigned int ind = 0; ind < indices.size(); ind++)
	{
		std::cout << "Vertex " << ind << "\n";
		std::cout << "Point: " << mesh[0].vertices[ind].position.value[0] << " " << mesh[0].vertices[ind].position.value[1] << " " << mesh[0].vertices[ind].position.value[2] << "\n";
		std::cout << "Normal: " << mesh[0].vertices[ind].normal.value[0] << " " << mesh[0].vertices[ind].normal.value[1] << " " << mesh[0].vertices[ind].normal.value[2] << "\n\n";
	}
	 
	system("PAUSE");	// Pause console
	return 0;	// Exit from console
}