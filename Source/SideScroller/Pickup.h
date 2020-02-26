// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pickup.generated.h"

UCLASS()
class SIDESCROLLER_API APickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickup();

public:
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* VisualMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
	float WaveAmplitude = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
		float WaveRate = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
		float RotationSpeed = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pickup")
		float Health = 100.0f;

	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, 
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	FVector StartLocation;
	float WaveTime = 1.0f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
