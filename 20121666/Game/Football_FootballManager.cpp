#include "Football_FootballManager.h"

FootballManager::FootballManager() 
{
	char playerform[] = "�����ܦ���";

	fStageInfo[0] = new StageInfo(3, 1000 * 20, 1, 20, 3, 300, 1);
	fStageInfo[1] = new StageInfo(10, 1000 * 30, 2, 20, 5, 300, 1);

	fPlayer = new Player(4, 0, 20, 22);
	fPlayer->SetnX(fPlayer->nMoveX - fPlayer->nCenterX);
	
	g_nStage = 0;
	g_strPlayer = new char[sizeof(playerform)];
	for (int i = 0; i < sizeof(playerform); i++)
		g_strPlayer[i] = playerform[i];

	g_LimitTime = fStageInfo[g_nStage]->GetLimitTime();  // ���� �ð� ����
	g_nGoalBallCount = fStageInfo[g_nStage]->GetGoalBall(); // ��ǥ ���� ����

	g_nLength = strlen(g_strPlayer);

	//���� �ʱ�ȭ
	fBall = new Ball(true, fPlayer->nMoveX, fPlayer->nMoveY -1, 100);
	
	//��� �ʱ�ȭ
	fGoalpost = new Goalpost(fStageInfo[g_nStage]->GetGoalDaeX(), fStageInfo[g_nStage]->GetGoalDaeY(), 
		fStageInfo[g_nStage]->GetGoalDaeLength(), fStageInfo[g_nStage]->GetnDist(), 
		fStageInfo[g_nStage]->GetMoveTime(), clock());

	//ȿ��
	fEffect = new Effect();
	fEffect->SetStartTime(2000); // 2�� ����
	g_nGoal = 0; //�������� �Ϸ� ����
	g_UpdateOldTime = clock();
	g_nBallCount = 0; // ������ ���� ����

	g_GameState = INIT;
}
FootballManager::~FootballManager()
{
}

void FootballManager::Init()
{
	fPlayer->nCenterX = 4;
	fPlayer->nCenterY = 0;
	fPlayer->nMoveX = 20;
	fPlayer->nMoveY = 22;
	fPlayer->SetnX(fPlayer->nMoveX - fPlayer->nCenterX);

	g_LimitTime = fStageInfo[g_nStage]->GetLimitTime();  // ���� �ð� ����
	g_nGoalBallCount = fStageInfo[g_nStage]->GetGoalBall(); // ��ǥ ���� ����

	fBall->SetIsReady(true);
	fBall->nMoveX = fPlayer->nMoveX;
	fBall->nMoveY = fPlayer->nMoveY -1;
	fBall->MoveTime = 100;

	fGoalpost->Init(fStageInfo[g_nStage]->GetGoalDaeX(), fStageInfo[g_nStage]->GetGoalDaeY(),
		fStageInfo[g_nStage]->GetGoalDaeLength(), fStageInfo[g_nStage]->GetnDist(),
		fStageInfo[g_nStage]->GetMoveTime(), clock());

	//ȿ��
	fEffect->SetStartTime(2000); // 2�� ����
	g_nGoal = 0; //�������� �Ϸ� ����
	g_UpdateOldTime = clock();
	g_nBallCount = 0; // ������ ���� ����
}

