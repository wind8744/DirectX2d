#ifndef _FUNC
#define _FUNC
#include "value.fx"

static float gaussian5x5[25] =
{
    0.003765, 0.015019, 0.023792, 0.015019, 0.003765,
    0.015019, 0.059912, 0.094907, 0.059912, 0.015019,
    0.023792, 0.094907, 0.150342, 0.094907, 0.023792,
    0.015019, 0.059912, 0.094907, 0.059912, 0.015019,
    0.003765, 0.015019, 0.023792, 0.015019, 0.003765,
};

float gaussian5x5Sample(in int2 _uv, in Texture2D _tex)
{
    float4 fOut = (float4) 0.f;
    for (int i = 0; i < 5; ++i)
    {
        for (int j = 0; j < 5; ++j)
        {
            fOut += _tex[_uv + int2(i - 2, j - 2)] * gaussian5x5[i * 5 + j];
        }
    }
    return fOut.x;
}


// 0 ~ 1 ���� ����
float Rand(in float _fKey)
{
    // ���� ���� ��ġ, ����               
    float2 vUV = float2(_fKey + g_AccTime, g_AccTime);
    vUV.y += sin(vUV.x * 2 * 3.141592);
            
    if (vUV.x > 0)
        vUV.x = frac(vUV.x);
    else
        vUV.x = 1.f - abs(vUV.x);
            
    if (vUV.y > 0)
        vUV.y = frac(vUV.y);
    else
        vUV.y = 1.f - abs(vUV.y);
            
    vUV = vUV * g_vNoiseResolution;
    
    return gaussian5x5Sample(vUV, g_noise);
}


// _lightcol : ���� �����޴� ����
// _vViewPos : �ȼ��� �佺���̽� ���� ��ǥ
// _iIdx : ���� �ε���
void CalLight2D(inout tLightColor _lightcol, float3 _vViewPos, uint _iIdx)
{
    float fRatio = 1.f;
    
    if (1 == g_Light2DInfo[_iIdx].eType)
    {
        float4 vLightWorldPos = float4(g_Light2DInfo[_iIdx].vWorldPos.xyz, 1.f);
        float3 vViewLightPos = mul(vLightWorldPos, g_matView);
        
        float2 vDiff = vViewLightPos.xy - _vViewPos.xy;
        fRatio = saturate(1.f - length(vDiff) / g_Light2DInfo[_iIdx].fRange);       
    }
    else
    {
        
    }
    
    _lightcol.vAmb += g_Light2DInfo[_iIdx].color.vAmb * fRatio;
}


#endif
