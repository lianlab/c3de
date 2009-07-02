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
uniform extern int gSelectedBoneIndex;
uniform extern float4x4 gFinalXForms[35];
uniform extern float4x4 gToRoot[50];
//updated every frame
uniform extern float4x4 gCurrentFrameToRoot[50];

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
    float4 color: COLOR0;
    float2 tex0    : TEXCOORD0;
    
};

//OutputVS SkinnedMeshVS(float3 posL : POSITION0, float3 normalL : NORMAL0, float2 tex0: TEXCOORD0)
OutputVS SkinnedMeshVS(float3 posL    : POSITION0, 
                   float3 normalL : NORMAL0, 
                   float2 tex0    : TEXCOORD0,
                   float weight0  : BLENDWEIGHT0, 
                   int boneIndex0 : BLENDINDICES0,
                   int boneIndex1 : BLENDINDICES1)
{
    // Zero out our output.
	OutputVS outVS = (OutputVS)0;
	
	float3 offsetPosL = float3(posL.x - gToRoot[boneIndex0][3][0],posL.y - gToRoot[boneIndex0][3][1], posL.z - gToRoot[boneIndex0][3][2]);
	
	
	//posL = mul(float4(posL, 1.0f), gToRoot[boneIndex]).xyz;
	//posL = mul(float4(posL, 1.0f), gCurrentFrameToRoot[boneIndex]).xyz;
	//posL = mul(float4(offsetPosL, 1.0f), gCurrentFrameToRoot[boneIndex0]).xyz;
	//posL.x += 5;
	//posL.x += gToRoot[boneIndex][3][0];
	//posL.y += gToRoot[boneIndex][3][1];
	//posL.z += gToRoot[boneIndex][3][2];
	
	
	
	// Transform normal to world space.
	//float3 normalW = mul(float4(normalL, 0.0f), gWorldInvTrans).xyz;
	//normalW = normalize(normalW);
	
	// Transform vertex position to world space.
	float3 posW  = mul(float4(posL, 1.0f), gWorld).xyz;
	posW = mul(posW,gTransformMatrix);
	//=======================================================
	// Compute the color: Equation 10.3.
	
	// Compute the vector from the vertex to the eye position.
	float3 toEye = normalize(gEyePosW - posW);
	
	
							
							
	outVS.color = float4(0.0f, 0.0f, 0.0f, 0.0f);
	if(boneIndex0 == gSelectedBoneIndex && gSelectedBoneIndex > -1)
	{
		//outVS.diffuse = float4(1.0f, 0.0f, 0.0f, 1.0f);
		//float value = float((gToRoot[gSelectedBoneIndex][3][0] * 5.0f));
		//float value = (-0.57f * 5.0f);
		//posL.x += (gToRoot[gSelectedBoneIndex][3][0] * 5.0f);
		outVS.color = float4(1.0f, 0.0f, 0.0f, 0.5f);
		
	}	
	if(boneIndex1 == gSelectedBoneIndex  && gSelectedBoneIndex > -1)
	{
		//outVS.diffuse = float4(0.0f, 1.0f, 0.0f, 1.0f);
		//posL.x += 5;
		//posL.y += 5;
		//posL.z += 5;
		outVS.color = float4(0.0f, 1.0f, 0.0f, 0.5f);
	}			
	
	
	// Transform to homogeneous clip space.
	float4 newPos = mul(float4(posL, 1.0f), gTransformMatrix);
	//outVS.posH = mul(float4(posL, 1.0f), gWVP);
	//newPos += gHack;
	outVS.posH = mul(newPos, gWVP);
	
	// Pass on texture coordinates to be interpolated in rasterization.
	outVS.tex0 = tex0;
	
	// Done--return the output.
    return outVS;
}

float4 SkinnedMeshPS(float4 color:COLOR0, float2 tex0 : TEXCOORD0) : COLOR
{
	
	float3 texColor = tex2D(TexS, tex0).rgb;
    color.rgb *= color.a;
    float3 final = color.rgb + texColor;
    return float4(final.rgb, 1.0f);
    
}

technique ShaderTech
{
    pass P0
    {
        // Specify the vertex and pixel shader associated with this pass.
        vertexShader = compile vs_2_0 SkinnedMeshVS();
        pixelShader  = compile ps_2_0 SkinnedMeshPS();
    }
}

