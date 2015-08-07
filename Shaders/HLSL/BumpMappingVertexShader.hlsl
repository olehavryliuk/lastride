float4x4 matModelView;
float4x4 matModelViewProjection;

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
	float  LightDistanse:	 TEXCOORD2;
};

VS_OUTPUT main(VS_INPUT Input)
{
	VS_OUTPUT Output;

	Output.Position         = mul(Input.Position, matModelViewProjection);
	Output.Texcoord         = Input.Texcoord;

	float3 fvObjectPosition = mul(Input.Position, matModelView);
	float3 fvViewDirection  = -fvObjectPosition;
	
	Output.LightDistanse	= length(fvViewDirection);

	float3 fvNormal         = normalize(mul(Input.Normal, matModelView));
	float3 fvTangent        = normalize(mul(Input.Tangent, matModelView));
	float3 fvBinormal       = normalize(mul(Input.Binormal, matModelView));

	Output.ViewDirection.x  = dot(fvTangent, fvViewDirection);
	Output.ViewDirection.y  = dot(fvBinormal, fvViewDirection);
	Output.ViewDirection.z  = dot(fvNormal, fvViewDirection);
   
	return Output;
};