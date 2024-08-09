// Fill out your copyright notice in the Description page of Project Settings.


#include "TheGeniusPlan/Widget/ChatWidget.h"
#include "Components/EditableTextBox.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"
#include "TheGeniusPlan/Widget/ChatEntryBoxWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "TheGeniusPlan/ChatComponent.h"

void UChatWidget::NativeConstruct()
{
	Super::NativeConstruct();

	MyChatComponent = GetWorld()->GetFirstPlayerController()->GetComponentByClass<UChatComponent>();
	ScrollMultiplier = 60.0f;

	if (!(EditableTextBox->OnTextCommitted.IsBound()))
	{
		EditableTextBox->OnTextCommitted.AddDynamic(this, &UChatWidget::EnterToEditableTextBox);
	}

	EditableTextBox->SetIsEnabled(false);
}

void UChatWidget::FocusChatWidget()
{
	EditableTextBox->SetUserFocus(GetWorld()->GetFirstPlayerController());
	EditableTextBox->SetIsEnabled(true);
	bIsFocus = true;
}

void UChatWidget::UnFocusChatWidget()
{
	bIsFocus = false;
	EditableTextBox->SetText(FText());
	EditableTextBox->SetIsEnabled(false);
	UWidgetBlueprintLibrary::SetInputMode_GameOnly(GetWorld()->GetFirstPlayerController());

}

void UChatWidget::ScrollChat(uint8 bIsUp)
{
	if (bIsFocus)
	{
		float Myfloat = FMath::FloatSelect(bIsUp, 1.0, -1.0);
		float Myfloattoo = (Myfloat * ScrollMultiplier);
		Myfloat = ScrollBox->GetScrollOffset() + Myfloattoo;
		ScrollBox->SetScrollOffset(FMath::Clamp(Myfloat, 0.0, ScrollBox->GetScrollOffsetOfEnd()));
	}
}

void UChatWidget::AddMyChatMessage(const FString& MyMessage, uint8 Type)
{
	UE_LOG(LogTemp, Error, TEXT("AddMyChatMessage Using Client Function"));

	if (ChatRoomType == (uint8)Type)
	{
		UTextBlock* NewTextBlock = NewObject<UTextBlock>(ScrollBox);
		NewTextBlock->SetText(FText::FromString(MyMessage));

		ScrollBox->AddChild(NewTextBlock);
		ScrollBox->ScrollToEnd();
	}
}

void UChatWidget::ClearChatWidget()
{
	ScrollBox->ClearChildren();
}

void UChatWidget::EnterToEditableTextBox(const FText& Text, ETextCommit::Type CommitMethod)
{
	if (CommitMethod == ETextCommit::OnEnter)
	{
		if (Text.IsEmpty())
		{
			UnFocusChatWidget();
			UE_LOG(LogTemp, Error, TEXT("Text is Empty"));
		}
		else
		{
			FString Message = Text.ToString();

			if (MyChatComponent)
			{
				MyChatComponent->SendMyMessage(Message, ChatRoomType);
			}

			UE_LOG(LogTemp, Error, TEXT("MyChatComponent Not Vaild"));
			UnFocusChatWidget();

		}
	}
	else
	{
		UnFocusChatWidget();
		UE_LOG(LogTemp, Error, TEXT("Commit is Not Enter"));
	}
}
