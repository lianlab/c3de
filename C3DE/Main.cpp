#include "CommonDefs.h"
#include "ReplayDefs.h"
#include "RandomDefs.h"
#include "Debug.h"

#include "D3DApplication.h"
#include "DirectInput.h"
#include <ctime>
#include "DebugMemory.h"



#define TOTAL_RECORDS 1000

#if 0
struct StructReplay
{
	StructReplay(float a_deltaTime, bool a_up, bool a_down, bool a_left, bool a_right){ 
		deltaTime = a_deltaTime;up = a_up; down = a_down; left = a_left; right = a_right;}
	bool up;
	bool down;
	bool left;
	bool right;
	float deltaTime;
};
#endif
struct StructReplay
{
	StructReplay(float a_deltaTime, int a_key1, int a_key2,int a_key3, int a_key4){ 
		deltaTime = a_deltaTime; key1 =  a_key1; key2 =  a_key2; key3 =  a_key3; key4 =  a_key4;}
	int key1;
	int key2;
	int key3;
	int key4;
	float deltaTime;
};

vector<StructReplay *> *m_replay;


	
void buildReplay()
{
	m_replay = new vector<StructReplay *>;

	FILE * pFile;
	long lSize;
	size_t result;
	fpos_t position;


	pFile = fopen ( "replay.bin" , "rb" );


	m_replay = new vector<StructReplay *>;

	// obtain file size:
	fseek (pFile , 0 , SEEK_END);
	lSize = ftell (pFile);
	rewind (pFile);
	fgetpos(pFile, &position);

	// allocate memory to contain the whole file:
	int *buffer = (int*)malloc(sizeof(int)*5);
	

#if 1
	while(position < lSize)
	{
		// copy the file into the buffer:
		fsetpos(pFile, &position);
		result = fread (buffer,5,sizeof(int),pFile);
		position += (sizeof(int)*5);
		
		m_replay->push_back(new StructReplay(buffer[0], buffer[1], buffer[2], buffer[3], buffer[4]));
	}
	
#endif

	

	fclose(pFile);




}




#if ENABLE_REPLAY

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, PSTR cmdLine, int showCmd)
{
#if USE_TIME_SEED
	srand(time(0));
#else
	srand(RANDOM_SEED);
#endif
	// Turn on the trace file 'dumpmemorylog.txt'

	DumpMemoryLogAllAllocations(TRUE);

    D3DApplication *app = new D3DApplication();

	//memory leak left on purpose to check the memory leak log
	//int *leak = new int();
	//int *lefdak = new int();

	//Create new window and Initiate Direct3D
	
	if(!app->Init(hInstance, SCREEN_WIDTH, SCREEN_HEIGHT, WINDOWED))
	{
		return 0;
	}
	
	MSG msg;
	memset(&msg, 0, sizeof(MSG));
	int startTime = timeGetTime(); 

#if REPLAYING
	buildReplay();
	int t_currentRecord = 0;
	int t_totalRecords = m_replay->size();
#endif
	//Start the message loop

#if RECORDING
	//char buf[1024];
	FILE *fp = fopen("replay.bin","wb");
	
#endif

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

			
#if REPLAYING
			float deltaTime = m_replay->at(t_currentRecord)->deltaTime;
			

			DirectInput::GetInstance()->ClearAllKeys();
			

			DirectInput::GetInstance()->SetKeyDown(m_replay->at(t_currentRecord)->key1, true);
			DirectInput::GetInstance()->SetKeyDown(m_replay->at(t_currentRecord)->key2, true);
			DirectInput::GetInstance()->SetKeyDown(m_replay->at(t_currentRecord)->key3, true);
			DirectInput::GetInstance()->SetKeyDown(m_replay->at(t_currentRecord)->key4, true);

			t_currentRecord++;
			if(t_currentRecord == t_totalRecords || t_currentRecord > t_totalRecords)
			{
				break;
			}
#endif
#if RECORDING
			float deltaTime = (t - startTime);
			int * t_keys = DirectInput::GetInstance()->GetKeysDown();
			int t_deltaTime = (int)deltaTime;
			//sprintf(buf, "%d,%d,%d,%d,%d\n", t_deltaTime, t_keys[0], t_keys[1],t_keys[2],t_keys[3]);
	
			
			int all[] = {t_deltaTime, t_keys[0], t_keys[1],t_keys[2],t_keys[3]};
			fwrite(all, 1, sizeof(all), fp);

				
			
			//fprintf(fp2,buf);
#endif



			//For each frame update and render our app
			app->Update(deltaTime);
			app->Render();
			
			
			
			startTime = t;
        }
    }


	//Cleanup before exit
	app->Cleanup();

	
	 
	

	
#if RECORDING  

	fclose(fp);
	//fclose(fp2);

#endif

	delete app;

	// Dump a report of any unfreed blocks to 'memoryleak.txt', then free the breadcrumb list
	DumpUnfreed(TRUE);

    return msg.wParam;
	
}

#else

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, PSTR cmdLine, int showCmd)
{
#if USE_TIME_SEED
	srand(time(0));
#else
	srand(RANDOM_SEED);
#endif
	// Turn on the trace file 'dumpmemorylog.txt'

	//DumpMemoryLogAllAllocations(TRUE);

    D3DApplication *app = new D3DApplication();

	//memory leak left on purpose to check the memory leak log
	//int *leak = new int();
	//int *lefdak = new int();

	//Create new window and Initiate Direct3D
	
	if(!app->Init(hInstance, SCREEN_WIDTH, SCREEN_HEIGHT, WINDOWED))
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
			float deltaTime = (t - startTime);			

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
	//DumpUnfreed(TRUE);

    return msg.wParam;
	
}
#endif
		
		
		


