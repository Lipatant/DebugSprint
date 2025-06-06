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

bool UPlayableSong::Initialize(const FString &FilePath)
{
	UPlayableSongChart* Chart = NULL;
	std::string Line;
	FString FilePathConverted = FPaths::ProjectContentDir() + "/" + FilePath;
	std::ifstream File(TCHAR_TO_UTF8(*FilePathConverted));
	if (!File.is_open()) {
		return false;
	}
	while (std::getline(File, Line)) {
		if (Line.starts_with("#NOTEDATA:;")) {
			if (Chart) {
				Charts.Add(Chart);
			}
			Chart = NewObject<UPlayableSongChart>(this);
		}
		if (Chart) {
			if (Line.starts_with("#DESCRIPTION:")) {
				Chart->Description = UTF8_TO_TCHAR(Line.substr(13, Line.find(';') - 13).c_str());
			}
			else if (Line.starts_with("#METER:")) {
				Chart->Meter = std::stoi(Line.substr(7, Line.find(';') - 7));
			}
			else if (Line.starts_with("#STEPSTYPE:")) {
				Chart->StepStype = UTF8_TO_TCHAR(Line.substr(11, Line.find(';') - 11).c_str());
			}
		}
	}
	if (Chart) {
		Charts.Add(Chart);
	}
	File.close();
	return true;
}