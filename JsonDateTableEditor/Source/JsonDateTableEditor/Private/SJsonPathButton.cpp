#include "JsonDateTableEditor.h"
#include "SJsonPathButton.h"
//#include "IDesktopPlatform.h"

#define  LOCTEXT_NAMESPACE "SJsonPathButton"

void SJsonPathButton::Construct(const FArguments& InArgs)
{
	FString InString = InArgs._InText.Get();
	this->ChildSlot
	[
		/*SNew(SVerticalBox)
		+SVerticalBox::Slot()
			[
				SNew(SButton)
			]
		+SVerticalBox::Slot()
			[
				SNew(SHorizontalBox)
				+SHorizontalBox::Slot()
					[
						SNew(SButton)
					]
				+SHorizontalBox::Slot()
					[
						SNew(SButton)
					]
				+ SHorizontalBox::Slot()
					[
						SNew(SButton)
					]
			]*/
		SNew(SButton).OnClicked(this, &SJsonPathButton::OnFindPathButtonClicked)
	];
}

FReply SJsonPathButton::OnFindPathButtonClicked()
{
//	UE_LOG(Log, Warning, TEXT("按钮被点击了"));

	FString path = FPaths::GameContentDir();
	FPlatformProcess::ExploreFolder(*path);

	//IDesktopPlatform* DesktopPlatform = FDesktopPlatformModule::Get();
	//if (DesktopPlatform)
	//{
	//	FString FolderName;
	//	const FString Title = NSLOCTEXT("UnrealEd", "ChooseADirectory", "Choose A Directory").ToString();
	//	const bool bFolderSelected = DesktopPlatform->OpenDirectoryDialog(
	//		FSlateApplication::Get().FindBestParentWindowHandleForDialogs(nullptr),
	//		Title,
	//		path,
	//		FolderName
	//	);
	//}

	return FReply::Handled();
}

#undef   LOCTEXT_NAMESPACE