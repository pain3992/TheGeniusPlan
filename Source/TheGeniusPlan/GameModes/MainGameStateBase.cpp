#include "TheGeniusPlan/GameModes/MainGameStateBase.h"
#include "TheGeniusPlan/HUD/MainGameHUD.h"
#include "TheGeniusPlan/Widget/MainGame/MainGameWidget.h"
#include "TheGeniusPlan/GameModes/MainGameModeBase.h"
#include "TheGeniusPlan/Player/GeniusPlayerState.h"
#include "Net/UnrealNetwork.h"
#include "Engine/Engine.h"


void AMainGameStateBase::AddPlayer(AGeniusPlayerState *NewPlayerState)
{
    // 플레이어 목록 중복 체크
    if (NewPlayerState && !PlayingPlayers.Contains(NewPlayerState))
    {
        PlayingPlayers.Add(NewPlayerState);
        UE_LOG(LogTemp, Log, TEXT("플레이어: '%s'가 참여하였습니다."), *NewPlayerState->GetPlayerName());
        OnRep_PlayingPlayers();
    }
}

void AMainGameStateBase::RemovePlayer(AGeniusPlayerState *RemovePlayerState)
{
    if (RemovePlayerState && PlayingPlayers.Contains(RemovePlayerState))
    {
        PlayingPlayers.Remove(RemovePlayerState);
        UE_LOG(LogTemp, Log, TEXT("플레이어: '%s'가 나갔습니다."), *RemovePlayerState->GetPlayerName());
        OnRep_PlayingPlayers();
    }
}

AMainGameStateBase::AMainGameStateBase()
{
    UE_LOG(LogTemp, Log, TEXT("AMainGameStateBase instance created."));
}

TArray<AGeniusPlayerState *> AMainGameStateBase::GetAllPlayingPlayers() const
{
    return PlayingPlayers;
}

void AMainGameStateBase::StartCountdown(int32 InitialCountdownTime)
{
    if (HasAuthority())
    {
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("StartCountdown"));
        CountdownTime = InitialCountdownTime;
        OnRep_CountdownTime();

        GetWorld()->GetTimerManager().SetTimer(CountdownTimerHandle, this, &AMainGameStateBase::UpdateCountdown, 1.0f, true);
    }
}

void AMainGameStateBase::OnRep_CountdownTime() const
{
    for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
    {
        if (AMainGameHUD *HUD = (*It)->GetHUD<AMainGameHUD>())
        {
            if (UMainGameWidget *MainGameWidget = HUD->GetMainGameWidget())
            {
                MainGameWidget->UpdateCountdownDisplay(CountdownTime);
            }
        }
    }
}

void AMainGameStateBase::OnRep_PlayingPlayers() const
{
    for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
    {
        if (AMainGameHUD *HUD = (*It)->GetHUD<AMainGameHUD>())
        {
            if (UMainGameWidget *MainGameWidget = HUD->GetMainGameWidget())
            {
                MainGameWidget->UpdatePlayerList(PlayingPlayers);
            }
        }
    }
}

void AMainGameStateBase::UpdateCountdown()
{
    if (CountdownTime > 0)
    {
        CountdownTime--;
        OnRep_CountdownTime();
    }
    else
    {
        CountdownFinished();
    }
}

void AMainGameStateBase::CountdownFinished()
{
    GetWorld()->GetTimerManager().ClearTimer(CountdownTimerHandle);

    // 타이머 종료 시 라운드 종료 처리
    if (AMainGameModeBase* GameMode = GetWorld()->GetAuthGameMode<AMainGameModeBase>())
    {
        GameMode->HandleRoundEnd();
    }
}

void AMainGameStateBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> &OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(AMainGameStateBase, CountdownTime);
    DOREPLIFETIME(AMainGameStateBase, PlayingPlayers);
}