//#version 120

varying vec2 texCoord;
varying vec3 position;
varying vec3 normal;

void main()
{
	gl_FrontColor =  gl_Color;
	gl_Position = gl_Vertex;
    gl_Position = ftransform();


    
//    vec4 bumpColor = texture2D(litsphereTexture, gl_MultiTexCoord0.st);
//    float df = 0.30 * bumpColor.x + 0.59 * bumpColor.y + 0.11 * bumpColor.z;
//    vec4 newVertexPos = vec4(gl_Normal * df * float(100.0), 0.0) + gl_Vertex;
//    texCoord = gl_TexCoord[0].st;
    
    position = vec3(gl_ModelViewMatrix * gl_Vertex);
    normal = normalize(gl_NormalMatrix * gl_Normal);
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
    
    gl_TexCoord[0] = gl_MultiTexCoord0;
    texCoord = gl_MultiTexCoord0.st;
}
