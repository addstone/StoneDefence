// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../StoneDefenceType.h"
#include "RuleOfTheBullet.generated.h"



class ARuleOfTheCharacter;
class USplineComponent;
struct FSkillData;
//����ʵ��
UCLASS()
class STONEDEFENCE_API ARuleOfTheBullet : public AActor
{
	GENERATED_BODY()
	
	////��ײ����
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BaseAttrubute", meta = (AllowPrivateAccess = "true"))
	//	class UParticleSystemComponent* ParticleMesh;

	//��ײ����
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BaseAttrubute", meta = (AllowPrivateAccess = "true"))
		class USphereComponent* BoxDamage;

	//��Ϊ�����
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BaseAttrubute", meta = (AllowPrivateAccess = "true"))
		class USceneComponent* RootBullet;

	//�����ƶ����Ե����
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BaseAttrubute", meta = (AllowPrivateAccess = "true"))
		class UProjectileMovementComponent* ProjectileMovement;

public:
	UPROPERTY(EditDefaultsOnly, Category = "Bullet")
		int32 SkillID;

	// Sets default values for this actor's properties
	ARuleOfTheBullet();

	void InitSkill();

	UPROPERTY(EditDefaultsOnly, Category = "Bullet")
		TEnumAsByte<EBulletType> BulletType;

	UPROPERTY()
		ESubmissionSkillRequestType SubmissionSkillRequestType;

	//�ӵ����˺���Ч(��ײ���������Ч)
	UPROPERTY(EditDefaultsOnly, Category = "Bullet")
		UParticleSystem* DamgageParticle;

	//������Ч
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
