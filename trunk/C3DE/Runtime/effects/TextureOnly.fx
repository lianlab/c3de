//=============================================================================
// dirLightTex.fx by Frank Luna (C) 2004 All Rights Reserved.
//
// Uses a directional light plus texturing.
//=============================================================================

uniform extern float4x4 gWorld;
uniform extern float4x4 gWorldInvTrans;
uniform extern float4x4 gWVP;

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
    float2 tex0    : TEXCOORD0;
};

OutputVS TextureOnlyVS(float3 posL : POSITION0, float3 normalL : NORMAL0, float2 tex0: TEXCOORD0)
{
    // Zero out our output.
	OutputVS outVS = (OutputVS)0;	
	
	// Transform vertex position to world space.
	float3 posW  = mul(float4(posL, 1.0f), gWorld).xyz;
	posW = mul(posW,gTransformMatrix);		
	
	//=======================================================
	
	// Transform to homogeneous clip space.
	float4 newPos = mul(float4(posL, 1.0f), gTransformMatrix);
	outVS.posH = mul(newPos, gWVP);
	
	// Pass on texture coordinates to be interpolated in rasterization.
	outVS.tex0 = tex0;
	
	
	
	
	// Done--return the output.
    return outVS;
}

float4 TextureOnlyPS(float2 tex0 : TEXCOORD0) : COLOR
{		
	float4 texColor4 = tex2D(TexS, tex0);
    return float4(texColor4);     
}

technique ShaderTech
{
    pass P0
    {
        // Specify the vertex and pixel shader associated with this pass.
        vertexShader = compile vs_2_0 TextureOnlyVS();
        pixelShader  = compile ps_2_0 TextureOnlyPS();
       
    }
}

