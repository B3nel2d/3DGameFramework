#include "Audio.h"

/**********************************************************************
	�R���X�g���N�^�[
**********************************************************************/
Audio::Audio(){
    xactEngine = NULL;
    waveBank = NULL;
    soundBank = NULL;
    cueIndex = 0;
    mapWaveBank = NULL;
    soundBankData = NULL;

    HRESULT result = CoInitializeEx(NULL, COINIT_MULTITHREADED);
    if(SUCCEEDED(result)){
        coInitialized = true;
	}
    else{
        coInitialized = false;
	}
}

/**********************************************************************
	�f�R���X�g���N�^�[
**********************************************************************/
Audio::~Audio(){
    if(xactEngine){
		xactEngine->ShutDown();
		xactEngine->Release();
    }

    if(soundBankData){
		delete[] soundBankData;
	}
    soundBankData = NULL;

    if(mapWaveBank){
		UnmapViewOfFile(mapWaveBank);
	}
    mapWaveBank = NULL;

	if(coInitialized){
		CoUninitialize();
	}
}

/**********************************************************************
	initialize

	�e�\���̂�ݒ�̏��������s��
**********************************************************************/
HRESULT Audio::initialize(){
	HRESULT result = E_FAIL;
    HANDLE file;
    DWORD fileSize;
    DWORD bytesRead;
    HANDLE mapFile;

    if(coInitialized == false){
		return E_FAIL;
	}

	result = XACT3CreateEngine(0, &xactEngine);
	if(FAILED(result) || xactEngine == NULL){
		return E_FAIL;
	}

    XACT_RUNTIME_PARAMETERS xactParameters = {0};
    xactParameters.lookAheadTime = XACT_ENGINE_LOOKAHEAD_DEFAULT;
    result = xactEngine->Initialize(&xactParameters);
    if(FAILED(result)){
        return result;
	}

    result = E_FAIL;
    file = CreateFile(WAVE_BANK, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);

    if(file != INVALID_HANDLE_VALUE){
        fileSize = GetFileSize(file, NULL);

        if(fileSize != -1){
            mapFile = CreateFileMapping(file, NULL, PAGE_READONLY, 0, fileSize, NULL);

            if(mapFile){
                mapWaveBank = MapViewOfFile(mapFile, FILE_MAP_READ, 0, 0, 0);

                if(mapWaveBank){
                    result = xactEngine->CreateInMemoryWaveBank(mapWaveBank, fileSize, 0, 0, &waveBank);
				}

                CloseHandle(mapFile);
            }
        }
        CloseHandle(file);
    }
    if(FAILED(result)){
        return HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND);
	}

    result = E_FAIL;
    file = CreateFile(SOUND_BANK, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);

    if(file != INVALID_HANDLE_VALUE){
        fileSize = GetFileSize(file, NULL);

        if(fileSize != -1){
            soundBankData = new BYTE[fileSize];

            if(soundBankData){
                if(0 != ReadFile(file, soundBankData, fileSize, &bytesRead, NULL)){
                    result = xactEngine->CreateSoundBank(soundBankData, fileSize, 0, 0, &soundBank);
				}
            }
        }

        CloseHandle(file);
    }
    if(FAILED(result)){
        return HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND);
	}

    return S_OK;
}

/**********************************************************************
	run

	�T�E���h�G���W���̃^�X�N�����s����
**********************************************************************/
void Audio::run(){
    if(xactEngine == NULL){
		return;
	}

    xactEngine->DoWork();
}

/**********************************************************************
	playCue

	�w�肵���������Đ�����
**********************************************************************/
void Audio::playCue(const char cue[]){
    if(soundBank == NULL){
		return;
	}

    cueIndex = soundBank->GetCueIndex(cue);
    soundBank->Play(cueIndex, 0, 0, NULL);
}

/**********************************************************************
	stopCue

	�w�肵���������~����
**********************************************************************/
void Audio::stopCue(const char cue[]){
    if(soundBank == NULL){
		return;
	}

    cueIndex = soundBank->GetCueIndex(cue);
    soundBank->Stop(cueIndex, XACT_FLAG_SOUNDBANK_STOP_IMMEDIATE);
}
