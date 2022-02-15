#ifndef _STD2D
#define _STD2D

#include "value.fx"
#include "func.fx"

struct VTX_INPUT
{
    float3 vPos : POSITION; // Sementic
    float4 vColor : COLOR;
    float2 vUV : TEXCOORD;
};

struct VTX_OUT
{
    float4 vPosition : SV_Position;
    float4 vColor : COLOR;
    float2 vUV : TEXCOORD;
    float2 vProjPos : POSITION;
    float3 vViewPos : POSITION1;
};

// 오브젝트만 쓰는 쉐이더
// ==========================
// Std2D Shader
// g_tex_0 : Output Texture
// ==========================

VTX_OUT VS_Std2D(VTX_INPUT _in)
{
    VTX_OUT output = (VTX_OUT) 0.f;
    
    float4 vWorldPos = mul(float4(_in.vPos, 1.f), g_matWorld);
    float4 vViewPos = mul(vWorldPos, g_matView);
    float4 vProjPos = mul(vViewPos, g_matProj);
        
    output.vPosition = vProjPos;
    output.vColor = _in.vColor;
    output.vUV = _in.vUV;
    output.vProjPos = output.vPosition.xy;
    output.vViewPos = vViewPos.xyz;
        
    return output;
}

float4 PS_Std2D(VTX_OUT _in) : SV_Target
{
    float4 vColor = (float4) 0.f;
    
    if (g_Anim2DInfo[0].iAnimUse[0])
    {
        float2 AnimUV = float2(g_Anim2DInfo[0].vLeftTop.x + g_Anim2DInfo[0].vStep.x * _in.vUV.x, g_Anim2DInfo[0].vLeftTop.y + g_Anim2DInfo[0].vStep.y * _in.vUV.y);
        vColor = g_animtex.Sample(g_sam_0, AnimUV);
    }
    if (0 == g_int_0)
    {
        vColor = g_tex_0.Sample(g_sam_0, _in.vUV);

    }
    else if (100 == g_int_0)
    {
        vColor = g_tex_1.Sample(g_sam_0, _in.vUV);
       // return float4(1.f, 0.f, 0.f, 1.f);
    }
        
     
    
    tLightColor LightColor = (tLightColor) 0.f;
        
    for (uint i = 0; i < iLight2DCount; ++i)
    {
        CalLight2D(LightColor, _in.vViewPos, i);
    }
    
    vColor.rgb = (vColor.rgb * LightColor.vDiff.rgb) + (vColor.rgb * LightColor.vAmb.rgb);
   
    return vColor;
}


// =========================
// Collider2D Shader
// g_int_0 : Collision check
// =========================
float4 VS_Collider2D(float3 _vPos : POSITION) : SV_Position
{
    float4 vPosition = (float4) 0.f;
    vPosition = mul(float4(_vPos, 1.f), g_matWVP);
    
    return vPosition;
}

float4 PS_Collider2D(float4 _vScreenPos : SV_Position) : SV_Target
{
    if (g_int_0)
    {
        return float4(1.f, 0.f, 0.f, 1.f);
    }
    else
    {
        return float4(0.f, 1.f, 0.f, 1.f);
    }
}


// =========================
// Particle Rendering Shader
// mesh : point mesh
// g_tex_0 : particle texture
// =========================
struct VTX_PARTICLE_IN
{
    float3 vLocalPos : POSITION;
    float2 vUV : TEXCOORD;
    uint iInstID : SV_InstanceID;
};

struct VTX_PARTICLE_OUT
{
    float4 vViewPos : POSITION;
    float2 vUV : TEXCOORD;
    float fInstID : FOG;
};

struct GS_PARTICLE_OUT
{
    float4 vPosition : SV_Position;
    float2 vUV : TEXCOORD;
    float fInstID : FOG;
};

StructuredBuffer<tParticle> g_particelbuffer : register(t100);

VTX_PARTICLE_OUT VS_Particle(VTX_PARTICLE_IN _in)
{
    VTX_PARTICLE_OUT output = (VTX_PARTICLE_OUT) 0.f;

    float3 vWorldPos = _in.vLocalPos;
    
    vWorldPos += g_particelbuffer[_in.iInstID].vWorldPos;
    
    output.vViewPos = mul(float4(vWorldPos, 1.f), g_matView);
    output.vUV = _in.vUV;
    output.fInstID = _in.iInstID;
    
    return output;
}

