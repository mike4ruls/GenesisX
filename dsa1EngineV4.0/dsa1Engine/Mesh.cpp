#include "Mesh.h"



Mesh::Mesh()
{
}
Mesh::Mesh(std::vector<Vertex> &v, std::vector<unsigned int> &i)
{
	verts = v;
	ind = i;
	count = ind.size();
	CreateBuffer();
}
Mesh::Mesh(std::string filename)
{
	using namespace std;
	ifstream inFile;
	string info;

	vector<glm::vec3> pos;
	vector<glm::vec2> uv;
	vector<glm::vec3> nor;
	vector<unsigned int> in;

	inFile.open(filename);
	if(inFile.is_open())
	{
		while(getline(inFile, info))
		{
			char type;
			istringstream ss(info);

			ss >> type;
			if(type == 'v')
			{
			
			}
			else if (type == 'vt')
			{

			}
			else if (type == 'vn')
			{

			}
			else if (type == 'f')
			{

			}
		}
		inFile.close();
	}
	


}

Mesh::~Mesh()
{
}

void Mesh::CreateBuffer()
{
	std::vector<Vertex> vertBufData(count);

	for (unsigned int i = 0; i < count; i++)
	{
		vertBufData[i] = verts[ind[i]];
	}

	// generating buffer and storing their addresses to out init variables
	glGenVertexArrays(1, &vertArr);
	glGenBuffers(1, &vertBuf);

	// placing our buffer on the machine
	glBindVertexArray(vertArr);
	glBindBuffer(GL_ARRAY_BUFFER, vertBuf);

	// binding our data to the buffer on the machine, know they wont change in size not matter what
	glBufferData(GL_ARRAY_BUFFER,
		sizeof(Vertex)*count,
		&vertBufData[0],
		GL_STATIC_DRAW);

	// letting the computer know how the buffer is structured
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(0, // the index
		3, // number of components to expect(x,y,z)
		GL_FLOAT, // Type of data
		GL_FALSE, // should we normalize the data
		sizeof(Vertex), // stride
		0); // the offset 
	
		glVertexAttribPointer(1,
			2, // number of components to expect(u,v)
			GL_FLOAT,
			GL_FALSE,
			sizeof(Vertex),
			reinterpret_cast<void *>(offsetof(Vertex, uv)));

		glVertexAttribPointer(2,
			3,// number of components to expect(x,y,z)
			GL_FLOAT, 
			GL_FALSE, 
			sizeof(Vertex), 
			reinterpret_cast<void *>(offsetof(Vertex, normal)));

		glVertexAttribPointer(3,
			4,// number of components to expect(r,g,b,a)
			GL_FLOAT,
			GL_FALSE,
			sizeof(Vertex),
			reinterpret_cast<void *>(offsetof(Vertex, color)));
	glBindVertexArray(0);
}
