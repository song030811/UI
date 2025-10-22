#include "SpawnVolume.h"
#include "Components/BoxComponent.h"
#include "Engine/World.h"
#include "Kismet/KismetMathLibrary.h"

ASpawnVolume::ASpawnVolume()
{
    PrimaryActorTick.bCanEverTick = false;

    SpawnArea = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnArea"));
    RootComponent = SpawnArea;
}

void ASpawnVolume::BeginPlay()
{
    Super::BeginPlay();
}

FVector ASpawnVolume::GetRandomPointInVolume() const
{
    FVector Origin = SpawnArea->Bounds.Origin;
    FVector Extent = SpawnArea->Bounds.BoxExtent;
    return UKismetMathLibrary::RandomPointInBoundingBox(Origin, Extent);
}

AActor* ASpawnVolume::SpawnRandomItem()
{
    if (SpawnItems.Num() > 0)
    {
        int32 Index = FMath::RandRange(0, SpawnItems.Num() - 1);
        TSubclassOf<AActor> SpawnClass = SpawnItems[Index];

        if (SpawnClass)
        {
            FVector SpawnLocation = GetRandomPointInVolume();
            FRotator SpawnRotation = FRotator::ZeroRotator;
            FActorSpawnParameters Params;
            return GetWorld()->SpawnActor<AActor>(SpawnClass, SpawnLocation, SpawnRotation, Params);
        }
    }
    return nullptr;
}
