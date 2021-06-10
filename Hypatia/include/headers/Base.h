#pragma once

namespace hypatia
{
	#ifdef HYPATIA_API
	#    define HYPATIA_API __declspec(dllexport)
	#else
	#    define HYPATIA_API __declspec(dllimport)
	#endif
}