// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "ChartStepType.generated.h"

UENUM(BlueprintType)
enum class EChartStepType : uint8 {
	NONE UMETA(DisplayName = "None"),
	TAP UMETA(DisplayName = "Tap"),
	HOLD UMETA(DisplayName = "Hold Head"),
	END UMETA(DisplayName = "Hold/Roll End"),
	ROLL UMETA(DisplayName = "Roll Head"),
	HOLD_BODY UMETA(DisplayName = "Hold Body"),
	ROLL_BODY UMETA(DisplayName = "Roll Body")
};
