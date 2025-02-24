// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../StoneDefenceType.h"
#include "RuleOfTheBullet.generated.h"



class ARuleOfTheCharacter;
class USplineComponent;
struct FSkillData;
//技能实例
UCLASS()
class STONEDEFENCE_API ARuleOfTheBullet : public AActor
{
	GENERATED_BODY()
	
	////碰撞盒子
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BaseAttrubute", meta = (AllowPrivateAccess = "true"))
	//	class UParticleSystemComponent* ParticleMesh;

	//碰撞盒子
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BaseAttrubute", meta = (AllowPrivateAccess = "true"))
		class USphereComponent* BoxDamage;

	//作为根组件
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BaseAttrubute", meta = (AllowPrivateAccess = "true"))
		class USceneComponent* RootBullet;

	//具有移动属性的组件
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BaseAttrubute", meta = (AllowPrivateAccess = "true"))
		class UProjectileMovementComponent* ProjectileMovement;

public:
	UPROPERTY(EditDefaultsOnly, Category = "Bullet")
		int32 SkillID;

	// Sets default values for this actor's properties
	ARuleOfTheBullet();

	void InitSkill();

	//void ResetIteration();


	UPROPERTY(EditDefaultsOnly, Category = "Bullet")
		TEnumAsByte<EBulletType> BulletType;

	UPROPERTY()
		ESubmissionSkillRequestType SubmissionSkillRequestType;

	//子弹的伤害特效(碰撞后产生的特效)
	UPROPERTY(EditDefaultsOnly, Category = "Bullet")
		UParticleSystem* DamgageParticle;

	//开火特效
	UPROPERTY(EditDefaultsOnly, Category = "Bullet")
		UParticleSystem* OpenFireParticle;

	UPROPERTY(EditDefaultsOnly, Category = "Bullet track line sp")
		float SplineOffset;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
		void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	void RadialDamage(const FVector& Origin, ARuleOfTheCharacter * InstigatorCharacter);

	UPROPERTY()
		USplineComponent *Spline;

	UPROPERTY()
		float CurrentSplineTime;

	FTimerHandle ChainAttackHandle;

	UPROPERTY()
		uint8 ChainAttackCount;

	UFUNCTION()
		void ChainAttack();


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	const FSkillData *GetSkillData();

	UFUNCTION(BlueprintCallable, Category = "Add Skill request")
		void SubmissionSkillRequest();
};
