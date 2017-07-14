#include "JsonDateTableEditor.h"
#include "Kismet/KismetStringLibrary.h"
#include "NotificationManager.h"
#include "SNotificationList.h"
#include "DesktopPlatformModule.h"
#include "Framework/Application/SlateApplication.h"
#include "JsonListWidget.h"

#define LOCTEXT_NAMESPACE "SJsonFilePathPicker"

void NotificationHandleMsg(FString Path);

void SJsonListWidget::Construct(const FArguments& Args)
{
	FString InString = Args._InText.Get();

	PluginDirectory = FPaths::GamePluginsDir();

	JsonPathDelegate.BindRaw(this, &SJsonListWidget::HandleJsonContent);

	JsonContentConvertDelegate.BindRaw(this, &SJsonListWidget::HandleJsonConvert);

	this->ChildSlot
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot().HAlign(HAlign_Left).VAlign(VAlign_Fill).FillWidth(1.0)
			[
				SNew(SBox)
				[
					SNew(SVerticalBox)
					+SVerticalBox::Slot().HAlign(HAlign_Center).VAlign(VAlign_Top).Padding(0,0,10,0).AutoHeight()
					[
						SNew(SButton)
						.OnClicked(this, &SJsonListWidget::ImportJsonContenButtonClick)
						[
							SNew(STextBlock)
							.Text(ImporJsonText)
						]
					]
					+SVerticalBox::Slot().HAlign(HAlign_Fill).VAlign(VAlign_Fill).FillHeight(1.0)
						[
							SNew(SScrollBox)
							+SScrollBox::Slot()
							[
								SAssignNew(ImportJsonTextBlock, STextBlock)
								.Text(JsonContentText)
							]
						]
				]
			]
			+ SHorizontalBox::Slot().Padding(10, 0,10,0).HAlign(HAlign_Center).VAlign(VAlign_Center).AutoWidth()
				[
					SNew(SButton)
					.OnClicked(this, &SJsonListWidget::ConvertKBEToUE4JsonClick)
					[
						SNew(STextBlock).Text(ConvertJsonText)
					]
				]
			+SHorizontalBox::Slot().HAlign(HAlign_Right).VAlign(VAlign_Fill).FillWidth(1.0)
				[
					SNew(SVerticalBox)
					+SVerticalBox::Slot().Padding(0,0,10,0).HAlign(HAlign_Center).VAlign(VAlign_Top).AutoHeight()
					[
						SNew(SButton)
						.OnClicked(this, &SJsonListWidget::SaveUE4JsonClick)
						[
							SNew(STextBlock).Text(SaveUE4JsonText)
						]
					]
					+ SVerticalBox::Slot().HAlign(HAlign_Fill).VAlign(VAlign_Fill).FillHeight(1.0)
					[
						SNew(SScrollBox)
						+ SScrollBox::Slot()
						[
							SAssignNew(SaveUE4JsonTextBlock, STextBlock).Text(JsonContentText)
						]
					]
				]
		];

}

void SJsonListWidget::HandleJsonContent(FString content)
{
	LoadContent = content;
	FString Msg = "json";
	JsonContentText = FText::FromString(content);
	ImportJsonTextBlock->SetText(JsonContentText);
	UE_LOG(LogKBEJson, Log, TEXT("Import json conent is load!------%s"), *Msg);
}

