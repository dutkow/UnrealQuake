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

	int			commandTime;	// cmd->serverTime of last executed command
	int			pm_type;
	int			bobCycle;		// for view bobbing and footstep generation
	int			pm_flags;		// ducked, jump_held, etc
	int			pm_time;

	FVector		origin;
	FVector		velocity;
	int			weaponTime;
	int			gravity;
	int			speed;
	int			delta_angles[3];	// add to command angles to get view direction
	// changed by spawns, rotating objects, and teleporters

	int			groundEntityNum;// ENTITYNUM_NONE = in air

	int			legsTimer;		// don't change low priority animations until this runs out
	int			legsAnim;		// mask off ANIM_TOGGLEBIT

	int			torsoTimer;		// don't change low priority animations until this runs out
	int			torsoAnim;		// mask off ANIM_TOGGLEBIT

	int			movementDir;	// a number 0 to 7 that represents the reletive angle
	// of movement to the view angle (axial and diagonals)
	// when at rest, the value will remain unchanged
	// used to twist the legs during strafing

	FVector		grapplePoint;	// location of grapple to pull towards if PMF_GRAPPLE_PULL

	int			eFlags;			// copied to entityState_t->eFlags

	int			eventSequence;	// pmove generated events
	//int			events[MAX_PS_EVENTS];
	//int			eventParms[MAX_PS_EVENTS];

	int			externalEvent;	// events set on player from another source
	int			externalEventParm;
	int			externalEventTime;

	int			clientNum;		// ranges from 0 to MAX_CLIENTS-1
	int			weapon;			// copied to entityState_t->weapon
	int			weaponstate;

	FVector		viewangles;		// for fixed views
	int			viewheight;

	// damage feedback
	int			damageEvent;	// when it changes, latch the other parms
	int			damageYaw;
	int			damagePitch;
	int			damageCount;

	//int			stats[MAX_STATS];
	//int			persistant[MAX_PERSISTANT];	// stats that aren't cleared on death
	//int			powerups[MAX_POWERUPS];	// level.time that the powerup runs out
	//int			ammo[MAX_WEAPONS];

	int			generic1;
	int			loopSound;
	int			jumppad_ent;	// jumppad entity hit this frame

	// not communicated over the net at all
	int			ping;			// server to game info for scoreboard
	int			pmove_framecount;	// FIXME: don't transmit over the network
	int			jumppad_frame;
	int			entityEventSequence;
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
