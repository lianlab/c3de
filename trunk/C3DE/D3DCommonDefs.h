#ifndef D3D_COMMON_DEFFS_H
#define D3D_COMMON_DEFFS_H

#include "dxerr9.h"

#if defined(DEBUG) | defined(_DEBUG)
	#ifndef HR
	
		#define HR(x)														\
			{																\
				HRESULT hr = x;												\
				if(FAILED(hr))												\
				{															\
					DXTrace(__FILE__, __LINE__, hr, #x, TRUE);				\
				}															\
			}
	#endif
#else
	#ifndef HR
		#define HR(x) x;
	#endif
#endif

#define ReleaseCOM(x) {if(x){x->Release();x= 0;}}

#endif