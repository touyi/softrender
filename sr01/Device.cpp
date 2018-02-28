#include "Device.h"


namespace easym {
	Device::Device(int width, int height):m_width(width),
		m_height(height)
	{
		m_zBuffer = new real*[m_width];
		for (int i = 0; i < m_width; i++) {
			m_zBuffer[i] = new real[m_height];
		}
	}


	Device::~Device()
	{
		if (m_zBuffer) {
			for (int i = 0; i < m_width; i++) {
				delete[] m_zBuffer[i];
			}
			delete[] m_zBuffer;
		}
	}
	void Device::DrawPixel(int x, int y, easym::Vector4 color)
	{
		if (m_pFrameBuffer != NULL) {
			m_pFrameBuffer[y*m_width + x] = easym::color2Uint(color);
		}
	}
	real Device::GetZ(int x, int y) const
	{
		if (x >= 0 && x < m_width && y >= 0 && y < m_height) {
			return m_zBuffer[x][y];
		}
		else {
			return static_cast<real>(1);
		}
	}
	void Device::SetZ(int x, int y, real z)
	{
		if (x >= 0 && x < m_width && y >= 0 && y < m_height) {
			m_zBuffer[x][y] = z;
		}
	}
	void Device::ClearBuffer(Vector3 color)
	{
		if (m_pFrameBuffer != NULL) {
			for (int i = 0; i < m_width; i++) {
				for (int j = 0; j < m_height; j++) {
					m_pFrameBuffer[j*m_width + i] = easym::color2Uint(color);
				}
			}
		}
	}
}

