cbuffer cBuf : register(b1)
{
	float4 face_color[6];
};

float4 main( uint tid : SV_PrimitiveID ) : SV_TARGET
{
	return face_color[tid / 2 % 6];
}