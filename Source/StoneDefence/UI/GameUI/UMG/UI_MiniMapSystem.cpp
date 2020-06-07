// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_MiniMapSystem.h"
#include "Components/Image.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Engine/SceneCapture2D.h"
#include "Components/SceneCaptureComponent2D.h"
#include "../../../StoneDefenceUtils.h"
#include "Materials/MaterialInterface.h"
#include "../../../Core/GameCore/TowerDefenceGameCamera.h"
#include "Components/SceneCaptureComponent2D.h"

void UUI_MiniMapSystem::NativeConstruct()
{
	Super::NativeConstruct();

	//float Life = 0.0f;
	//if (!URuleOfTheGameUserSettings::GetRuleOfTheGameUserSettings()->GetRealisticMap())
	//{
	//	Life = 0.03f;
	//}

	if (ASceneCapture2D *SceneCapture2D = RenderingUtils::SpawnSceneCapture2D(GetWorld(), CaptureClass, MapSize, 0.3f))
	{
		MiniMapImage->SetBrushFromMaterial(Cast<UMaterialInterface>(MiniMapMat.GetObject()));
	}

	//if (MiniMapImage)
	//{
	//	if (UCanvasPanelSlot *ImagePanelSlot = Cast<UCanvasPanelSlot>(MiniMapImage->Slot))
	//	{
	//		ImagePanelSlot->SetSize(FVector2D(GLOBAL_MANAGEMENT_MACRO()->GetGlobalConfiguration()->MaxMiniMapSize));
	//	}
	//}
}

//Tick
void UUI_MiniMapSystem::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	const TMap<FGuid, FCharacterData> &CharacterDatas = GetGameState()->GetCharacterDatas();

	if (UCanvasPanelSlot *ImagePanelSlot = Cast<UCanvasPanelSlot>(MiniMapImage->Slot))
	{
		//const float MaxMiniMapSize = GLOBAL_MANAGEMENT_MACRO()->GetGlobalConfiguration()->MaxMiniMapSize;
		//const float MaxTargetArmLength = GLOBAL_MANAGEMENT_MACRO()->GetGlobalConfiguration()->MaxTargetArmLength;

		//FVector2D LocalSize2D = MyGeometry.GetDrawSize();

		////��ͼ����
		//FVector2D ZoomSize;
		//{
		//	float TargetArmLength = Cast<ATowerDefenceGameCamera>(GetWorld()->GetFirstPlayerController()->GetPawn())->GetTargetArmLength();
		//	ZoomSize = FVector2D((MaxMiniMapSize / MaxTargetArmLength) * TargetArmLength);

		//	ImagePanelSlot->SetSize(ZoomSize);
		//}

	//	//��ͼλ��
	//	FVector2D MinImageMapOffset;
	//	{
	//		FVector Location = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
	//		MinImageMapOffset.Y = -(ZoomSize.X - (ZoomSize.X / MapSize.BigMapRealSize.X) * Location.X);
	//		MinImageMapOffset.X = -(ZoomSize.Y / MapSize.BigMapRealSize.Y) * Location.Y;

	//		ImagePanelSlot->SetPosition(MinImageMapOffset);
	//	}

	//	if (!URuleOfTheGameUserSettings::GetRuleOfTheGameUserSettings()->GetRealisticMap())
	//	{
			//�����еĽ�ɫ
			for (auto& Tmp : CharacterDatas)
			{
				if (Tmp.Value.Health > 0.f)
				{
					if (!IsExistence(Tmp.Key))
					{
						if (UImage* Point = NewObject<UImage>(GetWorld(), UImage::StaticClass()))
						{
							if (UCanvasPanelSlot* PanelSlot = MiniMap->AddChildToCanvas(Point))
							{
								//PanelSlot->SetZOrder(1.0f);
								//PanelSlot->SetAnchors(0.5f);
								Point->SetBrushFromTexture(Tmp.Value.Icon.LoadSynchronous());
								PanelSlot->SetSize(FVector2D(32.f));
								PanelSlot->SetAlignment(FVector2D(.5f));
								CharacterIcons.Add(Tmp.Key, PanelSlot);
							}
						}
					}
					else
					{
						if (UCanvasPanelSlot* PanelSlot = CharacterIcons[Tmp.Key].Get())
						{
							FVector2D MiniMapPos;
							//MinMapPos.Y = ZoomSize.X - (ZoomSize.X / MapSize.BigMapRealSize.X) * Tmp.Value.Location.X + MinImageMapOffset.Y;
							//MinMapPos.X = (ZoomSize.Y / MapSize.BigMapRealSize.Y) * Tmp.Value.Location.Y + MinImageMapOffset.X;
							
							float MiniSizeX = MyGeometry.GetLocalSize().X;
							float MiniSizeY = MyGeometry.GetLocalSize().Y;

							MiniMapPos.Y = MiniSizeY - (MiniSizeX / MapSize.BigMapRealSize.X)*Tmp.Value.Location.X;
							MiniMapPos.X = (MiniSizeY / MapSize.BigMapRealSize.Y)*Tmp.Value.Location.Y;

							PanelSlot->SetPosition(MiniMapPos);
							//ResetLocation(PanelSlot, MinMapPos, LocalSize2D);
						}
					}
				}
			}

			TArray<FGuid> RemoveGuid;
			for (auto& Tmp2 : CharacterIcons)
			{
				if (!CharacterDatas.Contains(Tmp2.Key))
				{
					if (UCanvasPanelSlot* PanelSlot = CharacterIcons[Tmp2.Key].Get())
					{
						MiniMap->RemoveChild(PanelSlot->Content);
						RemoveGuid.Add(Tmp2.Key);
					}
				}
			}

			for (auto& Tmp3 : RemoveGuid)
			{
				CharacterIcons.Remove(Tmp3);
			}
		//}
	}
}

