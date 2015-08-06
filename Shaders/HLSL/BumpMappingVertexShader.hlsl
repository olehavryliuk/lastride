float4x4 matModelView;
float4x4 matModelViewProjection;
//float3 fvLightPosition;
//float3 fvEyePosition;

struct VS_INPUT 
{
	float4 Position : POSITION0;
	float3 Normal :   NORMAL0;
	float2 Texcoord : TEXCOORD0;
	float3 Tangent :  TEXCOORD1;
	float3 Binormal : TEXCOORD2;
};

struct VS_OUTPUT 
{
	float4 Position :        POSITION0;
	float2 Texcoord :        TEXCOORD0;
	float3 ViewDirection :   TEXCOORD1;
	float3 LightDirection:   TEXCOORD2;
};

VS_OUTPUT main(VS_INPUT Input)
{
	VS_OUTPUT Output;

	Output.Position         = mul(Input.Position, matModelViewProjection);
	Output.Texcoord         = Input.Texcoord;
	//Output.Normal           = mul( Input.Normal, matWorld );

	float3 fvObjectPosition = mul(Input.Position, matModelView);
	float3 fvViewDirection  = -fvObjectPosition;
	float3 fvLightDirection = -fvObjectPosition;

	float3 fvNormal         = normalize(mul(Input.Normal, matModelView));
	float3 fvTangent        = normalize(mul(Input.Tangent, matModelView));
	float3 fvBinormal       = normalize(mul(Input.Binormal, matModelView));

	Output.ViewDirection.x  = dot(fvTangent, fvViewDirection);
	Output.ViewDirection.y  = dot(fvBinormal, fvViewDirection);
	Output.ViewDirection.z  = dot(fvNormal, fvViewDirection);

	Output.LightDirection.x  = dot(fvTangent, fvLightDirection);
	Output.LightDirection.y  = dot(fvBinormal, fvLightDirection);
	Output.LightDirection.z  = dot(fvNormal, fvLightDirection);
   
	return Output;
};