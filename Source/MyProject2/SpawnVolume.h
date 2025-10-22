#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnVolume.generated.h"

UCLASS()
class MYPROJECT2_API ASpawnVolume : public AActor
{
    GENERATED_BODY()

public:
    ASpawnVolume();

protected:
    virtual void BeginPlay() override;

public:
    UFUNCTION(BlueprintCallable, Category = "Spawning")
    AActor* SpawnRandomItem();

    UPROPERTY(EditAnywhere, Category = "Spawning")
    TArray<TSubclassOf<AActor>> SpawnItems;

    UPROPERTY(VisibleAnywhere, Category = "Spawning")
    class UBoxComponent* SpawnArea;

private:
    FVector GetRandomPointInVolume() const;
};
