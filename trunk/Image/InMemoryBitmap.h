/**************************************************************************************
 * Project: MapWindow Open Source (MapWinGis ActiveX control) 
 **************************************************************************************
 * The contents of this file are subject to the Mozilla Public License Version 1.1
 * (the "License"); you may not use this file except in compliance with 
 * the License. You may obtain a copy of the License at http://www.mozilla.org/mpl/ 
 * See the License for the specific language governing rights and limitations
 * under the License.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 ************************************************************************************** 
 * Contributor(s): 
 * (Open source contributors should list themselves and their modifications here). */
  // lsu 21 aug 2011 - created the file

#pragma once;
#include "base64.h"
#include <gdiplus.h>

// A wrapper for GDI+ bitmap located in the global heap
class CMemoryBitmap
{
private:	
	// icon stream (must be open for the lifetime of the Bitmap according to MSDN Bitmap constructor)
	IStream* m_stream;

	// underlying data for the image (must be released in destructor)
	HGLOBAL m_data;

	int m_size;
public:
	// for tiles
	int Provider;

	HGLOBAL getData()
	{
		return m_data;
	}
	
	// The actual bitmap	
	Gdiplus::Bitmap* m_bitmap;
	
	int get_Width()
	{
		if (m_bitmap)
			return m_bitmap->GetWidth();
		else
			return 0;
	}

	int get_Height()
	{
		if (m_bitmap)
			return m_bitmap->GetHeight();
		else
			return 0;
	}

	int get_Size()
	{
		return m_size;
	}

	// **************************************************
	//    Constructor()
	// **************************************************
	// Creates an empty instance of CMemoryBitmap class
	CMemoryBitmap::CMemoryBitmap()
	{
		m_bitmap = NULL;
		m_stream = NULL;
		m_data = NULL;
		m_size = 0;
	};
	
	// **************************************************
	//    LoadFromBase64String()
	// **************************************************
	// Loads data from base64 string
	bool LoadFromBase64String(std::string str)
	{
		if (str.size() != 0)
		{
			str = base64_decode(str);
			const char* data = str.c_str();
			
			return this->LoadFromRawData(data, (int)str.size());
		}
		return false;
	}

	// **************************************************
	//    SerializeToBase64String()
	// **************************************************
	std::string SerializeToBase64String()
	{
		return base64_encode(reinterpret_cast<unsigned char*>(m_data), m_size);
	}

	// **************************************************
	//    LoadFromRawData()
	// **************************************************
	bool LoadFromRawData(const char* data, int size)
	{
		this->Release();
		
		if (size <= 0)
			return false;

		m_data = ::GlobalAlloc(GMEM_MOVEABLE, size);
		if (m_data)
		{
			void* hMem = ::GlobalLock(m_data);
			if (hMem)
			{
				memcpy(hMem, data, size);
				::GlobalUnlock(hMem);

				if (::CreateStreamOnHGlobal(m_data, FALSE, &m_stream) == S_OK)
				{
					m_bitmap = new Gdiplus::Bitmap(m_stream);
					m_size = size;
					if (m_bitmap)
						return true;
				}
			}
		}

		this->Release();
		return false;
	}

	// ************************************************
	//	Release()
	// ************************************************
	void Release()
	{
		if (m_bitmap)
			delete m_bitmap;

		if (m_stream)
			m_stream->Release();

		if (m_data)
		{
			m_data = GlobalFree(m_data);
		}

		m_size = 0;
	}

	// Destructor. Underlying stream must be closed and data deleted
	virtual ~CMemoryBitmap()
	{
		this->Release();
	}
};
