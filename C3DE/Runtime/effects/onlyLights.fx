//=============================================================================
// spotlight.fx by Frank Luna (C) 2004 All Rights Reserved.
//
// Does ambient, diffuse, and specular lighting with a spotlight source.
//=============================================================================


uniform extern float4x4 gWorld;
uniform extern float4x4 gWorldInvTrans;
uniform extern float4x4 gWVP;
uniform extern float4x4 gTransformMatrix;
uniform extern float3   gEyePosW;

uniform extern float4 gAmbientMtrl;
uniform extern float4 gDiffuseMtrl;
uniform extern float4 gSpecMtrl;
uniform extern float  gSpecPower;
	
uniform extern float4 gAmbientLight;
uniform extern float4 gDiffuseLight;
uniform extern float4 gSpecLight;
uniform extern float3 gLightPosW;  
uniform extern float3 gLightDirW;
uniform extern float3 gAttenuation012; 
uniform extern float  gSpotPower;

uniform extern texture gTex;

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
    float4 posH  : POSITION0;
    float3 normalW: TEXCOORD0;
    float3 posW: TEXCOORD1;
    float2 tex0 : TEXCOORD2;
   
};



OutputVS LightsVS(float3 posL : POSITION0, float3 normalL : NORMAL0, float2 tex0: TEXCOORD0)
{
    // Zero out our output.
	OutputVS outVS = (OutputVS)0;
	
	// Transform normal to world space.
	float3 normalW = mul(float4(normalL, 0.0f), gWorldInvTrans).xyz;
	normalW = normalize(normalW);
	
	// Transform vertex position to world space.
	float3 posW  = mul(float4(posL, 1.0f), gWorld).xyz;
	
	outVS.posW = posW;
	outVS.normalW = normalW;
	// Transform to homogeneous clip space.
	outVS.posH = mul(float4(posL, 1.0f), gWVP);
	
	// Pass on texture coordinates to be interpolated in rasterization.
	outVS.tex0 = tex0;
	
	// Done--return the output.
    return outVS;
}

//float4 SpotlightPS(float4 c : COLOR0) : COLOR
float4 LightsPS(float3 normalW:TEXCOORD0, float3 posW:TEXCOORD1, float2 tex0 : TEXCOORD2):COLOR
{
	
	float3 texColor = tex2D(TexS, tex0).rgb;
	
	

    // Unit vector from vertex to light source.
	float3 lightVecW = normalize(gLightPosW - posW);
	
	// Ambient Light Computation.
	gAmbientMtrl = (0.0f, 0.0f, 1.0f, 1.0f);
	gAmbientLight = (0.4f, 0.4f, 0.4f, 0.4f);
	float3 ambient = (gAmbientMtrl*gAmbientLight).rgb;
	
	// Diffuse Light Computation.
	float s = max(dot(normalW, lightVecW), 0.0f);
	
	float3 diffuse = s*(gDiffuseMtrl*gDiffuseLight).rgb;
	
	
	// Specular Light Computation.
	float3 toEyeW   = normalize(gEyePosW - posW);
	float3 reflectW = reflect(-lightVecW, normalW);
	float t = pow(max(dot(reflectW, toEyeW), 0.0f), gSpecPower);
	float3 spec = t*(gSpecMtrl*gSpecLight).rgb;
	
	// Attentuation.
	float d = distance(gLightPosW, posW);
	float A = gAttenuation012.x + gAttenuation012.y*d + gAttenuation012.z*d*d;
	
	// Spotlight factor.
	float spot = pow(max(dot(-lightVecW, gLightDirW), 0.0f), gSpotPower);
	
	// Everything together.
	//float3 color = spot*(ambient + ((diffuse + spec) / A));
	float3 color = spot*(ambient + diffuse);
	
	
	color = color;// * texColor;
	
	
	
	
	// Pass on color and diffuse material alpha.
	return float4(color, gDiffuseMtrl.a);
	
}

technique ShaderTech
{
    pass P0
    {
        // Specify the vertex and pixel shader associated with this pass.
        vertexShader = compile vs_2_0 LightsVS();
        pixelShader  = compile ps_2_0 LightsPS();
    }
}
