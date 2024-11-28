// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UQ_Shared.h"

#include "UQ_Local.generated.h"

/**
	Source file: bg_local.h
	Description: Adds necessary definitions used by movement component
*/

USTRUCT(BlueprintType)
struct Fpmovel
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


class UNREALQUAKE_API UQ_Local
{
public:
	UQ_Local();
	~UQ_Local();
};
