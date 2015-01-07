#include <gol.hpp>

#define BOARD_WIDTH		800
#define BOARD_HEIGHT	600

GameOfLife::GameOfLife()
{
	

}
GameOfLife::~GameOfLife()
{
	free2d((void**)board, BOARD_WIDTH, BOARD_HEIGHT);
	free2d((void**)newboard, BOARD_WIDTH, BOARD_HEIGHT);

}
void GameOfLife::Init()
{
	m_rounds = 150;
	board = (char**)malloc2d(BOARD_WIDTH, BOARD_HEIGHT, sizeof(char));
	newboard = (char**)malloc2d(BOARD_WIDTH, BOARD_HEIGHT, sizeof(char));

	m_pDevice = new fb::GraphicDevice();
	m_pBuffer = m_pDevice->CreateBuffer();

	int	i, j;

	for (i=0; i<BOARD_WIDTH; i++) 
	{
		for (j=0; j<BOARD_HEIGHT; j++)
		{ 

			board[i][j] = rand_m(0,1);
		}
	}
}
void GameOfLife::Move()
{
	int	i, j, a;

	for (i=0; i<BOARD_WIDTH; i++) for (j=0; j<BOARD_HEIGHT; j++) {
		a = adjacent_to (i, j);
		if (a == 2) newboard[i][j] = board[i][j];
		if (a == 3) newboard[i][j] = 1;
		if (a < 2) newboard[i][j] = 0;
		if (a > 3) newboard[i][j] = 0;
	}


	for (i=0; i<BOARD_WIDTH; i++) for (j=0; j<BOARD_HEIGHT; j++) {
		board[i][j] = newboard[i][j];
	}
}
void GameOfLife::Draw()
{

	for (int j=0; j<BOARD_HEIGHT; j++) 
	{
		for (int i=0; i<BOARD_WIDTH; i++) 
		{
			m_pBuffer->Pixel(i,j, (board[i][j] ? 0x00FF00 * m_rounds : 0x000000) );
		}
	}
    
	m_rounds--;
}
void GameOfLife::Run()
{
	while(m_rounds >= 0)
	{
		m_pBuffer->Clear();
		Move();
		Draw();
		m_pDevice->SwapBuffer(m_pBuffer);
	}
    gotoxy(4,4);
    printf("Bitte druecken Sie eine Taste\n");
    getch();
}
int GameOfLife::xadd(int i, int a)
{
    i += a;
	while (i < 0) i += BOARD_WIDTH;
	while (i >= BOARD_WIDTH) i -= BOARD_WIDTH;
	return i;
}
int GameOfLife::yadd (int i, int a)
{
    i += a;
	while (i < 0) i += BOARD_HEIGHT;
	while (i >= BOARD_HEIGHT) i -= BOARD_HEIGHT;
	return i;
}
int GameOfLife::adjacent_to (int i, int j)
{
    int	k, l, count;

	count = 0;

	for (k=-1; k<=1; k++) for (l=-1; l<=1; l++)

		if (k || l)
			if (board[xadd(i,k)][yadd(j,l)]) count++;
	return count;
}
int gameOfLife(int argc, char **argv)
{
	GameOfLife *life = new GameOfLife();
	life->Init();
	life->Run();


	if(life != NULL) { delete[] life; life = NULL; }
	return 0;
}