void SJsonListWidget::HandleJsonConvert()
{
	{
		FString resultJson;

		TArray<FString> result;

		result = SplitStringToArray(LoadContent, "\": {"); //字符串内双引号，“\"”
		FString str1 = result[0];
		int32 index = str1.Find("\"", ESearchCase::IgnoreCase, ESearchDir::FromEnd, str1.Len()); //找到最右侧 “ 下标
		FString keyStr = UKismetStringLibrary::GetSubstring(str1, index + 1, str1.Len() - 1); //获得了Key

		str1.RemoveAt(index, str1.Len() - index);

		TArray<FString> KeyArray;
		KeyArray.Add(keyStr);
		resultJson.Append(str1);

		for (int i = 1; i < result.Num() - 1; i++)
		{
			FString temp = result[i];
			int32 index1 = temp.Find("\"", ESearchCase::IgnoreCase, ESearchDir::FromEnd, temp.Len()); //找到最右侧 “ 下标
			FString keyStr1 = UKismetStringLibrary::GetSubstring(temp, index1 + 1, temp.Len() - 1); //获得了Key
			temp.RemoveAt(index1, temp.Len() - index1);
			FString tempPre = "{\n\t\"Name\": \"" + KeyArray[i - 1] + "\"" + ",";
			KeyArray.Add(keyStr1);
			tempPre = tempPre.Append(temp);
			resultJson.Append(tempPre);
		}
		FString tempNext = "{\n\t\"Name\": \"" + KeyArray[KeyArray.Num() - 1] + "\"" + ",";
		resultJson.Append(tempNext);
		resultJson.Append(result[result.Num() - 1]);

		resultJson.RemoveAt(0);
		resultJson = "[" + resultJson;
		resultJson.RemoveAt(resultJson.Len() - 1);
		resultJson.Append("]");

		FString resultJson2;
		//处理[ ]  == { }
		{
			TArray<FString> result2;
			result2 = SplitStringToArray(resultJson, ": [");

			for (int j = 0;j < result2.Num();j++)
			{

				int32 indextemp = result2[j].Find("],", ESearchCase::IgnoreCase, ESearchDir::FromEnd, result2[j].Len());
				if (indextemp < 0 || indextemp > result2[j].Len() - 1)
				{
					resultJson2.Append(result2[j]);
					continue;
				}
				FString keytempStr = UKismetStringLibrary::GetSubstring(result2[j], 0, indextemp);
				TArray<FString> vecStr = SplitStringToArray(keytempStr, ",");
				if (vecStr.Num() > 0)
				{
					FString tempvecx = "\"x\":" + vecStr[0];
					FString tempvecy = "\"y\":" + vecStr[1];
					FString tempvecz = "\"z\":" + vecStr[2];

					FString all = ":{" + tempvecx + "," + tempvecy + "," + tempvecz + "},"; //{"X": 0,"Y": 0,"Z": 0},

					result2[j].RemoveAt(0, indextemp + 2);
					result2[j] = all + result2[j];
					resultJson2.Append(result2[j]);
				}
			}
		}
		ConvertContent = resultJson2;
		SaveUE4JsonTextBlock->SetText(FText::FromString(ConvertContent));
		isConvert = true;
	}
}

FReply SJsonListWidget::ImportJsonContenButtonClick() const
{
	const FString Msg = "test----";
	UE_LOG(LogKBEJson, Log, TEXT("Import json button is click!------%s"), *Msg);

	IDesktopPlatform* DesktopPlatform = FDesktopPlatformModule::Get();
	if (DesktopPlatform == nullptr)
	{
		return FReply::Handled();
	}

	const FString DefalutPath = PluginDirectory.IsEmpty() ? FPaths::GamePluginsDir() : PluginDirectory;

	TSharedPtr<SWindow> ParentWindow = FSlateApplication::Get().FindWidgetWindow(AsShared());

	void* ParentWindowHandle = (ParentWindow.IsValid() && ParentWindow->GetNativeWindow().IsValid())
		? ParentWindow->GetNativeWindow()->GetOSWindowHandle() : nullptr;

	TArray<FString> OutFiles;
	
	FText tempBrowseTitle = FText::FromString("File picker...");

	FString meta = "json";

	FString FileTypeFilter = FString::Printf(TEXT("%s files (*.%s)"), *meta, *meta);

	FString tt;

	if (DesktopPlatform->OpenFileDialog(ParentWindowHandle, tempBrowseTitle.ToString(), DefalutPath, TEXT(""), FileTypeFilter, EFileDialogFlags::None, OutFiles))
	{
		FString FilePath = OutFiles[0];
		if (FFileHelper::LoadFileToString(tt, *FilePath))
		{
			JsonPathDelegate.ExecuteIfBound(tt);
			NotificationHandleMsg(FilePath);
		}
	}
	return FReply::Handled();
}

