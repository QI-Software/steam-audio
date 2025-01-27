//
// Copyright 2017-2023 Valve Corporation.
//

#pragma once

#include "SteamAudioEditorModule.h"
#include "IDetailCustomization.h"
#include "Input/Reply.h"

class USteamAudioBakedListenerComponent;


namespace SteamAudio {

// ---------------------------------------------------------------------------------------------------------------------
// FSteamAudioBakedListenerDetails
// ---------------------------------------------------------------------------------------------------------------------

class FSteamAudioBakedListenerDetails : public IDetailCustomization
{
public:
	static TSharedRef<IDetailCustomization> MakeInstance();

private:
	TWeakObjectPtr<USteamAudioBakedListenerComponent> BakedListenerComponent;

	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;

	FReply OnBakeReflections();
};

}
