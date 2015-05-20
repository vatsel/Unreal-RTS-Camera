#include "RtsCamera.h"
#include "RtsCameraGameMode.h"
#include "RtsCameraPlayerController.h"
#include "RtsCameraDefaultPawn.h"

ARtsCameraGameMode::ARtsCameraGameMode(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PlayerControllerClass = ARtsCameraPlayerController::StaticClass();
	DefaultPawnClass = ARtsCameraDefaultPawn::StaticClass();
}


