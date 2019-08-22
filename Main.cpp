#include"Function.h"

int main()
{
	resizeConsole(1400, 800);
	PlaySoundA("Music.wav", NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
	// ------------------------------------------------------------------------------------------KHAI BÁO CÁC BIẾN-------------------------------------------------------------------------------
	int LEVEL, SPEED, maxCharacter;// LEVEL: độ khó màn chơi  ;  SPEED: tốc độ chạy của xe  ;  maxCharacter: số lượng nhân vật cần đạt được trong 1 màn chơi
	char choose = 'N', key; // choose: biến dùng cho vòng lặp do-while ; key: nhận mã từ bàn phím
	bool isExit = false;
	int timeStop = 0;

	BOARD board; // khung bao bên ngoài

	CHARACTER character; // nhân vật chính

	IMPEDIMENT **impediment; // chướng ngại vật (xe)
	int numberRowImpediment, numberColImpediment;// số dòng và số cột 
	bool isFirstTurn; // biến cờ ( đánh dấu có phải là lượt đi đầu của các toa xe )  

	LIGHT *light; // đèn giao thông
	int numberLight;

	CHARACTER *listCharacter; // các nhân vật qua đường thành công
	int numberCharacter;

	SCORE score; // điểm
	int count;
	int highScore = 0;
	do//---------------------------------------------------------------------------------------BẮT ĐẦU CHƯƠNG TRÌNH CHÍNH-----------------------------------------------------------------------------------------------
	{
		system("cls");
		readFile("MENU.txt", 14); // giao diện trang menu

		board.init();
		board.setBoard(HEIGHT_BOARD, WIDTH_BOARD, 95);

		character.init();
		character.setCharacter(3, 3, 207, NUDE{ WIDTH_BOARD / 2, HEIGHT_BOARD - 5 }, WAIT, LIVING, ON_STREET);

		numberRowImpediment = 4; // mặc định có 4 dòng
		numberColImpediment = 1; // bắt đầu với 1 toa xe
		isFirstTurn = true; // mỗi lần xe khởi động đều là lượt đi đầu
		allocationArrayImpediment(impediment, numberRowImpediment, numberColImpediment);
		initArrayImpediment(impediment, numberRowImpediment, numberColImpediment);

	    numberLight = numberRowImpediment; // số đèn giao thông bằng số dòng xe
		allocationArrayLight(light, numberLight);
		initArrayLight(light, numberLight);
		setArrayLight(light, numberLight);

		listCharacter = NULL;
		numberCharacter = 0;

		score.init();
		score.setScore(0, 11, NUDE{ WIDTH_BOARD + 37, 11 });
		count = 0;

		LEVEL = 1;
		play(LEVEL, SPEED, maxCharacter, 
			impediment, numberRowImpediment, numberColImpediment, isFirstTurn); // bắt đầu bằng màn 1
		option(board, 
			LEVEL, SPEED, maxCharacter, 
			character, 
			listCharacter, numberCharacter, 
			impediment, numberRowImpediment, numberColImpediment, isFirstTurn, 
			light, numberLight,
			score, highScore, count, 
			isExit); // các tùy chọn menu
		while (true)
		{
			// check có thoát game hay không
			if (isExit)
				break;
			drawArrayLight(light, numberLight); // vẽ đèn giao thông
			if (_kbhit()) // nhận mã phím-------------------------------------------------------------------------------------------------------------------------------------
			{
				key = _getch();
				if (key == ESC)
					break;
				switch (key)
				{
				case 'W':case 'w':
					character.setMoving(UP);
					break;
				case 'S':case 's':
					character.setMoving(DOWN);
					break;
				case 'A':case 'a':
					character.setMoving(LEFT);
					break;
				case 'D':case 'd':
					character.setMoving(RIGHT);
					break;
				case 'N': case 'n':
					saveInfoGame(LEVEL, SPEED, maxCharacter, 
						character, 
						listCharacter, numberCharacter, 
						impediment, numberRowImpediment, numberColImpediment, isFirstTurn, 
						light, numberLight, 
						score, highScore);
					system("cls");
					readFile("SCORE.txt", 10);
					readFile("GUIDE.txt", 78);
					board.draw();
					continue;
				case 'L': case 'l':
					loadInfoGame(LEVEL, SPEED, maxCharacter, 
						character, 
						listCharacter, numberCharacter, 
						impediment, numberRowImpediment, numberColImpediment, isFirstTurn, 
						light, numberLight, 
						score, highScore);
					count = score.getCount();
					system("cls");
					readFile("SCORE.txt", 10);
					readFile("GUIDE.txt", 78);
					board.draw();
					continue;
				case 'P':case'p':
					for (int i = 0; i < numberRowImpediment; i++)
					{
						for (int j = 0; j < numberColImpediment; j++)
							impediment[i][j].setState(STOP);
						light[i].setState(STOP);
					}
					break;
				case'R':case'r':
					for (int i = 0; i < numberRowImpediment; i++)
					{
						for (int j = 0; j < numberColImpediment; j++)
							impediment[i][j].setState(GO);
						light[i].setState(GO);
					}
					break;
				case 'M':case'm':
					system("cls");
					readFile("MENU.txt", 14);
					option(board, 
						LEVEL, SPEED, maxCharacter, 
						character, 
						listCharacter, numberCharacter, 
						impediment, numberRowImpediment, numberColImpediment, isFirstTurn, 
						light, numberLight, 
						score, highScore, count,
						isExit);
					continue;
				case 'E':case'e':
					isExit = true;
					break;
				case '1':
					for (int j = 0; j < numberColImpediment; j++)
						impediment[0][j].setState(STOP);
					light[0].setState(STOP);
					break;
				case '2':
					for (int j = 0; j < numberColImpediment; j++)
						impediment[1][j].setState(STOP);
					light[1].setState(STOP);
					break;
				case '3':
					for (int j = 0; j < numberColImpediment; j++)
						impediment[2][j].setState(STOP);
					light[2].setState(STOP);
					break;
				case '4':
					for (int j = 0; j < numberColImpediment; j++)
						impediment[3][j].setState(STOP);
					light[3].setState(STOP);
					break;
				default:
					break;
				}
			}//---------------------------------------------------------------------------------------------------------------------------------------------
			movingArrayImpediment(impediment, numberRowImpediment, numberColImpediment, isFirstTurn); // vận hành các toa xe
			character.moving(); // nhân vật di chuyển theo mã phím
			drawArrayCharacter(listCharacter, numberCharacter);
			score.draw();
			//-------------------------------------------------------------KIỂM TRA VA CHẠM----------------------------------------------------------------
			if (isImpact(character, listCharacter, numberCharacter, impediment, numberRowImpediment, numberColImpediment))
			{
				if (character.getPlace() == ON_STREET) // va chạm xe HOẶC va chạm nhân vật đã qua đường 
				{
					processingDead(choose, character, impediment, numberRowImpediment, numberColImpediment);
					Sleep(1000);
					break;
				}
				else// va chạm khúc gỗ 
				{
					if (character.getNudeBody()[0].y == yRow_1)
					{
						if (light[0].getState() == GO)
							character.setMoving(RIGHT);
					}
					else
					{
						if (light[1].getState() == GO)
							character.setMoving(LEFT);
					}
				}
			}
			else if (character.getPlace() == ON_RIVER) // rơi xuống nước
			{
				processingDead(choose, character, impediment, numberRowImpediment, numberColImpediment);
				Sleep(1000);
				break;
			}
			//-----------------------------------------------------KIỂM TRA NHÂN VẬT CÓ QUA ĐƯỜNG THÀNH CÔNG-------------------------------------------------
			if (isCrossingStreet(character))
			{
				addNewCharacter(character, listCharacter, numberCharacter); // thêm vào danh sách
				character.erase();
				// cộng điểm
				count += 100;
				score.setCount(count);
				// ghi nhận điểm cao
				if (highScore < score.getCount())
				{
					highScore = score.getCount();
					effectHighScore();
				}
				// check có đủ tiêu chuẩn qua màn
				if (numberCharacter == maxCharacter) // nếu bằng số lượng yêu cầu của màn chơi
				{
					score.draw();
					processingSwitchToNextPlay(board, 
						LEVEL, SPEED, maxCharacter, 
						character,
						listCharacter, numberCharacter, 
						impediment, numberRowImpediment, numberColImpediment, isFirstTurn, 
						light, numberLight);
					continue;
				}

				character.setNudeBody(NUDE{ WIDTH_BOARD / 2, HEIGHT_BOARD - 5 });
			}
			//------------------------------------------------------------RANDOM THỜI GIAN DỪNG KHI LÊN CẤP----------------------------------------------------------
			if (LEVEL >= 5)
			{
				timeStop++;
				switch (timeStop)
				{
				case 100:
					for (int i = 0; i < numberRowImpediment; i++)
					{
						for (int j = 0; j < numberColImpediment; j++)
							impediment[i][j].setState(STOP);
						light[i].setState(STOP);
					}
					continue;
				case 150:
					for (int i = 0; i < numberRowImpediment; i++)
					{
						for (int j = 0; j < numberColImpediment; j++)
							impediment[i][j].setState(GO);
						light[i].setState(GO);
					}
					timeStop = 0;
					break;
				default:
					break;
				}
			}
			Sleep(SPEED);
		}
		// hàm hủy
		character.cleanGabage();
		cleanArrayGabageImpediment(impediment, numberRowImpediment, numberColImpediment);
		cleanArrayGabageLight(light);
		cleanArrayGabageCharacter(listCharacter, numberCharacter);
	} while (choose != 'N' && choose != 'n' && isExit == false);

	_getch();
	return 0;
}