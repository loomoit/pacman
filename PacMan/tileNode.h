#pragma once

//한 타일의 규격은 32 x 32로 한다
#define TILESIZE 32
#define TILEWIDTH 32
#define TILEHEIGHT 32

//타일 갯수 X 20, Y 20
#define TILEX 20
#define TILEY 20

//타일 갯수
#define TILENUMX (640 / TILEWIDTH)
#define TILENUMY (WINSIZEY / TILEHEIGHT)

//타일 총 사이즈 640 x 640
#define TILESIZEX TILESIZE * TILEX
#define TILESIZEY TILESIZE * TILEY

//타일셋 (맵툴에서의 샘플타일) 갯수
#define SAMPLETILEX 16
#define SAMPLETILEY 5

//비트필드 예전엔 많이 썻는데 요즘은 ... 메모리가 풍부해서 별로 그닥
#define ATTR_UNMOVE 0x00000001		//못가는 지형
#define ATTR_SWAMP	0x00000002		//늪지대 스피드가 느려진다던가...
#define ATTR_POISON 0x00000004		//독지대
#define ATTR_EAT	0x00000008		//먹을수 있는 지형
//#define ATTR_FROZEN 0x00000008	//빙결지대

/*
enum ATTRIBUTE
{
	UNMOVE, SWAMP, POISON, FROZEN
};
*/
//터레인 == 지형
enum TERRAIN
{
	TR_CEMENT, TR_DESERT, TR_GRASS, TR_WATER, TR_WALL, TR_END
};

//오브젝트 
enum OBJECT
{
	OBJ_BLOCK1, OBJ_BLOCK3, OBJ_BLOCKS,	//벽돌 오브젝트
	OBJ_FLAG1, OBJ_FLAG2,				//진영 별 깃발
	OBJ_TANK1, OBJ_TANK2,				//탱크 리스폰위치
	OBJ_EAT,
	OBJ_NONE
};

//포지션에 대한 정의
enum POS
{
	POS_FLAG1, POS_FLAG2,	//깃발 위치(타일)
	POS_TANK1, POS_TANK2	//탱크 위치(타일)
};

//타일에 대한 구조체
struct tagTile
{
	TERRAIN terrain;			//지형 이넘문
	OBJECT	obj;				//오브젝트 이넘문
	RECT	rc;					//렉트
	int		terrainFrameX;		//지형 프레임 번호(이미지)
	int		terrainFrameY;		//지형 프레임 번호
	int		objFrameX;			//오브젝트 프레임 번호
	int		objFrameY;			//오브젝트 프레임 번호
};

//타일셋 구조체
struct tagSampleTile
{
	RECT rcTile;		//타일셋 렉트
	int terrainFrameX;	//타일셋 프레임 번호
	int terrainFrameY;	//타일셋 프레임 번호
};

//현재 타일 == 내가 현재 클릭한 타일에 대한 정보 저장용 구조체
struct tagCurrentTile
{
	int x;
	int y;
};