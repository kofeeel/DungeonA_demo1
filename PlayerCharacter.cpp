// 플레이어 캐릭터의 움직임을 구현합니다.
#include "PlayerCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"

// 기본 값을 설정합니다.
APlayerCharacter::APlayerCharacter()
{
    // 이 캐릭터가 매 프레임마다 Tick()을 호출하도록 설정합니다. 필요하지 않은 경우 이 기능을 끌 수 있습니다.
    PrimaryActorTick.bCanEverTick = true;

    // 카메라 붐 생성 및 설정
    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(RootComponent);
    CameraBoom->TargetArmLength = 300.0f; // 카메라가 캐릭터로부터 얼마나 떨어져 있는지 설정합니다.
    CameraBoom->bUsePawnControlRotation = true; // 카메라 붐이 컨트롤러에 의해 회전되도록 설정합니다.

    // 따라다니는 카메라 생성 및 설정
    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // 카메라를 붐 끝에 부착합니다.
    FollowCamera->bUsePawnControlRotation = false; // 카메라가 붐의 회전을 따르지 않도록 설정합니다.

    // 카메라 회전 속도 설정
    BaseTurnRate = 45.f;
    BaseLookUpRate = 45.f;

    // 캐릭터 이동 속도 및 설정
    GetCharacterMovement()->bOrientRotationToMovement = true; // 캐릭터가 이동 방향으로 회전하도록 설정합니다.
    GetCharacterMovement()->RotationRate = FRotator(0.f, 540.f, 0.f);
    GetCharacterMovement()->JumpZVelocity = 600.f;
    GetCharacterMovement()->AirControl = 0.2f;

    // 입력 액션들 생성
    MoveForwardAction = CreateDefaultSubobject<UInputAction>(TEXT("MoveForwardAction"));
    MoveRightAction = CreateDefaultSubobject<UInputAction>(TEXT("MoveRightAction"));
    TurnAction = CreateDefaultSubobject<UInputAction>(TEXT("TurnAction"));
    LookUpAction = CreateDefaultSubobject<UInputAction>(TEXT("LookUpAction"));

    // 입력 매핑 컨텍스트 생성
    DefaultMappingContext = CreateDefaultSubobject<UInputMappingContext>(TEXT("DefaultMappingContext"));
}

// 게임이 시작되거나 캐릭터가 스폰될 때 호출됩니다.
void APlayerCharacter::BeginPlay()
{
    Super::BeginPlay();

    if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
    {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
        {
            Subsystem->AddMappingContext(DefaultMappingContext, 1);
        }
    }
}

// 매 프레임마다 호출됩니다.
void APlayerCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// 입력 기능을 바인딩합니다.
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        EnhancedInputComponent->BindAction(MoveForwardAction, ETriggerEvent::Triggered, this, &APlayerCharacter::MoveForward);
        EnhancedInputComponent->BindAction(MoveRightAction, ETriggerEvent::Triggered, this, &APlayerCharacter::MoveRight);
        EnhancedInputComponent->BindAction(TurnAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Turn);
        EnhancedInputComponent->BindAction(LookUpAction, ETriggerEvent::Triggered, this, &APlayerCharacter::LookUp);
    }
}

// 앞으로 이동
void APlayerCharacter::MoveForward(const FInputActionValue& Value)
{
    const float AxisValue = Value.Get<float>();
    if (Controller && AxisValue != 0.0f)
    {
        // 컨트롤러의 회전에서 전방 벡터를 얻습니다.
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);

        // 전방 벡터 생성
        const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
        AddMovementInput(Direction, AxisValue);
    }
}

// 오른쪽으로 이동
void APlayerCharacter::MoveRight(const FInputActionValue& Value)
{
    const float AxisValue = Value.Get<float>();
    if (Controller && AxisValue != 0.0f)
    {
        // 컨트롤러의 회전에서 오른쪽 벡터를 얻습니다.
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);

        // 오른쪽 벡터 생성
        const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
        AddMovementInput(Direction, AxisValue);
    }
}

// 카메라 회전 속도
void APlayerCharacter::Turn(const FInputActionValue& Value)
{
    const float AxisValue = Value.Get<float>();
    AddControllerYawInput(AxisValue * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

// 위쪽으로 카메라 회전 속도
void APlayerCharacter::LookUp(const FInputActionValue& Value)
{
    const float AxisValue = Value.Get<float>();
    AddControllerPitchInput(AxisValue * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}
