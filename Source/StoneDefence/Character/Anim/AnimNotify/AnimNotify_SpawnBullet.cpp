// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_SpawnBullet.h"
#include "../../Core/RuleOfTheCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "../../../StoneDefenceUtils.h"
#include "../../../Bullet/RuleOfTheBullet.h"

UAnimNotify_SpawnBullet::UAnimNotify_SpawnBullet()
	:Super()
{

#if WITH_EDITORONLY_DATA
	InSocketName = TEXT("OpenFire");
	NotifyColor = FColor(196, 142, 255, 255);
#endif // WITH_EDITORONLY_DATA
}

FString UAnimNotify_SpawnBullet::GetNotifyName_Implementation() const
{
	if (BulletClass)
	{
		return BulletClass->GetName();
	}
	else
	{
		return Super::GetNotifyName_Implementation();
	}
}

void UAnimNotify_SpawnBullet::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
//#if WITH_EDITOR
//	FVector ComponentLocation = MeshComp->GetSocketLocation(InSocketName);
//	FRotator ComponentRotation = MeshComp->GetSocketRotation(InSocketName);
//#else
//	FVector ComponentLocation = Character->GetFirePoint()->GetComponentLocation();
//	FRotator ComponentRotation = Character->GetFirePoint()->GetComponentRotation();
//#endif

#if WITH_EDITOR
	FVector ComponentLocation = MeshComp->GetSocketLocation(InSocketName);
	FRotator ComponentRotation = MeshComp->GetSocketRotation(InSocketName);
	if (APawn *Character = Cast<APawn>(MeshComp->GetOuter()))
#else
	FVector ComponentLocation = Character->GetFirePoint()->GetComponentLocation();
	FRotator ComponentRotation = Character->GetFirePoint()->GetComponentRotation();
	if (ARuleOfTheCharacter *Character = Cast<ARuleOfTheCharacter>(MeshComp->GetOuter()))
#endif
	{
		//if (ARuleOfTheBullet *Bullet = StoneDefenceUtils::SpawnBullet(Character->GetWorld(), Cast<APawn>(Character), BulletClass, ComponentLocation, ComponentRotation))
		//{
		//	//Bullet->SubmissionSkillRequestType = ESubmissionSkillRequestType::MANUAL;
		//	//Bullet->InitSkill();
		//}
		FTransform Transform;
		Transform.SetLocation(ComponentLocation);
		Transform.SetRotation(ComponentRotation.Quaternion());

		FActorSpawnParameters ActorSpawnParameters;
		ActorSpawnParameters.Instigator = Character;


		if (ARuleOfTheBullet *Bullet = Character->GetWorld()->SpawnActor<ARuleOfTheBullet>(BulletClass, Transform, ActorSpawnParameters))
		{

		}
	}
}
