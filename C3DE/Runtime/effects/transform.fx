//=============================================================================
// heightcolor.fx by Frank Luna (C) 2004 All Rights Reserved.
//
// Animates vertices in a wave motion and generates vertex colors 
// based on their height.
//=============================================================================

uniform extern float4x4 gWVP;
uniform extern float4x4 gWorldInverseTranspose;


uniform extern float4 gAmbientMtrl;
uniform extern float4 gAmbientLight;

uniform extern float4 gDiffuseMtrl;
uniform extern float4 gDiffuseLight;
uniform extern float3 gLightVecW;

struct OutputVS
{
    float4 posH  : POSITION0;
    float3 normalW: TEXCOORD0;
    float3 posW: TEXCOORD1;
   
};

OutputVS DiffuseVS(float3 posL : POSITION0, float3 normalL : NORMAL0)
{
    // Zero out our output.
	OutputVS outVS = (OutputVS)0;
	
	// Transform normal to world space.
	float3 normalW = mul(float4(normalL, 0.0f), gWorldInverseTranspose).xyz;
	normalW = normalize(normalW);
	
	
	outVS.normalW = normalW;
	
	outVS.posW = mul(float4(posL, 1.0f), gWVP);
	
	// Transform to homogeneous clip space.
	outVS.posH = mul(float4(posL, 1.0f), gWVP);
	
	// Done--return the output.
    return outVS;
}

float4 PhongPS(float3 normalW:TEXCOORD0, float3 posW:TEXCOORD1):COLOR
{
	
	
	normalW = normalize(normalW);
	
	float s = max(dot(gLightVecW, normalW), 0.0f);
	float3 diffuse = s* (gDiffuseMtrl*gDiffuseLight).rgb;
	
	return float4(diffuse, gDiffuseMtrl.a);	
	
}

technique HeightColorTech
{
    pass P0
    {
        // Specify the vertex and pixel shader associated with this pass.
        vertexShader = compile vs_2_0 DiffuseVS();        
        pixelShader  = compile ps_2_0 PhongPS();

		// Specify the render/device states associated with this pass.
		//FillMode = WireFrame;
    }
   
}
