// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "UQ_Shared.generated.h"

/**
	Source file: q_shared.c
	Description: Adds necessary definitions used by movement component
*/

// Eventually, this would likely be moved to a subclass of Player State or an Actor Component which is attached to the Player State

USTRUCT(BlueprintType)
struct FUQ_playerState // hehe, funny prefixes
{
    GENERATED_BODY()

    int32 CommandTime;
    int32 PMType;
    int32 BobCycle;
    int32 PMFlags;
    int32 PMTime;
    FVector Origin;
    FVector Velocity;
    int32 WeaponTime;
    int32 Gravity;
    int32 Speed;
    TArray<int32> DeltaAngles;
    int32 GroundEntityNum;
    int32 LegsTimer;
    int32 LegsAnim;
    int32 TorsoTimer;
    int32 TorsoAnim;
    int32 MovementDir;
    FVector GrapplePoint;
    int32 EFlags;
    int32 EventSequence;
    TArray<int32> Events;
    TArray<int32> EventParms;
    int32 ExternalEvent;
    int32 ExternalEventParm;
    int32 ExternalEventTime;
    int32 ClientNum;
    int32 Weapon;
    int32 WeaponState;
    FVector ViewAngles;
    int32 ViewHeight;
    int32 DamageEvent;
    int32 DamageYaw;
    int32 DamagePitch;
    int32 DamageCount;
    TArray<int32> Stats;
    TArray<int32> Persistant;
    TArray<int32> Powerups;
    TArray<int32> Ammo;
    int32 Generic1;
    int32 LoopSound;
    int32 JumppadEnt;
    int32 Ping;
    int32 PMoveFrameCount;
    int32 JumppadFrame;
    int32 EntityEventSequence;
};

USTRUCT(BlueprintType)
struct FUQ_usercmd 
{
    GENERATED_BODY()
    
public:
    UPROPERTY(BlueprintReadOnly, Category = "UserCmd")
    int32 serverTime;

    UPROPERTY(BlueprintReadOnly, Category = "UserCmd")
    FIntVector angles;

    UPROPERTY(BlueprintReadOnly, Category = "UserCmd")
    int32 buttons = 0;

    // If we want to expose the below to Blueprints, we would need to switch to int32, but leaving as-is for now

    uint8 weapon = 0;
    int8 forwardmove = 0, rightmove = 0, upmove = 0;
};

USTRUCT(BlueprintType)
struct FUQ_cplane
{
    GENERATED_BODY()

public:

    FVector	normal;
    float	dist;
    uint8	type;			// for fast side tests: 0,1,2 = axial, 3 = nonaxial
    uint8	signbits;		// signx + (signy<<1) + (signz<<2), used as lookup during collision
    uint8	pad[2];
};

USTRUCT(BlueprintType)
struct FUQ_trace
{
    GENERATED_BODY()

public:

    bool	    allsolid;	// if true, plane is not valid
    bool	    startsolid;	// if true, the initial point was in a solid area
    float		fraction;	// time completed, 1.0 = didn't hit anything
    FVector		endpos;		// final position
    FUQ_cplane  plane;		// surface normal at impact, transformed to world space
    int			surfaceFlags;	// surface hit
    int			contents;	// contents on other side of surface hit
    int			entityNum;	// entity the contacted sirface is a part of
};

class UNREALQUAKE_API UQ_Shared
{
public:
	UQ_Shared();
	~UQ_Shared();
};