void FootballManager::InitScreen()
{
	globalScreen->GetScreen()->ScreenPrint(0, 0, "����������������������������������������������");
	globalScreen->GetScreen()->ScreenPrint(0, 1, "��                                          ��");
	globalScreen->GetScreen()->ScreenPrint(0, 2, "��             �ব������                   ��");
	globalScreen->GetScreen()->ScreenPrint(0, 3, "��                                          ��");
	globalScreen->GetScreen()->ScreenPrint(0, 4, "��                        ///.   ��~~~      ��");
	globalScreen->GetScreen()->ScreenPrint(0, 5, "��                       (^.^)              ��");
	globalScreen->GetScreen()->ScreenPrint(0, 6, "��                      ���� ����           ��");
	globalScreen->GetScreen()->ScreenPrint(0, 7, "��                         ����             ��");
	globalScreen->GetScreen()->ScreenPrint(0, 8, "��                     ��  ����             ��");
	globalScreen->GetScreen()->ScreenPrint(0, 9, "��                                          ��");
	globalScreen->GetScreen()->ScreenPrint(0, 10, "��                                          ��");
	globalScreen->GetScreen()->ScreenPrint(0, 11, "��       �� ���� ����  Go! Go!              ��");
	globalScreen->GetScreen()->ScreenPrint(0, 12, "��                                          ��");
	globalScreen->GetScreen()->ScreenPrint(0, 13, "��                                          ��");
	globalScreen->GetScreen()->ScreenPrint(0, 14, "��       j :���� l : ������ k :��           ��");
	globalScreen->GetScreen()->ScreenPrint(0, 15, "��                                          ��");
	globalScreen->GetScreen()->ScreenPrint(0, 16, "��                                          ��");
	globalScreen->GetScreen()->ScreenPrint(0, 17, "��                                          ��");
	globalScreen->GetScreen()->ScreenPrint(0, 18, "��        ���ܦ�  space Ű�� �����ּ���     ��");
	globalScreen->GetScreen()->ScreenPrint(0, 19, "��                                          ��");
	globalScreen->GetScreen()->ScreenPrint(0, 20, "��                                          ��");
	globalScreen->GetScreen()->ScreenPrint(0, 21, "��                                          ��");
	globalScreen->GetScreen()->ScreenPrint(0, 22, "����������������������������������������������");
}

void FootballManager::ReadyScreen()
{
	char string[100];

	globalScreen->GetScreen()->ScreenPrint(0, 0, "����������������������������������������������");
	globalScreen->GetScreen()->ScreenPrint(0, 1, "�����������������������᦭");
	globalScreen->GetScreen()->ScreenPrint(0, 2, "�����������������������᦭");
	globalScreen->GetScreen()->ScreenPrint(0, 3, "�����������������������᦭");
	globalScreen->GetScreen()->ScreenPrint(0, 4, "�����������������������᦭");
	globalScreen->GetScreen()->ScreenPrint(0, 5, "�����������������������᦭");
	globalScreen->GetScreen()->ScreenPrint(0, 6, "�����������������������᦭");
	globalScreen->GetScreen()->ScreenPrint(0, 7, "�����������������������᦭");
	globalScreen->GetScreen()->ScreenPrint(0, 8, "�����������������������᦭");
	globalScreen->GetScreen()->ScreenPrint(0, 9, "�����������������������᦭");
	globalScreen->GetScreen()->ScreenPrint(0, 10, "��������                    ������᦭");
	sprintf_s(string, "��������     %d   ��������   ������᦭", g_nStage + 1);
	globalScreen->GetScreen()->ScreenPrint(0, 11, string);
	globalScreen->GetScreen()->ScreenPrint(0, 12, "��������                    ������᦭");
	globalScreen->GetScreen()->ScreenPrint(0, 13, "�����������������������᦭");
	globalScreen->GetScreen()->ScreenPrint(0, 14, "�����������������������᦭");
	globalScreen->GetScreen()->ScreenPrint(0, 15, "�����������������������᦭");
	globalScreen->GetScreen()->ScreenPrint(0, 16, "�����������������������᦭");
	globalScreen->GetScreen()->ScreenPrint(0, 17, "�����������������������᦭");
	globalScreen->GetScreen()->ScreenPrint(0, 18, "�����������������������᦭");
	globalScreen->GetScreen()->ScreenPrint(0, 19, "�����������������������᦭");
	globalScreen->GetScreen()->ScreenPrint(0, 20, "�����������������������᦭");
	globalScreen->GetScreen()->ScreenPrint(0, 21, "�����������������������᦭");
	globalScreen->GetScreen()->ScreenPrint(0, 22, "�����������������������᦭");
	globalScreen->GetScreen()->ScreenPrint(0, 23, "����������������������������������������������");
}

