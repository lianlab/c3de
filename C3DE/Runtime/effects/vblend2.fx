//=============================================================================
// vblend2.fx by Frank Luna (C) 2004 All Rights Reserved.
//
// Does vertex blending with _two_ bone influences per vertex and
// phong directional lighting.
//
// NOTE: Assumes the bone transformations are rigid body so that we
//       do not need to apply the inverse transpose.  (We do not make
//       this assumption with the world matrix though.)
//=============================================================================

struct Mtrl
{
	float4 ambient;
	float4 diffuse;
	float4 spec;
	float  specPower;
};

struct DirLight
{
	float4 ambient;
	float4 diffuse;
	float4 spec;
	float3 dirW;  
};

uniform extern float4x4 gWorld;
uniform extern float4x4 gWorldInvTrans;
uniform extern float4x4 gWVP;
uniform extern float4x4 gFinalXForms[35];
uniform extern Mtrl     gMtrl;
uniform extern DirLight gLight;
uniform extern float3   gEyePosW;
uniform extern texture  gTex;

uniform extern float4 gAmbientMtrl;
uniform extern float4 gAmbientLight;
uniform extern float4 gDiffuseMtrl;
uniform extern float4 gDiffuseLight;
uniform extern float4 gSpecularMtrl;
uniform extern float4 gSpecularLight;
uniform extern float  gSpecularPower;
uniform extern float3 gLightVecW;


uniform extern float4x4 gTransformMatrix;
uniform extern float gAlpha;

sampler TexS = sampler_state
{
	Texture = <gTex>;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
	AddressU  = WRAP;
    AddressV  = WRAP;
};
 
struct OutputVS
{
    float4 posH    : POSITION0;
    float3 normalW : TEXCOORD0;
    float3 toEyeW  : TEXCOORD1;
    float2 tex0    : TEXCOORD2;
};


OutputVS VBlend2VS(float3 posL    : POSITION0, 
                   float3 normalL : NORMAL0, 
                   float2 tex0    : TEXCOORD0,
                   float weight0  : BLENDWEIGHT0, 
                   int4 boneIndex : BLENDINDICES0)
{
    // Zero out our output.
	OutputVS outVS = (OutputVS)0;
	
	// Do the vertex blending calculation for posL and normalL.
	float weight1 = 1.0f - weight0;
    
    float4 p = weight0 * mul(float4(posL, 1.0f), gFinalXForms[boneIndex[0]]);
    p       += weight1 * mul(float4(posL, 1.0f), gFinalXForms[boneIndex[1]]);
    p.w = 1.0f;
    
    // We can use the same matrix to transform normals since we are assuming
    // no scaling (i.e., rigid-body).
    float4 n = weight0 * mul(float4(normalL, 0.0f), gFinalXForms[boneIndex[0]]);
    n       += weight1 * mul(float4(normalL, 0.0f), gFinalXForms[boneIndex[1]]);
    n.w = 0.0f;

	// Transform normal to world space.
	outVS.normalW = mul(n, gWorldInvTrans).xyz;
	
	// Transform vertex position to world space.
	float3 posW  = mul(p, gWorld).xyz;
	
	// Compute the vector from the vertex to the eye.
	outVS.toEyeW = gEyePosW - posW;
	
	float4 newPos = mul(p, gTransformMatrix);
	
	// Transform to homogeneous clip space.
	//outVS.posH = mul(p, gWVP);
	outVS.posH = mul(newPos, gWVP);
	
	// Pass on texture coordinates to be interpolated in rasterization.
	outVS.tex0 = tex0;

	// Done--return the output.
    return outVS;
}

float4 VBlend2PS(float3 normalW : TEXCOORD0, float3 toEyeW  : TEXCOORD1, float2 tex0 : TEXCOORD2) : COLOR
{
	// Interpolated normals can become unnormal--so normalize.
	normalW = normalize(normalW);
	toEyeW  = normalize(toEyeW);
	
	// Light vector is opposite the direction of the light.
	float3 lightVecW = -float3(0.0f, 0.0f, 0.0f);
	//float3 lightVecW = gLight.dirW;
	
	// Compute the reflection vector.
	float3 r = reflect(-lightVecW, normalW);
	
	// Determine how much (if any) specular light makes it into the eye.
	//float t  = pow(max(dot(r, toEyeW), 0.0f), gMtrl.specPower);
	float t  = pow(max(dot(r, toEyeW), 0.0f), 48.0f);
	
	// Determine the diffuse light intensity that strikes the vertex.
	float s = max(dot(lightVecW, normalW), 0.0f);
	
	// Compute the ambient, diffuse and specular terms separatly. 
	//float3 spec = t*(gMtrl.spec*gLight.spec).rgb;
	float3 spec = t*(float4(0.6f,0.6f,0.6f,0.6f)*float4(0.8f, 0.8f, 0.8f, 1.0f)).rgb;
	//float3 diffuse = s*(gMtrl.diffuse*gLight.diffuse).rgb;
	float3 diffuse = s*(float4(0.6f,0.6f,0.6f,0.6f)*float4(0.8f,0.8f,0.8f,1.0f)).rgb;
	//float3 ambient = gMtrl.ambient*gLight.ambient;
	float3 ambient = float4(0.9f,0.9f,0.9f,0.9f)*float4(0.5f,0.5f,0.5f,1.0f);
	
	// Get the texture color.
	float4 texColor = tex2D(TexS, tex0);
	
	// Combine the color from lighting with the texture color.
	float3 color = (ambient + diffuse)*texColor.rgb + spec;
		
	// Sum all the terms together and copy over the diffuse alpha.
    //return float4(color, gMtrl.diffuse.a*texColor.a);
    return float4(color, 0.6f*texColor.a);
}

technique ShaderTech
{
    pass P0
    {
        // Specify the vertex and pixel shader associated with this pass.
        vertexShader = compile vs_2_0 VBlend2VS();
        pixelShader  = compile ps_2_0 VBlend2PS();
    }
}