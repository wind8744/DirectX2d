#ifndef _VALUE
#define _VALUE

#include "struct.fx"

cbuffer TRANSFORM : register(b0)
{
    row_major matrix g_matWorld;
    row_major matrix g_matView;
    row_major matrix g_matProj;
    row_major matrix g_matWV;
    row_major matrix g_matWVP;    
};

cbuffer MATERIAL_DATA : register(b1)
{
    float4 g_vDiff;
    float4 g_vSpec;
    float4 g_vEmis;
    
    int g_int_0;
    int g_int_1;
    int g_int_2;
    int g_int_3;
    
    float g_float_0;
    float g_float_1;
    float g_float_2;
    float g_float_3;
    
    float2 g_vec2_0;
    float2 g_vec2_1;
    float2 g_vec2_2;
    float2 g_vec2_3;
    
    float4 g_vec4_0;
    float4 g_vec4_1;
    float4 g_vec4_2;
    float4 g_vec4_3;
    
    row_major matrix g_mat_0;
    row_major matrix g_mat_1;
    row_major matrix g_mat_2;
    row_major matrix g_mat_3;
    
    int btex_0;
    int btex_1;
    int btex_2;
    int btex_3;
    int btex_4;
    int btex_5;
    int btex_6;
    int btex_7;
    int btex_8;
    int btexarr_0;
    int btexarr_1;
    int btexarr_2;
    int btexarr_3;    
}


cbuffer GLOBAL_VALUE : register(b2)
{
    float2  g_vResolution;  // render target resolution
    float2  g_vNoiseResolution; // noise texture resolution
    float   g_DT;           
    float   g_AccTime;      // �����ð�       
    
    uint    iLight2DCount; // 2D���� ����
    uint    iLight3DCount; // 3D���� ����
}

Texture2D g_tex_0 : register(t0);
Texture2D g_tex_1 : register(t1);
Texture2D g_tex_2 : register(t2);
Texture2D g_tex_3 : register(t3);
Texture2D g_tex_4 : register(t4);
Texture2D g_tex_5 : register(t5);
Texture2D g_tex_6 : register(t6);
Texture2D g_tex_7 : register(t7);
Texture2DArray g_texarr_0 : register(t8);
Texture2DArray g_texarr_1 : register(t9);
Texture2DArray g_texarr_2 : register(t10);
Texture2DArray g_texarr_3 : register(t11);


Texture2D g_noise : register(t70);
StructuredBuffer<tLight2DInfo> g_Light2DInfo : register(t71);

StructuredBuffer<tAnim2D> g_Anim2DInfo : register(t72);
Texture2D g_animtex : register(t73);


SamplerState g_sam_0 : register(s0); // anisotropic
SamplerState g_sam_1 : register(s1); // point

#endif