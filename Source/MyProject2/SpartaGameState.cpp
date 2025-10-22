#include "SpartaGameState.h"
#include "SpawnVolume.h"
#include "Engine/World.h"
#include "Engine/Engine.h"
#include "TimerManager.h"
#include "EngineUtils.h"

ASpartaGameState::ASpartaGameState()
{
    CurrentWaveIndex = 0;
    MaxWaves = 3;
    WaveDuration = 10.0f;
    ItemsToSpawnPerWave = { 10, 15, 20 };
}

void ASpartaGameState::BeginPlay()
{
    Super::BeginPlay();
    StartWave();
}

void ASpartaGameState::StartWave()
{
    for (AActor* Item : CurrentWaveItems)
    {
        if (Item && Item->IsValidLowLevelFast())
        {
            Item->Destroy();
        }
    }
    CurrentWaveItems.Empty();

    FString Msg = FString::Printf(TEXT("Wave %d 시작!"), CurrentWaveIndex + 1);
    UE_LOG(LogTemp, Warning, TEXT("%s"), *Msg);

    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Yellow, Msg);
    }

    int32 ItemCount = ItemsToSpawnPerWave.IsValidIndex(CurrentWaveIndex)
        ? ItemsToSpawnPerWave[CurrentWaveIndex]
        : 10;

    ASpawnVolume* SpawnVolume = nullptr;
    for (TActorIterator<ASpawnVolume> It(GetWorld()); It; ++It)
    {
        SpawnVolume = *It;
        break;
    }

    if (SpawnVolume)
    {
        for (int32 i = 0; i < ItemCount; ++i)
        {
            if (AActor* Spawned = SpawnVolume->SpawnRandomItem())
            {
                CurrentWaveItems.Add(Spawned);
            }
        }
    }

    GetWorldTimerManager().SetTimer(
        WaveTimerHandle,
        this,
        &ASpartaGameState::OnWaveTimeUp,
        WaveDuration,
        false
    );
}

void ASpartaGameState::OnWaveTimeUp()
{
    CurrentWaveIndex++;

    if (CurrentWaveIndex < MaxWaves)
    {
        StartWave();
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("모든 웨이브 종료!"));
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("모든 웨이브 완료!"));
        }
    }
}