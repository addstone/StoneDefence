// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

DECLARE_DELEGATE_RetVal_OneParam(bool, FSimpleTutoriaMulticastDelegate, int32 );
static FSimpleTutoriaMulticastDelegate SimpleTutoriaMulticastDelegate;//不加static编译不通过