FReply SJsonListWidget::ConvertKBEToUE4JsonClick() const
{
	JsonContentConvertDelegate.ExecuteIfBound();
	NotificationHandleMsg(PluginDirectory);
	const FString Msg = "test----";
	UE_LOG(LogKBEJson, Log, TEXT("convert kbe json button is click!------%s"), *Msg);
	return FReply::Handled();
}

FReply SJsonListWidget::SaveUE4JsonClick() const
{
	const FString Msg = "test----";
	UE_LOG(LogKBEJson, Log, TEXT("save ue4 json button is click!------%s"), *Msg);

	IDesktopPlatform* DesktopPlatform = FDesktopPlatformModule::Get();
	if (DesktopPlatform == nullptr)
	{
		return FReply::Handled();
	}

	const FString DefalutPath = PluginDirectory.IsEmpty() ? FPaths::GamePluginsDir() : PluginDirectory;

	TSharedPtr<SWindow> ParentWindow = FSlateApplication::Get().FindWidgetWindow(AsShared());

	void* ParentWindowHandle = (ParentWindow.IsValid() && ParentWindow->GetNativeWindow().IsValid())
		? ParentWindow->GetNativeWindow()->GetOSWindowHandle() : nullptr;

	TArray<FString> OutFiles;

	FText tempBrowseTitle = FText::FromString("File save...");

	FString meta = "json";

	FString FileTypeFilter = FString::Printf(TEXT("%s files (*.%s)"), *meta, *meta);

	if (DesktopPlatform->SaveFileDialog(ParentWindowHandle, tempBrowseTitle.ToString(), DefalutPath, TEXT(""), FileTypeFilter, EFileDialogFlags::None, OutFiles))
	{
		FString FilePath = OutFiles[0];
		if (FilePath.Contains("."))
		{
			int32 index = FilePath.Find(".", ESearchCase::IgnoreCase, ESearchDir::FromEnd, FilePath.Len());
			FilePath.RemoveAt(index, FilePath.Len() - index);
		}
		FilePath += ".json";
		FFileHelper::SaveStringToFile(ConvertContent, *FilePath, FFileHelper::EEncodingOptions::Type::ForceUTF8);
		UE_LOG(LogKBEJson, Log, TEXT("save ue4 json  is ok!------%s"), *FilePath);
		NotificationHandleMsg(FilePath);
	}

	return FReply::Handled();
}

void NotificationHandleMsg(FString Path)
{
	auto Message = NSLOCTEXT("UnrealEnditor", "JsonDataTableEditor", "JsonDataTableEditor Convert!!");
	FNotificationInfo Info(Message);
	Info.bFireAndForget = true;
	Info.ExpireDuration = 5.0f;
	Info.bUseSuccessFailIcons = false;
	Info.bUseLargeFont = false;

	const FString HyperLinkText = FPaths::ConvertRelativePathToFull(Path);
	Info.Hyperlink = FSimpleDelegate::CreateStatic([](FString SourceFilePath)
	{
		FPlatformProcess::ExploreFolder(*(FPaths::GetPath(SourceFilePath)));
	}, HyperLinkText);
	Info.HyperlinkText = FText::FromString(HyperLinkText);
	FSlateNotificationManager::Get().AddNotification(Info);
}

TArray<FString> SJsonListWidget::SplitStringToArray(FString SRC, FString Arg)
{
	TArray<FString> result;
	if (SRC.Contains(Arg, ESearchCase::CaseSensitive))
	{
		FString leftStr;
		FString rightStr;
		SRC.Split(Arg, &leftStr, &rightStr, ESearchCase::CaseSensitive);
		if (leftStr.Len() > 0)
		{
			result.Add(leftStr);
		}
		result.Append(SplitStringToArray(rightStr, Arg));
		return result;
	}
	else {
		if (SRC.Len() > 0)
		{
			result.Add(SRC);
		}
		return result;
	}
}

#undef LOCTEXT_NAMESPACE