// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayableSongChart.h"

UPlayableSongChart::UPlayableSongChart()
{
    Steps.Reset();
    Steps.Empty();
    Steps.Shrink();
}

UPlayableSongChart::~UPlayableSongChart()
{
}

float UPlayableSongChart::GetDeltaFromBeat(float const Beat)
{
    if (BPMChanges.Num() == 0)
    {
        return Offset;
    }

    float Delta = Offset;
    float CurrentBPM = BPMChanges[0].BPM;
    float CurrentBeat = 0.0f;

    for (int i = 1; i < BPMChanges.Num(); i++)
    {
        const FBPMChange &Next = BPMChanges[i];
        if (Next.Beat > Beat) {
            break;
        }

        Delta += (60.0f / CurrentBPM) * (Next.Beat - CurrentBeat);
        CurrentBPM = Next.BPM;
        CurrentBeat = Next.Beat;
    }

    Delta += (60.0f / CurrentBPM) * (Beat - CurrentBeat);
    return Delta;
}

int32 UPlayableSongChart::ParseAndAddBPM(FString const &Data)
{
    TArray<FString> DataList;
    Data.ParseIntoArray(DataList, TEXT(",;"), true);
    for (const FString& BPMChangeData : DataList)
    {
        FString BeatData;
        FString BPMData;
        if (BPMChangeData.Split("=", &BeatData, &BPMData))
        {
            BPMChanges.Add({ FCString::Atof(*BeatData), FCString::Atof(*BPMData) });
        }
    }
    if (DataList.Num() > 0) {
        BPMChanges.Sort([](const FBPMChange& A, const FBPMChange& B) {
            return A.Beat < B.Beat;
        });
    }
    return DataList.Num();
}

void UPlayableSongChart::ResetSteps()
{
    Steps.Reset();
    Steps.Empty();
    Steps.Shrink();
}
