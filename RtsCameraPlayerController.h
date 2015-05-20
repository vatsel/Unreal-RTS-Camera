// by Mark Vatsel

#pragma once

#include "RtsCamera.h"
#include "GameFramework/Pawn.h"
#include "RtsCameraPlayerController.generated.h"

UCLASS()
class RTSCAMERA_API ARtsCameraPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ARtsCameraPlayerController(const FObjectInitializer& ObjectInitializer);
		
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
};