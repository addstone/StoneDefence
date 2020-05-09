// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

enum EScreenMoveState
{
	Screen_None,
	Screen_UP,
	Screen_Down,
	Screen_Right,
	Screen_Left,
	Screen_RightAndUP,
	Screen_RightAndDown,
	Screen_LeftAndUP,
	Screen_LeftAndDown,
	Screen_MAX
};

class APlayerController;
struct STONETOOLCLASS_API FScreenMoveUnits
{
	//************************************
	// Method:    ListenScreenMove
	// FullName:  FScreenMoveUnits::ListenScreenMove
	// Access:    public 
	// Returns:   bool
	// Qualifier:
	// Parameter: APlayerController * PlayerController
	// Parameter: float ScreenMoveSpeed
	//************************************
	bool ListenScreenMove(APlayerController *PlayerController, const float &ScreenMoveSpeed);

protected:
	//************************************
	// Method:    CursorMove
	// FullName:  FScreenMoveUnits::CursorMove
	// Access:    protected 
	// Returns:   EScreenMoveState
	// Qualifier:
	// Parameter: const APlayerController * PlayerController
	//************************************
	EScreenMoveState CursorMove(const APlayerController *PlayerController);

	//************************************
	// Method:    MoveDirection
	// FullName:  FScreenMoveUnits::MoveDirection
	// Access:    protected 
	// Returns:   bool
	// Qualifier:
	// Parameter: APlayerController * PlayerController
	// Parameter: EScreenMoveState ScreenMoveState
	// Parameter: float ScreenMoveSpeed
	//************************************
	bool MoveDirection(APlayerController *PlayerController, EScreenMoveState ScreenMoveState, const float &ScreenMoveSpeed);
};