#ifndef HEIGHTMAP_H
#define HEIGHTMAP_H

#include <d3dx9.h>
#include "intpoint.h"

struct PARTICLE{
	D3DXVECTOR3 position;
	D3DCOLOR color;
	static const DWORD FVF;
};

struct HeightMap
{
	//Functions
	HeightMap(IntPoint _size, float _maxHeigh);
	~HeightMap();
	void Release();
	HRESULT LoadFromFile(IDirect3DDevice9* Device, char fileName[]);
	//HRESULT CreateParticles();
	//void Render();
	//D3DXVECTOR2 GetCentre(){return D3DXVECTOR2(m_size.x / 2.0f, m_size.y / 2.0f);}
	HRESULT CreateRandomHeightMap(int seed, float noiseSize, float persistence, int octaves);

	void RaiseTerrain(RECT r, float f);
	void SmoothTerrain();

	//variables
	IntPoint m_size;		//Size of HeightMap
	float m_maxHeight;		//The height of the highest peak
	float *m_pHeightMap;	//Array with height values

	//Vertex buffer for points
	//IDirect3DVertexBuffer9 *m_pVb;

	void Cap(float capHeight);

	//Our device
	//IDirect3DDevice9* m_pDevice; 

	//Sprite
	//ID3DXSprite *m_pSprite;
	//IDirect3DTexture9 *m_pHeightMapTexture;

	void operator*=(const HeightMap &rhs);
};

#endif