void FootballManager::BackScreen()
{
	char string[100];

	globalScreen->GetScreen()->ScreenPrint(0, 0, "����������������������������������������������");
	globalScreen->GetScreen()->ScreenPrint(0, 1, "��                                          ��");
	globalScreen->GetScreen()->ScreenPrint(0, 2, "��                                          ��");
	globalScreen->GetScreen()->ScreenPrint(0, 3, "��                                          ��");
	sprintf_s(string, "��                                          ����������: %d", g_nStage + 1);
	globalScreen->GetScreen()->ScreenPrint(0, 4, string);
	globalScreen->GetScreen()->ScreenPrint(0, 5, "��                                          ��");
	sprintf_s(string, "�������������������������������������������������� �ð�: %d", fStageInfo[g_nStage]->GetLimitTime() / 1000);
	globalScreen->GetScreen()->ScreenPrint(0, 6, string);
	globalScreen->GetScreen()->ScreenPrint(0, 7, "��                                          ��");
	sprintf_s(string, "��                                          ������ �ð�: %d", (clock() - g_GameStartTime) / 1000);
	globalScreen->GetScreen()->ScreenPrint(0, 8, string);
	globalScreen->GetScreen()->ScreenPrint(0, 9, "��                                          ��");
	sprintf_s(string, "��                                          ����ǥ ����: %d ", fStageInfo[g_nStage]->GetGoalBall());
	globalScreen->GetScreen()->ScreenPrint(0, 10, string);
	globalScreen->GetScreen()->ScreenPrint(0, 11, "��                                          ��");
	sprintf_s(string, "��                                          ������ �� ����: %d ", g_nBallCount);
	globalScreen->GetScreen()->ScreenPrint(0, 12, string);

	globalScreen->GetScreen()->ScreenPrint(0, 13, "��                                          ��");
	sprintf_s(string, "��                                          ��");
	globalScreen->GetScreen()->ScreenPrint(0, 14, string);
	globalScreen->GetScreen()->ScreenPrint(0, 15, "��                                          ��");
	sprintf_s(string, "��                                          ��");
	globalScreen->GetScreen()->ScreenPrint(0, 16, string);
	globalScreen->GetScreen()->ScreenPrint(0, 17, "��                                          ��");
	globalScreen->GetScreen()->ScreenPrint(0, 18, "��                                          ��");
	globalScreen->GetScreen()->ScreenPrint(0, 19, "��                                          ��");
	globalScreen->GetScreen()->ScreenPrint(0, 20, "��                                          ��");
	globalScreen->GetScreen()->ScreenPrint(0, 21, "��                                          ��");
	globalScreen->GetScreen()->ScreenPrint(0, 22, "��                                          ��");
	globalScreen->GetScreen()->ScreenPrint(0, 23, "����������������������������������������������");
}

void FootballManager::GoalMessage(int nX, int nY)
{
	globalScreen->GetScreen()->ScreenPrint(nX, nY, "�� )) ���� (( ��");
	globalScreen->GetScreen()->ScreenPrint(nX, nY + 1, "��(^^')/ ��(\"*')/");
	globalScreen->GetScreen()->ScreenPrint(nX, nY + 2, "   ��       ��");
	globalScreen->GetScreen()->ScreenPrint(nX, nY + 3, "  ����    ����");
}

void FootballManager::SuccessScreen()
{
	globalScreen->GetScreen()->ScreenPrint(0, 0, "����������������������������������������������");
	globalScreen->GetScreen()->ScreenPrint(0, 1, "��                                          ��");
	globalScreen->GetScreen()->ScreenPrint(0, 2, "��                                          ��");
	globalScreen->GetScreen()->ScreenPrint(0, 3, "��                                          ��");
	globalScreen->GetScreen()->ScreenPrint(0, 4, "��                                          ��");
	globalScreen->GetScreen()->ScreenPrint(0, 5, "��                                          ��");
	globalScreen->GetScreen()->ScreenPrint(0, 6, "��                ////����                  ��");
	globalScreen->GetScreen()->ScreenPrint(0, 7, "��               q ��  �� p                 ��");
	globalScreen->GetScreen()->ScreenPrint(0, 8, "��               (��������)                 ��");
	globalScreen->GetScreen()->ScreenPrint(0, 9, "��             �� �̼� ���� ��              ��");
	globalScreen->GetScreen()->ScreenPrint(0, 10, "��                                          ��");
	globalScreen->GetScreen()->ScreenPrint(0, 11, "��                                          ��");
	globalScreen->GetScreen()->ScreenPrint(0, 12, "��                                          ��");
	globalScreen->GetScreen()->ScreenPrint(0, 13, "��                                          ��");
	globalScreen->GetScreen()->ScreenPrint(0, 14, "��                                          ��");
	globalScreen->GetScreen()->ScreenPrint(0, 15, "��                                          ��");
	globalScreen->GetScreen()->ScreenPrint(0, 16, "��                                          ��");
	globalScreen->GetScreen()->ScreenPrint(0, 17, "��                                          ��");
	globalScreen->GetScreen()->ScreenPrint(0, 18, "��                                          ��");
	globalScreen->GetScreen()->ScreenPrint(0, 19, "��                                          ��");
	globalScreen->GetScreen()->ScreenPrint(0, 20, "��                                          ��");
	globalScreen->GetScreen()->ScreenPrint(0, 21, "��                                          ��");
	globalScreen->GetScreen()->ScreenPrint(0, 22, "��                                          ��");
	globalScreen->GetScreen()->ScreenPrint(0, 23, "����������������������������������������������");
}

