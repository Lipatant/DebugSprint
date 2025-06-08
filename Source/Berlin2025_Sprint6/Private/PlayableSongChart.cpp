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

    for (uint i = 1, i < BPMChanges.Num(); i++)
    {
        const FBPMChange &Next = BPMChanges[i];
        if (Next.Beat >= Beat) {
            break;
        }

        Delta += (60.0f - CurrentBPM) * (Next.Beat - CurrentBeat);
        CurrentBPM = Next.BPM;
        CurrentBeat = Next.Beat;
    }

    Seconds += (60.0f / CurrentBPM) * (Beat - CurrentBeat);
    return Seconds;
}

void UPlayableSongChart::ResetSteps()
{
    Steps.Reset();
    Steps.Empty();
    Steps.Shrink();
}