[maxvertexcount(6)]
void GS_Particle(point VTX_PARTICLE_OUT _in[1], inout TriangleStream<GS_PARTICLE_OUT> _stream)
{
    GS_PARTICLE_OUT arrVTX[4] = { (GS_PARTICLE_OUT) 0.f, (GS_PARTICLE_OUT) 0.f, (GS_PARTICLE_OUT) 0.f, (GS_PARTICLE_OUT) 0.f };
        
    // 인스턴스 아이디로, 파티클 버퍼의 활성유무 체크
    uint instID = (uint) _in[0].fInstID;
    if (0 == g_particelbuffer[instID].iAlive)
    {
        // 비활성 파티클인 경우 폐기
        return;
    }
    
    // 0 -- 1
    // | \  |
    // 3 -- 2
    float fRatio = g_particelbuffer[instID].m_fCurTime / g_particelbuffer[instID].m_fMaxLife;
    float fScale = (g_vec4_1 - g_vec4_0) * fRatio + g_vec4_0;
    
        
    arrVTX[0].vPosition = _in[0].vViewPos + float4(-fScale / 2.f, fScale / 2, 0.f, 0.f);
    arrVTX[0].vUV = float2(0.f, 0.f);
    arrVTX[0].fInstID = (float) instID;
    
    arrVTX[1].vPosition = _in[0].vViewPos + float4(fScale / 2.f, fScale / 2, 0.f, 0.f);
    arrVTX[1].vUV = float2(1.f, 0.f);
    arrVTX[1].fInstID = (float) instID;
    
    arrVTX[2].vPosition = _in[0].vViewPos + float4(fScale / 2.f, -fScale / 2, 0.f, 0.f);
    arrVTX[2].vUV = float2(1.f, 1.f);
    arrVTX[2].fInstID = (float) instID;
    
    arrVTX[3].vPosition = _in[0].vViewPos + float4(-fScale / 2.f, -fScale / 2, 0.f, 0.f);
    arrVTX[3].vUV = float2(0.f, 1.f);
    arrVTX[3].fInstID = (float) instID;
    
    for (int i = 0; i < 4; ++i)
    {
        arrVTX[i].vPosition = mul(arrVTX[i].vPosition, g_matProj);
    }
    
    _stream.Append(arrVTX[0]);
    _stream.Append(arrVTX[2]);
    _stream.Append(arrVTX[3]);
    _stream.RestartStrip();
    
    _stream.Append(arrVTX[2]);
    _stream.Append(arrVTX[0]);
    _stream.Append(arrVTX[1]);
    _stream.RestartStrip();
}


float4 PS_Particle(GS_PARTICLE_OUT _in) : SV_Target
{
    float4 vColor = (float4) 0.f;
    
    uint iInst = (uint) _in.fInstID;
    
    float fRatio = g_particelbuffer[iInst].m_fCurTime / g_particelbuffer[iInst].m_fMaxLife;
    vColor = (g_vec4_3 - g_vec4_2) * fRatio + g_vec4_2;
        
    return g_tex_0.Sample(g_sam_0, _in.vUV) * vColor;
}


struct VTX_TILE_IN
{
    float3 vPos : POSITION; // Sementic
    float4 vColor : COLOR;
    float2 vUV : TEXCOORD;
};

struct VTX_TILE_OUT
{
    float4 vPosition : SV_Position;
    float4 vColor : COLOR;
    float2 vUV : TEXCOORD;
    float2 vProjPos : POSITION;
    float3 vViewPos : POSITION1;
};

StructuredBuffer<tTile> g_tilebuffer : register(t101);
StructuredBuffer<tTileShared> g_tileshared : register(t102);

VTX_TILE_OUT VS_TILE(VTX_TILE_IN _in)
{
    VTX_TILE_OUT output = (VTX_TILE_OUT) 0.f;
    
    float4 vWorldPos = mul(float4(_in.vPos, 1.f), g_matWorld);
    float4 vViewPos = mul(vWorldPos, g_matView);
    float4 vProjPos = mul(vViewPos, g_matProj);
        
    output.vPosition = vProjPos;
    output.vColor = _in.vColor;
    output.vUV = _in.vUV;
    output.vProjPos = output.vPosition.xy;
    output.vViewPos = vViewPos.xyz;
        
    return output;
}


