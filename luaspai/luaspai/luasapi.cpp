// luasapi.cpp : Defines the exported functions for the DLL application.
//

#include <sapi.h>
#include <sphelper.h>

#include "stdafx.h"

HRESULT hr = S_OK;
CComPtr<ISpVoice> cpVoice;
CComPtr<ISpStream> cpStream;
CComPtr<IStream> cpBaseStream;
GUID guidFormat;
WAVEFORMATEX* pWavFormatEx = nullptr;

// grifted from https://github.com/yashasvigirdhar/MS-SAPI-demo
extern "C" {
	__declspec(dllexport) bool speak(const char *words) {
		_LARGE_INTEGER a = { 0 };
		cpStream->Seek(a, STREAM_SEEK_SET, NULL);
		ULARGE_INTEGER b = { 0 };
		cpStream->SetSize(b);

		const size_t ct = strlen(words) + 1;
		wchar_t* wc = new wchar_t[ct];
		mbstowcs(wc, words, ct);

		cpVoice->Speak(wc, SPF_ASYNC, NULL);
		cpVoice->WaitUntilDone(-1);

		delete wc;

		return hr != S_OK;
	}

	__declspec(dllexport) ULONG get_size() {
		_LARGE_INTEGER a = { 0 };
		cpStream->Seek(a, STREAM_SEEK_SET, NULL);

		IStream *pIstream;
		cpStream->GetBaseStream(&pIstream);

		STATSTG stats;
		pIstream->Stat(&stats, STATFLAG_NONAME);

		ULONG sSize = stats.cbSize.QuadPart;

		return sSize;
	}

	__declspec(dllexport) ULONG fill_buffer(unsigned char *buf, ULONG sz) {
		IStream *pIstream;
		cpStream->GetBaseStream(&pIstream);

		ULONG bytesRead;
		pIstream->Read(buf, sz, &bytesRead);
		return bytesRead;
	}

	__declspec(dllexport) bool init_sapi() {
		if (FAILED(::CoInitialize(NULL)))
			return FALSE;

		if (SUCCEEDED(hr)) {
			hr = cpVoice.CoCreateInstance(CLSID_SpVoice);
		}

		if (SUCCEEDED(hr)) {
			hr = cpStream.CoCreateInstance(CLSID_SpStream);
		}

		if (SUCCEEDED(hr)) {
			hr = CreateStreamOnHGlobal(NULL, TRUE, &cpBaseStream);
		}

		if (SUCCEEDED(hr)) {
			hr = SpConvertStreamFormatEnum(SPSF_44kHz16BitStereo, &guidFormat, &pWavFormatEx);
		}

		if (SUCCEEDED(hr)) {
			hr = cpStream->SetBaseStream(cpBaseStream, guidFormat, pWavFormatEx);
			cpBaseStream.Release();
		}

		if (SUCCEEDED(hr)) {
			hr = cpVoice->SetOutput(cpStream, TRUE);
		}

		return hr != S_OK;
	}

	__declspec(dllexport) void deinit_sapi() {
		cpStream.Release();
		cpVoice.Release();

		::CoUninitialize();
	}
}