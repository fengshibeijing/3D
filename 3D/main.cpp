#include "include/sharpnow.hpp"
#include <iostream>
#include <Windows.h>
#pragma comment(lib,"user32.lib")

sharpnow::SDK sdk;
namespace vidkey
{
	float ix,iy;
	int modeflag=0;
	int loadvid()
	{
		// 加载动态链接库
		if (!sdk.LoadInPath("../lib")) return -1;

		std::cout << "等待设备连接 ... " << std::endl;
		bool connected[] = { false, false };
		while (true)
		{
			for (int device = 0; device < 2; ++device)
			{
				if (sdk.RetrieveFrame(device))
				{
					// 检测是否为新连接设备
					if (!connected[device])
					{
						//std::cout << "检测到微动 " << device << " 连接" << std::endl;
						//std::cout << "伸出单指可控制屏幕光标移动" << std::endl;
						connected[device] = true;
					}




					// 确认收到最新数据
					const sharpnow::Frame* frame = sdk.GetFrameInfo();
					if (!frame->updated) continue;

					const sharpnow::Hand* hand=sdk.GetHandFocus();
					const sharpnow::Finger* finger = sdk.GetFingerFocus();
					if (hand&&finger)
					{
						
						// 单手指时，控制屏幕光标
						std::cout << "\r" << finger->cursor.x << " " << finger->cursor.y;
						//keybd_event(17,0,0,0);
						//keybd_event(80,0,0,0);
						//keybd_event(80,0,KEYEVENTF_KEYUP,0);
						//keybd_event(17,0,KEYEVENTF_KEYUP,0);
						if (frame->finger_number>2)
						{
							SetCursorPos(
								int(finger->cursor.x * ::GetSystemMetrics(SM_CXSCREEN)),
								int(finger->cursor.y * ::GetSystemMetrics(SM_CYSCREEN)));	
						}
					
						if (frame->finger_number==1&&finger->stop==50)
						{
							mouse_event(MOUSEEVENTF_LEFTUP,finger->cursor.x,finger->cursor.y,0,0);
							//ix=finger->cursor.x;
							//iy=finger->cursor.y;
							keybd_event(17,0,0,0);
							keybd_event(80,0,0,0);
							keybd_event(80,0,KEYEVENTF_KEYUP,0);
							keybd_event(17,0,KEYEVENTF_KEYUP,0);
							
							modeflag=1;
								mouse_event(MOUSEEVENTF_LEFTDOWN,finger->cursor.x,finger->cursor.y,0,0);
						}
						if (frame->finger_number==2&&finger->stop==50)
						{
							mouse_event(MOUSEEVENTF_LEFTUP,finger->cursor.x,finger->cursor.y,0,0);
							//ix=finger->cursor.x;
							//iy=finger->cursor.y;
							keybd_event(17,0,0,0);
							keybd_event(82,0,0,0);
							keybd_event(82,0,KEYEVENTF_KEYUP,0);
							keybd_event(17,0,KEYEVENTF_KEYUP,0);
							mouse_event(MOUSEEVENTF_LEFTDOWN,finger->cursor.x,finger->cursor.y,0,0);
							modeflag=1;
						}
						/*if (frame->finger_number>=3&&modeflag)
						{
							mouse_event(MOUSEEVENTF_LEFTDOWN,finger->cursor.x,finger->cursor.y,0,0);
						}*/
						if (frame->finger_number>=3&&finger->stop==60)
						{
							modeflag=0;
							mouse_event(MOUSEEVENTF_LEFTUP,finger->cursor.x,finger->cursor.y,0,0);
							//SetCursorPos(ix,iy);
						}
						//if (finger->tap&&finger)
						//{

						//	mouse_event(MOUSEEVENTF_LEFTUP,finger->cursor.x,finger->cursor.y,0,0);

						//}
						//if (hand->finger_number<=2)
						//{
						//	if (finger->stop>40)
						//	{
						//		mouse_event(MOUSEEVENTF_LEFTUP,finger->cursor.x,finger->cursor.y,0,0);
						//
						//		mouse_event(MOUSEEVENTF_LEFTDOWN,finger->cursor.x,finger->cursor.y,0,0);
						//	}
					
						//}
						//if (hand->finger_number>=4)
						//{
						//	float x=finger->cursor.x;
						//	float y=finger->cursor.y;
						//	if (finger->stop>60)
						//	{
						//		//mouse_event(MOUSEEVENTF_LEFTUP,finger->cursor.x,finger->cursor.y,0,0);
						//		keybd_event(17,0,0,0);
						//		keybd_event(82,0,0,0);
						//		keybd_event(82,0,KEYEVENTF_KEYUP,0);
						//		keybd_event(17,0,KEYEVENTF_KEYUP,0);
						//		mouse_event(MOUSEEVENTF_LEFTDOWN,finger->cursor.x,finger->cursor.y,0,0);
						//	}
						
					
						}
					}
					


				
				else
				{
					// 检测设备断开
					if (connected[device])
					{
						std::cout << "检测到微动 " << device << " 断开" << std::endl;
						connected[device] = false;
					}
					continue;
				}
			}
			::Sleep(1);
		}

		return 0;
	}
	}

	//void mode1(float a,float b)
	//{
	//	mouse_event(MOUSEEVENTF_LEFTUP,a,b,0,0);
	//	keybd_event(17,0,0,0);
	//	keybd_event(80,0,0,0);
	//	keybd_event(80,0,KEYEVENTF_KEYUP,0);
	//	keybd_event(17,0,KEYEVENTF_KEYUP,0);
	//	mouse_event(MOUSEEVENTF_LEFTDOWN,a,b,0,0);
	//	
	//
	//}
	//void mode2(float a,float b)
	//{
	//	mouse_event(MOUSEEVENTF_LEFTUP,a,b,0,0);
	//	keybd_event(17,0,0,0);
	//	keybd_event(82,0,0,0);
	//	keybd_event(82,0,KEYEVENTF_KEYUP,0);
	//	keybd_event(17,0,KEYEVENTF_KEYUP,0);
	//	mouse_event(MOUSEEVENTF_LEFTDOWN,a,b,0,0);
	//	
	//}



using namespace vidkey;
int main(int argc, char** argv)
{
	while(true)
		//mouse_event(MOUSEEVENTF_LEFTDOWN,1000,1000,0,0);
	{
		loadvid();
	}

	

	system("pause");
}

