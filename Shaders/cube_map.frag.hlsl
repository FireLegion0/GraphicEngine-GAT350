#include "uniforms.hlsli"

TextureCube<float4> Cubemap : register(t0, FRAGMENT_TEXTURE_SPACE);
SamplerState Sampler : register(s0, FRAGMENT_TEXTURE_SPACE);
 
struct Input
{
    float3 TexCoord : TEXCOORD0;
    float4 Position : SV_Position;
};

float4 main(Input input) : SV_Target0
{
    return Cubemap.Sample(Sampler, input.TexCoord);
}