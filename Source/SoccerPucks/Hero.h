// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Hero.generated.h"

UCLASS()
class SOCCERPUCKS_API AHero : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AHero();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	UBoxComponent* skeletal_component;

	//Input functions
	void Move_XAxis(float AxisValue);
	void Move_YAxis(float AxisValue);

	//Input variables
	FVector CurrentVelocity;
	bool bGrowing;

	float x_value;
	float y_value;
};
