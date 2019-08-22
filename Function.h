#include<iostream>
#include<iomanip>
#include<conio.h>
#include<Windows.h>
#include <mmsystem.h>
#include <cstdlib>
#pragma comment(lib, "WinMM.Lib")
//----------------------------------------------------------------------DEFINE----------------------------------------------------------------------
#define HEIGHT_BOARD 43
#define WIDTH_BOARD 120
#define STEP_MOVING HEIGHT_BOARD / 7
#define STEP_RUN 3
#define ESC 27
#define COLOR_RIVER 159
#define COLOR_STREET 7
#define yRow_1 1 * HEIGHT_BOARD / 7 + 2
#define yRow_2 2 * HEIGHT_BOARD / 7 + 2
#define yRow_3 4 * HEIGHT_BOARD / 7 + 2
#define yRow_4 5 * HEIGHT_BOARD / 7 + 2
//----------------------------------------------------------------------ENUM----------------------------------------------------------------------
enum MOVING { UP, DOWN, LEFT, RIGHT, WAIT };
enum STATE { DEAD, LIVING, GO, STOP};
enum PLACE { ON_STREET, ON_RIVER };
enum SHAPE { CAR , TRUCK , WOOD};
//----------------------------------------------------------------------WINDOWS.H--------------------------------------------------------------------
void gotoXY(const int &x, const int &y);
void resizeConsole(const int &width, const int &height);
void drawChar(const int &x, const int &y, const char &c, const int &color);
//----------------------------------------------------------------------STRUCT----------------------------------------------------------------------
struct nude
{
	int x;
	int y;
}; typedef struct nude NUDE;
struct board
{
private:
	int _height;
	int _width;
	int _color;
public:
	void init();
	void setBoard(const int &height, const int &width, const int &color);

	void setHeight(const int &height);
	void setWidth(const int &width);
	void setColor(const int &color);
	int getHeight();
	int getWidth();
	int getColor();

	void draw();
}; typedef struct board BOARD;
struct character
{
private:
	int _height;
	int _width;
	int _color;
	NUDE *_nudeBody;
	MOVING _move;
	STATE _state;
	PLACE _place;
public:
	void init();
	void setCharacter(const int &height, const int &width, const int &color, const NUDE &firstNudeBody, const MOVING &move, const STATE &state, const PLACE &place);

	void setHeight(const int &height);
	void setWidth(const int &width);
	void setColor(const int &color);
	void setNudeBody(const NUDE &firstNudeBody);
	void setMoving(const MOVING &move);
	void setState(const STATE &state);
	void setPlace(const PLACE &place);
	int getHeight();
	int getWidth();
	int getColor();
	NUDE* getNudeBody();
	MOVING getMoving();
	STATE getState();
	PLACE getPlace();

	void draw();
	void erase();
	void moving();
	void cleanGabage();
}; typedef struct character CHARACTER;
struct impediment
{
private:
	int _height;
	int _width;
	int _color;
	NUDE *_nudeBody;
	MOVING _move;
	STATE _state;
	SHAPE _shape;
	PLACE _place;
public:
	void init();
	void setImpediment(const int &height, const int &width, const int &color, const NUDE &firstNudeBody, const MOVING &move, const STATE &state, const SHAPE &shape, const PLACE &place);

	void setHeight(const int &height);
	void setWidth(const int &width);
	void setColor(const int &color);
	void setNudeBody(const NUDE &firstNudeBody);
	void setMoving(const MOVING &move);
	void setState(const STATE &state);
	void setShape(const SHAPE &shape);
	void setPlace(const PLACE &place);
	int getHeight();
	int getWidth();
	int getColor();
	NUDE* getNudeBody();
	MOVING getMoving();
	STATE getState();
	SHAPE getShape();
	PLACE getPlace();

	void draw();
	void erase();
	void moving();
	void cleanGabage();
}; typedef struct impediment IMPEDIMENT;
struct light
{
private:
	int _height;
	int _width;
	NUDE _firstBodyNude;
	STATE _state;
public:
	void init();
	void setLight(const int &height, const int &width, const NUDE &firstBodyNude, const STATE &state);

	void setHeight(const int &height);
	void setWidth(const int &width);
	void setFirstBodyNude(const NUDE &firstBodyNude);
	void setState(const STATE &state);
	int getHeight();
	int getWidth();
	NUDE getBodyNude();
	STATE getState();

	void draw();
	void erase();
}; typedef struct light LIGHT;
struct score
{
private:
	int _count;
	int _color;
	NUDE _nude;
public:
	void init();
	void setScore(const int &count, const int &color, const NUDE &nude);

	void setCount(const int &count);
	void setColor(const int &color);
	void setNude(const NUDE &nude);
	int getCount();
	int getColor();
	NUDE getNude();

