#pragma once

//�� Ÿ���� �԰��� 32 x 32�� �Ѵ�
#define TILESIZE 32
#define TILEWIDTH 32
#define TILEHEIGHT 32

//Ÿ�� ���� X 20, Y 20
#define TILEX 20
#define TILEY 20

//Ÿ�� ����
#define TILENUMX (640 / TILEWIDTH)
#define TILENUMY (WINSIZEY / TILEHEIGHT)

//Ÿ�� �� ������ 640 x 640
#define TILESIZEX TILESIZE * TILEX
#define TILESIZEY TILESIZE * TILEY

//Ÿ�ϼ� (���������� ����Ÿ��) ����
#define SAMPLETILEX 16
#define SAMPLETILEY 5

//��Ʈ�ʵ� ������ ���� ���µ� ������ ... �޸𸮰� ǳ���ؼ� ���� �״�
#define ATTR_UNMOVE 0x00000001		//������ ����
#define ATTR_SWAMP	0x00000002		//������ ���ǵ尡 �������ٴ���...
#define ATTR_POISON 0x00000004		//������
#define ATTR_EAT	0x00000008		//������ �ִ� ����
//#define ATTR_FROZEN 0x00000008	//��������

/*
enum ATTRIBUTE
{
	UNMOVE, SWAMP, POISON, FROZEN
};
*/
//�ͷ��� == ����
enum TERRAIN
{
	TR_CEMENT, TR_DESERT, TR_GRASS, TR_WATER, TR_WALL, TR_END
};

//������Ʈ 
enum OBJECT
{
	OBJ_BLOCK1, OBJ_BLOCK3, OBJ_BLOCKS,	//���� ������Ʈ
	OBJ_FLAG1, OBJ_FLAG2,				//���� �� ���
	OBJ_TANK1, OBJ_TANK2,				//��ũ ��������ġ
	OBJ_EAT,
	OBJ_NONE
};

//�����ǿ� ���� ����
enum POS
{
	POS_FLAG1, POS_FLAG2,	//��� ��ġ(Ÿ��)
	POS_TANK1, POS_TANK2	//��ũ ��ġ(Ÿ��)
};

//Ÿ�Ͽ� ���� ����ü
struct tagTile
{
	TERRAIN terrain;			//���� �̳ѹ�
	OBJECT	obj;				//������Ʈ �̳ѹ�
	RECT	rc;					//��Ʈ
	int		terrainFrameX;		//���� ������ ��ȣ(�̹���)
	int		terrainFrameY;		//���� ������ ��ȣ
	int		objFrameX;			//������Ʈ ������ ��ȣ
	int		objFrameY;			//������Ʈ ������ ��ȣ
};

//Ÿ�ϼ� ����ü
struct tagSampleTile
{
	RECT rcTile;		//Ÿ�ϼ� ��Ʈ
	int terrainFrameX;	//Ÿ�ϼ� ������ ��ȣ
	int terrainFrameY;	//Ÿ�ϼ� ������ ��ȣ
};

//���� Ÿ�� == ���� ���� Ŭ���� Ÿ�Ͽ� ���� ���� ����� ����ü
struct tagCurrentTile
{
	int x;
	int y;
};