bool UUI_MiniMapSystem::IsExistence(const FGuid &ID)
{
	for (auto &Tmp : CharacterIcons)
	{
		if (Tmp.Key == ID)
		{
			return true;
		}
	}

	return false;
}

void UUI_MiniMapSystem::ResetLocation(UCanvasPanelSlot* PanelSlot, const FVector2D &MinMapPos, const FVector2D &LocalSize2D)
{
	//FVector2D IconSize = PanelSlot->GetSize() / 2;

	//auto IsRange = [&](const float &CompareValue, const float &Value)->bool
	//{
	//	return Value > -CompareValue && Value < CompareValue;
	//};

	//FVector2D NewPos = MinMapPos;
	//if (MinMapPos.X <= LocalSize2D.X &&
	//	MinMapPos.Y <= LocalSize2D.Y &&
	//	MinMapPos.X >= -LocalSize2D.X &&
	//	MinMapPos.Y >= -LocalSize2D.Y)
	//{

	//}
	//else if (MinMapPos.Y < -LocalSize2D.Y && IsRange(LocalSize2D.X, MinMapPos.X))//��
	//{
	//	NewPos = FVector2D(MinMapPos.X, -LocalSize2D.Y + IconSize.Y);
	//}
	//else if (MinMapPos.X < -LocalSize2D.X && IsRange(LocalSize2D.Y, MinMapPos.Y))//��
	//{
	//	NewPos = FVector2D(-LocalSize2D.X + IconSize.Y, MinMapPos.Y);
	//}
	//else if (MinMapPos.Y > LocalSize2D.Y && IsRange(LocalSize2D.X, MinMapPos.X))//��
	//{
	//	NewPos = FVector2D(MinMapPos.X, LocalSize2D.Y - IconSize.Y);
	//}
	//else if (MinMapPos.X > LocalSize2D.X && IsRange(LocalSize2D.Y, MinMapPos.Y))//��
	//{
	//	NewPos = FVector2D(LocalSize2D.X - IconSize.X, MinMapPos.Y);
	//}
	//else if (MinMapPos.X < -LocalSize2D.X && MinMapPos.Y < -LocalSize2D.Y)//����
	//{
	//	NewPos = -LocalSize2D + IconSize;
	//}
	//else if (MinMapPos.X < -LocalSize2D.X && MinMapPos.Y > LocalSize2D.Y)//����
	//{
	//	NewPos = FVector2D(-LocalSize2D.X + IconSize.X, LocalSize2D.Y - IconSize.Y);
	//}
	//else if (MinMapPos.X > LocalSize2D.X && MinMapPos.Y > LocalSize2D.Y)//����
	//{
	//	NewPos = LocalSize2D - IconSize;
	//}
	//else if (MinMapPos.X > LocalSize2D.X && MinMapPos.Y < -LocalSize2D.Y)//����
	//{
	//	NewPos = FVector2D(LocalSize2D.X - IconSize.X, -LocalSize2D.Y + IconSize.Y);
	//}

	//PanelSlot->SetPosition(NewPos);
}
