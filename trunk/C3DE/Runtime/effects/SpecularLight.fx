//=============================================================================
// dirLightTex.fx by Frank Luna (C) 2004 All Rights Reserved.
//
// Uses a directional light plus texturing.
//=============================================================================

uniform extern float4x4 gWorld;
uniform extern float4x4 gWorldInvTrans;
uniform extern float4x4 gWVP;

//uniform extern float4 gAmbientMtrl;
//uniform extern float4 gAmbientLight;
//uniform extern float4 gDiffuseMtrl;
//uniform extern float4 gDiffuseLight;
uniform extern float4 gSpecularMtrl;
uniform extern float4 gSpecularLight;
uniform extern float  gSpecularPower;
uniform extern float3 gLightVecW;
uniform extern float3 gEyePosW;
uniform extern texture gTex;
uniform extern float4x4 gTransformMatrix;
//uniform extern float gAlpha;


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
    float4 specular : COLOR0;
    //float4 spec    : COLOR1;
    float2 tex0    : TEXCOORD0;
};

OutputVS SpecularLightVS(float3 posL : POSITION0, float3 normalL : NORMAL0, float2 tex0: TEXCOORD0)
{
    // Zero out our output.
	OutputVS outVS = (OutputVS)0;
	
	// Transform normal to world space.
	float3 normalW = mul(float4(normalL, 0.0f), gWorldInvTrans).xyz;
	normalW = normalize(normalW);
	
	// Transform vertex position to world space.
	float3 posW  = mul(float4(posL, 1.0f), gWorld).xyz;
	posW = mul(posW,gTransformMatrix);
	//=======================================================
	
	float3 toEye = normalize(gEyePosW - posW);
	float3 r = reflect(-gLightVecW, normalW);
	
	float t = pow(max(dot(r, toEye), 0.0f), gSpecularPower);
	
	float4 spec = t*(gSpecularMtrl*gSpecularLight);


	
	
	outVS.specular = spec;
	//=======================================================
	
	// Transform to homogeneous clip space.
	float4 newPos = mul(float4(posL, 1.0f), gTransformMatrix);
	//outVS.posH = mul(float4(posL, 1.0f), gWVP);
	outVS.posH = mul(newPos, gWVP);
	
	// Pass on texture coordinates to be interpolated in rasterization.
	outVS.tex0 = tex0;
	
    return outVS;
}

//float4 DiffuseStaticLightPS(float4 c : COLOR0, float4 spec : COLOR1, float2 tex0 : TEXCOORD0) : COLOR
float4 SpecularLightPS(float4 c : COLOR0, float2 tex0 : TEXCOORD0) : COLOR
{
	
	
	float4 texColor4 = tex2D(TexS, tex0);
	
    return float4(c * texColor4); 
    
    
}

technique ShaderTech
{
    pass P0
    {
        // Specify the vertex and pixel shader associated with this pass.
        vertexShader = compile vs_2_0 SpecularLightVS();
        pixelShader  = compile ps_2_0 SpecularLightPS();
        
       
    }
}

