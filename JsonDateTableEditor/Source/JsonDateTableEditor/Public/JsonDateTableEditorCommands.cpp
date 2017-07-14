// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "JsonDateTableEditor.h"
#include "JsonDateTableEditorCommands.h"

#define LOCTEXT_NAMESPACE "FJsonDateTableEditorModule"

void FJsonDateTableEditorCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "JsonDateTable", "Bring up JsonDateTableEditor window", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
