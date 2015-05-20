// by Mark Vatsel

#pragma once

#include "GameFramework/GameMode.h"
#include "RtsCameraGameMode.generated.h"

UCLASS()
class RTSCAMERA_API ARtsCameraGameMode : public AGameMode
{
	GENERATED_BODY()	
	
public:
	ARtsCamerasGameMode(const FObjectInitializer& ObjectInitializer);
	
};