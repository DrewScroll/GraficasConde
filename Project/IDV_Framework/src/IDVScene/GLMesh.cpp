#include <IDVVideo/IDVGLShader.h>
#include <IDVScene/GLMesh.h>
#include <IDVUtils/IDVUtils.h>
#define BUFFER_OFFSET(i) ((char *)NULL + (i))

void GLMesh::Create(char* t) {
	SigBase = IDVSig::HAS_TEXCOORDS0 | IDVSig::HAS_NORMALS;

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
		mesh_info tmp;
		glGenBuffers(1, &tmp.VB_ID);
		glBindBuffer(GL_ARRAY_BUFFER, tmp.VB_ID);
		glBufferData(GL_ARRAY_BUFFER, ParserMesh.Meshes[i]->vert * sizeof(MeshVertex), ParserMesh.Meshes[i]->vertices, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glGenBuffers(1, &tmp.IB_ID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, tmp.IB_ID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, (ParserMesh.Meshes[i]->ind * 3) * sizeof(unsigned short), ParserMesh.Meshes[i]->indices, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		for (int j = 0; j < ParserMesh.Meshes[i]->totalmaterial; j++)
		{
			subset_info tmp_2;
			glGenBuffers(1, &tmp_2.IB_ID);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, tmp_2.IB_ID);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, (ParserMesh.Meshes[i]->materials[j]->ind * 3) * sizeof(unsigned short), &ParserMesh.Meshes[i]->materials[j]->indices[0], GL_STATIC_DRAW);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
			tmp.subInfo.push_back(tmp_2);
		}

		MeshInfo.push_back(tmp);
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

	XMATRIX44 Scale;
	XMATRIX44 View;
	XMATRIX44 Projection;
	XMatViewLookAtLH(View, XVECTOR3(0.0f, 0.0f, -10.0f), XVECTOR3(0.0f, 0.0f, 1.0f), XVECTOR3(0.0f, 1.0f, 0.0f));
	XMatPerspectiveLH(Projection, Deg2Rad(60.0f), 1280.0f / 720.0f, 0.1f, 100.0f);
	XMatScaling(Scale, 0.15f, 0.15f, 0.15f);
	XMATRIX44 WVP = Scale*View*Projection;

	glUseProgram(s->ShaderProg);

	glUniformMatrix4fv(s->matWorldUniformLoc, 1, GL_FALSE, &transform.m[0][0]);
	glUniformMatrix4fv(s->matWorldViewProjUniformLoc, 1, GL_FALSE, &WVP.m[0][0]);
	glUniformMatrix4fv(s->matWorldViewUniformLoc, 1, GL_FALSE, &WV.m[0][0]);

	for (int i = 0; i < ParserMesh.Meshes.size(); i++)
	{
		glBindBuffer(GL_ARRAY_BUFFER, MeshInfo[i].VB_ID);

		glEnableVertexAttribArray(s->vertexAttribLoc);
		glVertexAttribPointer(s->vertexAttribLoc, 4, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), BUFFER_OFFSET(0));
		if (s->normalAttribLoc != -1) {
			glEnableVertexAttribArray(s->normalAttribLoc);
			glVertexAttribPointer(s->normalAttribLoc, 4, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), BUFFER_OFFSET(16));
		}
		if (s->uvAttribLoc != -1) {
			glEnableVertexAttribArray(s->uvAttribLoc);
			glVertexAttribPointer(s->uvAttribLoc, 2, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), BUFFER_OFFSET(32));
		}

		for (int j = 0; j < ParserMesh.Meshes[i]->materials.size(); j++)
		{
		//	if (diffuseAttribLoc != -1)
		//	{
		//		glActiveTexture(GL_TEXTURE0);
		//		glBindTexture(GL_TEXTURE_2D, Meshes[i]->materials[j]->diffuse_textID);
		//		glUniform1i(diffuseAttribLoc, 0);
		//	}
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, MeshInfo[i].subInfo[j].IB_ID);
		//	//glDrawElements(GL_TRIANGLES, Meshes[i]->ind * 3, GL_UNSIGNED_SHORT, 0);
			glDrawElements(GL_TRIANGLES, ParserMesh.Meshes[i]->materials[j]->ind * 3, GL_UNSIGNED_SHORT, 0);
		}
	}
}

void GLMesh::Destroy() {
}