#include "IDV_Parser.h"

Parser::Parser()
{
}


Parser::~Parser()
{
}

void Parser::Lectura(const char * NombreArchivo)
{
	ifstream Archivo(NombreArchivo);
	if (Archivo.is_open())
	{
		while (getline(Archivo, LineaActual))
		{
			if (LineaActual == "xof 0303txt 0032")
			{
				cout << LineaActual << '\n';
			}

			int MatrizRelativo = LineaActual.find("FrameTransformMatrix relative");
			int findMesh = LineaActual.find("Mesh mesh");
			int findNormals = LineaActual.find("MeshNormals normals");
			int findTexture = LineaActual.find("MeshTextureCoords tc0");
			int findMaterialList = LineaActual.find("MeshMaterialList mtls");
			int findDiffuseMap = LineaActual.find("diffuseMap");

			if (findMesh != -1)
			{
				XMesh = new ContMesh;
				Archivo >> XMesh->vert >> separator;
				cout << "vertices: " << XMesh->vert << endl;
				XMesh->vertices = new MeshVertex[XMesh->vert];
				for (int i = 0; i < XMesh->vert; i++)
				{
					Archivo >> XMesh->vertices[i].x >> separator >> XMesh->vertices[i].y >> separator >> XMesh->vertices[i].z >> separator >> separator;
					//vertices.push_back(V);
				}
				Archivo >> XMesh->ind >> separator;
				cout << "indices: " << XMesh->ind << endl;
				XMesh->indices = new unsigned short[XMesh->ind * 3];
				for (int i = 0; i < XMesh->ind * 3; i++)
				{
					Archivo >> separator >> separator >> XMesh->indices[i] >> separator;
					i++;
					Archivo >> XMesh->indices[i] >> separator;
					i++;
					Archivo >> XMesh->indices[i] >> separator >> separator;
				}
			}
			if (findNormals != -1)
			{
				Archivo >> XMesh->vert >> separator;
				cout << "normals vertices: " << XMesh->vert << endl;
				for (int i = 0; i < XMesh->vert; i++)
				{
					Archivo >> XMesh->vertices[i].nx >> separator >> XMesh->vertices[i].ny >> separator >> XMesh->vertices[i].nz >> separator >> separator;
				}
			}
			if (findTexture != -1)
			{
				Archivo >> XMesh->vert >> separator;
				cout << "texture vertices: " << XMesh->vert;
				for (int i = 0; i < XMesh->vert; i++)
				{
					Archivo >> XMesh->vertices[i].s >> separator >> XMesh->vertices[i].t >> separator >> separator;
				}
			}
			if (findMaterialList != -1)
			{
			int ntriangles = 0;
			int nmaterial = 0;
			Archivo >> XMesh->totalmaterial >> separator;
			totMat = XMesh->totalmaterial;
			Archivo >> ntriangles >> separator;
			for (int i = 0; i < XMesh->totalmaterial; i++)
			{
				XMaterial = new Material;
				XMaterial->ind = 0;
				XMesh->materials.push_back(XMaterial);
			}

			for (int i = 0; i < ntriangles; i++)
			{
				Archivo >> nmaterial >> separator;
				XMesh->materials[nmaterial]->indices.push_back(XMesh->indices[i * 3 + 0]);
				XMesh->materials[nmaterial]->indices.push_back(XMesh->indices[i * 3 + 1]);
				XMesh->materials[nmaterial]->indices.push_back(XMesh->indices[i * 3 + 2]);
				XMesh->materials[nmaterial]->ind++;
			}
			/*contDiffuse = 0;
			}
			if (findDiffuseMap != -1)
			{
			myfile >> XMesh->materials[contDiffuse]->diffusepath;
			XMesh->materials[contDiffuse]->diffusepath = XMesh->materials[contDiffuse]->diffusepath.substr(1, XMesh->materials[contDiffuse]->diffusepath.size() - 3);
			cout << XMesh->materials[contDiffuse]->diffusepath;
			contDiffuse++;
			}
			if (contDiffuse == totMat)
			{
			contDiffuse = 0;
			while (contDiffuse < XMesh->totalmaterial)
			{
			int x = 0, y = 0, channels = 0;
			string path = "Textures/";
			path += XMesh->materials[contDiffuse]->diffusepath;
			unsigned char *buffer = stbi_load(path.c_str(), &x, &y, &channels, 0);

			glGenTextures(1, &XMesh->materials[contDiffuse]->diffuse_textID);
			glBindTexture(GL_TEXTURE_2D, XMesh->materials[contDiffuse]->diffuse_textID);

			glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, (void*)(buffer));
			glGenerateMipmap(GL_TEXTURE_2D);
			++contDiffuse;
			}
			contDiffuse = 0;*/
			Meshes.push_back(XMesh);
			}
			//cout << currentline << '\n';
		}
		Archivo.close();
	}

	else
	{
		cout << "invalid file type: exiting." << endl;
	}
}