float4 PS_TILE(VTX_TILE_OUT _in) : SV_Target
{
    float4 vColor = (float4) 0.f;
    float2 MapUV = (float2) 0.f;
    
    int XIdx = _in.vUV.x * g_tileshared[0].iTileXSize; //Col
    int YIdx = _in.vUV.y * g_tileshared[0].iTileYSize; //Raw
    int Idx = XIdx + YIdx * g_tileshared[0].iTileXSize; // 맵Vector의 Index
    
    float TileUV_x = (_in.vUV.x - ((float) (1.f / g_tileshared[0].iTileXSize) * XIdx)) * g_tileshared[0].iTileXSize; // 작은 타일 한개의 0~1 의 UV값
    float TileUV_y = (_in.vUV.y - ((float) (1.f / g_tileshared[0].iTileYSize) * YIdx)) * g_tileshared[0].iTileYSize;
    
    // test
    if(XIdx==0 &&YIdx ==1)
    {
        if ((0 < TileUV_x && TileUV_x < 0.5) && (0 < TileUV_y && TileUV_y < 0.5))
        {
            return vColor = float4(1, 0, 1, 0);
        };
    }
  
    MapUV = float2(g_tilebuffer[Idx].vLeftTop.x + g_tilebuffer[Idx].vStep.x * TileUV_x, // 맵Vector Index에 저장된 (마우스로 선택한) 맵이미지의 타일 xy 좌표 + 이미지값*작은타일의 UV값 =작은 타일에 선택한 이미지 픽셀 인쇄
    g_tilebuffer[Idx].vLeftTop.y + g_tilebuffer[Idx].vStep.y * TileUV_y);

    return vColor = g_tex_0.Sample(g_sam_1, MapUV);
     
    tLightColor LightColor = (tLightColor) 0.f;
        
    for (uint i = 0; i < iLight2DCount; ++i)
    {
        CalLight2D(LightColor, _in.vViewPos, i);
    }
 
    if (g_tilebuffer[Idx].vStep.x == 0 && g_tilebuffer[Idx].vStep.y == 0)
    {
        if (TileUV_x <= 0.01f || TileUV_y <= 0.01f || TileUV_x > 0.99f || TileUV_y > 0.99f)
        {
            vColor.rgba = float4(0.f, 1.f, 0.f, 0.8f);
        }
        else
            vColor.rgba = float4(0.f, 0.f, 0.f, 1.f);
    }
    else
        vColor.rgb = (vColor.rgb * LightColor.vDiff.rgb) + (vColor.rgb * LightColor.vAmb.rgb);
    
    return vColor;
}

StructuredBuffer<tDamageFont> g_DamageFont : register(t103);
StructuredBuffer<tDamageFontShared> g_DamageFontShared : register(t104);
struct VTX_DAMAGE_IN
{
    float3 vPos : POSITION; // Sementic
    float4 vColor : COLOR;
    float2 vUV : TEXCOORD;
};

struct VTX_DAMAGE_OUT
{
    float4 vPosition : SV_Position;
    float4 vColor : COLOR;
    float2 vUV : TEXCOORD;
    float2 vProjPos : POSITION;
    float3 vViewPos : POSITION1;
};
VTX_DAMAGE_OUT VS_DAMAGE(VTX_DAMAGE_IN _in)
{
    VTX_DAMAGE_OUT output = (VTX_DAMAGE_OUT) 0.f;
    
    float4 vWorldPos = mul(float4(_in.vPos, 1.f), g_matWorld);
    float4 vViewPos = mul(vWorldPos, g_matView);
    float4 vProjPos = mul(vViewPos, g_matProj);
        
    output.vPosition = vProjPos;
    output.vColor = _in.vColor;
    output.vUV = _in.vUV;
    output.vProjPos = output.vPosition.xy;
    output.vViewPos = vViewPos.xyz;
        
    return output;
}


float4 PS_DAMAGE(VTX_DAMAGE_OUT _in) : SV_Target
{
    float4 vColor = (float4) 0.f;
    float2 MapUV = (float2) 0.f;

    
    
    
    int XIdx = _in.vUV.x * g_DamageFontShared[0].iTileXSize;

    int YIdx = _in.vUV.y * g_DamageFontShared[0].iTileYSize;
    
    
    int Idx = XIdx + YIdx * g_DamageFontShared[0].iTileXSize;
    
    float x = (_in.vUV.x - ((float) (1.f / g_DamageFontShared[0].iTileXSize) * XIdx)) * g_DamageFontShared[0].iTileXSize;
    float y = (_in.vUV.y - ((float) (1.f / g_DamageFontShared[0].iTileYSize) * YIdx)) * g_DamageFontShared[0].iTileYSize;
  
  
    MapUV = float2(g_DamageFont[Idx].vLeftTop.x + g_DamageFont[Idx].vStep.x * x,
    g_DamageFont[Idx].vLeftTop.y + g_DamageFont[Idx].vStep.y * y);
      
    return vColor = g_tex_0.Sample(g_sam_1, MapUV);
     
    tLightColor LightColor = (tLightColor) 0.f;
        
    for (uint i = 0; i < iLight2DCount; ++i)
    {
        CalLight2D(LightColor, _in.vViewPos, i);
    }
 
    if (g_DamageFont[Idx].vStep.x == 0 && g_DamageFont[Idx].vStep.y == 0)
    {
        if (x <= 0.01f || y <= 0.01f || x > 0.99f || y > 0.99f)
        {
            vColor.rgba = float4(0.f, 1.f, 0.f, 0.8f);
        }
        else
            vColor.rgba = float4(0.f, 0.f, 0.f, 1.f);
    }
    else
        vColor.rgb = (vColor.rgb * LightColor.vDiff.rgb) + (vColor.rgb * LightColor.vAmb.rgb);
    
    return vColor;
}


