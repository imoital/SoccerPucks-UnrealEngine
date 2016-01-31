// Fill out your copyright notice in the Description page of Project Settings.

#include "SoccerPucks.h"
#include "Hero.h"
#include "Ball.h"

// Sets default values
AHero::AHero()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set this pawn to be controlled by the lowest-numbered player
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void AHero::BeginPlay()
{
	Super::BeginPlay();

	TArray<UBoxComponent*> all_box_components;
	GetComponents(all_box_components);

	for (UBoxComponent* box_comp : all_box_components)
	{
		box_component = box_comp;
	}

	TArray<USphereComponent*> all_sphere_components;
	GetComponents(all_sphere_components);

	for (USphereComponent* sphere_comp : all_sphere_components)
	{
		if (sphere_comp->GetName().Equals("ShootCollider")) {
			shoot_collider = sphere_comp;
		}
	}

	if (shoot_collider != NULL) {
		UE_LOG(LogTemp, Warning, TEXT("REGISTERED"));
		shoot_collider->OnComponentBeginOverlap.AddDynamic(this, &AHero::OnOverlapBegin);
		shoot_collider->OnComponentEndOverlap.AddDynamic(this, &AHero::OnOverlapEnd);
	}
}

// Called every frame
void AHero::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	const FVector MoveDirection = FVector(x_value, y_value, 0.f).GetClampedToMaxSize(1.0f);
	//const float MoveSpeed = 20.0f;
	
	if (box_component != NULL) {
		//push_force = 9990000.0f
		const FVector Movement = MoveDirection * push_force;
		GEngine->AddOnScreenDebugMessage(0, 15.0f, FColor::Red, box_component->GetPhysicsLinearVelocity().ToString() /*Movement.ToString()*/);
		if (Movement.SizeSquared() > 0.0f)
		{
			box_component->AddForce(Movement);
		}
	}

}

// Called to bind functionality to input
void AHero::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	// Respond every frame to the values of our two movement axes, "MoveX" and "MoveY".
	InputComponent->BindAxis("MoveX", this, &AHero::Move_XAxis);
	InputComponent->BindAxis("MoveY", this, &AHero::Move_YAxis);
}

void AHero::OnOverlapBegin_Implementation(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{	
	UE_LOG(LogTemp, Warning, TEXT("ENTER"));
	UE_LOG(LogTemp, Warning, TEXT("%s"), *OtherComp->GetName());
	if(OtherActor->IsA(ABall::StaticClass()))
		UE_LOG(LogTemp, Warning, TEXT("Your message"));
}

void AHero::OnOverlapEnd_Implementation(AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("LEAVE"));
}

void AHero::Shoot()
{

}

void AHero::Move_XAxis(float AxisValue)
{
	x_value = AxisValue;
}

void AHero::Move_YAxis(float AxisValue)
{
	y_value = AxisValue;
}