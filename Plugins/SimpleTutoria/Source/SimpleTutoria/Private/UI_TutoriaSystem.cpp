// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_TutoriaSystem.h"
#include "Tutoria/UI_TutoriaSlot.h"
#include "MediaAssets/Public/MediaPlayer.h"
#include "Components/Image.h"
#include "Components/CheckBox.h"
#include "Components/Slider.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

void UUI_TutoriaSystem::NativeConstruct()
{
	InitMadia(1);

	MediaPlayer->OnEndReached.AddDynamic(this, &UUI_TutoriaSystem::FinshPlayMovie);

	ReplayButton->OnClicked.AddDynamic(this, &UUI_TutoriaSystem::Replay);
	PauseButton->OnClicked.AddDynamic(this, &UUI_TutoriaSystem::Pause);
	CloseButton->OnClicked.AddDynamic(this, &UUI_TutoriaSystem::Close);
	SuspendButton->OnCheckStateChanged.AddDynamic(this, &UUI_TutoriaSystem::ClickedCheckBox);

	MovieProgress->OnMouseCaptureBegin.AddDynamic(this, &UUI_TutoriaSystem::MouseCaptureBegin);
	MovieProgress->OnMouseCaptureEnd.AddDynamic(this, &UUI_TutoriaSystem::MouseCaptureEnd);
}

void UUI_TutoriaSystem::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (MediaPlayer)
	{
		float NewValue = MediaPlayer->GetTime().GetTotalSeconds() / MediaPlayer->GetDuration().GetTotalSeconds();
		MovieProgress->SetValue(NewValue);

		PlayTimeText->SetText(FText::FromString(FString::Printf(TEXT("%02d:%02d:%02d/%02d:%02d:%02d"), MediaPlayer->GetTime().GetHours(), MediaPlayer->GetTime().GetMinutes(), MediaPlayer->GetTime().GetSeconds(), MediaPlayer->GetDuration().GetHours(), MediaPlayer->GetDuration().GetMinutes(), MediaPlayer->GetDuration().GetSeconds())));
	}
}

void UUI_TutoriaSystem::InitMadia(bool bPlayMovie)
{
	if (UUI_TutoriaSlot *TutoriaSlot = CreateWidget<UUI_TutoriaSlot>(GetWorld(), TutoriaSlotClass))
	{
		if (MediaPlayer)
		{
			MediaPlayer->OpenSource(TutoriaSlot->MediaSource);
		}
	}
}

void UUI_TutoriaSystem::ActivationMovie()
{
	if (MediaPlayer->IsPlaying())
	{
		MediaPlayer->Pause();
		PauseImage->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		SuspendButton->SetCheckedState(ECheckBoxState::Unchecked);
	}
	else
	{
		MediaPlayer->Play();
		PauseImage->SetVisibility(ESlateVisibility::Hidden);
		SuspendButton->SetCheckedState(ECheckBoxState::Checked);
	}
	
}

void UUI_TutoriaSystem::ClickedCheckBox(bool ClickedWidget)
{
	ActivationMovie();
}

void UUI_TutoriaSystem::Replay()
{
	if (MediaPlayer->IsReady())
	{
		MediaPlayer->Rewind();
	}
}

void UUI_TutoriaSystem::Close()
{
	if (MediaPlayer->IsPlaying())
	{
		MediaPlayer->Pause();
		PauseImage->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		SuspendButton->SetCheckedState(ECheckBoxState::Unchecked);
	}
	MediaPlayer->Close();
}

void UUI_TutoriaSystem::Pause()
{
	ActivationMovie();
}

void UUI_TutoriaSystem::FinshPlayMovie()
{
	if (MediaPlayer->IsReady())
	{
		MediaPlayer->Close();
	}
}

void UUI_TutoriaSystem::MouseCaptureBegin()
{

}

void UUI_TutoriaSystem::MouseCaptureEnd()
{

}
