#version 120

uniform sampler2D litsphereTexture;

varying vec2 texCoord;
varying vec3 position;
varying vec3 normal;

void main()
{
	gl_FrontColor =  gl_Color;
	gl_TexCoord[0] = gl_MultiTexCoord00
	gl_Position = gl_Vertex;
    
    texCoord = vec2(gl_MultiTexCoord);
    
    position = vec3(gl_ModelViewMatrix * gl_Vertex);
    normal = normalize(gl_NormalMatrix * gl_Normal);
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}
