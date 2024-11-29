// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "QuakeGame/UQ_Shared.h"
#include "QuakeGame/UQ_Public.h"

#include "UQ_Local.generated.h"

/**
	Source file: bg_local.h
	Description: Adds necessary definitions used by movement component
*/

#define	MIN_WALK_NORMAL	0.7f		// can't walk on very steep slopes

#define	STEPSIZE		18

#define	JUMP_VELOCITY	270

#define	TIMER_LAND		130
#define	TIMER_GESTURE	(34*66+50)

#define	OVERCLIP		1.001f

USTRUCT(BlueprintType)
struct Fpml
{
	GENERATED_BODY()

public:

	FVector		forward, right, up;
	float		frametime;

	int32		msec;

	bool		walking;
	bool		groundPlane;
	FUQ_trace	groundTrace;

	float		impactSpeed;

	FVector		previous_origin;
	FVector		previous_velocity;
	int32		previous_waterlevel;
};
//@TODO Get these working. They are not commented out in q3 and have placeholders that are accessible in movement component for now
//extern	Fpmove* pm;
//extern	Fpml	pml;

// movement parameters
extern	float	pm_stopspeed;
extern	float	pm_duckScale;
extern	float	pm_swimScale;
extern	float	pm_wadeScale;

extern	float	pm_accelerate;
extern	float	pm_airaccelerate;
extern	float	pm_wateraccelerate;
extern	float	pm_flyaccelerate;

extern	float	pm_friction;
extern	float	pm_waterfriction;
extern	float	pm_flightfriction;

extern	int		c_pmove;

bool		PM_SlideMove(bool gravity);
void		PM_StepSlideMove(bool gravity);