	void draw();
}; typedef struct score SCORE;
//----------------------------------------------------------------------MẢNG CHƯỚNG NGẠI VẬT--------------------------------------------------------
void allocationArrayImpediment(IMPEDIMENT **&impediment, const int &numberRowImpediment, const int &numberColImpediment);
void initArrayImpediment(IMPEDIMENT **&impediment, const int &numberRowImpediment, const int &numberColImpediment);
void setArrayImpediment(IMPEDIMENT **&impediment, const int &numberRowImpediment, const int &numberColImpediment);
void movingArrayImpediment(IMPEDIMENT **&impediment, const int &numberRowImpediment, const int &numberColImpediment, bool &isFirstTurn);
void cleanArrayGabageImpediment(IMPEDIMENT **&impediment, const int &numberRowImpediment, const int &numberColImpediment);
//----------------------------------------------------------------------MẢNG ĐÈN GIAO THÔNG--------------------------------------------------------
void allocationArrayLight(LIGHT *&light, const int &numberLight);
void initArrayLight(LIGHT *&light, const int &numberLight);
void setArrayLight(LIGHT *&light, const int &numberLight);
void drawArrayLight(LIGHT *light, const int &numberLight);
void cleanArrayGabageLight(LIGHT *&light);
//----------------------------------------------------------------MẢNG NHÂN VẬT QUA ĐƯỜNG THÀNH CÔNG-----------------------------------------------
void addNewCharacter(CHARACTER newCharacter, CHARACTER *&listCharacter, int &numberCharacter);
void initArrayCharacter(CHARACTER *&listCharacter, int &numberCharacter);
void drawArrayCharacter(CHARACTER *character, const int &numberCharacter);
void cleanArrayGabageCharacter(CHARACTER *&listCharacter, const int &numberCharacter);
//-------------------------------------------------------------------CÁC HÀM KIỂM TRA----------------------------------------------------------------------
bool isCrossingStreet(CHARACTER character);
bool isImpact(CHARACTER character, 
	          CHARACTER *listCharacter, const int &numberCharacter, 
	          IMPEDIMENT **impediment, const int &numberRowImpediment, const int &numberColImpedimnet);
//-------------------------------------------------------------------CÁC HÀM TẠO HIỆU ỨNG----------------------------------------------------------------------
void readFile(const char *fileName, const int &color);
void effectLoading();
void effectLevelUp();
void effectHighScore();
void exitOrContinue(char &choose);
//-------------------------------------------------------------------CÁC HÀM MENU----------------------------------------------------------------------------
void option(BOARD board,
	int &LEVEL, int &SPEED, int &maxCharacter,
	CHARACTER &character,
	CHARACTER *&listCharacter, int &numberCharacter,
	IMPEDIMENT **&impediment, int &numberRowImpediment, int &numberColImpediment, bool &isFirstTurn,
	LIGHT *&light, int &numberLight,
	SCORE &score, int &highScore, int &count,
	bool &isExit);
void saveInfoGame(const int &LEVEL, const int &SPEED, const int &maxCharacter,
	CHARACTER character,
	CHARACTER *listCharacter, const int &numberCharacter,
	IMPEDIMENT **impediment, const int &numberRowImpediment, const int &numberColImpediment, const bool &isFirstTurn,
	LIGHT *light, const int &numberLight,
	SCORE score, const int &highScore);
void loadInfoGame(int &LEVEL, int &SPEED, int &maxCharacter,
	CHARACTER &character,
	CHARACTER *&listCharacter, int &numberCharacter,
	IMPEDIMENT **&impediment, int &numberRowImpediment, int &numberColImpediment, bool &isFirstTurn,
	LIGHT *&light, int &numberLight,
	SCORE &score, int &highScore);
void setting(CHARACTER &character,
	IMPEDIMENT **impediment, const int &numberRowImpediment, const int &numberColImpediment);
void play(int &LEVEL, int &SPEED, int &maxCharacter,
	IMPEDIMENT **&impediment, const int &numberRowImpediment, int &numberColImpediment, bool &isFirstTurn);
//-------------------------------------------------------------------CÁC HÀM XỬ LÍ-----------------------------------------------------------------------
void processingDead(char &choose,
	CHARACTER &character,
	IMPEDIMENT **impediment, const int &numberRowImpediment, const int &numberColImpediment);
void processingSwitchToNextPlay(BOARD board,
	int &LEVEL, int &SPEED, int &maxCharacter,
	CHARACTER &character,
	CHARACTER *&listCharacter, int &numberCharacter,
	IMPEDIMENT **&impediment, int &numberRowImpediment, int &numberColImpediment, bool &isFirstTurn,
	LIGHT *&light, int &numberLight);
void processingWin();