#include"Function.h"
//----------------------------------------------------------------------WINDOWS.H---------------------------------------------------------------------
void gotoXY(const int &x, const int &y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void resizeConsole(const int &width, const int &height)
{
	HWND console = GetConsoleWindow();
	RECT rect;
	GetWindowRect(console, &rect);
	MoveWindow(console, rect.left, rect.top, width, height, TRUE);
}
void textColor(const int &x)
{
	HANDLE color;
	color = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(color, x);
}
void drawChar(const int &x, const int &y, const char &c, const int &color)
{
	gotoXY(x, y);
	textColor(color);
	std::cout << c;
	textColor(7);
}
//----------------------------------------------------------------------KHUNG TRÒ CHƠI-----------------------------------------------------------------
void BOARD::init()
{
	_height = 0;
	_width = 0;
	_color = 7;
}
void BOARD::setBoard(const int &height, const int &width, const int &color)
{
	_width = width;
	_height = height;
	_color = color;
}

void BOARD::setHeight(const int &height)
{
	_height = height;
}
void BOARD::setWidth(const int &width)
{
	_width = width;
}
void BOARD::setColor(const int &color)
{
	_color = color;
}
int BOARD::getHeight()
{
	return _height;
}
int BOARD::getWidth()
{
	return _width;
}
int BOARD::getColor()
{
	return _color;
}

void BOARD::draw()
{
	for (int i = 0; i < _height; i++)
	{
		for (int j = 0; j < _width; j++)
		{
			if (i == 0 || i == _height - 1)
				drawChar(j, i, ' ', _color);
			else if (j == 0 || j == _width - 1)
				drawChar(j, i, ' ', _color);
			else if (j == 13 || j == _width - 14)
				drawChar(j, i, '|', 14);
			else if (i == 1 * _height / 7 || 
				     i == 2 * _height / 7 || 
					 i == 3 * _height / 7 || 
					 i == 4 * _height / 7 || 
					 i == 5 * _height / 7 ||
					 i == 6 * _height / 7)
				drawChar(j, i, '-', 14);
			else if (i >  1 * _height / 7 && i < 3 * _height / 7)
				drawChar(j, i, '~', COLOR_RIVER);
			else
				drawChar(j, i, ' ', COLOR_STREET);
		}
	}
}
//----------------------------------------------------------------------NHÂN VẬT CHÍNH-----------------------------------------------------------------
void CHARACTER::init()
{
	_height = 0;
	_width = 0;
	_color = 7;
	_nudeBody = NULL;
	_move = WAIT;
	_state = LIVING;
	_place = ON_STREET;
}
void CHARACTER::setCharacter(const int &height, const int &width, const int &color, const NUDE &firstNudeBody, const MOVING &move, const STATE &state, const PLACE &place)
{
	_height = height;
	_width = width;
	_color = color;

	_nudeBody = new NUDE[_width*_height];
	_nudeBody[0] = firstNudeBody;
	for (int i = 1; i < _width*_height; i++)
	{
		_nudeBody[i].x = _nudeBody[0].x + i % _width;
		_nudeBody[i].y = _nudeBody[0].y + i / _width;
	}

	_move = move;
	_state = state;
	_place = place;
}

void CHARACTER::setHeight(const int &height)
{
	_height = height;
}
void CHARACTER::setWidth(const int &width)
{
	_width = width;
}
void CHARACTER::setColor(const int &color)
{
	_color = color;
}
void CHARACTER::setNudeBody(const NUDE &firstNudeBody)
{
	_nudeBody = new NUDE[_width*_height];
	_nudeBody[0] = firstNudeBody;
	for (int i = 1; i < _width*_height; i++)
	{
		_nudeBody[i].x = _nudeBody[0].x + i % _width;
		_nudeBody[i].y = _nudeBody[0].y + i / _width;
	}
}
void CHARACTER::setMoving(const MOVING &move)
{
	_move = move;
}
void CHARACTER::setState(const STATE &state)
{
	_state = state;
}
void CHARACTER::setPlace(const PLACE &place)
{
	_place = place;
}
int CHARACTER::getHeight()
{
	return _height;
}
int CHARACTER::getWidth()
{
	return _width;
}
int CHARACTER::getColor()
{
	return _color;
}
NUDE* CHARACTER::getNudeBody()
{
	return _nudeBody;
}
MOVING CHARACTER::getMoving()
{
	return _move;
}
STATE CHARACTER::getState()
{
	return _state;
}
PLACE CHARACTER::getPlace()
{
	return _place;
}

void CHARACTER::draw()
{
	char **body = new char*[_height]; // xin cấp phát _height con trỏ cấp 1

	if (_state == DEAD)
	{
		body[0] = " O ";
		body[1] = "DIE";
		body[2] = "| |";
	}
	else if (_state == LIVING)
	{
		switch (_move)
		{
		case WAIT:
			body[0] = " O ";
			body[1] = "/|\\";
			body[2] = "/ \\";
			break;
		case UP:
			body[0] = "\\O/";
			body[1] = " | ";
			body[2] = "/ \\";
			break;
		case DOWN:
			body[0] = "\\O/";
			body[1] = " | ";
			body[2] = "| |";
			break;
		case LEFT:
			body[0] = "\\O ";
			body[1] = " |\\ ";
			body[2] = "| \\";
			break;
		default:
			body[0] = " O/";
			body[1] = "/| ";
			body[2] = "/ |";
			break;
		}
	}
	else
		std::cout << "Error" << std::endl;

	for (int i = 0; i < _width*_height; i++)
	{
		if (body[i / _width][i % _width] != ' ')
			drawChar(_nudeBody[i].x, _nudeBody[i].y, body[i / _width][i % _width], _color);
	}

	delete[] body;
}
void CHARACTER::erase()
{
	if (_place == ON_STREET)
	{
		for (int i = 0; i < _width*_height; i++)
			drawChar(_nudeBody[i].x, _nudeBody[i].y, ' ', COLOR_STREET);
	}
	else
	{
		for (int i = 0; i < _width*_height; i++)
			drawChar(_nudeBody[i].x, _nudeBody[i].y, '~', COLOR_RIVER);
	}
}
void CHARACTER::moving()
{
	if (_state == DEAD)
		draw();
	else if (_state == LIVING)
	{
		erase();
		switch (_move)
		{
		case WAIT:
			break;
		case UP:
			if (_nudeBody[0].y > STEP_MOVING)
				_nudeBody[0].y -= STEP_MOVING;
			break;
		case DOWN:
			if (_nudeBody[0].y < HEIGHT_BOARD - _height - STEP_MOVING )
				_nudeBody[0].y += STEP_MOVING;
			break;
		case LEFT:
			if (_nudeBody[0].x > STEP_MOVING / 2 + 13 && _place == ON_STREET)
				_nudeBody[0].x -= STEP_MOVING / 2;
			else if (_nudeBody[0].x > STEP_RUN + 13 && _place == ON_RIVER)
				_nudeBody[0].x -= STEP_RUN;
			break;
		default:
			if (_nudeBody[0].x < WIDTH_BOARD - _width - STEP_MOVING / 2 - 13 && _place == ON_STREET)
				_nudeBody[0].x += STEP_MOVING / 2;
			else if (_nudeBody[0].x < WIDTH_BOARD - _width - STEP_RUN - 13 && _place == ON_RIVER)
				_nudeBody[0].x += STEP_RUN;
			break;
		}
		for (int i = 1; i < _width*_height; i++) // cập nhật lại vị trí các bộ phân của nhân vật
		{
			_nudeBody[i].x = _nudeBody[0].x + i % _width; 
			_nudeBody[i].y = _nudeBody[0].y + i / _width;
		}
		draw();
		_move = WAIT; // trở lại trạng thái chờ
	}
	else
		std::cout << "Error" << std::endl;
	// xác định nhân vật chính đang ở trên cạn hay dưới nước
	if (_nudeBody[0].y < 1 * HEIGHT_BOARD / 7 || _nudeBody[0].y  > 3 * HEIGHT_BOARD / 7)
		_place = ON_STREET;
	else
		_place = ON_RIVER;
}
void CHARACTER::cleanGabage()
{
	if (_nudeBody)
		delete[] _nudeBody;
}
//----------------------------------------------------------------------CHƯỚNG NGẠI VẬT-----------------------------------------------------------------
void IMPEDIMENT::init()
{
	_height = 0;
	_width = 0;
	_color = 7;
	_nudeBody = NULL;
	_move = WAIT;
	_state = GO;
	_shape = CAR;
	_place = ON_STREET;
}
void IMPEDIMENT::setImpediment(const int &height, const int &width, const int &color, const NUDE &firstNudeBody, const MOVING &move, const STATE &state, const SHAPE &shape, const PLACE &place)
{
	_height = height;
	_width = width;
	_color = color;

	_nudeBody = new NUDE[_width*_height];
	_nudeBody[0] = firstNudeBody;
	for (int i = 1; i < _width*_height; i++)
	{
		_nudeBody[i].x = _nudeBody[0].x + i % _width;
		_nudeBody[i].y = _nudeBody[0].y + i / _width;
	}

	_move = move;
	_state = state;
	_shape = shape;
	_place = place;
}

void IMPEDIMENT::setHeight(const int &height)
{
	_height = height;
}
void IMPEDIMENT::setWidth(const int &width)
{
	_width = width;
}
void IMPEDIMENT::setColor(const int &color)
{
	_color = color;
}
void IMPEDIMENT::setNudeBody(const NUDE &firstNudeBody)
{
	_nudeBody = new NUDE[_width*_height];
	_nudeBody[0] = firstNudeBody;
	for (int i = 1; i < _width*_height; i++)
	{
		_nudeBody[i].x = _nudeBody[0].x + i % _width;
		_nudeBody[i].y = _nudeBody[0].y + i / _width;
	}
}
void IMPEDIMENT::setMoving(const MOVING &move)
{
	_move = move;
}
void IMPEDIMENT::setState(const STATE &state)
{
	_state = state;
}
void IMPEDIMENT::setShape(const SHAPE &shape)
{
	_shape = shape;
}
void IMPEDIMENT::setPlace(const PLACE &place)
{
	_place = place;
}
int IMPEDIMENT::getHeight()
{
	return _height;
}
int IMPEDIMENT::getWidth()
{
	return _width;
}
int IMPEDIMENT::getColor()
{
	return _color;
}
NUDE* IMPEDIMENT::getNudeBody()
{
	return _nudeBody;
}
MOVING IMPEDIMENT::getMoving()
{
	return _move;
}
STATE IMPEDIMENT::getState()
{
	return _state;
}
SHAPE IMPEDIMENT::getShape()
{
	return _shape;
}
PLACE IMPEDIMENT::getPlace()
{
	return _place;
}

void IMPEDIMENT::draw()
{
	char **body = new char*[_height];

	switch (_shape)
	{
	case CAR:
		if (_move == RIGHT)
		{
			body[0] = " ________    ";
			body[1] = "/ |_||_\\ \\__ ";
			body[2] = "\\_(-)___(-)_|";
		}
		else if (_move == LEFT)
		{
			body[0] = "    ________ ";
			body[1] = " __/ /_||_| \\";
			body[2] = "|_(-)___(-)_/";
		}
		else
			std::cout << "Error" << std::endl;
		break;
	case TRUCK:
		if (_move == RIGHT)
		{
			body[0] = " __________  ";
			body[1] = "||_| |_| |_\\";
			body[2] = "|_(-)___(-)_|";
		}
		else if (_move == LEFT)
		{
			body[0] = "  __________ ";
			body[1] = " /_| |_| |_||";
			body[2] = "|_(-)___(-)_|";
		}
		else
			std::cout << "Error" << std::endl;
		break;
	case WOOD:
		body[0] = "- - - - - - -";
		body[1] = "- - - - - - -";
		body[2] = "- - - - - - -";
		break;
	}

	for (int i = 0; i < _width*_height; i++)
	{
		if (body[i / _width][i % _width] != ' ')
			drawChar(_nudeBody[i].x, _nudeBody[i].y, body[i / _width][i % _width], _color);
	}

	delete[] body;
}
void IMPEDIMENT::erase()
{
	if (_place == ON_STREET)
	{
		for (int i = 0; i < _width*_height; i++)
			drawChar(_nudeBody[i].x, _nudeBody[i].y, ' ', COLOR_STREET);
	}
	else
	{
		for (int i = 0; i < _width*_height; i++)
			drawChar(_nudeBody[i].x, _nudeBody[i].y, '~', COLOR_RIVER);
	}
}
void IMPEDIMENT::moving()
{
	if (_state == STOP)
		draw();
	else if (_state == GO)
	{
		erase();
		switch (_move)
		{
		case LEFT:
			if (_nudeBody[0].x > STEP_RUN)
				_nudeBody[0].x -= STEP_RUN;
			break;
		case RIGHT:
			if (_nudeBody[0].x <WIDTH_BOARD - _width - STEP_RUN)
				_nudeBody[0].x += STEP_RUN;
			break;
		default:
			std::cout << "Error" << std::endl;
			break;
		}
		for (int i = 1; i < _width*_height; i++)
		{
			_nudeBody[i].x = _nudeBody[0].x + i % _width;
			_nudeBody[i].y = _nudeBody[0].y + i / _width;
		}
		draw();
	}
	else
		std::cout << "Error" << std::endl;
}
void IMPEDIMENT::cleanGabage()
{
	if (_nudeBody)
		delete[] _nudeBody;
}
//----------------------------------------------------------------------ĐÈN GIAO THÔNG-----------------------------------------------------------------
void LIGHT::init()
{
	_height = 0;
	_width = 0;
	_firstBodyNude = NUDE{ 0, 0 };
	_state = GO;
}
void LIGHT::setLight(const int &height, const int &width, const NUDE &firstBodyNude, const STATE &state)
{
	_height = height;
	_width = width;
	_firstBodyNude = firstBodyNude;
	_state = state;
}

void LIGHT::setHeight(const int &height)
{
	_height = height;
}
void LIGHT::setWidth(const int &width)
{
	_width = width;
}
void LIGHT::setFirstBodyNude(const NUDE &firstBodyNude)
{
	_firstBodyNude = firstBodyNude;
}
void LIGHT::setState(const STATE &state)
{
	_state = state;
}
int LIGHT::getHeight()
{
	return _height;
}
int LIGHT::getWidth()
{
	return _width;
}
NUDE LIGHT::getBodyNude()
{
	return _firstBodyNude;
}
STATE LIGHT::getState()
{
	return _state;
}

void LIGHT::draw()
{
	int color;
	switch (_state)
	{
	case GO:
		color = 160; // đèn xanh
		break;
	case STOP:
		color = 200; // đèn đỏ
		break;
	default:
		std::cout << "Error" << std::endl;
		break;
	}
	for (int i = 0; i < _height; i++)
		for (int j = 0; j < _width; j++)
			drawChar(_firstBodyNude.x + j, _firstBodyNude.y + i, ' ', color);
}
void LIGHT::erase()
{
	for (int i = 0; i < _height; i++)
		for (int j = 0; j < _width; j++)
			drawChar(_firstBodyNude.x, _firstBodyNude.y, ' ', 7);
}
//----------------------------------------------------------------------------ĐIỂM-----------------------------------------------------------------
void SCORE::init()
{
	_count = 0;
	_color = 7;
	_nude = NUDE{ 0, 0 };
}
void SCORE::setScore(const int &count, const int &color, const NUDE &nude)
{
	_count = count;
	_color = color;
	_nude = nude;
}

void SCORE::setCount(const int &count)
{
	_count = count;
}
void SCORE::setColor(const int &color)
{
	_color = color;
}
void SCORE::setNude(const NUDE &nude)
{
	_nude = nude;
}
int SCORE::getCount()
{
	return _count;
}
int SCORE::getColor()
{
	return _color;
}
NUDE SCORE::getNude()
{
	return _nude;
}

void SCORE::draw()
{
	gotoXY(_nude.x, _nude.y);
	textColor(_color);
	std::cout << _count;
	textColor(7);
}
//-----------------------------------------------------------MẢNG CÁC CHƯỚNG NGẠI VẬT-----------------------------------------------------------------
void allocationArrayImpediment(IMPEDIMENT **&impediment, const int &numberRowImpediment, const int &numberColImpediment)
{
	impediment = new IMPEDIMENT*[numberRowImpediment];
	for (int i = 0; i < numberRowImpediment; i++)
		impediment[i] = new IMPEDIMENT[numberColImpediment];
}
void initArrayImpediment(IMPEDIMENT **&impediment, const int &numberRowImpediment, const int &numberColImpediment)
{
	for (int i = 0; i < numberRowImpediment; i++)
		for (int j = 0; j < numberColImpediment; j++)
			impediment[i][j].init();
}
void setArrayImpediment(IMPEDIMENT **&impediment, const int &numberRowImpediment, const int &numberColImpediment)
{
		for (int i = 0; i < numberRowImpediment; i++)
		{
			for (int j = 0; j < numberColImpediment; j++)
			{
				if (i == 0)
					impediment[i][j].setImpediment(3, 13, 78, NUDE{ 1, yRow_1 }, RIGHT, GO, WOOD, ON_RIVER);
				else if (i == 1)
					impediment[i][j].setImpediment(3, 13, 78, NUDE{ WIDTH_BOARD - 14, yRow_2 }, LEFT, GO, WOOD, ON_RIVER);
				else if (i == 2)
					impediment[i][j].setImpediment(3, 13, 15, NUDE{ 1, yRow_3 }, RIGHT, GO, TRUCK, ON_STREET);
				else
					impediment[i][j].setImpediment(3, 13, 15, NUDE{ WIDTH_BOARD - 14, yRow_4 }, LEFT, GO, CAR, ON_STREET);
			}
		}
}
void movingArrayImpediment(IMPEDIMENT **&impediment, const int &numberRowImpediment, const int &numberColImpediment, bool &isFirstTurn)
{
	if (isFirstTurn)// khởi động các toa xe ở lượt đi đầu tiên
	{
		// khởi động các toa đầu
		for (int i = 0; i < numberRowImpediment; i++)
			impediment[i][0].moving();
		// khởi động các toa sau 
		for (int i = 0; i < numberRowImpediment; i++)
		{
			for (int j = 1; j < numberColImpediment; j++)
			{
				if (impediment[i][0].getMoving() == RIGHT) // dãy xe đi sang phải
				{
					if (impediment[i][0].getNudeBody()[0].x >= j*(WIDTH_BOARD - impediment[i][0].getWidth()) / numberColImpediment)
						impediment[i][j].moving();
				}
				else if (impediment[i][0].getMoving() == LEFT)
				{
					if (impediment[i][0].getNudeBody()[0].x <= (numberColImpediment - j)*(WIDTH_BOARD - impediment[i][0].getWidth() - 2) / numberColImpediment)
						impediment[i][j].moving();
				}
				else
					std::cout << "Error" << std::endl;
			}
		}
	}
	else // kể từ lượt đầu trở đi
	{
		for (int i = 0; i < numberRowImpediment; i++)
			for (int j = 0; j < numberColImpediment; j++)
				impediment[i][j].moving();
	}
	// check va chạm với tường (xe nào chạm tường sẽ xuất phát lại vị trí đầu)
	for (int i = 0; i < numberRowImpediment; i++)
	{
		for (int j = 0; j < numberColImpediment; j++)
		{
			if (impediment[i][j].getMoving() == LEFT)
			{
				if (impediment[i][j].getNudeBody()[0].x <= 1) // mép tường trái
				{
					impediment[i][j].erase();
					if (i == 1)
						impediment[i][j].getNudeBody()[0] = NUDE{ WIDTH_BOARD - 14, yRow_2 };
					else if (i == 3)
						impediment[i][j].getNudeBody()[0] = NUDE{ WIDTH_BOARD - 14, yRow_4 };
					isFirstTurn = false;
				}
			}
			else if (impediment[i][j].getMoving() == RIGHT)
			{
				if (impediment[i][j].getNudeBody()[0].x >= WIDTH_BOARD - impediment[i][j].getWidth() - 1) // mép tường phải
				{
					impediment[i][j].erase();
					if (i == 0)
						impediment[i][j].getNudeBody()[0] = NUDE{ 1, yRow_1 };
					else if (i == 2)
						impediment[i][j].getNudeBody()[0] = NUDE{ 1, yRow_3 };
					isFirstTurn = false;
				}
			}
			else
				std::cout << "Error" << std::endl;
		}
	}
}
void cleanArrayGabageImpediment(IMPEDIMENT **&impediment, const int &numberRowImpediment, const int &numberColImpediment)
{
	for (int i = 0; i < numberRowImpediment; i++)
	{
		for (int j = 0; j < numberColImpediment; j++)
			impediment[i][j].cleanGabage();
		delete[] impediment[i];
	}
	delete[] impediment;
}
//----------------------------------------------------------MẢNG CÁC ĐÈN GIAO THÔNG-----------------------------------------------------------------
void allocationArrayLight(LIGHT *&light, const int &numberLight)
{
	light = new LIGHT[numberLight];
}
void initArrayLight(LIGHT *&light, const int &numberLight)
{
	for (int i = 0; i < numberLight; i++)
		light[i].init();
}
void setArrayLight(LIGHT *&light, const int &numberLight)
{
	for (int i = 0; i < numberLight; i++)
	{
		if (i == 0)
			light[i].setLight(1, 4, NUDE{ WIDTH_BOARD - 9, yRow_1 - 1 }, GO);
		else if (i == 1)
			light[i].setLight(1, 4, NUDE{ 5 , yRow_2 - 1 }, GO);
		else if (i == 2)
			light[i].setLight(1, 4, NUDE{ WIDTH_BOARD - 9, yRow_3 - 1 }, GO);
		else if (i == 3)
			light[i].setLight(1, 4, NUDE{ 5, yRow_4 - 1 }, GO);
	}
}
void drawArrayLight(LIGHT *light, const int &numberLight)
{
	for (int i = 0; i < numberLight; i++)
		light[i].draw();
}
void cleanArrayGabageLight(LIGHT *&light)
{
	delete[] light;
}
//-------------------------------------------------MẢNG CÁC NHÂN VẠT QUA ĐƯỜNG THÀNH CÔNG----------------------------------------------------------
void addNewCharacter(CHARACTER newCharacter, CHARACTER *&listCharacter, int &numberCharacter)
{
	listCharacter = (CHARACTER*)realloc(listCharacter, (numberCharacter + 1)*sizeof(CHARACTER));
	listCharacter[numberCharacter] = newCharacter;
	numberCharacter++;
}
void initArrayCharacter(CHARACTER *&listCharacter, int &numberCharacter)
{
	for (int i = 0; i < numberCharacter; i++)
		listCharacter[i].init();
}
void drawArrayCharacter(CHARACTER *character, const int &numberCharacter)
{
	for (int i = 0; i < numberCharacter; i++)
		character[i].draw();
}
void cleanArrayGabageCharacter(CHARACTER *&listCharacter, const int &numberCharacter)
{
	for (int i = 0; i < numberCharacter; i++)
		listCharacter[i].cleanGabage();
	free(listCharacter);
}
//-------------------------------------------------------------------CÁC HÀM KIỂM TRA--------------------------------------------------------------
bool isCrossingStreet(CHARACTER character)
{
	return character.getNudeBody()[0].y < HEIGHT_BOARD / 6;
}
bool isImpact(CHARACTER character, 
			  CHARACTER *listCharacter, const int &numberCharacter, 
	          IMPEDIMENT **impediment, const int &numberRowImpediment, const int &numberColImpedimnet)
{
	// check va chạm với xe
	for (int i = 0; i < numberRowImpediment; i++)
	{
		for (int j = 0; j < numberColImpedimnet; j++)
			for (int k = 0; k < character.getHeight()*character.getWidth(); k++)
				for (int l = 0; l < impediment[i][j].getHeight()*impediment[i][j].getWidth(); l++)
					if (character.getNudeBody()[k].x == impediment[i][j].getNudeBody()[l].x && character.getNudeBody()[k].y == impediment[i][j].getNudeBody()[l].y)
						return true;
	}
	// check va chạm với nhân vật qua đường trước đó
	for (int i = 0; i < numberCharacter; i++)
	{
		for (int j = 0; j < character.getHeight()*character.getWidth(); j++)
			for (int k = 0; k < character.getHeight()*character.getWidth(); k++)
				if (character.getNudeBody()[k].x == listCharacter[i].getNudeBody()[j].x && character.getNudeBody()[k].y == listCharacter[i].getNudeBody()[j].y)
					return true;
	}
	return false;
}
//-----------------------------------------------------------------CÁC HÀM TẠO HIỆU ỨNG-------------------------------------------------------------
void readFile(const char *fileName, const int &color)
{
	char *A = NULL; int nA = 0;
	FILE *fileIn;
	fopen_s(&fileIn, fileName, "r");
	if (!fileIn)
		std::cout << "Error read file" << std::endl;
	else
	{
		while (!feof(fileIn))
		{
			A = (char*)realloc(A, sizeof(char)*(nA + 1));
			fscanf_s(fileIn, "%c", &A[nA++]);
		}
	}
	fclose(fileIn);
	// Xuất
	for (int i = 0; i < nA - 1; i++)
	{
		textColor(color);
		std::cout << A[i];
		textColor(7);
	}
	free(A);
}
void effectLoading()
{
	NUDE pos = NUDE{ 70, 20 };
	for (int j = 0; j < 60; j++)
	{
		for (int i = 0; i < 3; i++)
			drawChar(pos.x + j, pos.y + i, ' ', 160);
		Sleep(20);
	}
}
void effectLevelUp()
{
	char *levelUp[3];
	levelUp[0] = " /\\            /\\ ";
	levelUp[1] = "/||\\ LEVEL UP /||\\";
	levelUp[2] = " ||            || ";
	NUDE pos = NUDE{ WIDTH_BOARD + 2, HEIGHT_BOARD - 4 };

	while (pos.y >= 3)
	{
		// vẽ
		for (int j = 0; j < 3; j++)
			for (int k = 0; k < 18; k++)
				drawChar(pos.x + k, pos.y + j, levelUp[j][k], 10);
		Sleep(50);
		// xóa
		for (int j = 0; j < 3; j++)
			for (int k = 0; k < 18; k++)
				drawChar(pos.x + k, pos.y + j, ' ', 7);
		// di chuyển
		pos.y -= 3;
	}
}
void effectHighScore()
{
	char *highScore[3];
	highScore[0] = "==---------------==";
	highScore[1] = "||--HIGHT SCORE--||";
	highScore[2] = "==---------------==";
	NUDE pos = NUDE{ (WIDTH_BOARD - 18) / 2, (HEIGHT_BOARD - 3) / 2 };
	for (int i = 0; i < 4; i++)
	{
		if (i % 2 == 0)
		{
			for (int j = 0; j < 3; j++)
				for (int k = 0; k < 19; k++)
					drawChar(pos.x + k, pos.y + j, highScore[j][k], 94);
		}
		else
		{
			for (int j = 0; j < 3; j++)
				for (int k = 0; k < 19; k++)
					drawChar(pos.x + k, pos.y + j, ' ', 7);
		}
		Sleep(200);
	}
}
void exitOrContinue(char &choose)
{
	gotoXY(WIDTH_BOARD + 2, HEIGHT_BOARD - 5);
	std::cout << "========================< GAME OVER >============================";
	gotoXY(WIDTH_BOARD + 2, HEIGHT_BOARD - 5 + 1);
	std::cout << "DO YOU WANT TO PLAY AGAIN ? ~~ (PRESS 'Y' IS \"YES\" OR 'N' IS \"NO\")";
	gotoXY(WIDTH_BOARD + 2 + 24, HEIGHT_BOARD - 5 + 2);
	std::cout << "YES        NO";
	gotoXY(WIDTH_BOARD + 2 + 24 + 7, HEIGHT_BOARD - 5 + 3);
	std::cin >> choose; std::cin.ignore();
	if (choose == 'N' || choose == 'n')
	{
		gotoXY(WIDTH_BOARD + 2 + 24 + 11, HEIGHT_BOARD - 5 + 2);
		textColor(78);
		std::cout << "NO" << std::endl;
		textColor(7);
	}
	else
	{
		gotoXY(WIDTH_BOARD + 2 + 24, HEIGHT_BOARD - 5 + 2);
		textColor(78);
		std::cout << "YES" << std::endl;
		textColor(7);
	}
}
//-------------------------------------------------------------------CÁC HÀM MENU------------------------------------------------------------------
void option(BOARD board,
	int &LEVEL, int &SPEED, int &maxCharacter,
	CHARACTER &character,
	CHARACTER *&listCharacter, int &numberCharacter,
	IMPEDIMENT **&impediment, int &numberRowImpediment, int &numberColImpediment, bool &isFirstTurn,
	LIGHT *&light, int &numberLight, 
	SCORE &score, int &highScore, int &count,
	bool &isExit)
{
	while (true)
	{
		if (_kbhit())
		{
			char choose = _getch();
			if (choose == '1') // 1. PLAY
			{
				system("cls");
				effectLoading();
				system("cls");
				readFile("SCORE.txt", 10);
				readFile("GUIDE.txt", 78);
				board.draw();
				break;
			}
			else if (choose == '2') // 2.CONTINUE
			{
				system("cls");
				readFile("LOAD_GAME.txt", 10);
				effectLoading();
				loadInfoGame(LEVEL, SPEED, maxCharacter, 
					character, 
					listCharacter, numberCharacter, 
					impediment, numberRowImpediment, numberColImpediment, 
					isFirstTurn, 
					light, numberLight,
					score, highScore);
				count = score.getCount();
				system("cls");
				readFile("SCORE.txt", 10);
				readFile("GUIDE.txt", 78);
				board.draw();
				break;
			}
			else if (choose == '3') // 3.HIGHT SCORE
			{
				system("cls");
				effectLoading();
				system("cls");
				readFile("HIGH_SCORE.txt", 10);
				gotoXY(95, 23);
				std::cout << highScore;
				while (true)
				{
					if (_kbhit())
						break;
				}
				system("cls");
				readFile("SCORE.txt", 10);
				readFile("GUIDE.txt", 78);
				board.draw();
				break;
			}
			else if (choose == '4') // 4.LEVEL
			{
				system("cls");
				effectLoading();
				system("cls");
				readFile("LEVEL.txt", 10);
				gotoXY(92, 22);
				std::cin >> LEVEL; std::cin.ignore();
				// cài đặt lại nhân vật chính
				character.setNudeBody(NUDE{ WIDTH_BOARD / 2, HEIGHT_BOARD - 5 });
				// cài đặt lại các trạng thái ban đầu
				cleanArrayGabageCharacter(listCharacter, numberCharacter);
				listCharacter = NULL;
				numberCharacter = 0;
				for (int i = 0; i < numberLight; i++)
					light[i].setState(GO);
				// bắt dầu màn tiếp theo
				play(LEVEL, SPEED, maxCharacter, impediment, numberRowImpediment, numberColImpediment, isFirstTurn);
				system("cls");
				readFile("SCORE.txt", 10);
				readFile("GUIDE.txt", 78);
				board.draw();
				break;
			}
			else if (choose == '5') // 5.SETTING
			{
				system("cls");
				effectLoading();
				system("cls");
				setting(character, impediment, numberRowImpediment, numberColImpediment);
				system("cls");
				readFile("SCORE.txt", 10);
				readFile("GUIDE.txt", 78);
				board.draw();
				break;
			}
			else if (choose == '6')
			{
				isExit = true;
				break;
			}
		}
	}
}
void saveInfoGame(const int &LEVEL, const int &SPEED, const int &maxCharacter,
	CHARACTER character,
	CHARACTER *listCharacter, const int &numberCharacter,
	IMPEDIMENT **impediment, const int &numberRowImpediment, const int &numberColImpediment, const bool &isFirstTurn, 
	LIGHT *light, const int &numberLight,
	SCORE score, const int &highScore)
{
	char *nameFileInfoGame = NULL; int nNameFileInfoGame = 0;
	char c;
	// nhập tên file cần lưu
	gotoXY(0, HEIGHT_BOARD + 1);
	std::cout << "Please input file name you want to save: ";
	while (true)
	{
		c = getchar();
		nameFileInfoGame = (char*)realloc(nameFileInfoGame, (nNameFileInfoGame + 1)*sizeof(char));
		if (c != '\n')
		{
			nameFileInfoGame[nNameFileInfoGame] = c;
			nNameFileInfoGame++;
		}
		else
		{
			nameFileInfoGame[nNameFileInfoGame] = '\0';
			break;
		}
	}
	// mở fileOut để ghi vào
	FILE *fileOut;
	fopen_s(&fileOut, nameFileInfoGame, "w");
	// ghi độ khó màn chơi
	fprintf_s(fileOut, "%d", LEVEL); fprintf_s(fileOut, "%c", '\n');
	fprintf_s(fileOut, "%d", SPEED); fprintf_s(fileOut, "%c", '\n');
	fprintf_s(fileOut, "%d", maxCharacter); fprintf_s(fileOut, "%c%c", '\n', '\n');
	// ghi nhân vật chính
	fprintf_s(fileOut, "%d", character.getHeight()); fprintf_s(fileOut, "%c", '\n');
	fprintf_s(fileOut, "%d", character.getWidth()); fprintf_s(fileOut, "%c", '\n');
	fprintf_s(fileOut, "%d", character.getColor()); fprintf_s(fileOut, "%c", '\n');
	fprintf_s(fileOut, "%d", character.getNudeBody()[0].x); fprintf_s(fileOut, "%c", '\n');
	fprintf_s(fileOut, "%d", character.getNudeBody()[0].y); fprintf_s(fileOut, "%c", '\n');
	fprintf_s(fileOut, "%d", character.getMoving()); fprintf_s(fileOut, "%c", '\n');
	fprintf_s(fileOut, "%d", character.getState()); fprintf_s(fileOut, "%c", '\n');
	fprintf_s(fileOut, "%d", character.getPlace()); fprintf_s(fileOut, "%c%c", '\n', '\n');
	// ghi mảng nhân vật đã băng qua đường thành công
	fprintf_s(fileOut, "%d", numberCharacter); fprintf_s(fileOut, "%c", '\n');
	for (int i = 0; i < numberCharacter; i++)
	{
		fprintf_s(fileOut, "%d", listCharacter[i].getHeight()); fprintf_s(fileOut, "%c", '\n');
		fprintf_s(fileOut, "%d", listCharacter[i].getWidth()); fprintf_s(fileOut, "%c", '\n');
		fprintf_s(fileOut, "%d", listCharacter[i].getColor()); fprintf_s(fileOut, "%c", '\n');
		fprintf_s(fileOut, "%d", listCharacter[i].getNudeBody()[0].x); fprintf_s(fileOut, "%c", '\n');
		fprintf_s(fileOut, "%d", listCharacter[i].getNudeBody()[0].y); fprintf_s(fileOut, "%c", '\n');
		fprintf_s(fileOut, "%d", listCharacter[i].getMoving()); fprintf_s(fileOut, "%c", '\n');
		fprintf_s(fileOut, "%d", listCharacter[i].getState()); fprintf_s(fileOut, "%c", '\n');
		fprintf_s(fileOut, "%d", listCharacter[i].getPlace()); fprintf_s(fileOut, "%c%c", '\n', '\n');
	}
	// ghi mảng vật cản
	fprintf_s(fileOut, "%d", numberRowImpediment); fprintf_s(fileOut, "%c", '\n');
	fprintf_s(fileOut, "%d", numberColImpediment); fprintf_s(fileOut, "%c", '\n');
	fprintf_s(fileOut, "%d", isFirstTurn); fprintf_s(fileOut, "%c", '\n');
	for (int i = 0; i < numberRowImpediment; i++)
	{
		for (int j = 0; j < numberColImpediment; j++)
		{
			fprintf_s(fileOut, "%d", impediment[i][j].getHeight()); fprintf_s(fileOut, "%c", '\n');
			fprintf_s(fileOut, "%d", impediment[i][j].getWidth()); fprintf_s(fileOut, "%c", '\n');
			fprintf_s(fileOut, "%d", impediment[i][j].getColor()); fprintf_s(fileOut, "%c", '\n');
			fprintf_s(fileOut, "%d", impediment[i][j].getNudeBody()[0].x); fprintf_s(fileOut, "%c", '\n');
			fprintf_s(fileOut, "%d", impediment[i][j].getNudeBody()[0].y); fprintf_s(fileOut, "%c", '\n');
			fprintf_s(fileOut, "%d", impediment[i][j].getMoving()); fprintf_s(fileOut, "%c", '\n');
			fprintf_s(fileOut, "%d", impediment[i][j].getState()); fprintf_s(fileOut, "%c", '\n');
			fprintf_s(fileOut, "%d", impediment[i][j].getShape()); fprintf_s(fileOut, "%c", '\n');
			fprintf_s(fileOut, "%d", impediment[i][j].getPlace()); fprintf_s(fileOut, "%c%c", '\n', '\n');
		}
	}
	// ghi mảng đèn giao thông
	fprintf_s(fileOut, "%d", numberLight); fprintf_s(fileOut, "%c", '\n');
	for (int i = 0; i < numberLight; i++)
	{
		fprintf_s(fileOut, "%d", light[i].getHeight()); fprintf_s(fileOut, "%c", '\n');
		fprintf_s(fileOut, "%d", light[i].getWidth()); fprintf_s(fileOut, "%c", '\n');
		fprintf_s(fileOut, "%d", light[i].getBodyNude().x); fprintf_s(fileOut, "%c", '\n');
		fprintf_s(fileOut, "%d", light[i].getBodyNude().y); fprintf_s(fileOut, "%c", '\n');
		fprintf_s(fileOut, "%d", light[i].getState()); fprintf_s(fileOut, "%c%c", '\n', '\n');
	}
	// ghi điểm
	fprintf_s(fileOut, "%d", score.getCount()); fprintf_s(fileOut, "%c", '\n');
	fprintf_s(fileOut, "%d", score.getColor()); fprintf_s(fileOut, "%c", '\n');
	fprintf_s(fileOut, "%d", score.getNude().x); fprintf_s(fileOut, "%c", '\n');
	fprintf_s(fileOut, "%d", score.getNude().y); fprintf_s(fileOut, "%c", '\n');
	fprintf_s(fileOut, "%d", highScore);

	fclose(fileOut);

	delete[] nameFileInfoGame;
}
void loadInfoGame(int &LEVEL, int &SPEED, int &maxCharacter,
	CHARACTER &character,
	CHARACTER *&listCharacter, int &numberCharacter,
	IMPEDIMENT **&impediment, int &numberRowImpediment, int &numberColImpediment, bool &isFirstTurn,
	LIGHT *&light, int &numberLight,
	SCORE &score, int &highScore)
{
	char *nameFileInfoGame = NULL; int nNameFileInfoGame = 0;
	char c;
	int height, width, color, bodyX, bodyY ,move, state, shape, place, isFirst, count;
	// nhập tên file cần load
	gotoXY(0, HEIGHT_BOARD + 1);
	std::cout << "Please input file name you want to load: ";
	while (true)
	{
		c = getchar();
		if (c != '\n')
		{
			nameFileInfoGame = (char*)realloc(nameFileInfoGame, (nNameFileInfoGame + 1)*sizeof(char));
			nameFileInfoGame[nNameFileInfoGame] = c;
			nNameFileInfoGame++;
		}
		else
		{
			nameFileInfoGame = (char*)realloc(nameFileInfoGame, (nNameFileInfoGame + 1)*sizeof(char));
			nameFileInfoGame[nNameFileInfoGame] = '\0';
			break;
		}
	}
	FILE *fileIn;
	fopen_s(&fileIn, nameFileInfoGame, "r");
	if (!fileIn)
	{
		std::cout << "Error" << std::endl;
		return;
	}
	// đọc độ khó màn chơi
	fscanf_s(fileIn, "%d", &LEVEL);
	fscanf_s(fileIn, "%d", &SPEED);
	fscanf_s(fileIn, "%d", &maxCharacter);
	// đọc nhân vật chính
	fscanf_s(fileIn, "%d", &height);
	fscanf_s(fileIn, "%d", &width); 
	fscanf_s(fileIn, "%d", &color); 
	fscanf_s(fileIn, "%d", &bodyX);
	fscanf_s(fileIn, "%d", &bodyY); 
	fscanf_s(fileIn, "%d", &move); 
	fscanf_s(fileIn, "%d", &state);
	fscanf_s(fileIn, "%d", &place);
	character.setCharacter(height, width, color, NUDE{ bodyX, bodyY }, (MOVING)move, (STATE)state, (PLACE)place);
	// đọc mảng nhân vật đã băng qua đường thành công
	initArrayCharacter(listCharacter, numberCharacter);
	fscanf_s(fileIn, "%d", &numberCharacter); 
	listCharacter = (CHARACTER*)realloc(listCharacter, numberCharacter*sizeof(CHARACTER));
	for (int i = 0; i < numberCharacter; i++)
	{
		fscanf_s(fileIn, "%d", &height);
		fscanf_s(fileIn, "%d", &width); 
		fscanf_s(fileIn, "%d", &color); 
		fscanf_s(fileIn, "%d", &bodyX);
		fscanf_s(fileIn, "%d", &bodyY); 
		fscanf_s(fileIn, "%d", &move); 
		fscanf_s(fileIn, "%d", &state);
		fscanf_s(fileIn, "%d", &place);
		listCharacter[i].setCharacter(height, width, color, NUDE{ bodyX, bodyY }, (MOVING)move, (STATE)state, (PLACE)place);
	}
	// đọc mảng vật cản
	fscanf_s(fileIn, "%d", &numberRowImpediment);
	fscanf_s(fileIn, "%d", &numberColImpediment);
	fscanf_s(fileIn, "%d", &isFirst); 
	isFirstTurn = (bool)isFirst;
	impediment = new IMPEDIMENT*[numberRowImpediment];
	for (int i = 0; i < numberRowImpediment; i++)
		impediment[i] = new IMPEDIMENT[numberColImpediment];
	for (int i = 0; i < numberRowImpediment; i++)
	{
		for (int j = 0; j < numberColImpediment; j++)
		{
			fscanf_s(fileIn, "%d", &height);
			fscanf_s(fileIn, "%d", &width); 
			fscanf_s(fileIn, "%d", &color);
			fscanf_s(fileIn, "%d", &bodyX);
			fscanf_s(fileIn, "%d", &bodyY);
			fscanf_s(fileIn, "%d", &move); 
			fscanf_s(fileIn, "%d", &state); 
			fscanf_s(fileIn, "%d", &shape);
			fscanf_s(fileIn, "%d", &place);
			impediment[i][j].setImpediment(height, width, color, NUDE{ bodyX, bodyY }, (MOVING)move, (STATE)state, (SHAPE)shape, (PLACE)place);
		}
	}
	// đọc mảng đèn giao thông
	fscanf_s(fileIn, "%d", &numberLight);
	light = new LIGHT[numberRowImpediment];
	for (int i = 0; i < numberLight; i++)
	{
		fscanf_s(fileIn, "%d", &height);
		fscanf_s(fileIn, "%d", &width); 
		fscanf_s(fileIn, "%d", &bodyX);
		fscanf_s(fileIn, "%d", &bodyY); 
		fscanf_s(fileIn, "%d", &state);
		light[i].setLight(height, width, NUDE{ bodyX, bodyY }, (STATE)state);
	}
	// đọc điểm
	fscanf_s(fileIn, "%d", &count);
	fscanf_s(fileIn, "%d", &color);
	fscanf_s(fileIn, "%d", &bodyX);
	fscanf_s(fileIn, "%d", &bodyY);
	score.setScore(count, color, NUDE{ bodyX, bodyY });
	fscanf_s(fileIn, "%d", &highScore);

	fclose(fileIn);

	delete[] nameFileInfoGame;
}
void setting(CHARACTER &character,
	IMPEDIMENT **impediment, const int &numberRowImpediment, const int &numberColImpediment)
{
	readFile("SETTINGS.txt", 10);
	int count = 0;
	for (int i = 0; i < 17; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			textColor(++count);
			std::cout << std::setw(7) << count << ".code";
			textColor(7);
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
	int color;
	std::cout << "CHARACTER: "; std::cin >> color; std::cin.ignore();  character.setColor(color);
	std::cout << "IMPDIMENT: " << std::endl;
	std::cout << "\t+ Color row 1 : "; std::cin >> color; std::cin.ignore();
	for (int j = 0; j < numberColImpediment; j++)
		impediment[0][j].setColor(color);
	std::cout << "\t+ Color row 2 : "; std::cin >> color; std::cin.ignore();
	for (int j = 0; j < numberColImpediment; j++)
		impediment[1][j].setColor(color);
	std::cout << "\t+ Color row 3 : "; std::cin >> color; std::cin.ignore();
	for (int j = 0; j < numberColImpediment; j++)
		impediment[2][j].setColor(color);
	std::cout << "\t+ Color row 4 : "; std::cin >> color; std::cin.ignore();
	for (int j = 0; j < numberColImpediment; j++)
		impediment[3][j].setColor(color);
}
void play(int &LEVEL, int &SPEED, int &maxCharacter, 
	IMPEDIMENT **&impediment, const int &numberRowImpediment, int &numberColImpediment, bool &isFirstTurn)
{
	cleanArrayGabageImpediment(impediment, numberRowImpediment, numberColImpediment);
	switch (LEVEL)
	{
	case 1:
		SPEED = 20;
		maxCharacter = 1;
		numberColImpediment = 1;
		break;
	case 2:
		SPEED = 30;
		maxCharacter = 2;
		numberColImpediment = 2;
		break;
	case 3:
		SPEED = 20;
		maxCharacter = 3;
		numberColImpediment = 2;
		break;
	case 4:
		SPEED = 10;
		maxCharacter = 4;
		numberColImpediment = 3;
		break;
	case 5:
		SPEED = 20;
		maxCharacter = 5;
		numberColImpediment = 4;
		break;
	case 6:
		SPEED = 0;
		maxCharacter = 6;
		numberColImpediment = 4;
		break;
	case 7:
		SPEED = 20;
		maxCharacter = 7;
		numberColImpediment = 5;
		break;
	case 8:
		SPEED = 10;
		maxCharacter = 8;
		numberColImpediment = 5;
		break;
	case 9:
		SPEED = 0;
		maxCharacter = 9;
		numberColImpediment = 5;
		break;
	case 10:
		SPEED = 0;
		maxCharacter = 10;
		numberColImpediment = 6;
		break;
	default:
		LEVEL = 1;
		std::cout << "Error" << std::endl;
		break;
	}
	allocationArrayImpediment(impediment, numberRowImpediment, numberColImpediment);
	setArrayImpediment(impediment, numberRowImpediment, numberColImpediment);
	isFirstTurn = true;
}
//-------------------------------------------------------------------CÁC HÀM XỬ LÍ------------------------------------------------------------------
void processingDead(char &choose,
	CHARACTER &character,
	IMPEDIMENT **impediment, const int &numberRowImpediment, const int &numberColImpediment)
{
	// vẽ lại mảng impediment
	for (int i = 0; i < numberRowImpediment; i++)
		for (int j = 0; j < numberColImpediment; j++)
			impediment[i][j].draw();
	// vẽ nhân vật khi chết
	character.setState(DEAD);
	character.erase();
	character.draw();
	// đưa ra lựa chọn cho người chơi
	exitOrContinue(choose);
}
void processingSwitchToNextPlay(BOARD board,
	int &LEVEL, int &SPEED, int &maxCharacter,
	CHARACTER &character,
	CHARACTER *&listCharacter, int &numberCharacter,
	IMPEDIMENT **&impediment, int &numberRowImpediment, int &numberColImpediment, bool &isFirstTurn,
	LIGHT *&light, int &numberLight)
{
	// cài đặt lại nhân vật chính
	character.erase();
	character.draw();
	character.setNudeBody(NUDE{ WIDTH_BOARD / 2, HEIGHT_BOARD - 5 });
	// vẽ lại mảng impediment
	for (int i = 0; i < numberRowImpediment; i++)
		for (int j = 0; j < numberColImpediment; j++)
			impediment[i][j].draw();
	LEVEL++; // tăng độ khó
	if (LEVEL > 10)
		processingWin();
	effectLevelUp();
	// cài đặt lại các trạng thái ban đầu
	cleanArrayGabageCharacter(listCharacter, numberCharacter);
	listCharacter = NULL;
	numberCharacter = 0;
	for (int i = 0; i < numberLight; i++)
		light[i].setState(GO);
	// bắt dầu màn tiếp theo
	play(LEVEL, SPEED, maxCharacter, impediment, numberRowImpediment, numberColImpediment, isFirstTurn);
	system("cls");
	readFile("SCORE.txt", 10);
	readFile("GUIDE.txt", 78);
	board.draw();
}
void processingWin()
{
	system("cls");
	readFile("WIN.txt", 11);
	while (true)
	{
		if (_kbhit())
			break;
	}
	system("cls");
}