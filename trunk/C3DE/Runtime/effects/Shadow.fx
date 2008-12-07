//=============================================================================
// dirLightTex.fx by Frank Luna (C) 2004 All Rights Reserved.
//
// Uses a directional light plus texturing.
//=============================================================================

uniform extern float4x4 gWorld;
uniform extern float4x4 gWorldInvTrans;
uniform extern float4x4 gWVP;

uniform extern float4 gAmbientMtrl;
uniform extern float4 gAmbientLight;
uniform extern float4 gDiffuseMtrl;
uniform extern float4 gDiffuseLight;
uniform extern float4 gSpecularMtrl;
uniform extern float4 gSpecularLight;
uniform extern float  gSpecularPower;
uniform extern float3 gLightVecW;
uniform extern float3 gEyePosW;
uniform extern texture gTex;
uniform extern float4x4 gTransformMatrix;

sampler TexS = sampler_state
{
	Texture = <gTex>;
	MinFilter = Anisotropic;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
	MaxAnisotropy = 8;
	AddressU  = WRAP;
    AddressV  = WRAP;
};
 
struct OutputVS
{
    float4 posH    : POSITION0;
    float4 diffuse : COLOR0;
    float4 spec    : COLOR1;
    float2 tex0    : TEXCOORD0;
};

OutputVS DirLightTexVS(float3 posL : POSITION0, float3 normalL : NORMAL0, float2 tex0: TEXCOORD0)
{
	float4 BLACK = float4(0.0f, 0.0f, 0.0f, 1.0f);
	float4 DIFFUSE_BLACK = float4(0.0f, 0.0f, 0.0f, 0.5f);
    // Zero out our output.
	OutputVS outVS = (OutputVS)0;
	
	// Transform normal to world space.
	float3 normalW = mul(float4(normalL, 0.0f), gWorldInvTrans).xyz;
	normalW = normalize(normalW);
	
	// Transform vertex position to world space.
	float3 posW  = mul(float4(posL, 1.0f), gWorld).xyz;
	posW = mul(posW,gTransformMatrix);
	//=======================================================
	// Compute the color: Equation 10.3.
	
	// Compute the vector from the vertex to the eye position.
	float3 toEye = normalize(gEyePosW - posW);
	
	// Compute the reflection vector.
	float3 r = reflect(-gLightVecW, normalW);
	
	// Determine how much (if any) specular light makes it into the eye.
	float t  = pow(max(dot(r, toEye), 0.0f), 1.0f);
	
	// Determine the diffuse light intensity that strikes the vertex.
	float s = max(dot(gLightVecW, normalW), 0.0f);
	
	// Compute the ambient, diffuse and specular terms separatly. 
	float3 spec = t*(BLACK*gSpecularLight).rgb;
	float3 diffuse = s*(DIFFUSE_BLACK*gDiffuseLight).rgb;
	float3 ambient = BLACK*gAmbientLight;
	
	// Sum all the terms together and copy over the diffuse alpha.
	
	outVS.diffuse  = (0.0f, 0.0f, 0.0f, 0.5f);
	outVS.spec = float4(spec, 0.5f);
	//=======================================================
	
	// Transform to homogeneous clip space.
	float4 newPos = mul(float4(posL, 1.0f), gTransformMatrix);
	//outVS.posH = mul(float4(posL, 1.0f), gWVP);
	outVS.posH = mul(newPos, gWVP);
	
	// Pass on texture coordinates to be interpolated in rasterization.
	outVS.tex0 = tex0;
	
	// Done--return the output.
    return outVS;
}

float4 DirLightTexPS(float4 c : COLOR0, float4 spec : COLOR1, float2 tex0 : TEXCOORD0) : COLOR
{
	
	
    return float4(0.0f, 0.0f, 0.0f, 0.5f); 
}

technique ShaderTech
{
    pass P0
    {
        // Specify the vertex and pixel shader associated with this pass.
        vertexShader = compile vs_2_0 DirLightTexVS();
        pixelShader  = compile ps_2_0 DirLightTexPS();
    }
}
