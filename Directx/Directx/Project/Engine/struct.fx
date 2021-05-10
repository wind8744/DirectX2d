#ifndef _STRUCT
#define _STRUCT

struct tParticle
{
    float3 vWorldPos;
    float3 vWorldDir;

    float m_fCurTime;
    float m_fMaxLife;
    float m_fSpeed;
    
    int iAlive;
    int iPadding[2];
};

struct tParticleShared
{
    int iAliveCount;
    int iPadding[3];
};
struct tTile
{
   
    float2 vLeftTop;
    float2 vStep;

};
struct tTileShared
{
    int iTileXSize;
    int iTileYSize;
    int iPadding[2];
};
struct tLightColor
{
    float4 vDiff; // Diffuse (난반사광 세기)	
    float4 vAmb; // Ambient (환경광)
};

struct tLight2DInfo
{
    tLightColor color; // 광원 색상

    float4 vDir; // 광원의 방향
    float4 vWorldPos; // 광원의 월드 위치
    
    uint  eType; // 광원 타입		
    float fRange; // 광원의 범위
    float fAngle; // 광원 각도
	
    int iPadding;
};

struct tAnim2D
{
    float2  vLeftTop;
    float2  vStep;
    int     iAnimUse[4];
};

#endif
