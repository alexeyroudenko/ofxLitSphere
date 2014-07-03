//#version 120

varying vec2 texCoord;
varying vec3 position;
varying vec3 normal;

void main()
{
	gl_FrontColor =  gl_Color;
	gl_Position = gl_Vertex;
    gl_Position = ftransform();
    
    position = vec3(gl_ModelViewMatrix * gl_Vertex);
    normal = normalize(gl_NormalMatrix * gl_Normal);
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
    
    gl_TexCoord[0] = gl_MultiTexCoord0;
    texCoord = gl_MultiTexCoord0.st;
}
