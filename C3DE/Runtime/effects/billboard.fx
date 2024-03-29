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
uniform extern float gAlpha;



static float3 gFogColor = (0.5f, 0.5f, 0.5f);
static float gFogStart = 1.0f;
static float gFogRange = 200.0f;



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
    float2 tex0    : TEXCOORD0;
    float  fogLerpParam : TEXCOORD1;
    
};

OutputVS GrassVS(float3 posL : POSITION0, 
                 float3 normal:NORMAL0,  
                 float2 tex0 : TEXCOORD0)
{
    
	// Zero out our output.
	OutputVS outVS = (OutputVS)0;
	
	float3 t_pos = float3(0.0f, 0.0f, 0.0f);
	float3 t_transformedQuadPos = mul(float4(t_pos, 1.0f), gTransformMatrix);
	
	// Compute billboard matrix.
	float3 look = normalize(gEyePosW - t_transformedQuadPos);
	
	float3 right = normalize(cross(float3(0.0f, 1.0f, 0.0f), look));
	float3 up    = cross(look, right);
	
	// Build look-at rotation matrix which makes the billboard face the camera.
	float4x4 lookAtMtx;
	lookAtMtx[0] = float4(right, 0.0f);
	lookAtMtx[1] = float4(up, 0.0f);
	lookAtMtx[2] = float4(look, 0.0f);
	lookAtMtx[3] = float4(t_transformedQuadPos, 1.0f);
	//lookAtMtx[3] = float4(posL, 1.0f);
	
	float3 t_transformedPosL = mul(float4(posL, 1.0f), gTransformMatrix);	
	float3 t_pseudo = t_transformedPosL - t_transformedQuadPos;
	
	
	// Transform to world space.
	
	float4 posW = mul(float4(t_pseudo, 1.0f), lookAtMtx);
	
	// Transform to homogeneous clip space.
	outVS.posH = mul(posW, gWVP);
	
	// Pass on texture coordinates to be interpolated in rasterization.
	outVS.tex0 = tex0;

	// Compute vertex distance from camera in world space for fog calculation.
	float dist = distance(posW, gEyePosW);
	outVS.fogLerpParam = saturate((dist - gFogStart) / gFogRange);

	
	
	// Done--return the output.
    return outVS;
    
}

float4 GrassPS(float2 tex0 : TEXCOORD0,
               float fogLerpParam : TEXCOORD1/*,
               float4 colorOffset : COLOR0*/) : COLOR
{
	// Get the texture color.
	float4 texColor = tex2D(TexS, tex0);
	
	
	
	 // Add fog.
    float3 final = lerp(texColor.rgb, gFogColor, fogLerpParam);
 
	return float4(final, texColor.a);   
}

technique ShaderTech
{
    pass P0
    {
        // Specify the vertex and pixel shader associated with this pass.
        vertexShader = compile vs_2_0 GrassVS();
        pixelShader  = compile ps_2_0 GrassPS();
        
        AlphaRef = 200;
        AlphaFunc = GreaterEqual;
        AlphaTestEnable = true;
        
        CullMode = None;
    }
}

