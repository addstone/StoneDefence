// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../../Interface/Character/RuleCharacter.h"
#include "../../Core/GameCore/TowersDefencePlayerController.h"
#include "../../Core/GameCore/TowersDefenceGameState.h"
#include "../../Core/GameCore/TowersDefencePlayerState.h"
#include "../../StoneDefenceType.h"
#include "Engine/StaticMesh.h"
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
	UPROPERTY(EditDefaultsOnly, Category = UI)
		TSubclassOf<class ADrawText> DrawTextClass;

	UPROPERTY(EditDefaultsOnly, Category = Death)
		float DelayDeath;

	//被动技能
	UPROPERTY(EditDefaultsOnly, Category = "Skill")
		TArray<int32> SkillIDs;

public:
	// Sets default values for this character's properties
	ARuleOfTheCharacter();

	UFUNCTION(/*Server*/)
		void ResetGUID();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
		virtual void OnClicked(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed);
public:
	void UpdateUI();

	//更新被动技能
	void UpdateSkill(int32 SkillID);

	UFUNCTION(/*Client*/)
		void InitSkill();

public:	

	UFUNCTION(/*Client*/)
		void RemoveSkillSlot_Client(const FGuid &SlotID);

	UFUNCTION(/*Client*/)
		void AddSkillSlot_Client(const FGuid &SlotID);

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CharacterAttrubute")
		bool bAttack;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ID")
		FGuid GUID;

	UPROPERTY(EditDefaultsOnly, Category = Type)
		TEnumAsByte<EGameCharacterType::Type> CharacterType;

protected:
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

public:
	//由服务器调用
	virtual void RegisterTeam() {}

	virtual EGameCharacterType::Type GetCharacterType();
	virtual bool IsDeath();
	virtual float GetHealth();
	virtual float GetMaxHealth();
	virtual ETeam GetTeamType();

	virtual FCharacterData &GetCharacterData();

	UFUNCTION(Blueprintable, BlueprintPure, Category = "Towers|Test")
		UStaticMesh *GetDollMesh(FTransform &Transform, int32 MeshID);

	UFUNCTION(BlueprintImplementableEvent)
		void AttackBegin();

	UFUNCTION(BlueprintImplementableEvent)
		void AttackEnd();

	UFUNCTION(BlueprintImplementableEvent)
		void CharacterDeath();

	UFUNCTION(BlueprintImplementableEvent)
		void AnimTag();

public:
	FORCEINLINE ATowersDefencePlayerController* GetGameController() { return GetWorld() ? GetWorld()->GetFirstPlayerController<ATowersDefencePlayerController>() : nullptr; }
	FORCEINLINE ATowersDefenceGameState* GetGameState() { return GetWorld() ? GetWorld()->GetGameState<ATowersDefenceGameState>() : nullptr; }
	FORCEINLINE ATowersDefencePlayerState* GetPlayerState() { return GetGameController()->GetPlayerState<ATowersDefencePlayerState>(); }

	FORCEINLINE USceneComponent *GetHommingPoint() const { return HomePoint; }
	FORCEINLINE UArrowComponent *GetFirePoint() const { return OpenFriePoint; }

public:
	UFUNCTION(Blueprintable, BlueprintPure, Category = "Towers|Attrubute")
		bool IsActive() { return !IsDeath(); }

#if WITH_EDITOR
private:
	FCharacterData NULLData;
#endif
};
