#include <IDVVideo/IDVGLShader.h>
#include <IDVScene/IDVGLQuad.h>
#include <IDVUtils/IDVUtils.h>

void GLQuad::Create(){
	SigBase = IDVSig::HAS_TEXCOORDS0;

	char *vsSourceP = file2string("Shaders/VS_Quad.glsl");
	char *fsSourceP = file2string("Shaders/FS_Quad.glsl");

	std::string vstr = std::string(vsSourceP);
	std::string fstr = std::string(fsSourceP);

	free(vsSourceP);
	free(fsSourceP);

	g_pBaseDriver->CreateShader(vstr, fstr, SigBase);

	vertices[0] = { -1.0f,  1.0f, 0.0f, 1.0f,  0.0f, 0.0f };
	vertices[1] = { -1.0f, -1.0f, 0.0f, 1.0f,  0.0f, 1.0f };
	vertices[2] = {  1.0f, -1.0f, 0.0f, 1.0f,  1.0f, 1.0f };
	vertices[3] = {  1.0f,  1.0f, 0.0f, 1.0f,  1.0f, 0.0f };

	indices[0] = 2;
	indices[1] = 1;
	indices[2] = 0;
	indices[3] = 3;
	indices[4] = 2;
	indices[5] = 0;

	glGenBuffers(1, &VB);
	glBindBuffer(GL_ARRAY_BUFFER, VB);
	glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(Vert), &vertices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &IB);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned short), indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

void GLQuad::Transform(float *t){
	transform = t;
}

void GLQuad::Draw(float *t, float *vp){

	if (t)
		transform = t;

	unsigned int sig = SigBase;
	sig |= gSig;
	IDVGLShader * s = dynamic_cast<IDVGLShader*>(g_pBaseDriver->GetShaderSig(sig));

	XMATRIX44 VP = vp;
	XMATRIX44 WV = vp;
	
	glUseProgram(s->ShaderProg);

	glUniformMatrix4fv(s->matWorldUniformLoc, 1, GL_FALSE, &transform.m[0][0]);
	glUniformMatrix4fv(s->matWorldViewProjUniformLoc, 1, GL_FALSE, &transform.m[0][0]);
	glUniformMatrix4fv(s->matWorldViewUniformLoc, 1, GL_FALSE, &WV.m[0][0]);

	glBindBuffer(GL_ARRAY_BUFFER, VB);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);

	glEnableVertexAttribArray(s->vertexAttribLoc);
	glVertexAttribPointer(s->vertexAttribLoc, 4, GL_FLOAT, GL_FALSE, sizeof(Vert), BUFFER_OFFSET(0));
	glEnableVertexAttribArray(s->uvAttribLoc);
	glVertexAttribPointer(s->uvAttribLoc, 2, GL_FLOAT, GL_FALSE, sizeof(Vert), BUFFER_OFFSET(16));

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
}

void GLQuad::Destroy(){

}
