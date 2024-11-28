// Fill out your copyright notice in the Description page of Project Settings.


#include "UQ_MovementComponent.h"
#include "UQ_Shared.h"
#include "UQ_Local.h"
#include "UQ_Public.h"
#include "UQ_SurfaceFlags.h"

// Initialize default q3 values
UUQ_MovementComponent::UUQ_MovementComponent()
	: pm_stopspeed(100.0f)
	, pm_duckScale(0.25f)
	, pm_swimScale(0.50f)
	, pm_wadeScale(0.70f)
	, pm_accelerate(10.0f)
	, pm_airaccelerate(1.0f)
	, pm_wateraccelerate(4.0f)
	, pm_flyaccelerate(8.0f)
	, pm_friction(6.0f)
	, pm_waterfriction(1.0f)
	, pm_flightfriction(3.0f)
	, pm_spectatorfriction(5.0f)
	, c_pmove(0)
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UUQ_MovementComponent::BeginPlay()
{
	Super::BeginPlay();	
}

void UUQ_MovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}


void UUQ_MovementComponent::PM_AddEvent(int newEvent)
{
}

void UUQ_MovementComponent::PM_AddTouchEnt(int entityNum)
{
}

void UUQ_MovementComponent::PM_StartTorsoAnim(int anim)
{
}

void UUQ_MovementComponent::PM_StartLegsAnim(int anim)
{
}

void UUQ_MovementComponent::PM_ContinueLegsAnim(int anim)
{
}

void UUQ_MovementComponent::PM_ContinueTorsoAnim(int anim)
{
}

void UUQ_MovementComponent::PM_ForceLegsAnim(int anim)
{
}

void UUQ_MovementComponent::PM_ClipVelocity(FVector in, FVector normal, FVector out, float overbounce)
{
}

void UUQ_MovementComponent::PM_Friction()
{
}

void UUQ_MovementComponent::PM_Accelerate(FVector wishdir, float wishspeed, float accel)
{
}

float UUQ_MovementComponent::PM_CmdScale(FUQ_usercmd* cmd)
{
	return 0.0f;
}

void UUQ_MovementComponent::PM_SetMovementDir()
{
}

bool UUQ_MovementComponent::PM_CheckJump()
{
	return false;
}

bool UUQ_MovementComponent::PM_CheckWaterJump()
{
	return false;
}

void UUQ_MovementComponent::PM_WaterJumpMove()
{
}

void UUQ_MovementComponent::PM_WaterMove()
{
}

void UUQ_MovementComponent::PM_InvulnerabilityMove()
{
}

void UUQ_MovementComponent::PM_FlyMove()
{
}

void UUQ_MovementComponent::PM_AirMove()
{
}

void UUQ_MovementComponent::PM_GrappleMove()
{
}

