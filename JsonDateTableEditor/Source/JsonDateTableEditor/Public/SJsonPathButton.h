/**
@ 选择Json路径按钮
@Author TeenWolf
@Email  731796991@qq.com
@Date   2017-06-17 11:04:30

濂藉ソ瀛︿範
*/


#pragma once

class  SJsonPathButton : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SJsonPathButton){}
	SLATE_ATTRIBUTE(FString, InText)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);
private:
	FReply OnFindPathButtonClicked();
};