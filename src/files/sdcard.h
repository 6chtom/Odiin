#pragma once

#include <cstdint>
#include <cstddef>

#include "ff.h"

namespace Files
{
	// #todo: actual abstraction
	using SdCardFile = FIL;
	using SdCardFileInfo = FILINFO;
	using SdCardDirectory = DIR;

	class SdCard
	{
	public:
		SdCard();
		virtual ~SdCard() = default;
		SdCard(const SdCard &) = delete;
		SdCard &operator=(const SdCard &) = delete;
		bool Mount();
		bool Unmount();

		// #todo: these belong in their own class
		bool DirectoryOpen(SdCardDirectory& dir, const char* directoryPath);
		bool DirectoryRead(SdCardDirectory& dir, SdCardFileInfo& info);
		bool DirectoryClose(SdCardDirectory& dir);

		// #todo: these belong in their own class
		bool FileOpen(SdCardFile& file, const char* filePath, uint8_t mode);
		bool FileRead(SdCardFile& file, void* buffer, size_t amountToRead, size_t* amountRead);
		bool FileWrite(SdCardFile& file, const void* buffer, size_t bufferLength, size_t* amountWritten);
		bool FileSeek(SdCardFile& file, size_t offset);
		bool FileClose(SdCardFile& file);
		bool FileStat(const char* path, SdCardFileInfo& fileInfo);

		static constexpr const char* RootDirectory = "/";

		inline const char* GetDriveLabel() { return driveLabel; }
		inline uint32_t GetDriveSerial() { return driveSerial; }

	private:
		FATFS fileSystem; // #todo: abstract out the fs.
		static bool registered;
		uint8_t diskIndex = -1;
		bool initialized = false;
		bool mounted = false;
		uint32_t driveSerial = 0;
		char driveLabel[16] = { 0 };
		void RegisterBlockDevice();
		bool Initialize();
		bool Uninitialize();
	};
} // namespace Files
