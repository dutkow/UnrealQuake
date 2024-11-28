// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UQ_Shared.h"

#include "UQ_Public.generated.h"

/**
	Source file: bg_public.h
	Description: Adds necessary definitions used by movement component
*/

USTRUCT(BlueprintType)
struct Fpmove
{
    GENERATED_BODY()

public:

	// state (in / out)
	FUQ_playerState* ps;

	// command (in)
	FUQ_usercmd	cmd;
	int32		tracemask;			// collide against these types of surfaces
	int32		debugLevel;			// if set, diagnostic output will be printed
	bool		noFootsteps;		// if the game is setup for no footsteps by the server
	bool		gauntletHit;		// true if a gauntlet attack would actually hit something

	int32		framecount;

	// results (out)
	int32		numtouch;
	//int32		touchents[MAXTOUCH];

	FVector		mins, maxs;			// bounding box size

	int32		watertype;
	int32		waterlevel;

	float		xyspeed;

	// for fixed msec Pmove
	int32		pmove_fixed;
	int32		pmove_msec;

	// callbacks to test the world
	// these will be different functions during game and cgame
	//void		(*trace)(trace_t* results, const vec3_t start, const vec3_t mins, const vec3_t maxs, const vec3_t end, int passEntityNum, int contentMask);
	//int			(*pointcontents)(const vec3_t point, int passEntityNum);
};


class UNREALQUAKE_API UQ_Public
{
public:
	UQ_Public();
	~UQ_Public();
};
