// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayableSong.h"

#include <fstream>
#include <sstream>

UPlayableSong::UPlayableSong()
{
}

UPlayableSong::~UPlayableSong()
{
}

void UPlayableSong::Initialize(const FString FilePath, bool& Success)
{
	UPlayableSongChart* Chart = NULL;
	std::string Line;
	FString FilePathConverted = FPaths::ProjectContentDir() + "/" + FilePath;
	std::ifstream File(std::string(TCHAR_TO_UTF8(*FilePathConverted)));
	if (!File) {
		Success = false;
		return;
	}
	while (std::getline(File, Line)) {
		if (Line.starts_with("#NOTEDATA:;")) {
			if (Chart) {
				Charts.Add(Chart);
			}
			Chart = NewObject<UPlayableSongChart>();
		}
		if (Chart) {
			if (Line.starts_with("#DESCRIPTION:")) {
				Chart->Description = Line.substr(13, Line.find(';') - 13).c_str();
			}
			else if (Line.starts_with("#METER:")) {
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
	Success = true;
}