// Player 전용
// ==========================
// Std2D Shader22222222222222222222
// g_tex_1 : Output Texture
// ==========================

VTX_OUT VS_Std2D2(VTX_INPUT _in)
{
    VTX_OUT output = (VTX_OUT) 0.f;
    
    float4 vWorldPos = mul(float4(_in.vPos, 1.f), g_matWorld);
    float4 vViewPos = mul(vWorldPos, g_matView);
    float4 vProjPos = mul(vViewPos, g_matProj);
        
    output.vPosition = vProjPos;
    output.vColor = _in.vColor;
    output.vUV = _in.vUV;
    output.vProjPos = output.vPosition.xy;
    output.vViewPos = vViewPos.xyz;
        
    return output;
}

float4 PS_Std2D2(VTX_OUT _in) : SV_Target
{
    float4 vColor = (float4) 0.f;
    
    if (g_Anim2DInfo[0].iAnimUse[0])
    {
        float2 AnimUV = float2(g_Anim2DInfo[0].vLeftTop.x + g_Anim2DInfo[0].vStep.x * _in.vUV.x, g_Anim2DInfo[0].vLeftTop.y + g_Anim2DInfo[0].vStep.y * _in.vUV.y);
        vColor = g_animtex.Sample(g_sam_0, AnimUV);
    }
    else
    {
        vColor = g_tex_0.Sample(g_sam_0, _in.vUV);
    }
     
    if (g_int_1==2)
    {
        return vColor;
    }
    
    tLightColor LightColor = (tLightColor) 0.f;
        
    for (uint i = 0; i < iLight2DCount; ++i)
    {
        CalLight2D(LightColor, _in.vViewPos, i);
    }
    
    vColor.rgb = (vColor.rgb * LightColor.vDiff.rgb) + (vColor.rgb * LightColor.vAmb.rgb);
    
    
    if (g_int_1==1)
    {
        return vColor * (float4(1.0f, 0.1f, 0.1f, 1.f));
    }
    else if (g_int_1 == 3)
    {
        vColor.rgb = vColor.rgb * g_float_0;
        return vColor;

    }
     else  
    {
        return vColor;
    }
    
}



// skill 전용
// ==========================
// Std2D Shader33333333333333333333
// g_tex_1 : Output Texture
// ==========================

VTX_OUT VS_Std2D_SKILL(VTX_INPUT _in)
{
    VTX_OUT output = (VTX_OUT) 0.f;
    
    float4 vWorldPos = mul(float4(_in.vPos, 1.f), g_matWorld);
    float4 vViewPos = mul(vWorldPos, g_matView);
    float4 vProjPos = mul(vViewPos, g_matProj);
        
    output.vPosition = vProjPos;
    output.vColor = _in.vColor;
    output.vUV = _in.vUV;
    output.vProjPos = output.vPosition.xy;
    output.vViewPos = vViewPos.xyz;
        
    return output;
}

float4 PS_Std2D_SKILL(VTX_OUT _in) : SV_Target
{
    float4 vColor = (float4) 0.f;
    
    if (g_Anim2DInfo[0].iAnimUse[0])
    {
        float2 AnimUV = float2(g_Anim2DInfo[0].vLeftTop.x + g_Anim2DInfo[0].vStep.x * _in.vUV.x, g_Anim2DInfo[0].vLeftTop.y + g_Anim2DInfo[0].vStep.y * _in.vUV.y);
        vColor = g_animtex.Sample(g_sam_0, AnimUV);
    }
    else
    {
        vColor = g_tex_0.Sample(g_sam_0, _in.vUV);
    }
     
    
    tLightColor LightColor = (tLightColor) 0.f;
        
    for (uint i = 0; i < iLight2DCount; ++i)
    {
        CalLight2D(LightColor, _in.vViewPos, i);
    }
    vColor.rgb = (vColor.rgb * LightColor.vDiff.rgb) + (vColor.rgb * LightColor.vAmb.rgb);
    
    


        
    return vColor;
}






#endif

