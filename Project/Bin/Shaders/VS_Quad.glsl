attribute highp vec4 Vertex;
attribute highp vec2 UV;

varying highp vec2 vecUVCoords;
varying highp vec4 Pos;

uniform highp mat4 WVP;
uniform highp mat4 World;
uniform highp mat4 WorldView;

void main(){
	vecUVCoords = UV;	
	Pos = Vertex;
	gl_Position = Pos;
}