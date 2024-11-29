/*
===========================================================================
// Copyright (C) 2024 Vincent Dutkowski. All Rights Reserved.

file: bg_pmove.h
descripion: Not part of the original Quake III Arena source code.
Instead, this is an attempt at encapsulating much of that logic inside
of a UActorComponent to be able to expose and use the Quake III movement
logic inside of Unreal.
===========================================================================
*/

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "bg_public.h" 

#include "bg_pmove.generated.h"

USTRUCT(BlueprintType)
struct FUQ_PlayerMovementInput
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, Category = "Movement")
    float ForwardInput;

    UPROPERTY(BlueprintReadWrite, Category = "Movement")
    float RightInput;

    UPROPERTY(BlueprintReadWrite, Category = "Movement")
    float UpInput;

    FUQ_PlayerMovementInput()
        : ForwardInput(0.0f), RightInput(0.0f), UpInput(0.0f)
    {
    }
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UNREALQUAKE_API UBP_Pmove : public UActorComponent
{
    GENERATED_BODY()

public:
    UBP_Pmove();

protected:
    virtual void BeginPlay() override;

public:
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    UFUNCTION(BlueprintCallable)
    void HandlePlayerMovementInput(FUQ_PlayerMovementInput InPlayerMovementInput);

    void PM_WalkMove(void);

    void PmoveSingle(pmove_t* pmove);

    void Pmove(pmove_t* pmove);

    UPROPERTY(BlueprintReadWrite)
    FUQ_PlayerMovementInput PlayerMovementInput;
};