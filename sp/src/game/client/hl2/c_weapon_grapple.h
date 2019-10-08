//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: Implements the grapple hook weapon.
//
// Primary attack: fires a beam that hooks on a surface.
// Secondary attack: switches between pull and rapple modes
//
//
//=============================================================================//
#ifndef WEAPON_GRAPPLE_H
#define WEAPON_GRAPPLE_H
#ifdef _WIN32
#pragma once
#endif
//#include "weapon_hl2mpbasehlmpcombatweapon.h"
#include "c_basehlcombatweapon.h"
#include "sprite.h"
#ifndef CLIENT_DLL
#include "rope.h"
#include "props.h"
#endif
#include "rope_shared.h"
#include "c_te_effect_dispatch.h"
#include "beam_shared.h"
#ifndef CLIENT_DLL
class CWeaponGrapple;
//-----------------------------------------------------------------------------
// Grapple Hook
//-----------------------------------------------------------------------------
class CGrappleHook : public CBaseCombatCharacter
{
	DECLARE_CLASS(CGrappleHook, CBaseCombatCharacter);
public:
	CGrappleHook() { };
	~CGrappleHook();
	Class_T Classify(void) { return CLASS_NONE; }
public:
	void Spawn(void);
	void Precache(void);
	void FlyThink(void);
	void HookedThink(void);
	void HookTouch(CBaseEntity *pOther);
	bool CreateVPhysics(void);
	unsigned int PhysicsSolidMaskForEntity() const;
	static CGrappleHook *HookCreate(const Vector &vecOrigin, const QAngle &angAngles, CBaseEntity *pentOwner = NULL);
protected:
	DECLARE_DATADESC();
private:
	CHandle<CWeaponGrapple> m_hOwner;
	CHandle<CBasePlayer> m_hPlayer;
	CHandle<CDynamicProp> m_hBolt;
	IPhysicsSpring *m_pSpring;
	float	m_fSpringLength;
	bool	m_bPlayerWasStanding;
};
#endif
//-----------------------------------------------------------------------------
// CWeaponGrapple
//-----------------------------------------------------------------------------
#ifdef CLIENT_DLL
#define CWeaponGrapple C_WeaponGrapple
#endif
//class CWeaponGrapple : public CBaseHL2MPCombatWeapon
class CWeaponGrapple : public CBaseHLCombatWeapon
{
	// DECLARE_CLASS( CWeaponGrapple, CBaseHL2MPCombatWeapon );
	DECLARE_CLASS(CWeaponGrapple, CBaseHLCombatWeapon);
public:
	CWeaponGrapple(void);
	virtual void	Precache(void);
	virtual void	PrimaryAttack(void);
	virtual void	SecondaryAttack(void);
	virtual bool	Deploy(void);
	bool	CanHolster(void);
	virtual bool	Holster(CBaseCombatWeapon *pSwitchingTo = NULL);
	void	Drop(const Vector &vecVelocity);
	virtual bool	Reload(void);
	virtual void	ItemPostFrame(void);
	virtual void	ItemBusyFrame(void);
	void	NotifyHookDied(void);
	bool	HasAnyAmmo(void);
	CBaseEntity *GetHook(void) { return m_hHook; }
	bool ToggleHook(void);
	void DrawBeam(const Vector &startPos, const Vector &endPos, float width);
	void	DoImpactEffect(trace_t &tr, int nDamageType);
	bool m_bHook;
	DECLARE_NETWORKCLASS();
	DECLARE_PREDICTABLE();
private:
	void	FireHook(void);
#ifndef CLIENT_DLL
	DECLARE_ACTTABLE();
#endif
private:
#ifndef CLIENT_DLL
	CHandle<CBeam> pBeam;
	CHandle<CSprite> m_pLightGlow;
#endif
	CNetworkVar(bool, m_bInZoom);
	CNetworkVar(bool, m_bMustReload);
	CNetworkHandle(CBaseEntity, m_hHook);
	CWeaponGrapple(const CWeaponGrapple &);
	CNetworkVar(int, m_nBulletType);
};
#endif // WEAPON_GRAPPLE_H