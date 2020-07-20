#pragma once

#include <map>
using std::map;

#include "app_usbd.h"

namespace Usb
{
	namespace Device
	{
		struct class_info_t
		{
			const app_usbd_class_inst_t* classInstance;
			const void* context;
			const char* name;
		};

		using EventCallback = void (*)(app_usbd_event_type_t);
		bool Initialize(bool supportsPowerDetection = true);
		bool IsInitialized();
		bool Enable();
		bool Disable();
		bool IsEnabled();
		bool RegisterDeviceClass(const class_info_t * const deviceClass);

		// Update should be called in the main loop before or after __WFE.
		void Update();

	} // namespace Device
} // namespace Usb
