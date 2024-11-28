// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UQ_Public.h"
#include "UQ_Local.h"

#include "UQ_MovementComponent.generated.h"

/** 
	Source file: bg_pmove.c
	Description: Implementation of movement functions as a UActorComponent 
*/

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALQUAKE_API UUQ_MovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UUQ_MovementComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Beginning of Quake III parameters

	//@TODO Fix these variables
	//Fpmove pm;
	//Fpmovel pml;

	// movement parameters
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float pm_stopspeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float pm_duckScale;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float pm_swimScale;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float pm_wadeScale;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float pm_accelerate;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float pm_airaccelerate;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float pm_wateraccelerate;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float pm_flyaccelerate;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float pm_friction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float pm_waterfriction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float pm_flightfriction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float pm_spectatorfriction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int c_pmove;

	// Beginning of Quake III Arena functions

	UFUNCTION(BlueprintCallable)
	void PM_AddEvent(int newEvent);

	UFUNCTION(BlueprintCallable)
	void PM_AddTouchEnt(int entityNum);

	UFUNCTION(BlueprintCallable)
	static void PM_StartTorsoAnim(int anim);

	UFUNCTION(BlueprintCallable)
	static void PM_StartLegsAnim(int anim);

	UFUNCTION(BlueprintCallable)
	static void PM_ContinueLegsAnim(int anim);

	UFUNCTION(BlueprintCallable)
	static void PM_ContinueTorsoAnim(int anim);

	UFUNCTION(BlueprintCallable)
	static void PM_ForceLegsAnim(int anim);

	// This is not static in q3, but it gave compiler errors. May need to reverse
	UFUNCTION(BlueprintCallable)
	static void PM_ClipVelocity(FVector in, FVector normal, FVector out, float overbounce);

	UFUNCTION(BlueprintCallable)
	static void PM_Friction();

	UFUNCTION(BlueprintCallable)
	static void PM_Accelerate(FVector wishdir, float wishspeed, float accel);

	static float PM_CmdScale(FUQ_usercmd* cmd);

	UFUNCTION(BlueprintCallable)
	static void PM_SetMovementDir();

	UFUNCTION(BlueprintCallable)
	static bool PM_CheckJump();

	UFUNCTION(BlueprintCallable)
	static bool PM_CheckWaterJump();

	UFUNCTION(BlueprintCallable)
	static void PM_WaterJumpMove();

	UFUNCTION(BlueprintCallable)
	static void PM_WaterMove();

	//#ifdef MISSIONPACK
	UFUNCTION(BlueprintCallable)
	static void PM_InvulnerabilityMove();
	//#endif

	UFUNCTION(BlueprintCallable)
	static void PM_FlyMove();

	UFUNCTION(BlueprintCallable)
	static void PM_AirMove();

	UFUNCTION(BlueprintCallable)
	static void PM_GrappleMove();

	// This is static in q3 but static causes compiler errors. May need to revert
	UFUNCTION(BlueprintCallable)
	void PM_WalkMove();

	UFUNCTION(BlueprintCallable)
	static void PM_DeadMove();

	UFUNCTION(BlueprintCallable)
	static void PM_NoclipMove();

	UFUNCTION(BlueprintCallable)
	static int PM_FootstepForSurface();

	UFUNCTION(BlueprintCallable)
	static void PM_CrashLand();

	//UFUNCTION(BlueprintCallable)
	//static bool PM_CorrectAllSolid(FTraceResult& Trace);

	UFUNCTION(BlueprintCallable)
	static void PM_GroundTraceMissed();

	UFUNCTION(BlueprintCallable)
	static void PM_GroundTrace();

	UFUNCTION(BlueprintCallable)
	static void PM_SetWaterLevel();

	UFUNCTION(BlueprintCallable)
	static void PM_CheckDuck();

	UFUNCTION(BlueprintCallable)
	static void PM_Footsteps();

	UFUNCTION(BlueprintCallable)
	static void PM_WaterEvents();

	UFUNCTION(BlueprintCallable)
	static void PM_BeginWeaponChange(int weapon);

	UFUNCTION(BlueprintCallable)
	static void PM_FinishWeaponChange();

	UFUNCTION(BlueprintCallable)
	static void PM_TorsoAnimation();

	UFUNCTION(BlueprintCallable)
	static void PM_Weapon();

	UFUNCTION(BlueprintCallable)
	static void PM_Animate();

	UFUNCTION(BlueprintCallable)
	static void PM_DropTimers();

	//UFUNCTION(BlueprintCallable)
	//void PM_UpdateViewAngles(playerState_t* ps, const usercmd_t* cmd);

	//UFUNCTION(BlueprintCallable)
	//void PmoveSingle(pmove_t* pmove);

	//UFUNCTION(BlueprintCallable)
	//void Pmove(pmove_t* pmove);
};
