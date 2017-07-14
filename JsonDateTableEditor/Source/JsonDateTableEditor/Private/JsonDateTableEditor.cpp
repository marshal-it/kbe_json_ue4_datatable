// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "JsonDateTableEditor.h"

#include "SlateBasics.h"
#include "SlateExtras.h"

#include "JsonListWidget.h"
#include "SJsonPathButton.h"

#include "JsonDateTableEditorStyle.h"
#include "JsonDateTableEditorCommands.h"

#include "LevelEditor.h"

DEFINE_LOG_CATEGORY(LogKBEJson);

static const FName JsonDateTableEditorTabName("JsonDateTableEditor");

#define LOCTEXT_NAMESPACE "FJsonDateTableEditorModule"

void FJsonDateTableEditorModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FJsonDateTableEditorStyle::Initialize();
	FJsonDateTableEditorStyle::ReloadTextures();

	FJsonDateTableEditorCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FJsonDateTableEditorCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FJsonDateTableEditorModule::PluginButtonClicked),
		FCanExecuteAction());
		
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	
	{
		TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());
		MenuExtender->AddMenuExtension("WindowLayout", EExtensionHook::After, PluginCommands, FMenuExtensionDelegate::CreateRaw(this, &FJsonDateTableEditorModule::AddMenuExtension));

		LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
	}
	
	{
		TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);
		ToolbarExtender->AddToolBarExtension("Settings", EExtensionHook::After, PluginCommands, FToolBarExtensionDelegate::CreateRaw(this, &FJsonDateTableEditorModule::AddToolbarExtension));
		
		LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
	}
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(JsonDateTableEditorTabName, FOnSpawnTab::CreateRaw(this, &FJsonDateTableEditorModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FJsonDateTableEditorTabTitle", "JsonDateTableEditor"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FJsonDateTableEditorModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	FJsonDateTableEditorStyle::Shutdown();

	FJsonDateTableEditorCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(JsonDateTableEditorTabName);
}

TSharedRef<SDockTab> FJsonDateTableEditorModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{

	//FText WidgetText = FText::Format(
	//	LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
	//	FText::FromString(TEXT("FJsonDateTableEditorModule::OnSpawnPluginTab")),
	//	FText::FromString(TEXT("JsonDateTableEditor.cpp"))
	//	);

	//return SNew(SDockTab)
	//	.TabRole(ETabRole::NomadTab)
	//	[
	//		// Put your tab content here!
	//		SNew(SBox)
	//		.HAlign(HAlign_Center)
	//		.VAlign(VAlign_Center)
	//		[
	//			SNew(STextBlock)
	//			.Text(WidgetText)
	//		]
	//	];

	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			SNew(SJsonListWidget).InText(FString("Hello Slate"))
		];
}

void FJsonDateTableEditorModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->InvokeTab(JsonDateTableEditorTabName);
}

void FJsonDateTableEditorModule::AddMenuExtension(FMenuBuilder& Builder)
{
	Builder.AddMenuEntry(FJsonDateTableEditorCommands::Get().OpenPluginWindow);
}

void FJsonDateTableEditorModule::AddToolbarExtension(FToolBarBuilder& Builder)
{
	Builder.AddToolBarButton(FJsonDateTableEditorCommands::Get().OpenPluginWindow);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FJsonDateTableEditorModule, JsonDateTableEditor)