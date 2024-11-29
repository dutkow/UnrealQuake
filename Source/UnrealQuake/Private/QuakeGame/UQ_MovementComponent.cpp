// Fill out your copyright notice in the Description page of Project Settings.


#include "QuakeGame/UQ_MovementComponent.h"
#include "QuakeGame/UQ_Shared.h"
#include "QuakeGame/UQ_Local.h"
#include "QuakeGame/UQ_Public.h"
#include "QuakeGame/UQ_SurfaceFlags.h"
#include "UQ_MathLibrary.h"


// UQ: Declaring global variables like this isn't really recommended in Unreal, but to maintain consistency with the q3 source code on a first pass I am leaving this as-is
Fpmove* pm;
Fpml	pml;

// movement parameters
float	pm_stopspeed = 100.0f;
float	pm_duckScale = 0.25f;
float	pm_swimScale = 0.50f;
float	pm_wadeScale = 0.70f;

float	pm_accelerate = 10.0f;
float	pm_airaccelerate = 1.0f;
float	pm_wateraccelerate = 4.0f;
float	pm_flyaccelerate = 8.0f;

float	pm_friction = 6.0f;
float	pm_waterfriction = 1.0f;
float	pm_flightfriction = 3.0f;
float	pm_spectatorfriction = 5.0f;

int		c_pmove = 0;


// Initialize default q3 values
UUQ_MovementComponent::UUQ_MovementComponent()
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

void UUQ_MovementComponent::PM_ForceLegsAnim(EUQ_animNumber anim)
{
}

void UUQ_MovementComponent::PM_ClipVelocity(FVector in, FVector normal, FVector out, float overbounce)
{
}

void UUQ_MovementComponent::PM_Friction()
{
}

/*
==============
PM_Accelerate

Handles user intended acceleration
==============
*/
void UUQ_MovementComponent::PM_Accelerate(FVector wishdir, float wishspeed, float accel)
{
	// UQ: Need to fix the declared variables in .h; these are just placeholders to compile the rest of the code
	//Fpmove pm = Fpmove();
	//Fpml pml = Fpml();

#if 1
	// q2 style
	int			i;
	float		addspeed, accelspeed, currentspeed;

	currentspeed = FVector::DotProduct(pm->ps->velocity, wishdir);
	addspeed = wishspeed - currentspeed;
	if (addspeed <= 0) {
		return;
	}
	accelspeed = accel * pml.frametime * wishspeed;
	if (accelspeed > addspeed) {
		accelspeed = addspeed;
	}

	for (i = 0; i < 3; i++) {
		pm->ps->velocity[i] += accelspeed * wishdir[i];
	}
#else
	{
		// proper way (avoids strafe jump maxspeed bug), but feels bad
		FVector		wishVelocity;
		FVector		pushDir;
		float		pushLen;
		float		canPush;

		wishVelocity = wishdir * wishspeed;
		pushDir = wishVelocity - pm->ps->velocity;
		pushLen = pushDir.Normalize();

		canPush = accel * pml.frametime * wishspeed;
		if (canPush > pushLen) {
			canPush = pushLen;
		}
		// UQ: This is not commented out in q3, but I haven't had to do this math yet and this movement is not even used and I am lazy
		//VectorMA(pm->ps->velocity, canPush, pushDir, pm->ps->velocity);
	}
#endif
}

/*
============
PM_CmdScale

Returns the scale factor to apply to cmd movements
This allows the clients to use axial -127 to 127 values for all directions
without getting a sqrt(2) distortion in speed.
============
*/
float UUQ_MovementComponent::PM_CmdScale(FUQ_usercmd* cmd)
{
	int		max;
	float	total;
	float	scale;

	max = abs(cmd->forwardmove);
	if (abs(cmd->rightmove) > max) {
		max = abs(cmd->rightmove);
	}
	if (abs(cmd->upmove) > max) {
		max = abs(cmd->upmove);
	}
	if (!max) {
		return 0;
	}

	total = sqrt(cmd->forwardmove * cmd->forwardmove
		+ cmd->rightmove * cmd->rightmove + cmd->upmove * cmd->upmove);
	scale = (float)pm->ps->speed * max / (127.0 * total);

	return scale;
}

