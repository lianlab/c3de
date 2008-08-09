#include "D3DApplication.h"
#include "DebugMemory.h"
#include "CommonDefs.h"
//#include "Debug.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, PSTR cmdLine, int showCmd)
{
	// Turn on the trace file 'dumpmemorylog.txt'
	DumpMemoryLogAllAllocations(TRUE);

    D3DApplication *app = new D3DApplication();

	//memory leak left on purpose to check the memory leak log
	//int *leak = new int();
	//int *lefdak = new int();

	//Create new window and Initiate Direct3D
	//if(FAILED(app.Init(hInstance, 640, 480, true)))
	//	return 0;
	if(!app->Init(hInstance, SCREEN_WIDTH, SCREEN_HEIGHT, true))
	{
		return 0;
	}

	MSG msg;
	memset(&msg, 0, sizeof(MSG));
	int startTime = timeGetTime(); 

	

	//Start the message loop

	while(msg.message != WM_QUIT)
	{
		if(::PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}
		else
        {	
			
			int t = timeGetTime();
			float deltaTime = (t - startTime)*0.001f;

			//For each frame update and render our app
			app->Update(deltaTime);
			app->Render();

			
			startTime = t;
        }
    }


	//Cleanup before exit
	app->Cleanup();
	

	delete app;

	// Dump a report of any unfreed blocks to 'memoryleak.txt', then free the breadcrumb list
	DumpUnfreed(TRUE);

    return msg.wParam;
}
