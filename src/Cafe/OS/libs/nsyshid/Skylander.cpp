#include "Skylander.h"

#include "nsyshid.h"
#include "Backend.h"

SkylanderUSB::SkylanderUSB()
	: Device(0x1430, 0x0150, 1, 2, 0)
{
	m_IsOpened = false;
}

bool SkylanderUSB::Open()
{
    if (!m_IsOpened) {
        m_IsOpened = true;
    }
    return true;
}

void SkylanderUSB::Close()
{
    if(m_IsOpened) {
        m_IsOpened = false;
    }
}

nsyshid::Device::ReadResult SkylanderUSB::Read(uint8* data, sint32 length, sint32& bytesRead)
{

}