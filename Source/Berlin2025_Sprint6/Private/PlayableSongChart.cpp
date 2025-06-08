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

void UPlayableSongChart::ResetSteps()
{
    Steps.Reset();
    Steps.Empty();
    Steps.Shrink();
}
