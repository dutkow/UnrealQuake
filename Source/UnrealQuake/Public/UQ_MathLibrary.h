// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 *	The goal of the QU_MathLibrary is to provide utility functions so that Quake math library functions can be easily replaced by a corresponding
 *	and clearly named function from the UQ math library.
 * 
 *	Where applicable, this library will serve as an intermediary for built-in Unreal functions.
 * 
 *	While this approach may seem unnecessary for functions that seem to have an obvious corresponding function from an Unreal math library function, 
 *  this approach should help to speed up conversion of Quake code, promote consistency across the code base, and prevent user error.
 * 
 *  In short, if we screw it up, it will be screwed up everywhere, and we will be able to unscrew it up here.
 */
class UNREALQUAKE_API UQ_MathLibrary
{
public:
	UQ_MathLibrary();
	~UQ_MathLibrary();

	static float VectorNormalize(FVector& Vector);

	static void VectorCopy(FVector& in, FVector& out);

	static float VectorLength(FVector& in);

	static void VectorScale(const FVector& v, float scale, FVector& out);

};
