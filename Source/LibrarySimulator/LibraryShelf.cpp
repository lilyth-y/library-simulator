#include "LibraryShelf.h"
#include "LibraryBook.h"

ALibraryShelf::ALibraryShelf()
{
    PrimaryActorTick.bCanEverTick = false;

    ShelfMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShelfMesh"));
    RootComponent = ShelfMesh;

    PlacementTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("PlacementTrigger"));
    PlacementTrigger->SetupAttachment(RootComponent);
    PlacementTrigger->SetBoxExtent(FVector(50.f, 200.f, 50.f));
    
    ShelfCategoryID = 0;
    CategoryRange = 100.0f;
}

void ALibraryShelf::BeginPlay()
{
    Super::BeginPlay();
    PlacementTrigger->OnComponentBeginOverlap.AddDynamic(this, &ALibraryShelf::OnBookPlaced);
}

void ALibraryShelf::OnBookPlaced(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    ALibraryBook* Book = Cast<ALibraryBook>(OtherActor);
    if (!Book) return;

    if (Book->BookData.bIsBeingCarried)
    {
        return;
    }

    // Logic: Calculate Score
    // e.g., If Book Category is 150 and Shelf is 100 (Range 100), Match!
    
    const float BookCat = Book->BookData.CategoryID;
    const bool bMatch = (BookCat >= ShelfCategoryID) && (BookCat < ShelfCategoryID + CategoryRange);

    if (bMatch)
    {
        UE_LOG(LogTemp, Log, TEXT("SCORE! Book %s placed correctly on Shelf %.1f."), *Book->BookData.Title, ShelfCategoryID);
        Book->BookData.bIsBeingRelocated = false;
        // TODO: Add to Global Score Manager
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("WRONG SHELF! Book %s (%.1f) does not belong on Shelf %.1f."), *Book->BookData.Title, BookCat, ShelfCategoryID);
        // TODO: Play Error Sound / Decrease Reputation
    }

    OnShelfPlacementEvaluated(Book, bMatch);
}
