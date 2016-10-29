#version 120

uniform sampler2D litsphereTexture;

varying vec2 texCoord;
varying vec3 position;
varying vec3 normal;

void main (void)
{
    //   gl_FragColor = gl_Color;
    
	vec3 eyeNormal = normal;
	vec3 L = normalize(gl_LightSource[0].position.xyz - position);
	vec3 E = normalize(-position); // we are in Eye Coordinates, so EyePos is (0,0,0)
	vec3 R = normalize(-reflect(L, eyeNormal));
    
	//calculate Ambient Term:
	vec4 Iamb = gl_FrontLightProduct[0].ambient;
    
	//calculate Diffuse Term:
	vec4 Idiff = gl_FrontLightProduct[0].diffuse * max(dot(eyeNormal, L), 0.0);
	Idiff = clamp(Idiff, 0.0, 1.0);
    
	// calculate Specular Term:
	vec4 Ispec = gl_FrontLightProduct[0].specular * pow(max(dot(R, E), 0.0),0.3 * gl_FrontMaterial.shininess);
	Ispec = clamp(Ispec, 0.0, 1.0);
    
//    vec4 shading = texture2D(litsphereTexture, vec2(normal.xyz * vec3(0.495) + vec3(0.5)));

	vec4 color = texture2D(litsphereTexture, texCoord);
	gl_FragColor = gl_FrontLightModelProduct.sceneColor + Iamb + Idiff + Ispec + color;// + color;
//    gl_FragColor = shading;
}