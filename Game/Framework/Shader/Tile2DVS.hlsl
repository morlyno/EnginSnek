cbuffer transform
{
    matrix model;
    matrix modelview;
};

float4 main( float2 pos : Position2D ) : SV_POSITION
{
    return mul(float4(pos, 0.0f, 1.0f), modelview);
}