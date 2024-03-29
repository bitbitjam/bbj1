#define BADDIES_COUNT 42

typedef struct {
	int x, y;
	unsigned char x1, y1, x2, y2;
	char mx, my;
	char t;
#ifdef PLAYER_CAN_FIRE
	unsigned char life;
#endif
} MALOTE;

MALOTE malotes [] = {
	{112, 128, 112, 128, 192, 128, 1, 0, 2},
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{64, 64, 64, 64, 64, 112, 0, 1, 3},
	{128, 64, 128, 64, 128, 112, 0, 4, 3},
	{192, 48, 192, 48, 192, 112, 0, 4, 3},
	{32, 112, 32, 112, 112, 112, 4, 0, 2},
	{128, 112, 128, 112, 224, 112, 1, 0, 2},
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{128, 128, 128, 128, 208, 128, 1, 0, 2},
	{32, 48, 32, 48, 112, 96, 4, 4, 3},
	{112, 96, 112, 96, 112, 96, 0, 0, 0},
	{192, 32, 192, 32, 192, 80, 0, 4, 3},
	{96, 16, 96, 16, 144, 48, 4, 4, 3},
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{32, 96, 32, 96, 96, 96, 2, 0, 4},
	{112, 96, 112, 96, 208, 96, 2, 0, 4},
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{160, 96, 160, 96, 192, 96, 2, 0, 3},
	{80, 96, 80, 96, 144, 96, 4, 0, 3},
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{48, 112, 48, 112, 112, 112, 2, 0, 2},
	{96, 112, 96, 112, 176, 112, 2, 0, 2},
	{176, 64, 176, 64, 176, 96, 0, 2, 3},
	{64, 128, 64, 128, 160, 128, 2, 0, 1},
	{64, 64, 64, 64, 160, 128, 4, 4, 3},
	{144, 112, 144, 112, 144, 112, 0, 0, 0},
	{16, 128, 16, 128, 48, 128, 2, 0, 1},
	{208, 16, 208, 16, 208, 64, 0, 4, 3},
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{96, 80, 96, 80, 176, 128, 4, 4, 1},
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{80, 80, 80, 80, 80, 128, 0, 2, 2},
	{96, 96, 96, 96, 176, 128, 2, 2, 1},
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{16, 96, 16, 96, 64, 112, 2, 2, 3},
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{32, 96, 32, 96, 80, 128, 2, 2, 3},
	{176, 96, 176, 96, 128, 128, -2, 2, 3},
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{112, 32, 112, 32, 112, 112, 0, 2, 4},
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{48, 80, 48, 80, 192, 80, 2, 0, 4},
	{80, 48, 80, 48, 144, 96, 2, 2, 3},
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{48, 128, 48, 128, 128, 128, 2, 0, 4},
	{176, 32, 176, 32, 176, 128, 0, 2, 4},
	{96, 48, 96, 48, 144, 96, 1, 1, 3},
	{176, 32, 176, 32, 176, 96, 0, 2, 3},
	{32, 32, 32, 32, 32, 80, 0, 2, 1},
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{112, 96, 112, 96, 160, 96, 2, 0, 2},
	{64, 64, 64, 64, 64, 112, 0, 1, 3},
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{32, 128, 32, 128, 80, 128, 2, 0, 1},
	{112, 96, 112, 96, 176, 128, 2, 2, 2},
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{128, 96, 128, 96, 192, 128, 4, 4, 1},
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0}
};

typedef struct {
	unsigned char xy, tipo, act;
} HOTSPOT;

HOTSPOT hotspots [] = {
	{0, 0, 0},
	{0, 0, 0},
	{0, 0, 0},
	{0, 0, 0},
	{0, 0, 0},
	{0, 0, 0},
	{0, 0, 0},
	{0, 0, 0},
	{0, 0, 0},
	{0, 0, 0},
	{0, 0, 0},
	{0, 0, 0},
	{0, 0, 0},
	{0, 0, 0},
	{0, 0, 0},
	{0, 0, 0},
	{0, 0, 0},
	{0, 0, 0},
	{0, 0, 0},
	{0, 0, 0},
	{0, 0, 0},
	{0, 0, 0},
	{0, 0, 0},
	{0, 0, 0},
	{0, 0, 0},
	{0, 0, 0},
	{0, 0, 0},
	{0, 0, 0},
	{0, 0, 0},
	{0, 0, 0}
};

