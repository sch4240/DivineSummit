// Fill out your copyright notice in the Description page of Project Settings.


#include "DBaseAIController.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "DivineSummit/Characters/DGodCharacter.h"
#include "DivineSummit/Characters/DHeroCharacter.h"

void ADBaseAIController::MoveToPoint(int x, int y)
{
	MoveToLocation(grid[x][y]);
}


void ADBaseAIController::BeginPlay()
{
    Super::BeginPlay();
    navMesh = Cast<AVolume>(UGameplayStatics::GetActorOfClass(GetWorld(), AVolume::StaticClass()));

    if (navMesh)
    {
        auto box = navMesh->GetBounds().GetBox();
        box.GetCenterAndExtents(center, extent);
        UE_LOG(LogTemp, Warning, L"Box Info %s", *(box.ToString()));
        UE_LOG(LogTemp, Warning, L"Box Center %s", *(center.ToString()));
        UE_LOG(LogTemp, Warning, L"Box Extent %s", *(extent.ToString()));
        point = UKismetMathLibrary::RandomPointInBoundingBox(center, extent);

        Start = box.Min;
        End = box.Max;
        x_step = extent.X * 2 / n_rows;
        y_step = extent.Y * 2 / n_cols;

        for (int i = 0; i < n_rows; i++)
        {
            for (int j = 0; j < n_cols; j++)
            {
                grid[i][j] = Start + FVector(j * x_step, i * y_step, 150);
                UKismetSystemLibrary::DrawDebugPoint(this, grid[i][j], 10, FLinearColor::Red, INFINITY);
            }
        }
    }
    GodPawn = Cast<ADGodCharacter>(UGameplayStatics::GetActorOfClass(GetWorld(), ADGodCharacter::StaticClass()));
    PlayerPawn = Cast<ADHeroCharacter>(UGameplayStatics::GetActorOfClass(GetWorld(), ADHeroCharacter::StaticClass()));

}