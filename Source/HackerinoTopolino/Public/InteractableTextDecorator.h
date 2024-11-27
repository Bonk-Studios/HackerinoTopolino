// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/RichTextBlockDecorator.h"
#include "InteractableTextDecorator.generated.h"

/**
 * 
 */
UCLASS()
class HACKERINOTOPOLINO_API UInteractableTextDecorator : public URichTextBlockDecorator {
	GENERATED_BODY()

public:
	UInteractableTextDecorator(const FObjectInitializer& ObjectInitializer);

	virtual TSharedPtr<ITextDecorator> CreateDecorator(URichTextBlock* InOwner) override;
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnTextClicked(const FString& Type, const FString& Data);
};
