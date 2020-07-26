#pragma once
#include <cstdint>

#include "usb/usb_msc.h"

#include "display/display_screen.h"
#include "files/sdcard.h"
#include "fsm/app_odiin_fsm.h"
#include "input/input_keypad.h"
#include "nfc_tag_emulation/nxp_ntag21x_emulator.h"

using NfcTagEmulator = nfc_tag_emulation::nxp_ntag21x::Ntag21xEmulator;
using NtagPayload = nfc_tag_emulation::nxp_ntag21x::Ntag21XPayload;

namespace App
{
	class Odiin : public Usb::Listener
	{
		using StateMachine = Fsm::OdiinState;
	public:
		static Odiin* GetInstance();
		static Files::SdCard* GetSdCard();

		~Odiin();
		void Update();

    	template<typename E>
		inline void SendEvent(E const& ev) { StateMachine::dispatch(ev); }

		void SetNfcTagPayload(nfc_tag_emulation::Payload* pl);
		void SetNfcTagEnabled(bool enabled);

		virtual void UsbWillEnable(app_usbd_event_type_t event) override;
		virtual void UsbDidDisable(app_usbd_event_type_t event) override;
	private:
		Odiin();
		Odiin(const Odiin&) = delete;
		Odiin& operator=(const Odiin&) = delete;

		void InitializeLogs();
		void InitializeClocks();
		void InitializeTimers();
		void InitializeBsp();
		void InitializeUsbDevice();
		void InitializeSdCard();
		void InitializeInput();
		void InitializeScreen();
		void InitializeNfcTag();
		void StartApplication();

		Usb::MassStorageClass* usbMassStorageClass;
		Files::SdCard* sdCard;
		Input::Keypad* keypad;
		Display::Screen* screen;
		NfcTagEmulator* nfcTagEmulator;
	};
} // namespace App


