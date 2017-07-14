// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "SlateBasics.h"
#include "JsonDateTableEditorStyle.h"

class FJsonDateTableEditorCommands : public TCommands<FJsonDateTableEditorCommands>
{
public:

	FJsonDateTableEditorCommands()
		: TCommands<FJsonDateTableEditorCommands>(TEXT("JsonDateTableEditor"), NSLOCTEXT("Contexts", "JsonDateTableEditor", "JsonDateTableEditor Plugin"), NAME_None, FJsonDateTableEditorStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};