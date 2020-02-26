// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickup.h"
#include "SideScrollerCharacter.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
APickup::APickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	VisualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	VisualMesh->SetupAttachment(RootComponent);
	VisualMesh->BodyInstance.SetResponseToAllChannels(ECR_Overlap);
	VisualMesh->OnComponentBeginOverlap.AddDynamic(this, &APickup::OnOverlapBegin);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> VisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube"));
	if (VisualAsset.Succeeded()) 
	{
		VisualMesh->SetStaticMesh(VisualAsset.Object);
	}

}

void APickup::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp) 
	{
		ASideScrollerCharacter* Character = Cast<ASideScrollerCharacter>(OtherActor);
		if (Character) 
		{
			Character->PickUp(5.0f);
			Destroy();
		}
	}
}

// Called when the game starts or when spawned
void APickup::BeginPlay()
{
	Super::BeginPlay();
	StartLocation = GetActorLocation();
}

// Called every frame
void APickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	WaveTime = WaveTime + (WaveRate * DeltaTime);
	float Wave = FMath::Sin(WaveTime);

	FVector newLocation = StartLocation + FVector::UpVector * (Wave * WaveAmplitude);
	FRotator NewRotation = GetActorRotation();
	float DeltaRotation = DeltaTime * RotationSpeed;
	NewRotation.Yaw += DeltaRotation;

	SetActorLocationAndRotation(newLocation, NewRotation);

}

