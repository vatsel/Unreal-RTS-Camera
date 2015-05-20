// by Mark Vatsel

#include "RtsCamera.h"
#include "RtsCameraPlayerController.h"


ARtsCameraPlayerController::ARtsCameraPlayerController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;	
}

void ARtsCameraPlayerController::BeginPlay()
{
	Super::BeginPlay();	
}

void ARtsCameraPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);	
	
}
