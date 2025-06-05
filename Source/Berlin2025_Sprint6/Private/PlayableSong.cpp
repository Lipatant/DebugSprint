// Fill out your copyright notice in the Description page of Project Settings.

#include <fstream>
#include <sstream>

#include "PlayableSong.h"

UPlayableSong::UPlayableSong()
{
}

UPlayableSong::~UPlayableSong()
{
}

void UPlayableSong::Initialize(const FString FilePath)
{
	std::ifstream File(std::string(TCHAR_TO_UTF8(*FilePath)));
	std::string Line;
	UPlayableSongChart* Chart = NULL;
	while (std::getline(File, Line)) {
		if (Line.starts_with("#NOTEDATA:;")) {
			if (Chart) {
				Charts.Add(Chart);
			}
			Chart = NewObject<UPlayableSongChart>();
		}
		if (Chart) {
			if (Line.starts_with("#METER:")) {
				Chart->Meter = std::stoi(Line.substr(7, Line.find(';') - 7));
			}
			else if (Line.starts_with("#STEPSTYPE:")) {
				Chart->StepStype = Line.substr(11, Line.find(';') - 11).c_str();
			}
		}
	}
	if (Chart) {
		Charts.Add(Chart);
	}
	File.close();
}