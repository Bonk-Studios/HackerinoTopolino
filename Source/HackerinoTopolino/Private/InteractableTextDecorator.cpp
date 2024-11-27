// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableTextDecorator.h"

#include "Widgets/SToolTip.h"
#include "Widgets/Text/STextBlock.h"

// Class charged of creating the inline tooltip
class FInteractableText : public FRichTextDecorator {
	UInteractableTextDecorator* Decorator;
public:
	FInteractableText(URichTextBlock* InOwner, const FTextBlockStyle& InTextStyle ,UInteractableTextDecorator* InDecorator)
		: FRichTextDecorator(InOwner), HintTextStyle(InTextStyle) {
		Decorator = InDecorator;
	}
	

	// Only valid if text is: <tooltip text="Some infos">Some text</>
	virtual bool Supports(const FTextRunParseResults& RunParseResult, const FString& Text) const override {
		// debug log
		//UE_LOG(LogTemp, Warning, TEXT("Supports: %s"), *RunParseResult.Name);
		return RunParseResult.Name == TEXT("hint") && RunParseResult.MetaData.Contains(TEXT("type")) && RunParseResult.MetaData.Contains(TEXT("data"));
	}

protected:
	/**
	* Create a STextBlock with a tooltip text.
	* 
	* For <tooltip text="Some infos">Some text</>:
	* - RunInfo.Content is "Some text"
	* - RunInfo.MetaData[TEXT("text")] is "Some infos"
	*/
	virtual TSharedPtr<SWidget> CreateDecoratorWidget(const FTextRunInfo& InRunInfo, const FTextBlockStyle& InTextStyle) const override {
		return SNew(STextBlock)
			.Text(InRunInfo.Content).TextStyle(&HintTextStyle)
			.OnDoubleClicked(FPointerEventHandler::CreateLambda(
				[InRunInfo, this](const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) {
					//UE_LOG(LogTemp, Warning, TEXT("Double clicked on %s"), *InRunInfo.MetaData[TEXT("data")]);
					Decorator->OnTextClicked(InRunInfo.MetaData[TEXT("type")], InRunInfo.MetaData[TEXT("data")]);
					return FReply::Handled();
				}
			));
	}

private:
	FTextBlockStyle HintTextStyle;
};

/////////////////////////////////////////////////////
// USampleRichTextBlockTooltipDecorator

UInteractableTextDecorator::UInteractableTextDecorator(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer) {}

// Return our custom class for creating the inline widget
TSharedPtr<ITextDecorator> UInteractableTextDecorator::CreateDecorator(URichTextBlock* InOwner) {
	return MakeShareable(new FInteractableText(InOwner, HintTextStyle, this));
}

void UInteractableTextDecorator::OnTextClicked_Implementation(const FString& Type, const FString& Data) {
	
}

/////////////////////////////////////////////////////
