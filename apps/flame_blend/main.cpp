#include "mx3d.h"
#include "mx3d_texture.h"
#include<cstdlib>
#include<ctime>

mxHwnd mxhwnd;
mx3d::mxColor back_buffer[640][480];
mx3d::mxTexture imgs[4];
static bool fade_r = true;
static bool fade_g = false;
static bool fade_b = false;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {

	switch(msg) {
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		case WM_ACTIVATEAPP:
			mxhwnd.active = wParam;
			break;
		case WM_KEYDOWN:
			{
				switch(wParam) 
				{
				case 'R':
					fade_r = true;
					fade_g = false;
					fade_b = false;
					break;
				case 'G':
					fade_r = false;
					fade_g = true;
					fade_b = false;
					break;
				case 'B':
					fade_r = false;
					fade_g = false;
					fade_b = true;
					break;
				}
			}
			break;
		default:
			return DefWindowProc(hwnd,msg,wParam,lParam);
	}

	return 0;
}

inline void Blend(mx3d::mxTexture &tex) {
	static float alpha = 1.0f;
	static unsigned int i,z;
	for(i = 0; i < 640; i++)
		for(z = 0; z < 480; z++) {
			mx3d::mxColor col = tex.GetPixel(i,z);
			if((back_buffer[i][z].r = unsigned char( (back_buffer[i][z].r) + ( alpha * col.r ))) > 255) back_buffer[i][z].r = 255;
			if((back_buffer[i][z].g = unsigned char( (back_buffer[i][z].g) + ( alpha * col.g ))) > 255) back_buffer[i][z].g = 255;
			if((back_buffer[i][z].b = unsigned char( (back_buffer[i][z].b) + ( alpha * col.b ))) > 255) back_buffer[i][z].b = 255;
			
		}
		if(mxhwnd.input.key.KeyCheck(DIK_UP))
		alpha += 0.1f;
		if(mxhwnd.input.key.KeyCheck(DIK_DOWN))
		alpha -= 0.1f;
}

inline void Morph() {
	static unsigned int i,z;
	for(i = 0; i < 639; i++) {
		for(z = 0; z < 479; z++) {
			int col[3];
			col[0] = back_buffer[i][z].r + back_buffer[i+1][z].r + back_buffer[i][z+1].r + back_buffer[i+1][z+1].r;
			col[1] = back_buffer[i][z].g + back_buffer[i+1][z].g + back_buffer[i][z+1].g + back_buffer[i+1][z+1].g;
			col[2] = back_buffer[i][z].b + back_buffer[i+1][z].b + back_buffer[i][z+1].b + back_buffer[i+1][z+1].b;
			col[0] = col[0] / 4;
			col[1] = col[1] / 4;
			col[2] = col[2] / 4;
			if(fade_r == true) {
				back_buffer[i][z].r = ++col[0];
				back_buffer[i][z].g = --col[1];
				back_buffer[i][z].b = --col[2];
			}
			else if(fade_g == true) {
				back_buffer[i][z].r = --col[0];
				back_buffer[i][z].g = ++col[1];
				back_buffer[i][z].b = --col[2];
			}
			else if(fade_b == true) {
				back_buffer[i][z].r = --col[0];
				back_buffer[i][z].g = --col[1];
				back_buffer[i][z].b = ++col[2];
			}
		}
	}

	Blend(imgs[rand()%4]);
}

void render(int screen) {
	static unsigned int i,z;
	Morph();
	mxhwnd.paint.Lock();
	for(i = 0; i < 640; i++)
		for(z = 0; z < 480; z++)
			mxhwnd.paint.fast_sp(i,z,mxhwnd.paint.rect.Pitch, back_buffer[i][z].toD3D());
	mxhwnd.paint.UnLock();
}

inline void Init() {
	memset(back_buffer, 0, sizeof(back_buffer));
	imgs[0].LoadBMP("img\\1.bmp");
	imgs[1].LoadBMP("img\\2.bmp");
	imgs[2].LoadBMP("img\\3.bmp");
	imgs[3].LoadBMP("img\\4.bmp");

	srand(unsigned int(time(0)));

	for(unsigned int i = 0; i < 640; i++)
		for(unsigned int z = 0; z < 480; z++) {
			back_buffer[i][z].r = imgs[rand()%4].GetPixel(i,z).r;
			back_buffer[i][z].g = imgs[rand()%4].GetPixel(i,z).g;
			back_buffer[i][z].b = imgs[rand()%4].GetPixel(i,z).b;
		}
}

int PASCAL WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR lpszLine, int iCmdShow) {

	if(mxhwnd.Init("FlameBlend", false, 0,0,640,480, WndProc, 0) && mxhwnd.InitDX(false,32)) {
		Init();
		mxhwnd.InitLoop(render);
	}
	else
		ErrorMsg("DirectX (Update October) isnt properly installed or you dont have a good enough video card!\n");
	return 0;
}