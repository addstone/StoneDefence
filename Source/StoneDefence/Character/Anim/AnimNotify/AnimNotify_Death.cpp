// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_Death.h"

#if WITH_EDITOR
//Persona
#include "AnimationEditorPreviewActor.h"
#endif

UAnimNotify_Death::UAnimNotify_Death()
	:Super()
{

#if WITH_EDITORONLY_DATA
	NotifyColor = FColor(0, 0, 0, 255);
#endif // WITH_EDITORONLY_DATA

}

void UAnimNotify_Death::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
#if WITH_EDITOR
	AAnimationEditorPreviewActor *Character = Cast<AAnimationEditorPreviewActor>(MeshComp->GetOuter());
	if (!Character)
	{
		if (AActor *CharacterActor = Cast<AActor>(MeshComp->GetOuter()))
		{
			CharacterActor->Destroy();
		}
	}
#else
	if (AActor *Character = Cast<AActor>(MeshComp->GetOuter()))
	{
		Character->Destroy();
	}
#endif
}