void FootballManager::FailureScreen()
{
	globalScreen->GetScreen()->ScreenPrint(0, 0, "����������������������������������������������");
	globalScreen->GetScreen()->ScreenPrint(0, 1, "��                                          ��");
	globalScreen->GetScreen()->ScreenPrint(0, 2, "��                                          ��");
	globalScreen->GetScreen()->ScreenPrint(0, 3, "��                                          ��");
	globalScreen->GetScreen()->ScreenPrint(0, 4, "��                                          ��");
	globalScreen->GetScreen()->ScreenPrint(0, 5, "��                                          ��");
	globalScreen->GetScreen()->ScreenPrint(0, 6, "��                                          ��");
	globalScreen->GetScreen()->ScreenPrint(0, 7, "��                                          ��");
	globalScreen->GetScreen()->ScreenPrint(0, 8, "��                                          ��");
	globalScreen->GetScreen()->ScreenPrint(0, 9, "��                                          ��");
	globalScreen->GetScreen()->ScreenPrint(0, 10, "��                                          ��");
	globalScreen->GetScreen()->ScreenPrint(0, 11, "��                    �̼� ���� !!!!        ��");
	globalScreen->GetScreen()->ScreenPrint(0, 12, "��                                          ��");
	globalScreen->GetScreen()->ScreenPrint(0, 13, "��                                          ��");
	globalScreen->GetScreen()->ScreenPrint(0, 14, "��                 �ܦ�����                 ��");
	globalScreen->GetScreen()->ScreenPrint(0, 15, "��                   ��  ��                 ��");
	globalScreen->GetScreen()->ScreenPrint(0, 16, "��                  �����                ��");
	globalScreen->GetScreen()->ScreenPrint(0, 17, "��                                          ��");
	globalScreen->GetScreen()->ScreenPrint(0, 18, "��        �ٽ� �Ͻðڽ��ϱ�? (y/n)          ��");
	globalScreen->GetScreen()->ScreenPrint(0, 19, "��                                          ��");
	globalScreen->GetScreen()->ScreenPrint(0, 20, "��                                          ��");
	globalScreen->GetScreen()->ScreenPrint(0, 21, "��                                          ��");
	globalScreen->GetScreen()->ScreenPrint(0, 22, "����������������������������������������������");
}

