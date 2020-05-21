// Fill out your copyright notice in the Description page of Project Settings.


#include "RuleOfTheCharacter.h"
#include "Components/SceneComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "../../UI/Character/UI_Health.h"
#include "../../Data/CharacterData.h"
#include "../../StoneDefenceUtils.h"
#include "../../SimpleDrawText/Source/SimpleDrawText/Public/Actor/DrawText.h"

// Sets default values
ARuleOfTheCharacter::ARuleOfTheCharacter()
	:bAttack(false)
{
	GUID = FGuid::NewGuid();
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HomePoint = CreateDefaultSubobject<USceneComponent>(TEXT("HomePoint"));
	Widget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));
	OpenFriePoint = CreateDefaultSubobject<UArrowComponent>(TEXT("OpenFilePoint"));
	TraceShowCharacterInformation = CreateDefaultSubobject<UBoxComponent>(TEXT("TraceShowCharacterInformation"));

	HomePoint->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	Widget->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	OpenFriePoint->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	TraceShowCharacterInformation->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	//设置预设Scanning
	TraceShowCharacterInformation->SetCollisionProfileName("Scanning");
	TraceShowCharacterInformation->SetBoxExtent(FVector(38.f, 38.f, 100.f));
}

// Called when the game starts or when spawned
void ARuleOfTheCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	//生成角色需要生成一个默认的控制
	if (!GetController())
	{
		SpawnDefaultController();
	}

	UpdateUI();
}

void ARuleOfTheCharacter::UpdateUI()
{
	if (Widget)
	{
		//if (const FCharacterData *InCharacterData = GetCharacterData())
		//{
		//	if (InCharacterData->IsValid())
		//	{
				if (UUI_Health *HealthUI = Cast<UUI_Health>(Widget->GetUserWidgetObject()))
				{
					HealthUI->SetTitle(GetCharacterData().Name.ToString());
					HealthUI->SetHealth(GetHealth() / GetMaxHealth());
				}
			}
	//	}
	//}
}

// Called every frame
void ARuleOfTheCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float ARuleOfTheCharacter::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	float DamageValue = Expression::GetDamage(Cast<ARuleOfTheCharacter>(DamageCauser), this);

	GetCharacterData().Health -= DamageValue;
	if (!IsActive())
	{
		GetCharacterData().Health = 0.0f;
	}

	UpdateUI();

	if (DrawTextClass)
	{
		if (ADrawText* MyValueText = GetWorld()->SpawnActor<ADrawText>(DrawTextClass, GetActorLocation(), FRotator::ZeroRotator))
		{
			FString DamageText = FString::Printf(TEXT("-%0.f"), DamageValue);
			MyValueText->SetTextBlock(DamageText, FLinearColor::Red, DamageValue / GetCharacterData().MaxHealth);
		}
	}
	return DamageValue;
}

bool ARuleOfTheCharacter::IsDeath()
{
	
	return GetHealth() <= 0.f;
}

float ARuleOfTheCharacter::GetHealth()
{
	return GetCharacterData().Health;
}

float ARuleOfTheCharacter::GetMaxHealth()
{
	return GetCharacterData().MaxHealth;
}

bool ARuleOfTheCharacter::IsTeam()
{
	return false;
}

FCharacterData & ARuleOfTheCharacter::GetCharacterData()
{
	if (GetGameState())
	{
		return GetGameState()->GetCharacterData(GUID);
	}
	return CharacterDataNULL;
}

EGameCharacterType::Type ARuleOfTheCharacter::GetCharacterType()
{
	return EGameCharacterType::Type::MAX;
}
