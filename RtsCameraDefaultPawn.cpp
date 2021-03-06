// © 2015 Mark Vatsel.


#include "RtsCamera.h"
#include "RtsCameraDefaultPawn.h"
#include "RtsCameraPlayerController.h"

ARtsCameraDefaultPawn::ARtsCameraDefaultPawn(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

	CustomCollisionComponent = ObjectInitializer.CreateDefaultSubobject<USphereComponent>(this,FName("RtsCameraDefaultPawn_CollisionComponent0"));
	CustomCollisionComponent->InitSphereRadius(100.0f);
	CustomCollisionComponent->CanCharacterStepUpOn = ECB_No;
	CustomCollisionComponent->SetCanEverAffectNavigation(false);
	CustomCollisionComponent->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	RootComponent = CustomCollisionComponent;	

	MovementComponent = ObjectInitializer.CreateDefaultSubobject<UFloatingPawnMovement>(this, FName("RtsCameraDefaultPawn_MovementComponent0"));
	MovementComponent->UpdatedComponent = CustomCollisionComponent;
}

void ARtsCameraDefaultPawn::SetupPlayerInputComponent(UInputComponent* InputComponent)
{	
	check(InputComponent);
	
	InputComponent->BindAxis("Pan Forward", this, &ARtsCameraDefaultPawn::PanForward);
	InputComponent->BindAxis("Pan Right", this, &ARtsCameraDefaultPawn::PanRight);
	InputComponent->BindAxis("Mouse Wheel", this, &ARtsCameraDefaultPawn::ZoomIn);

	InputComponent->BindAction("Rotate Camera", IE_Pressed, this, &ARtsCameraDefaultPawn::EngageRotation);
	InputComponent->BindAction("Rotate Camera", IE_Released, this, &ARtsCameraDefaultPawn::DisengageRotation);
}

void ARtsCameraDefaultPawn::Tick(float DeltaSeconds)
{
	if (Controller)
	{
		APlayerController* playerController = Cast<APlayerController>(GetController());
		if (playerController != nullptr)
		{
			FVector2D mouseLocation;
			if (playerController->GetMousePosition(mouseLocation.X, mouseLocation.Y))
			{
				int32 screenWidth = 0;
				int32 screenHeight = 0;
				playerController->GetViewportSize(screenWidth, screenHeight);
								
				if (rotationMode) //Main Camera rotation calls
				{
					Orbit((mouseScreenLocationGrab.X - mouseLocation.X) / screenWidth);
					ChangePitch((mouseScreenLocationGrab.Y - mouseLocation.Y)*-1 / screenWidth);
				}
				else //  Mouse on screen edge pan
				{		
					const float xPanZone = screenWidth * ScreenEdgePanZonePercent / 100;
					const float yPanZone = screenHeight * ScreenEdgePanZonePercent / 100;
					
					if (mouseLocation.X < xPanZone)							PanRight((1 - mouseLocation.X / xPanZone) * -1);
					else if (mouseLocation.X > screenWidth - xPanZone)		PanRight(1 - (screenWidth - mouseLocation.X) / xPanZone);
					if (mouseLocation.Y < yPanZone)							PanForward(1 - mouseLocation.Y / yPanZone);
					else if (mouseLocation.Y > screenHeight - yPanZone)		PanForward((1 - (screenHeight - mouseLocation.Y) / yPanZone)*-1);
					
				}
				
							
			}
		}
	}	
}

void ARtsCameraDefaultPawn::ChangePitch(const float magnitude)
{
	if (magnitude != 0 && rotationMode && Controller)
		if (magnitude < 0 && GetControlRotation().Pitch < MaxPitch || magnitude > 0 && GetControlRotation().Pitch > MinPitch)
			AddControllerPitchInput(magnitude * PitchChangeRate * GetWorld()->GetDeltaSeconds());		
}

void ARtsCameraDefaultPawn::Yaw(const float magnitude)
{
	if (magnitude != 0 && rotationMode && Controller)
	{
		AddControllerYawInput(magnitude * YawRate *GetWorld()->GetDeltaSeconds());
	}		
			
}

void ARtsCameraDefaultPawn::Orbit(const float magnitude)
{
	if (magnitude != 0 && rotationMode && Controller)
	{
		APlayerController* playerController = Cast<APlayerController>(GetController());
		if (playerController != nullptr)
		{
			AddControllerYawInput(magnitude * YawRate *GetWorld()->GetDeltaSeconds());
			AddMovementInput(FRotationMatrix(GetControlRotation()).GetScaledAxis(EAxis::Y), magnitude * -(YawRate/4)* GetWorld()->GetDeltaSeconds());
		}
	}

}

void ARtsCameraDefaultPawn::PanForward(const float magnitude)
{
	if (magnitude != 0 && !rotationMode && Controller)
		AddMovementInput(FRotationMatrix(FRotator(0, GetControlRotation().Yaw, 0)).GetScaledAxis(EAxis::X), magnitude * 4000 * GetWorld()->GetDeltaSeconds());				
}

void ARtsCameraDefaultPawn::PanRight(const float magnitude)
{
	if (magnitude != 0  && !rotationMode && Controller)
		AddMovementInput(FRotationMatrix(GetControlRotation()).GetScaledAxis(EAxis::Y),magnitude * PanRate* GetWorld()->GetDeltaSeconds());
}

void ARtsCameraDefaultPawn::ZoomIn(const float magnitude)
{
	if (magnitude != 0 && !rotationMode && Controller)
		if (magnitude > 0 && GetActorLocation().Z > MinZoom || magnitude < 0 && GetActorLocation().Z < MaxZoom)
			AddMovementInput(FRotationMatrix(GetControlRotation()).GetScaledAxis(EAxis::X), magnitude * ZoomRate* GetWorld()->GetDeltaSeconds());	
}




void ARtsCameraDefaultPawn::EngageRotation()
{	
	if (Controller)
	{
		APlayerController* playerController = Cast<APlayerController>(GetController());
		if (playerController != nullptr)
		{				
			FVector2D mousePosition;
			if (playerController->GetMousePosition(mousePosition.X, mousePosition.Y))
			{
				mouseScreenLocationGrab = mousePosition;
				rotationMode = true;
			}
		}
	}
}

void ARtsCameraDefaultPawn::DisengageRotation()
{
	rotationMode = false;
}