void FootballManager::ResultScreen()
{
	char string[100];
	globalScreen->GetScreen()->ScreenPrint(0, 0, "����������������������������������������������");
	globalScreen->GetScreen()->ScreenPrint(0, 1, "��                                          ��");
	globalScreen->GetScreen()->ScreenPrint(0, 2, "��                                          ��");
	globalScreen->GetScreen()->ScreenPrint(0, 3, "��             �ব������                   ��");
	globalScreen->GetScreen()->ScreenPrint(0, 4, "��                                          ��");
	globalScreen->GetScreen()->ScreenPrint(0, 5, "��                                          ��");
	globalScreen->GetScreen()->ScreenPrint(0, 6, "��                                          ��");
	globalScreen->GetScreen()->ScreenPrint(0, 7, "��                                          ��");
	sprintf_s(string, "��      ������ �������� :  %2d               ��", g_nStage + 1);
	globalScreen->GetScreen()->ScreenPrint(0, 8, string);
	globalScreen->GetScreen()->ScreenPrint(0, 9, "��                                          ��");
	globalScreen->GetScreen()->ScreenPrint(0, 10, "��                                          ��");
	globalScreen->GetScreen()->ScreenPrint(0, 11, "��   ___�ƢƢ�___                           ��");
	globalScreen->GetScreen()->ScreenPrint(0, 12, "��     (*^  ^*)                             ��");
	globalScreen->GetScreen()->ScreenPrint(0, 13, "�� =====��==��=====                         ��");
	globalScreen->GetScreen()->ScreenPrint(0, 14, "��                                          ��");
	globalScreen->GetScreen()->ScreenPrint(0, 15, "��                                          ��");
	globalScreen->GetScreen()->ScreenPrint(0, 16, "��                                          ��");
	globalScreen->GetScreen()->ScreenPrint(0, 17, "��                                          ��");
	globalScreen->GetScreen()->ScreenPrint(0, 18, "��                      ���ܦ�              ��");
	globalScreen->GetScreen()->ScreenPrint(0, 19, "��                                          ��");
	globalScreen->GetScreen()->ScreenPrint(0, 20, "��                                          ��");
	globalScreen->GetScreen()->ScreenPrint(0, 21, "��                                          ��");
	globalScreen->GetScreen()->ScreenPrint(0, 22, "����������������������������������������������");
}

bool FootballManager::KeyHandle()
{
	if (_kbhit())
	{
		if (g_GameState == RESULT)
			return false;

		nKey = _getch();

		switch (nKey)
		{
		case 'j':
			if (fPlayer->nMoveX > 2) // ���� �浹 ��� ��ǥ üũ
			{
				fPlayer->nMoveX--;
				nRemain = g_nLength - fPlayer->nCenterX + 1; // ��ü ���� - ( �߽� ��ǥ + 1 )�� ���� ����
															  // Note: 2�÷��� �̵��ϱ� ���� �κ� ( ���� ��ģ ��� ) 
				if (fPlayer->nMoveX - fPlayer->nCenterX < 2 || fPlayer->nMoveX + nRemain > 43)
					fPlayer->nMoveX--;

				fPlayer->SetnX(fPlayer->nMoveX - fPlayer->nCenterX);
			}
			break;
		case 'l':
			if (fPlayer->nMoveX + 1 < 43) // ������ �浹 ��� ��ǥ üũ
			{
				fPlayer->nMoveX++;
				nRemain = g_nLength - fPlayer->nCenterX + 1; // ��ü ���� - ( �߽� ��ǥ + 1 )�� ���� ����
															  // Note: 2�÷��� �̵��ϱ� ���� �κ� ( ���� ��ģ ��� )
				if (fPlayer->nMoveX + nRemain > 43 || (fPlayer->nMoveX - fPlayer->nCenterX < 2))
					fPlayer->nMoveX++;

				fPlayer->SetnX(fPlayer->nMoveX - fPlayer->nCenterX);
			}
			break;
		case 'k':
			if (fBall->GetIsReady() && g_GameState == RUNNING)
			{
				fBall->nMoveX = fPlayer->nMoveX;
				fBall->nMoveY = fPlayer->nMoveY - 1;
				fBall->OldTime = clock();
				fBall->SetIsReady(false);
				//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[5], 0, &g_Channel[5]); // �� ���� �Ҹ� ���
			}
			break;

		case 'y':
		case 'Y':
			if (g_GameState == FAILED)
			{
				Init();
				g_GameState = READY;
				//FMOD_Channel_Stop( g_Channel[2] );  // �̼� ���� ���� ��� ���� 
				//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[3], 0, &g_Channel[3]);
			}
			break;
		case 'n':
		case 'N':
			if (g_GameState == FAILED)
			{
				g_GameState = RESULT;
				//FMOD_Channel_Stop( g_Channel[2] );  // �̼� ���� ���� ��� ����							
			}
			break;

		case ' ':
			if (g_GameState == INIT && g_nStage == 0)
			{
				g_GameState = READY;
				//FMOD_Channel_Stop( g_Channel[0] ); // ����� ����
				//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[3], 0, &g_Channel[3]); // ready ����
				g_UpdateOldTime = clock();  // ready�� �����ð� ������ �ֱ� ���� 							
			}
			break;
		}
	}

	return true;
}

