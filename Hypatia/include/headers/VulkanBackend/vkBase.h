#pragma once

namespace hypatia
{
#ifdef HYPATIA_VULKAN_API
#    define HYPATIA_VULKAN_API __declspec(dllexport)
#else
#    define HYPATIA_VULKAN_API __declspec(dllimport)
#endif
}