/*
================
PM_SetMovementDir

Determine the rotation of the legs reletive
to the facing dir
================
*/
void UUQ_MovementComponent::PM_SetMovementDir()
{
	if (pm->cmd.forwardmove || pm->cmd.rightmove) {
		if (pm->cmd.rightmove == 0 && pm->cmd.forwardmove > 0) {
			pm->ps->movementDir = 0;
		}
		else if (pm->cmd.rightmove < 0 && pm->cmd.forwardmove > 0) {
			pm->ps->movementDir = 1;
		}
		else if (pm->cmd.rightmove < 0 && pm->cmd.forwardmove == 0) {
			pm->ps->movementDir = 2;
		}
		else if (pm->cmd.rightmove < 0 && pm->cmd.forwardmove < 0) {
			pm->ps->movementDir = 3;
		}
		else if (pm->cmd.rightmove == 0 && pm->cmd.forwardmove < 0) {
			pm->ps->movementDir = 4;
		}
		else if (pm->cmd.rightmove > 0 && pm->cmd.forwardmove < 0) {
			pm->ps->movementDir = 5;
		}
		else if (pm->cmd.rightmove > 0 && pm->cmd.forwardmove == 0) {
			pm->ps->movementDir = 6;
		}
		else if (pm->cmd.rightmove > 0 && pm->cmd.forwardmove > 0) {
			pm->ps->movementDir = 7;
		}
	}
	else {
		// if they aren't actively going directly sideways,
		// change the animation to the diagonal so they
		// don't stop too crooked
		if (pm->ps->movementDir == 2) {
			pm->ps->movementDir = 1;
		}
		else if (pm->ps->movementDir == 6) {
			pm->ps->movementDir = 7;
		}
	}
}

