// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../../Interface/Character/IRuleCharacter.h"
#include "../../Core/GameCore/TowersDefencePlayerController.h"
#include "../../Core/GameCore/TowersDefenceGameState.h"
#include "../../Core/GameCore/TowersDefencePlayerState.h"
#include "RuleOfTheCharacter.generated.h"


class UBoxComponent;
class UArrowComponent;
class UWidgetComponent;
class USceneComponent;

UCLASS()
class STONEDEFENCE_API ARuleOfTheCharacter : public ACharacter, public IRuleCharacter
{
	GENERATED_BODY()

	//射线捕捉对象
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BaseAttrubute", meta = (AllowPrivateAccess = "true"))
		UBoxComponent *TraceShowCharacterInformation;

	//开火点
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BaseAttrubute", meta = (AllowPrivateAccess = "true"))
		UArrowComponent *OpenFriePoint;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BaseAttrubute", meta = (AllowPrivateAccess = "true"))
		UWidgetComponent *Widget;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BaseAttrubute", meta = (AllowPrivateAccess = "true"))
		USceneComponent *HomePoint;

public:
	// Sets default values for this character's properties
	ARuleOfTheCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


protected:
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	virtual bool IsDeath();
	virtual float GetHealth();
	virtual float GetMaxHealth();
	virtual bool IsTeam();

public:
	FORCEINLINE ATowersDefencePlayerController* GetGameController() { return GetWorld() ? GetWorld()->GetFirstPlayerController<ATowersDefencePlayerController>() : nullptr; }
	FORCEINLINE ATowersDefenceGameState* GetGameState() { return GetWorld() ? GetWorld()->GetGameState<ATowersDefenceGameState>() : nullptr; }
	FORCEINLINE ATowersDefencePlayerState* GetPlayerState() { return GetGameController()->GetPlayerState<ATowersDefencePlayerState>(); }

	FORCEINLINE USceneComponent *GetHommingPoint() const { return HomePoint; }
	FORCEINLINE UArrowComponent *GetFirePoint() const { return OpenFriePoint; }

public:
	UFUNCTION(Blueprintable, BlueprintPure, Category = "Towers|Attrubute")
		bool IsActive() { return !IsDeath(); }
};
