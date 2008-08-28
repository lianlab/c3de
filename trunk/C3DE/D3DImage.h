#ifndef D3D_IMAGE_H
#define D3D_IMAGE_H

#include <d3dx9.h>
#include "Image.h"

class D3DImage : Image
{
public:
	D3DImage(IDirect3DTexture9 * tex){m_tex = tex;}
	~D3DImage(){delete m_tex;}
	IDirect3DTexture9 * GetTexture(){ return m_tex;}
private:
	IDirect3DTexture9 * m_tex;
};
#endif