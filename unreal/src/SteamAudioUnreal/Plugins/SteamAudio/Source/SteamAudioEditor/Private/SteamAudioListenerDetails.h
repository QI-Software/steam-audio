//
// Copyright 2017-2023 Valve Corporation.
//

#pragma once

#include "SteamAudioEditorModule.h"
#include "IDetailCustomization.h"
#include "Input/Reply.h"

class USteamAudioListenerComponent;


namespace SteamAudio {

// ---------------------------------------------------------------------------------------------------------------------
// FSteamAudioListenerDetails
// ---------------------------------------------------------------------------------------------------------------------

class FSteamAudioListenerDetails : public IDetailCustomization
{
public:
    static TSharedRef<IDetailCustomization> MakeInstance();

private:
    TWeakObjectPtr<USteamAudioListenerComponent> ListenerComponent;

    virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;

    FReply OnBakeReverb();
};

}
