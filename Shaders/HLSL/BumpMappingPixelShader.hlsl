float4 fvAmbient;
float4 fvDiffuse;
float4 fvSpecular;
float fSpecularPower;

sampler2D diffuseMap;
sampler2D normalMap;

struct PS_INPUT
{
	float2 Texcoord :        TEXCOORD0;
	float3 ViewDirection :   TEXCOORD1;
	float  LightDistanse:	 TEXCOORD2;
};

float4 main(PS_INPUT Input) : COLOR0
{
	float3 fvViewDirection  = normalize(Input.ViewDirection);
	float3 fvNormal         = normalize((tex2D(normalMap, Input.Texcoord).xyz * 2.0f) - 1.0f);

	float  fNDotL           = max(0.0f, dot(fvNormal, fvViewDirection));

	float4 fvBaseColor      = tex2D(diffuseMap, Input.Texcoord);
	float4 fvTotalAmbient   = fvAmbient * fvBaseColor;
	float4 fvTotalDiffuse   = fvDiffuse * fNDotL * fvBaseColor; 
	float4 fvTotalSpecular  = fvSpecular * pow(fNDotL, fSpecularPower);

	float Attenuation = 1.0f / (0.000005f * Input.LightDistanse * Input.LightDistanse + 0.000003f * Input.LightDistanse + 1.0f);

	return(saturate(Attenuation * (fvTotalDiffuse + fvTotalSpecular) + fvTotalAmbient));
};