#pragma once
#include "SlateBasics.h"

DECLARE_DELEGATE_OneParam(FLoadJsonPathDelegate, FString);
DECLARE_DELEGATE(FConvertJsonContent);

class SJsonListWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SJsonListWidget) {}
	SLATE_ATTRIBUTE(FString, InText)
	SLATE_END_ARGS()

	void Construct(const FArguments& Args);

	FLoadJsonPathDelegate JsonPathDelegate;

	FConvertJsonContent JsonContentConvertDelegate;

	void HandleJsonContent(FString content);

	void HandleJsonConvert();

	FText ImporJsonText= FText::FromString("ImportKBEJson");

	FText SaveUE4JsonText = FText::FromString("SaveUE4Json");

	FText ConvertJsonText = FText::FromString("ConvertJson");

	FText JsonContentText = FText::FromString("\
		Winter grandpa left with the north, voice carrying a basket of flowers is coming!\n \
		The river stood a long braid of willow sister, on their long braid small rope full of promise.\n\
		There was a tree bent over, can't wait to want to wash and dress her beautiful long tails. \
		The photo under the peach tree, play.Peach sister is so happy, so he built a prank, \n \
		and handfuls of peach blossom petals, like a petal of rain.Petals fall on the grass, \n \
		the grass becomes red and green carpet of flowers.Petals fall on the kid's head, \n\
		face, clothing, children becomes a flower child. \
		Two busy honey bee was suddenly the petals rain frighten panic, had to hide in the blossom.\n\
		Tulips in a flower bed to open, there are red, yellow, pink, they are trying to outshine each other.\n\
		Warm sunshine in the body, the spring breeze stroke,\n\
		 feel very comfortable.\n\
		Winter grandpa left with the north, voice carrying a basket of flowers is coming!\n \
		The river stood a long braid of willow sister, on their long braid small rope full of promise.\n\
		There was a tree bent over, can't wait to want to wash and dress her beautiful long tails. \
		The photo under the peach tree, play.Peach sister is so happy, so he built a prank, \n \
		and handfuls of peach blossom petals, like a petal of rain.Petals fall on the grass, \n \
		the grass becomes red and green carpet of flowers.Petals fall on the kid's head, \n\
		face, clothing, children becomes a flower child. \
		Two busy honey bee was suddenly the petals rain frighten panic, had to hide in the blossom.\n\
		Tulips in a flower bed to open, there are red, yellow, pink, \n\
		they are trying to outshine each other.\n\
		Warm sunshine in the body, the spring breeze stroke, feel very comfortable.\n\
		Winter grandpa left with the north, voice carrying a basket of flowers is coming!\n \
		The river stood a long braid of willow sister, \n\
		on their long braid small rope full of promise.\n\
		There was a tree bent over, can't wait to want to wash and dress her beautiful long tails. \
		The photo under the peach tree, play.Peach sister is so happy, so he built a prank, \n \
		and handfuls of peach blossom petals, like a petal of rain.Petals fall on the grass, \n \
		the grass becomes red and green carpet of flowers.Petals fall on the kid's head, \n\
		face, clothing, children becomes a flower child. \
		Two busy honey bee was suddenly the petals rain frighten panic,\n\
		 had to hide in the blossom.\n\
		Tulips in a flower bed to open, there are red, yellow, pink, they are trying to outshine each other.\n\
		Warm sunshine in the body, the spring breeze stroke,\n\
		feel very comfortable.\n\
		Winter grandpa left with the north, voice carrying a basket of flowers is coming!\n \
		The river stood a long braid of willow sister, on their long braid small rope full of promise.\n\
		There was a tree bent over, can't wait to want to wash and dress her beautiful long tails. \
		The photo under the peach tree, play.Peach sister is so happy, so he built a prank, \n \
		and handfuls of peach blossom petals, like a petal of rain.Petals fall on the grass, \n \
		the grass becomes red and green carpet of flowers.Petals fall on the kid's head, \n\
		face, clothing, children becomes a flower child. \
		Two busy honey bee was suddenly the petals rain frighten panic, had to hide in the blossom.\n\
		Tulips in a flower bed to open, there are red, yellow, pink, they are trying to outshine each other.\n\
		Warm sunshine in the body, the spring breeze stroke, feel very comfortable.\n\
		Oh, I finally found the spring!");

private:
	FText testcontent = FText::FromString("Winter grandpa left with the north, voice carrying a basket of flowers is coming! \
		The river stood a long braid of willow sister, on their long braid small rope full of promise.There was a tree bent over, can't wait to want to wash and dress her beautiful long tails. \
		The photo under the peach tree, play.Peach sister is so happy, so he built a prank, and handfuls of peach blossom petals, like a petal of rain.Petals fall on the grass, the grass becomes red and green carpet of flowers.Petals fall on the kid's head, face, clothing, children becomes a flower child. \
		Two busy honey bee was suddenly the petals rain frighten panic, had to hide in the blossom.\
		Tulips in a flower bed to open, there are red, yellow, pink, they are trying to outshine each other.\
		Warm sunshine in the body, the spring breeze stroke, feel very comfortable.\
		Oh, I finally found the spring!");

private:
	FReply ImportJsonContenButtonClick() const;
	FReply ConvertKBEToUE4JsonClick() const;
	FReply SaveUE4JsonClick() const;

//	void NotificationHandleMsg(FString Path);

	TArray<FString> SplitStringToArray(FString SRC, FString Arg);

	TSharedPtr< STextBlock > ImportJsonTextBlock;

	TSharedPtr< STextBlock > SaveUE4JsonTextBlock;

	FString PluginDirectory;

	/** Holds the editable text box. */
	TSharedPtr<SEditableTextBox> TextBox;

	FString LoadContent = TEXT("");

	FString ConvertContent = TEXT("");

	bool isConvert = false;
};