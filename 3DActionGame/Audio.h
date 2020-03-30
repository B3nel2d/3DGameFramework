//======================================================================
//
//	Audio
//
//	âπê∫èàóùÇ‚ä«óùÇíSÇ§ÉNÉâÉX
//
//======================================================================

#pragma once

#define WIN32_LEAN_AND_MEAN

#include <xaudio2.h>
#include <xact3.h>
#include "Settings.h"

class Audio{
	private:
		IXACT3Engine* xactEngine;

		IXACT3WaveBank* waveBank;
		IXACT3SoundBank* soundBank;
		XACTINDEX cueIndex;
		void* mapWaveBank;
		void* soundBankData;

		bool coInitialized;

	public:
		Audio();
		~Audio();

		HRESULT initialize();

		void run();
		void playCue(const char cue[]);
		void stopCue(const char cue[]);
};
