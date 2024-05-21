#include"Global.h"
SDL_Surface* img[6];
SDL_Texture* texture[6];
SDL_Window* window = NULL;
SDL_Renderer* render = NULL;

int map[ROW][COLS] =
{
	1,1,1,1,1,1,1,1,
	1,3,1,1,0,3,0,1,
	1,4,0,0,0,4,0,1,
	1,0,1,1,0,0,1,1,
	1,0,0,0,5,0,1,1,
	1,4,1,1,4,0,1,1,
	1,3,1,0,3,0,1,1,
	1,1,1,1,1,1,1,1
};

void init_sdl()
{
	SDL_Init(SDL_INIT_EVERYTHING);;
	IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
	TTF_Init();

}

void create_window()
{
	window = SDL_CreateWindow(u8"爱坤推箱子", 100, 100, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	render = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
}
void destory()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(render);
}
//加载图片
void load_images()
{
	int index[6] = { 0,1,3,4,5,7 };
	char imgURL[30] = "";
	for (int i = 0; i < 6; i++)
	{
		sprintf_s(imgURL, 30, "./res/%d.bmp", index[i]);
		img[i] = IMG_Load(imgURL);
		texture[i] = SDL_CreateTextureFromSurface(render, img[i]);
	}
}
//画地图
void render_map()
{
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			SDL_Rect dst = { IMGW * j,IMGH * i,IMGW,IMGH };
			switch (map[i][j])
			{
			case Road:
				SDL_RenderCopy(render, texture[0], NULL, &dst);
				break;
			case Wall:
				SDL_RenderCopy(render, texture[1], NULL, &dst);
				break;
			case Board:
				SDL_RenderCopy(render, texture[2], NULL, &dst);
				break;
			case Ball:
				SDL_RenderCopy(render, texture[3], NULL, &dst);
				break;
			case Role:
			case SRole:
				SDL_RenderCopy(render, texture[4], NULL, &dst);
				break;
			case Chick:
				SDL_RenderCopy(render, texture[5], NULL, &dst);
				break;
			default:
				break;
			}
		}
	}
}
//获取位置信息

SDL_Point GetPos()
{
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			if (map[i][j] == Role || map[i][j] == SRole)
			{
				return (SDL_Point) { i, j };
			}
		}
	}
	return (SDL_Point) { -1, -1 };
}

//更新状态
bool over_game()
{
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			if (map[i][j] == Ball)
			{
				return false;
			}
		}
	}
	return true;
}
void event_game(SDL_Event* msg)
{
	int i = GetPos().x;
	int j = GetPos().y;
	if (msg->key.keysym.sym == SDLK_UP )
	{
		if (map[i - 1][j] == Road || map[i - 1][j] == Board)
		{
			map[i][j] -= Role;
			map[i - 1][j] += Role;
		}
		if (map[i - 1][j] == Ball || map[i - 1][j] == Chick)
		{
			if (map[i - 2][j] == Road || map[i - 2][j] == Board)
			{
				map[i][j] -= Role;
				map[i - 1][j] += Role - Ball;
				map[i - 2][j] += Ball;
			}
		}

	}
	else if (msg->key.keysym.sym == SDLK_DOWN)
	{
		if (map[i + 1][j] == Road || map[i +1][j] == Board)
		{
			map[i][j] -= Role;
			map[i + 1][j] += Role;
		}
		if (map[i + 1][j] == Ball || map[i + 1][j] == Chick)
		{
			if (map[i + 2][j] == Road || map[i + 2][j] == Board)
			{
				map[i][j] -= Role;
				map[i + 1][j] += Role - Ball;
				map[i + 2][j] += Ball;
			}
		}
	}
	else if (msg->key.keysym.sym == SDLK_LEFT )
	{
		if (map[i][j-1] == Road || map[i][j-1] == Board)
		{
			map[i][j] -= Role;
			map[i][j-1] += Role;
		}
		if (map[i ][j- 1] == Ball || map[i ][j- 1] == Chick)
		{
			if (map[i ][j- 2] == Road || map[i][j - 2] == Board)
			{
				map[i][j] -= Role;
				map[i][j - 1] += Role - Ball;
				map[i ][j- 2] += Ball;
			}
		}
	}
	else if (msg->key.keysym.sym == SDLK_RIGHT )
	{
		if (map[i][j+1] == Road || map[i][j+1] == Board)
		{
			map[i][j] -= Role;
			map[i][j+1] += Role;
		}
		if (map[i][j +1] == Ball || map[i][j + 1] == Chick)
		{
			if (map[i][j + 2] == Road || map[i][j +2] == Board)
			{
				map[i][j] -= Role;
				map[i][j + 1] += Role - Ball;
				map[i][j + 2] += Ball;
			}
		}
	}
}

void event_loop()
{
	bool isRunning = true;
	while (isRunning)
	{
		SDL_Event msg;
		if (SDL_WaitEvent(&msg) != 0)
		{
			switch (msg.type)
			{
			case SDL_QUIT:
				isRunning = false;
				break;
			case SDL_KEYDOWN:
				event_game(&msg);
				if (over_game())
					isRunning = false;
				break;
			}
		}
		//绘图
		SDL_RenderClear(render);
		render_map();
		SDL_RenderPresent(render);
		
	}
}

int main(int argc,char* argv[])
{
	init_sdl();
	create_window();
	load_images();//加载资源必须在创建窗口之后
	event_loop();

	destory();
	return 0;
}