/*
=============
PM_CheckJump
=============
*/
bool UUQ_MovementComponent::PM_CheckJump()
{
	if (pm->ps->pm_flags & PMF_RESPAWNED) {
		return false;		// don't allow jump until all buttons are up
	}

	if (pm->cmd.upmove < 10) {
		// not holding jump
		return false;
	}

	// must wait for jump to be released
	if (pm->ps->pm_flags & PMF_JUMP_HELD) {
		// clear upmove so cmdscale doesn't lower running speed
		pm->cmd.upmove = 0;
		return false;
	}

	pml.groundPlane = false;		// jumping away
	pml.walking = false;
	pm->ps->pm_flags |= PMF_JUMP_HELD;

	pm->ps->groundEntityNum = ENTITYNUM_NONE;
	pm->ps->velocity[2] = JUMP_VELOCITY;
	//PM_AddEvent(EV_JUMP);

	if (pm->cmd.forwardmove >= 0) {
		PM_ForceLegsAnim(EUQ_animNumber::LEGS_JUMP);
		pm->ps->pm_flags &= ~PMF_BACKWARDS_JUMP;
	}
	else {
		PM_ForceLegsAnim(EUQ_animNumber::LEGS_JUMPB);
		pm->ps->pm_flags |= PMF_BACKWARDS_JUMP;
	}
	return true;
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

/*
===================
PM_FlyMove

Only with the flight powerup
===================
*/
void UUQ_MovementComponent::PM_FlyMove()
{
	int		i;
	FVector	wishvel;
	float	wishspeed;
	FVector	wishdir;
	float	scale;

	// normal slowdown
	PM_Friction();

	scale = PM_CmdScale(&pm->cmd);
	//
	// user intentions
	//
	if (!scale) {
		wishvel[0] = 0;
		wishvel[1] = 0;
		wishvel[2] = 0;
	}
	else {
		for (i = 0; i < 3; i++) {
			wishvel[i] = scale * pml.forward[i] * pm->cmd.forwardmove + scale * pml.right[i] * pm->cmd.rightmove;
		}

		wishvel[2] += scale * pm->cmd.upmove;
	}

	UQ_MathLibrary::VectorCopy(wishvel, wishdir);
	wishspeed = UQ_MathLibrary::VectorNormalize(wishdir);

	PM_Accelerate(wishdir, wishspeed, pm_flyaccelerate);

	PM_StepSlideMove(false);
}

/*
===================
PM_AirMove

===================
*/
void UUQ_MovementComponent::PM_AirMove()
{
	int			i = 0;
	FVector		wishvel = FVector::ZeroVector;
	float		fmove, smove;
	FVector		wishdir = FVector::ZeroVector;
	float		wishspeed = 0;
	float		scale = 0;
	FUQ_usercmd	cmd;

	PM_Friction();

	fmove = pm->cmd.forwardmove;
	smove = pm->cmd.rightmove;

	cmd = pm->cmd;
	scale = PM_CmdScale(&cmd);

	// set the movementDir so clients can rotate the legs for strafing
	PM_SetMovementDir();
	wishvel[2] = 0;
	/*
	// project moves down to flat plane
	pml.forward[2] = 0;
	pml.right[2] = 0;
	VectorNormalize(pml.forward);
	VectorNormalize(pml.right);

	for (i = 0; i < 2; i++) {
		wishvel[i] = pml.forward[i] * fmove + pml.right[i] * smove;
	}

	VectorCopy(wishvel, wishdir);
	wishspeed = VectorNormalize(wishdir);
	wishspeed *= scale;

	// not on ground, so little effect on velocity
	PM_Accelerate(wishdir, wishspeed, pm_airaccelerate);

	// we may have a ground plane that is very steep, even
	// though we don't have a groundentity
	// slide along the steep plane
	if (pml.groundPlane) {
		PM_ClipVelocity(pm->ps->velocity, pml.groundTrace.plane.normal,
			pm->ps->velocity, OVERCLIP);
	}

#if 0
	//ZOID:  If we are on the grapple, try stair-stepping
	//this allows a player to use the grapple to pull himself
	//over a ledge
	if (pm->ps->pm_flags & PMF_GRAPPLE_PULL)
		PM_StepSlideMove(qtrue);
	else
		PM_SlideMove(qtrue);
#endif

	PM_StepSlideMove(qtrue);*/
}

/*
===================
PM_GrappleMove

===================
*/
void UUQ_MovementComponent::PM_GrappleMove()
{
	FVector vel, v;
	float vlen;

	UQ_MathLibrary::VectorScale(pml.forward, -16, v);
	UQ_MathLibrary::VectorAdd(pm->ps->grapplePoint, v, v);
	UQ_MathLibrary::VectorSubtract(v, pm->ps->origin, vel);
	vlen = UQ_MathLibrary::VectorLength(vel);
	UQ_MathLibrary::VectorNormalize(vel);

	if (vlen <= 100)
		UQ_MathLibrary::VectorScale(vel, 10 * vlen, vel);
	else
		UQ_MathLibrary::VectorScale(vel, 800, vel);

	UQ_MathLibrary::VectorCopy(vel, pm->ps->velocity);

	pml.groundPlane = false;
}

/*
===================
PM_WalkMove

===================
*/
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
	
	if (pm->waterlevel > 2 && FVector::DotProduct(pml.forward, pml.groundTrace.plane.normal) > 0) {
		// begin swimming
		PM_WaterMove();
		return;
	}
	
	if (PM_CheckJump()) {
		// jumped away
		if (pm->waterlevel > 1) {
			PM_WaterMove();
		}
		else {
			PM_AirMove();
		}
		return;
	}

	PM_Friction();

	fmove = pm->cmd.forwardmove;
	smove = pm->cmd.rightmove;

	cmd = pm->cmd;
	scale = PM_CmdScale(&cmd);

	// set the movementDir so clients can rotate the legs for strafing
	PM_SetMovementDir();

	// project moves down to flat plane
	pml.forward[2] = 0;
	pml.right[2] = 0;
	
	// project the forward and right directions onto the ground plane
	PM_ClipVelocity(pml.forward, pml.groundTrace.plane.normal, pml.forward, OVERCLIP);
	PM_ClipVelocity(pml.right, pml.groundTrace.plane.normal, pml.right, OVERCLIP);
	
	UQ_MathLibrary::VectorNormalize(pml.forward);
	UQ_MathLibrary::VectorNormalize(pml.right);
	
	// UQ: Alternatively, you could do wishvel.X = pml.forward.X * fmove + pml.right.X * smove for each of X, Y, Z, but leaving as-is since q3 code is nice and short
	for (i = 0; i < 3; i++) {
		wishvel[i] = pml.forward[i] * fmove + pml.right[i] * smove;
	}

	// UQ: This was commented out in q3 source
	// when going up or down slopes the wish velocity should Not be zero
	//	wishvel[2] = 0;

	// UQ: Consider implementing a UQ math library which uses Unreal's functions but with a naming convention similar to q3 to avoid confusion when comparing against source code
	UQ_MathLibrary::VectorCopy(wishvel, wishdir);
	wishspeed = UQ_MathLibrary::VectorNormalize(wishdir);
	wishspeed *= scale;

	// clamp the speed lower if ducking
	if (pm->ps->pm_flags & PMF_DUCKED) {
		if (wishspeed > pm->ps->speed * pm_duckScale) {
			wishspeed = pm->ps->speed * pm_duckScale;
		}
	}

	// clamp the speed lower if wading or walking on the bottom
	if (pm->waterlevel) {
		float	waterScale;

		waterScale = pm->waterlevel / 3.0;
		waterScale = 1.0 - (1.0 - pm_swimScale) * waterScale;
		if (wishspeed > pm->ps->speed * waterScale) {
			wishspeed = pm->ps->speed * waterScale;
		}
	}

	// when a player gets hit, they temporarily lose
	// full control, which allows them to be moved a bit
	if ((pml.groundTrace.surfaceFlags & SURF_SLICK) || pm->ps->pm_flags & PMF_TIME_KNOCKBACK) {
		accelerate = pm_airaccelerate;
	}
	else {
		accelerate = pm_accelerate;
	}

	PM_Accelerate(wishdir, wishspeed, accelerate);

	//Com_Printf("velocity = %1.1f %1.1f %1.1f\n", pm->ps->velocity[0], pm->ps->velocity[1], pm->ps->velocity[2]);
	//Com_Printf("velocity1 = %1.1f\n", VectorLength(pm->ps->velocity));

	if ((pml.groundTrace.surfaceFlags & SURF_SLICK) || pm->ps->pm_flags & PMF_TIME_KNOCKBACK) {
		pm->ps->velocity[2] -= pm->ps->gravity * pml.frametime;
	}
	else {
		// don't reset the z velocity for slopes
		// pm->ps->velocity[2] = 0;
	}

	vel = UQ_MathLibrary::VectorLength(pm->ps->velocity);

	// slide along the ground plane
	PM_ClipVelocity(pm->ps->velocity, pml.groundTrace.plane.normal,
		pm->ps->velocity, OVERCLIP);

	// don't decrease velocity when going up or down a slope
	UQ_MathLibrary::VectorNormalize(pm->ps->velocity);
	UQ_MathLibrary::VectorScale(pm->ps->velocity, vel, pm->ps->velocity);


	// don't do anything if standing still
	if (!pm->ps->velocity[0] && !pm->ps->velocity[1]) {
		return;
	}

	PM_StepSlideMove(false);
	// UQ: Could replace with a UE log if desired
	//Com_Printf("velocity2 = %1.1f\n", VectorLength(pm->ps->velocity));*/
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

void UUQ_MovementComponent::PM_UpdateViewAngles(FUQ_playerState* ps, const FUQ_usercmd cmd)
{
}

void UUQ_MovementComponent::PmoveSingle(Fpmove pmove)
{
}

void UUQ_MovementComponent::Pmove(Fpmove pmove)
{
}
