#ifndef SHELL_GOL_H
#define SHELL_GOL_H

#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 
#include <malloc.h>

#include <Framebuffer/GraphicDevice.hpp>
#include <Framebuffer/Buffer.hpp>


class GameOfLife
{
public:
	GameOfLife();
	~GameOfLife();

	void Init();
	void Move();
	void  Draw();

	void Run();
protected:

	int xadd(int i, int a);
	int yadd (int i, int a);
	int adjacent_to (int i, int j);
private:
	char** board, **newboard;
	fb::GraphicDevice	*m_pDevice;
	fb::GraphicBuffer   *m_pBuffer;
	int					m_rounds;
};


int gameOfLife(int argc, char **argv);
#endif