// 플레이어 캐릭터 클래스의 헤더 파일입니다.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnhancedInputComponent.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class DUNGEONA_DEMO1_API APlayerCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    // 캐릭터의 기본 값을 설정합니다.
    APlayerCharacter();

protected:
    // 게임이 시작되거나 캐릭터가 스폰될 때 호출됩니다.
    virtual void BeginPlay() override;

public:    
    // 매 프레임마다 호출됩니다.
    virtual void Tick(float DeltaTime) override;

    // 입력 기능을 바인딩합니다.
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
    // 이동 입력 처리 함수
    void MoveForward(const FInputActionValue& Value);
    void MoveRight(const FInputActionValue& Value);

    // 카메라 회전 입력 처리 함수
    void Turn(const FInputActionValue& Value);
    void LookUp(const FInputActionValue& Value);

    // 카메라 회전 속도
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera, meta = (AllowPrivateAccess = "true"))
    float BaseTurnRate;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera, meta = (AllowPrivateAccess = "true"))
    float BaseLookUpRate;

    // 카메라 붐 컴포넌트
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
    class USpringArmComponent* CameraBoom;

    // 따라다니는 카메라 컴포넌트
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
    class UCameraComponent* FollowCamera;

    // 입력 액션들
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    class UInputAction* MoveForwardAction;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    class UInputAction* MoveRightAction;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    class UInputAction* TurnAction;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    class UInputAction* LookUpAction;

    // 입력 매핑 컨텍스트
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    class UInputMappingContext* DefaultMappingContext;
};