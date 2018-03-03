#include <IDVVideo/IDVGLShader.h>
#include <IDVScene/GLMesh.h>
#include <IDVUtils/IDVUtils.h>
#define BUFFER_OFFSET(i) ((char *)NULL + (i))

void GLMesh::Create(char* t) {
	SigBase = IDVSig::HAS_TEXCOORDS0;

	char *vsSourceP = file2string("Shaders/VS_Mesh.glsl");
	char *fsSourceP = file2string("Shaders/FS_Mesh.glsl");

	std::string vstr = std::string(vsSourceP);
	std::string fstr = std::string(fsSourceP);

	free(vsSourceP);
	free(fsSourceP);

	g_pBaseDriver->CreateShader(vstr, fstr, SigBase);

	ParserMesh.Lectura(t);

	for (int i = 0; i < ParserMesh.Meshes.size(); i++)
	{
		glGenBuffers(1, &VB);
		glBindBuffer(GL_ARRAY_BUFFER, VB);
		glBufferData(GL_ARRAY_BUFFER, ParserMesh.Meshes[i]->vert * sizeof(MeshVertex), ParserMesh.Meshes[i]->vertices, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glGenBuffers(1, &IB);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, (ParserMesh.Meshes[i]->ind * 3) * sizeof(unsigned short), ParserMesh.Meshes[i]->indices, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	//	for (int j = 0; j <ParserMesh.Meshes[i]->totalmaterial; j++)
	//	{
	//		glGenBuffers(1, &ParserMesh.Meshes[i]->materials[j]->IB);
	//		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ParserMesh.Meshes[i]->materials[j]->IB);
	//		glBufferData(GL_ELEMENT_ARRAY_BUFFER, (ParserMesh.Meshes[i]->materials[j]->ind * 3) * sizeof(unsigned short), &ParserMesh.Meshes[i]->materials[j]->indices[0], GL_STATIC_DRAW);
	//		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	//	}
	}
	XMatIdentity(transform);
}

void GLMesh::Transform(float *t) {
	for (int i = 0; i < 16; i++)
	{
		transform.mat[i] = t[i];
	}
}

void GLMesh::Draw(float *t, float *vp) {
	if (t)
		for (int i = 0; i < 16; i++)
		{
			transform.mat[i] = t[i];
		}

	unsigned int sig = SigBase;
	sig |= gSig;
	IDVGLShader * s = dynamic_cast<IDVGLShader*>(g_pBaseDriver->GetShaderSig(sig));

	XMATRIX44 VP;
	XMATRIX44 WV;

	for (int i = 0; i < 16; i++)
	{
		VP.mat[i] = vp[i];
		WV.mat[i] = vp[i];
	}
	//XMATRIX44 WVP = transform * VP;

	glUseProgram(s->ShaderProg);

	glUniformMatrix4fv(s->matWorldUniformLoc, 1, GL_FALSE, &transform.m[0][0]);
	glUniformMatrix4fv(s->matWorldViewProjUniformLoc, 1, GL_FALSE, &transform.m[0][0]);
	glUniformMatrix4fv(s->matWorldViewUniformLoc, 1, GL_FALSE, &WV.m[0][0]);

	for (int i = 0; i < ParserMesh.Meshes.size(); i++)
	{
		glBindBuffer(GL_ARRAY_BUFFER, VB);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);

		glEnableVertexAttribArray(s->vertexAttribLoc);
		glVertexAttribPointer(s->vertexAttribLoc, 4, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), BUFFER_OFFSET(0));
		glEnableVertexAttribArray(s->normalAttribLoc);
		glVertexAttribPointer(s->normalAttribLoc, 4, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), BUFFER_OFFSET(16));
		glEnableVertexAttribArray(s->uvAttribLoc);
		glVertexAttribPointer(s->uvAttribLoc, 2, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), BUFFER_OFFSET(32));

		for (int j = 0; j < ParserMesh.Meshes[i]->materials.size(); j++)
		{
		//	if (diffuseAttribLoc != -1)
		//	{
		//		glActiveTexture(GL_TEXTURE0);
		//		glBindTexture(GL_TEXTURE_2D, Meshes[i]->materials[j]->diffuse_textID);
		//		glUniform1i(diffuseAttribLoc, 0);
		//	}
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ParserMesh.Meshes[i]->materials[j]->IB);
		//	//glDrawElements(GL_TRIANGLES, Meshes[i]->ind * 3, GL_UNSIGNED_SHORT, 0);
			glDrawElements(GL_TRIANGLES, ParserMesh.Meshes[i]->materials[j]->ind * 3, GL_UNSIGNED_SHORT, 0);
		}
	}
}

void GLMesh::Destroy() {
}