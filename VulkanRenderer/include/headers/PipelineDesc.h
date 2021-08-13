#pragma once
#include "PipelineDesc.h"

namespace hypatia
{
	typedef struct PIPELINE_DRAW_DESC
	{
	
	}PIPELINE_DRAW_DESC;
	
	typedef struct PIPELINE_COMPUTE_DESC
	{
	
	}PIPELINE_COMPUTE_DESC;
	
	typedef struct PIPELINE_UI_DESC
	{
	
	}PIPELINE_UI_DESC;
	
	typedef struct PIPELINE_POSTPROCESS_DESC
	{
	
	}PIPELINE_POSTPROCESS_DESC;

	typedef struct PIPELINE_DESC
	{
		HWND hwnd;
		HINSTANCE hInstance;
		std::vector<const char*> extensions;
		int frameBufferWidth;
		int frameBufferHeight;
	}PIPELINE_DESC;
}