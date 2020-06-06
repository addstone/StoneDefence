// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SimplePopupType.generated.h"

DECLARE_DYNAMIC_DELEGATE(FSimpleBlueprintDelegate);

UENUM(BlueprintType)
enum class ESimplePopupType :uint8
{
	NONE,//�յ�
	DELAY,//����һ��ʱ�䣬���˾�ɾ���Լ�
	WAIT,//������һֱ����
	ONE,//������һ����ť �����ť��ȡ��
	TWO,//��������һ����ȡ�� һ����ȷ��
};

class UUI_SimplePopup;
USTRUCT(BlueprintType)
struct FPopupHandle
{
	GENERATED_USTRUCT_BODY()

	SIMPLEPOPUP_API bool Sure();
	SIMPLEPOPUP_API bool Cancel();

	void SetSimplePopup( UUI_SimplePopup *NewSimplePopup);
private:
	TWeakObjectPtr<UUI_SimplePopup> SimplePopup;
};

