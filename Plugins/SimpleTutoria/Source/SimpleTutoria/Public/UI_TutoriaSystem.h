// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI_TutoriaSystem.generated.h"

class UScrollBox;
class UCheckBox;
class UButton;
class USlider;
class UImage;
class UTextBlock;
class UMediaPlayer;
class UUI_TutoriaSlot;
class UWidgetAnimation;
class UMediaSoundComponent;
class UComboBoxString;

UCLASS()
class SIMPLETUTORIA_API UUI_TutoriaSystem : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
		UScrollBox *ScrollMediaList;

	UPROPERTY(meta = (BindWidget))
		UCheckBox *ScreenButton;

	UPROPERTY(meta = (BindWidget))
		UButton* ReplayButton;

	UPROPERTY(meta = (BindWidget))
		UCheckBox* SuspendButton;

	UPROPERTY(meta = (BindWidget))
		UButton* PauseButton;

	UPROPERTY(meta = (BindWidget))
		USlider* MovieProgress;

	UPROPERTY(meta = (BindWidget))
		UImage*  PauseImage;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* PlayTimeText;

public:
	//载入视频播放
	UPROPERTY(EditAnywhere, Category = UI)
		UMediaPlayer* MediaPlayer;

	UPROPERTY(EditAnywhere, Category = UI)
		TSubclassOf<UUI_TutoriaSlot> TutoriaSlotClass;
protected:
	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	//初始化视频资源
	UFUNCTION()
		void InitMadia();

	UFUNCTION()
		void ActivationMovie();

	UFUNCTION()
		void ClickedCheckBox(bool ClickedWidget);

	UFUNCTION()
		void Replay();

	UFUNCTION()
		void Close();

	UFUNCTION()
		void Pause();

	UFUNCTION()
		bool Play(int32 InIndex);

	UFUNCTION()
		void FinshPlayMovie();

	UFUNCTION()
		void MouseCaptureBegin();

	UFUNCTION()
		void MouseCaptureEnd();

protected:
	UPROPERTY()
		UWidgetAnimation* OpenBarAnimation;

	UPROPERTY()
		UWidgetAnimation* CloseBarAnimation;

	float MouseMoveCount;
	bool bMouseMoveFinsh;

};
