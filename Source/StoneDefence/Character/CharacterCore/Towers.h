// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Core/RuleOfTheCharacter.h"
#include "../../StoneDefenceType.h"
#include "Towers.generated.h"


class UParticleSystemComponent;
class UStaticMeshComponent;
class UDestructibleComponent;
/**
 * 
 */
UCLASS()
class STONEDEFENCE_API ATowers : public ARuleOfTheCharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BaseAttrubute", meta = (AllowPrivateAccess = "true"))
		UParticleSystemComponent *ParticleMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BaseAttrubute", meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent *StaticMeshBuilding;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BaseAttrubute", meta = (AllowPrivateAccess = "true"))
		UDestructibleComponent *DestructibleMeshBuilding;
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BaseAttrubute")
		FRotator TowersRotator;

public:
	ATowers();

	virtual EGameCharacterType::Type GetCharacterType();

	virtual bool IsTeam();
protected:

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	
};
