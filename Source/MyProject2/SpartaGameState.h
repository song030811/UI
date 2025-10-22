#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "SpartaGameState.generated.h"

UCLASS()
class MYPROJECT2_API ASpartaGameState : public AGameStateBase
{
    GENERATED_BODY()

public:
    ASpartaGameState();

protected:
    virtual void BeginPlay() override;

private:
    void StartWave();
    void OnWaveTimeUp();

private:
    FTimerHandle WaveTimerHandle;
    int32 CurrentWaveIndex;
    int32 MaxWaves;
    float WaveDuration;

    TArray<int32> ItemsToSpawnPerWave;
    TArray<AActor*> CurrentWaveItems;
};