void FootballManager::Update()
{
	clock_t CurTime = clock();
	int nLength = fGoalpost->GetnLength() * 2 + 1; // Note: �迭�� �ִ� ����

	switch (g_GameState)
	{
	case READY:
		if (CurTime - g_UpdateOldTime > 2000)  // 2��
		{
			g_GameState = RUNNING;
			g_GameStartTime = CurTime;

			//FMOD_Channel_Stop( g_Channel[3] );  // ready ���� ����
			//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[1], 0, &g_Channel[1]); // running �����
		}
		break;
	case RUNNING:
		if (CurTime - g_GameStartTime > g_LimitTime) // Note: ���� �ð�
		{
			g_GameState = STOP;
			return;
		}
		else {
			// Note: ���
			if (CurTime - fGoalpost->OldTime > fGoalpost->MoveTime)
			{
				fGoalpost->OldTime = CurTime;
				if (fGoalpost->nMoveX + fGoalpost->GetnDist() >= 2 && ((fGoalpost->GetnLineX(nLength - 1) + 3) + fGoalpost->GetnDist()) <= 43)
				{
					fGoalpost->nMoveX += fGoalpost->GetnDist();
					fGoalpost->SetnLineX();
				}
				else {
					fGoalpost->SetnDist(fGoalpost->GetnDist() * -1); // -1 �� ������ �ٲپ� ��.
				}
			}

			if (fBall->GetIsReady() == false) // �̵� ���� �� 
			{	// �̵� �ð� ���ݿ� ���� �̵�
				if ((CurTime - fBall->OldTime) > fBall->MoveTime)
				{
					if (fBall->nMoveY - 1 > 0)
					{
						fBall->nMoveY--;
						fBall->OldTime = CurTime; // ���� �̵� �ð��� ���ϱ� ���� ���� �ð��� ���� �ð� ������ ����

												   // ��� ���� �浹
						if (fBall->nMoveX >= fGoalpost->GetnLineX(0) && fBall->nMoveX + 1 <= fGoalpost->GetnLineX(nLength - 1) + 1)
						{
							if (fBall->nMoveY <= fGoalpost->nMoveY)
							{   // �� �ʱ�ȭ
								fBall->SetIsReady(1);
								fBall->nMoveX = fPlayer->nMoveX;
								fBall->nMoveY = fPlayer->nMoveY - 1;
								g_nBallCount++;  // ������ ���� ����										

								if (g_nBallCount == g_nGoalBallCount) // ���� ��ǥ ������ ������ ������ SUCCESS
								{
									g_GameState = STOP;
									g_nGoal = 1;
									return;
								}

								// ȿ�� ���
								if (g_nIsGoal == 0)
								{
									g_nIsGoal = 1;
									fEffect->SetStartTime(CurTime);
								}

								// ���� ���� ���
								//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[6], 0, &g_Channel[6]); // ���� ���� �Ϳ�~
							}
							// ��� �浹 
						}
						else if ((fBall->nMoveX >= fGoalpost->GetnLineX(0) - 2 && fBall->nMoveX <= fGoalpost->GetnLineX(0) - 1) ||
							(fBall->nMoveX + 1 >= fGoalpost->GetnLineX(0) - 2 && fBall->nMoveX + 1 <= fGoalpost->GetnLineX(0) - 1) ||
							(fBall->nMoveX >= fGoalpost->GetnLineX(nLength - 1) + 2 && fBall->nMoveX <= fGoalpost->GetnLineX(nLength - 1) + 3) ||
							(fBall->nMoveX + 1 >= fGoalpost->GetnLineX(nLength - 1) + 2 && fBall->nMoveX + 1 <= fGoalpost->GetnLineX(nLength - 1) + 3))
						{
							if (fBall->nMoveY <= fGoalpost->nMoveY)
							{   // �� �ʱ�ȭ
								fBall->SetIsReady(1);
								fBall->nMoveX = fPlayer->nMoveX;
								fBall->nMoveY = fPlayer->nMoveY - 1;
							}
						}
					}
					else { // �� �ʱ�ȭ
						fBall->SetIsReady(1);
						fBall->nMoveX = fPlayer->nMoveX;
						fBall->nMoveY = fPlayer->nMoveY - 1;
					}
				}
			}
			else {
				fBall->nMoveX = fPlayer->nMoveX;
			}

			// ȿ�� 
			if (g_nIsGoal == 1)
			{
				if (CurTime - fEffect->GetStartTime() > fEffect->GetStayTime())
					g_nIsGoal = 0;
			}
		}
		break;
	case STOP:
		if (g_nGoal == 1)
		{
			g_GameState = SUCCESS;
			g_UpdateOldTime = CurTime;
			//FMOD_Channel_Stop( g_Channel[1] );  // running ���� ����
			//FMOD_Channel_Stop( g_Channel[1] );  // running ���� ����

			//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[4], 0, &g_Channel[4]); // �̼� ���� ����
		}
		else {
			g_GameState = FAILED;
			//FMOD_Channel_Stop( g_Channel[1] );  // running ���� ����
			//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[2], 0, &g_Channel[2]); // �̼� ���� ����
		}
		break;
	case SUCCESS:
		if (CurTime - g_UpdateOldTime > 3000)
		{
			g_UpdateOldTime = CurTime;
			++g_nStage;
			Init();
			g_GameState = READY;
			//FMOD_Channel_Stop( g_Channel[4] );  // �̼� ���� ���� ��� ����					
			//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[3], 0, &g_Channel[3]); //READY ���� 
		}
		break;
	}
}

