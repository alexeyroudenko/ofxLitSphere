////////////////////////////////////////////////////////////////////////
// litSphere.fx
// Matballz.fx
//
//	Shader by Charles Hollemeersch http://charles.hollemeersch.net/
//	Public domain.
//
//	Parameters:
//
//		Bumpmap Strength: Scales the bumps to be flatter/steeper
//                        (i.e. more/less towards 0,0,1).
//		Normal Map      : Provides a bumpmap if no map is provided the
//                        geometry normal is used.
//		Lit Sphere Map  : The prelighted sphere to apply as a light. Check
//                        http://www.cs.utah.edu/npr/papers/LitSphere_HTML/
//                        to get some inspiration.
//
//  Edited: 12/13/2009 - Leonardo Covarrubias - For use in Maya
// 	
//
////////////////////////////////////////////////////////////////////////



////////////////////////
// User interface
////////////////////////

float normalPower <
	string UIName = "Bumpmap Strength";
	string UIWidget = "slider";
	float UIMin = 0.0;
	float UIMax = 2.0;
	float UIStep = 0.1;
> = 1.0;

bool flipGreen
<
    string UIName = "Invert Normal Map Green Channel?";
> = false;

texture normalMap : Normal <
	string UIName = "Normal Map";
	string ResourceName = "";
	string ResourceType = "2D";
>;

texture litSphereMap : LitSphere <
	string UIName = "Lit Sphere Map";
	string ResourceName = "";
	string ResourceType = "2D";
>;

////////////////////////
// Samplers
////////////////////////

sampler NormalSampler = sampler_state {
	Texture = <normalMap>;
    MIPFILTER = LINEAR;
    MINFILTER = LINEAR;
    MAGFILTER = LINEAR;
    AddressU  = CLAMP;		
    AddressV  = CLAMP;	
};

sampler LightSampler = sampler_state {
	Texture = <litSphereMap>;
    MIPFILTER = LINEAR;
    MINFILTER = LINEAR;
    MAGFILTER = LINEAR;
    AddressU  = CLAMP;		
    AddressV  = CLAMP;
};

////////////////////////
// Matrices
////////////////////////

float4x4 WorldView            : WORLDVIEW;
float4x4 WorldViewProjection  : WORLDVIEWPROJECTION;

////////////////////////
// Exchange structs
////////////////////////

struct a2v 
{
	float4 Position : POSITION; 
	float2 TexCoord : TEXCOORD0;
	float3 Tangent  : TANGENT;
	float3 Binormal : BINORMAL;
	float3 Normal   : NORMAL;
};

struct v2f 
{
	float4 Position : POSITION;
	float2 TexCoord : TEXCOORD0;
	float3 TexCoord1 : TEXCOORD1;
	float3 TexCoord2 : TEXCOORD2;
	float3 TexCoord3 : TEXCOORD3;
};

////////////////////////
// Vertex shader
////////////////////////

v2f BumpReflectVS(a2v IN)
{
	v2f OUT;

	// Pos to NDC
	OUT.Position = mul(float4(IN.Position.xyz,1), WorldViewProjection);
	
	// Texcoords (for normal map)
	OUT.TexCoord.xy = IN.TexCoord;
	
	// Tangent space vectors
	float3 vtan = IN.Tangent;
	float3 vbinorm = -IN.Binormal;
	float3 vnorm = IN.Normal;

	OUT.TexCoord1.xyz = mul(vtan,WorldView);
	OUT.TexCoord2.xyz = mul(vbinorm,WorldView);
	OUT.TexCoord3.xyz = mul(vnorm,WorldView);
	
	return OUT;
}

////////////////////////
// Pixel shader
////////////////////////

float4 BumpReflectPS(v2f IN) : COLOR {

	float3 texNormal = tex2D(NormalSampler, IN.TexCoord.xy).xyz;
	if(flipGreen)texNormal.g = 1-texNormal.g;
	texNormal.rgb = texNormal.rgb*2.0-1.0;
	// Fixes normals if no normal map texture is supplied
	if ( dot(texNormal,texNormal) > 2.0 ) {
		texNormal = float3(0,0,1);
	}
	
	// The normalizes can probably go away... but meh...
    float3 T = normalize(IN.TexCoord1.xyz) * normalPower;
    float3 B = normalize(IN.TexCoord2.xyz) * normalPower;
    float3 N = normalize(IN.TexCoord3.xyz);
		
	// Put in world space and renormalize (after scaling)
    float3 worldNorm = normalize(N + texNormal.y * B + texNormal.x * T);

	// Swap it around a bit... 
	worldNorm.y = - worldNorm.y;

	// Look up in the litsphere!
	float3 light = tex2D(LightSampler, worldNorm.xy * 0.5 + 0.5).xyz;
	return float4( light, 1.0 );
}

////////////////////////
// Pixel shader
////////////////////////

technique litSphere
{
	pass one
    {
    VertexShader = compile vs_2_0 BumpReflectVS();
    PixelShader = compile ps_2_0 BumpReflectPS();
    }
}

