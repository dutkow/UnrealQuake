// Fill out your copyright notice in the Description page of Project Settings.


#include "UQ_MathLibrary.h"

UQ_MathLibrary::UQ_MathLibrary()
{
}

UQ_MathLibrary::~UQ_MathLibrary()
{
}

float UQ_MathLibrary::VectorNormalize(FVector& inout)
{
	inout.Normalize();
	return inout.Length();
}

void UQ_MathLibrary::VectorCopy(FVector& in, FVector& out)
{
	out = in;
}

float UQ_MathLibrary::VectorLength(FVector& in)
{
	return in.Length();
}

void UQ_MathLibrary::VectorScale(const FVector& v, float scale, FVector& out)
{
	out = v * scale;
}
