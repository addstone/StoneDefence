// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI_TutoriaSlot.generated.h"

class UButton;
class UMediaSource;
/**
 * 
 */
UCLASS()
class SIMPLETUTORIA_API UUI_TutoriaSlot : public UUserWidget
{
	GENERATED_BODY()

public:
	//������ƵԴ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
		UMediaSource *MediaSource;

};