// UQ: #COMPLETE
void UUQ_MovementComponent::PM_WalkMove()
{
	int32		i = 0;
	FVector		wishvel = FVector::ZeroVector;
	float		fmove = 0.0f, smove = 0.0f;
	FVector		wishdir = FVector::ZeroVector;
	float		wishspeed = 0.0f;
	float		scale = 0.0f;
	FUQ_usercmd	cmd;
	float		accelerate = 0.0f;
	float		vel = 0.0f;
	
	if (pm.waterlevel > 2 && FVector::DotProduct(pml.forward, pml.groundTrace.plane.normal) > 0) {
		// begin swimming
		PM_WaterMove();
		return;
	}
	
	if (PM_CheckJump()) {
		// jumped away
		if (pm.waterlevel > 1) {
			PM_WaterMove();
		}
		else {
			PM_AirMove();
		}
		return;
	}

	PM_Friction();

	fmove = pm.cmd.forwardmove;
	smove = pm.cmd.rightmove;

	cmd = pm.cmd;
	scale = PM_CmdScale(&cmd);

	// set the movementDir so clients can rotate the legs for strafing
	PM_SetMovementDir();

	// project moves down to flat plane
	pml.forward[2] = 0;
	pml.right[2] = 0;
	
	// project the forward and right directions onto the ground plane
	PM_ClipVelocity(pml.forward, pml.groundTrace.plane.normal, pml.forward, OVERCLIP);
	PM_ClipVelocity(pml.right, pml.groundTrace.plane.normal, pml.right, OVERCLIP);
	
	pml.forward.Normalize();
	pml.right.Normalize();

	
	// UQ: Alternatively, you could do wishvel.X = pml.forward.X * fmove + pml.right.X * smove for each of X, Y, Z, but leaving as-is since q3 code is nice and short
	for (i = 0; i < 3; i++) {
		wishvel[i] = pml.forward[i] * fmove + pml.right[i] * smove;
	}

	// UQ: This was commented out in q3 source
	// when going up or down slopes the wish velocity should Not be zero
	//	wishvel[2] = 0;

	wishdir = wishvel;
	wishspeed = wishdir.Normalize();
	wishspeed *= scale;

	// clamp the speed lower if ducking
	if (pm.ps->pm_flags & PMF_DUCKED) {
		if (wishspeed > pm.ps->speed * pm_duckScale) {
			wishspeed = pm.ps->speed * pm_duckScale;
		}
	}

	// clamp the speed lower if wading or walking on the bottom
	if (pm.waterlevel) {
		float	waterScale;

		waterScale = pm.waterlevel / 3.0;
		waterScale = 1.0 - (1.0 - pm_swimScale) * waterScale;
		if (wishspeed > pm.ps->speed * waterScale) {
			wishspeed = pm.ps->speed * waterScale;
		}
	}

	// when a player gets hit, they temporarily lose
	// full control, which allows them to be moved a bit
	if ((pml.groundTrace.surfaceFlags & SURF_SLICK) || pm.ps->pm_flags & PMF_TIME_KNOCKBACK) {
		accelerate = pm_airaccelerate;
	}
	else {
		accelerate = pm_accelerate;
	}

	PM_Accelerate(wishdir, wishspeed, accelerate);

	//Com_Printf("velocity = %1.1f %1.1f %1.1f\n", pm->ps->velocity[0], pm->ps->velocity[1], pm->ps->velocity[2]);
	//Com_Printf("velocity1 = %1.1f\n", VectorLength(pm->ps->velocity));

	if ((pml.groundTrace.surfaceFlags & SURF_SLICK) || pm.ps->pm_flags & PMF_TIME_KNOCKBACK) {
		pm.ps->velocity[2] -= pm.ps->gravity * pml.frametime;
	}
	else {
		// don't reset the z velocity for slopes
		// pm->ps->velocity[2] = 0;
	}

	vel = pm.ps->velocity.Length();

	// slide along the ground plane
	PM_ClipVelocity(pm.ps->velocity, pml.groundTrace.plane.normal,
		pm.ps->velocity, OVERCLIP);

	// don't decrease velocity when going up or down a slope
	pm.ps->velocity.Normalize();

	// UQ:commenting out q3 line, I think the below works
	//VectorScale(pm.ps->velocity, vel, pm.ps->velocity);
	pm.ps->velocity *= vel;


	// don't do anything if standing still
	if (!pm.ps->velocity[0] && !pm.ps->velocity[1]) {
		return;
	}

	PM_StepSlideMove(false);
	// UQ: Could replace with a UE log if desired
	//Com_Printf("velocity2 = %1.1f\n", VectorLength(pm->ps->velocity));
}

void UUQ_MovementComponent::PM_DeadMove()
{
}

void UUQ_MovementComponent::PM_NoclipMove()
{
}

int UUQ_MovementComponent::PM_FootstepForSurface()
{
	return 0;
}

void UUQ_MovementComponent::PM_CrashLand()
{
}

void UUQ_MovementComponent::PM_GroundTraceMissed()
{
}

void UUQ_MovementComponent::PM_GroundTrace()
{
}

void UUQ_MovementComponent::PM_SetWaterLevel()
{
}

void UUQ_MovementComponent::PM_CheckDuck()
{
}

void UUQ_MovementComponent::PM_Footsteps()
{
}

void UUQ_MovementComponent::PM_WaterEvents()
{
}

void UUQ_MovementComponent::PM_BeginWeaponChange(int weapon)
{
}

void UUQ_MovementComponent::PM_FinishWeaponChange()
{
}

void UUQ_MovementComponent::PM_TorsoAnimation()
{
}

void UUQ_MovementComponent::PM_Weapon()
{
}

void UUQ_MovementComponent::PM_Animate()
{
}

void UUQ_MovementComponent::PM_DropTimers()
{
}
