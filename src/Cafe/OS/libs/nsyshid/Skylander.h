#include "nsyshid.h"
#include "Backend.h"

class SkylanderUSB final : public nsyshid::Device {
  public:
	SkylanderUSB();
	~SkylanderUSB() = default;

	bool Open() override;

	void Close() override;

	bool IsOpened() override;

	ReadResult Read(uint8* data, sint32 length, sint32& bytesRead) override;

	WriteResult Write(uint8* data, sint32 length, sint32& bytesWritten) override;

	bool GetDescriptor(uint8 descType,
					   uint8 descIndex,
					   uint8 lang,
					   uint8* output,
					   uint32 outputMaxLength) override;

	bool SetProtocol(uint32 ifIndex, uint32 protocol) override;

	bool SetReport(uint8* reportData, sint32 length, uint8* originalData, sint32 originalLength) override;

  private:
	bool m_IsOpened;
};