// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_Tag.h"
#include "Components/SkeletalMeshComponent.h"
#include "../../Core/RuleOfTheCharacter.h"

UAnimNotify_Tag::UAnimNotify_Tag()
	:Super()
{

#if WITH_EDITORONLY_DATA
	NotifyColor = FColor(255, 0, 0, 255);
#endif // WITH_EDITORONLY_DATA

}

void UAnimNotify_Tag::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (ARuleOfTheCharacter *CharacterActor = Cast<ARuleOfTheCharacter>(MeshComp->GetOuter()))
	{
		CharacterActor->AnimTag();
	}
}