void FootballManager::Render()
{
	char string[100] = { 0, };
	int nLength, i;

	globalScreen->GetScreen()->ScreenClear();

	switch (g_GameState)
	{
	case INIT:
		if (g_nStage == 0)
			InitScreen();
		break;
	case READY:
		ReadyScreen();
		break;
	case RUNNING:
		BackScreen();
		globalScreen->GetScreen()->ScreenPrint(fGoalpost->nMoveX, fGoalpost->nMoveY, "��");
		nLength = fGoalpost->GetnLength() * 2 + 1;

		for (i = 0; i < nLength; i++)
			globalScreen->GetScreen()->ScreenPrint(fGoalpost->GetnLineX(i), fGoalpost->nMoveY, "��");

		globalScreen->GetScreen()->ScreenPrint(fGoalpost->GetnLineX(nLength - 1) + 2, fGoalpost->nMoveY, "��");

		// Note: ȿ�� ���  	
		if (g_nIsGoal == 1)
		{
			GoalMessage(10, 10);
		}

		// Note: 2 �÷��� Ŭ���� 
		if (fPlayer->GetnX() < 2)  //  ���� Ŭ���� ó��
			globalScreen->GetScreen()->ScreenPrint(2, fPlayer->nMoveY, &g_strPlayer[(fPlayer->GetnX() - 2)*-1]);	 // ��ǥ�� �迭 �ε��� 
		else if (fPlayer->nMoveX + (g_nLength - fPlayer->nCenterX + 1) > 43) // ������ Ŭ���� ó��
		{
			strncat_s(string, g_strPlayer, g_nLength - ((fPlayer->nMoveX + fPlayer->nCenterX + 1) - 43));
			globalScreen->GetScreen()->ScreenPrint(fPlayer->GetnX(), fPlayer->nMoveY, string);
		}
		else { // 1 �÷��� �̵�
			globalScreen->GetScreen()->ScreenPrint(fPlayer->GetnX(), fPlayer->nMoveY, g_strPlayer);
		}

		globalScreen->GetScreen()->ScreenPrint(fBall->nMoveX, fBall->nMoveY, "��");
		break;
	case SUCCESS:
		SuccessScreen();
		break;
	case FAILED:
		FailureScreen();
		break;
	case RESULT:
		ResultScreen();
		break;
	}

	// Note: ������ �� 
	globalScreen->GetScreen()->ScreenFlipping();
}
