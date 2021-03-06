#include "Football_FootballManager.h"

FootballManager::FootballManager() 
{
	char playerform[] = "曲收≒收旭";

	fStageInfo[0] = new StageInfo(3, 1000 * 20, 1, 20, 3, 300, 1);
	fStageInfo[1] = new StageInfo(10, 1000 * 30, 2, 20, 5, 300, 1);

	fPlayer = new Player(4, 0, 20, 22);
	fPlayer->SetnX(fPlayer->nMoveX - fPlayer->nCenterX);
	
	g_nStage = 0;
	g_strPlayer = new char[sizeof(playerform)];
	for (int i = 0; i < sizeof(playerform); i++)
		g_strPlayer[i] = playerform[i];

	g_LimitTime = fStageInfo[g_nStage]->GetLimitTime();  // 薯и 衛除 撲薑
	g_nGoalBallCount = fStageInfo[g_nStage]->GetGoalBall(); // 跡ル 埤檣 偃熱

	g_nLength = strlen(g_strPlayer);

	//奢曖 蟾晦��
	fBall = new Ball(true, fPlayer->nMoveX, fPlayer->nMoveY -1, 100);
	
	//埤渠 蟾晦��
	fGoalpost = new Goalpost(fStageInfo[g_nStage]->GetGoalDaeX(), fStageInfo[g_nStage]->GetGoalDaeY(), 
		fStageInfo[g_nStage]->GetGoalDaeLength(), fStageInfo[g_nStage]->GetnDist(), 
		fStageInfo[g_nStage]->GetMoveTime(), clock());

	//�膩�
	fEffect = new Effect();
	fEffect->SetStartTime(2000); // 2蟾 撲薑
	g_nGoal = 0; //蝶纔檜雖 諫猿 滲熱
	g_UpdateOldTime = clock();
	g_nBallCount = 0; // 埤檣и 奢曖 偃熱

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

	g_LimitTime = fStageInfo[g_nStage]->GetLimitTime();  // 薯и 衛除 撲薑
	g_nGoalBallCount = fStageInfo[g_nStage]->GetGoalBall(); // 跡ル 埤檣 偃熱

	fBall->SetIsReady(true);
	fBall->nMoveX = fPlayer->nMoveX;
	fBall->nMoveY = fPlayer->nMoveY -1;
	fBall->MoveTime = 100;

	fGoalpost->Init(fStageInfo[g_nStage]->GetGoalDaeX(), fStageInfo[g_nStage]->GetGoalDaeY(),
		fStageInfo[g_nStage]->GetGoalDaeLength(), fStageInfo[g_nStage]->GetnDist(),
		fStageInfo[g_nStage]->GetMoveTime(), clock());

	//�膩�
	fEffect->SetStartTime(2000); // 2蟾 撲薑
	g_nGoal = 0; //蝶纔檜雖 諫猿 滲熱
	g_UpdateOldTime = clock();
	g_nBallCount = 0; // 埤檣и 奢曖 偃熱
}

void FootballManager::InitScreen()
{
	globalScreen->GetScreen()->ScreenPrint(0, 0, "旨收收收收收收收收收收收收收收收收收收收收收旬");
	globalScreen->GetScreen()->ScreenPrint(0, 1, "早                                          早");
	globalScreen->GetScreen()->ScreenPrint(0, 2, "早             ﹤收收收﹤                   早");
	globalScreen->GetScreen()->ScreenPrint(0, 3, "早                                          早");
	globalScreen->GetScreen()->ScreenPrint(0, 4, "早                        ///.   螂~~~      早");
	globalScreen->GetScreen()->ScreenPrint(0, 5, "早                       (^.^)              早");
	globalScreen->GetScreen()->ScreenPrint(0, 6, "早                      曲朽 曳旬           早");
	globalScreen->GetScreen()->ScreenPrint(0, 7, "早                         旨旭             早");
	globalScreen->GetScreen()->ScreenPrint(0, 8, "早                     Ⅸ  旭′             早");
	globalScreen->GetScreen()->ScreenPrint(0, 9, "早                                          早");
	globalScreen->GetScreen()->ScreenPrint(0, 10, "早                                          早");
	globalScreen->GetScreen()->ScreenPrint(0, 11, "早       螂 埤檣 啪歜  Go! Go!              早");
	globalScreen->GetScreen()->ScreenPrint(0, 12, "早                                          早");
	globalScreen->GetScreen()->ScreenPrint(0, 13, "早                                          早");
	globalScreen->GetScreen()->ScreenPrint(0, 14, "早       j :豭薹 l : 螃艇薹 k :螂           早");
	globalScreen->GetScreen()->ScreenPrint(0, 15, "早                                          早");
	globalScreen->GetScreen()->ScreenPrint(0, 16, "早                                          早");
	globalScreen->GetScreen()->ScreenPrint(0, 17, "早                                          早");
	globalScreen->GetScreen()->ScreenPrint(0, 18, "早        曲≒旭  space 酈蒂 揚楝輿撮蹂     早");
	globalScreen->GetScreen()->ScreenPrint(0, 19, "早                                          早");
	globalScreen->GetScreen()->ScreenPrint(0, 20, "早                                          早");
	globalScreen->GetScreen()->ScreenPrint(0, 21, "早                                          早");
	globalScreen->GetScreen()->ScreenPrint(0, 22, "曲收收收收收收收收收收收收收收收收收收收收收旭");
}

void FootballManager::ReadyScreen()
{
	char string[100];

	globalScreen->GetScreen()->ScreenPrint(0, 0, "旨收收收收收收收收收收收收收收收收收收收收收旬");
	globalScreen->GetScreen()->ScreenPrint(0, 1, "早﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥早");
	globalScreen->GetScreen()->ScreenPrint(0, 2, "早﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥早");
	globalScreen->GetScreen()->ScreenPrint(0, 3, "早﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥早");
	globalScreen->GetScreen()->ScreenPrint(0, 4, "早﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥早");
	globalScreen->GetScreen()->ScreenPrint(0, 5, "早﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥早");
	globalScreen->GetScreen()->ScreenPrint(0, 6, "早﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥早");
	globalScreen->GetScreen()->ScreenPrint(0, 7, "早﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥早");
	globalScreen->GetScreen()->ScreenPrint(0, 8, "早﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥早");
	globalScreen->GetScreen()->ScreenPrint(0, 9, "早﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥早");
	globalScreen->GetScreen()->ScreenPrint(0, 10, "早﹥﹥﹥﹥﹥                    ﹥﹥﹥﹥﹥﹥早");
	sprintf_s(string, "早﹥﹥﹥﹥﹥     %d   蝶纔檜雖   ﹥﹥﹥﹥﹥﹥早", g_nStage + 1);
	globalScreen->GetScreen()->ScreenPrint(0, 11, string);
	globalScreen->GetScreen()->ScreenPrint(0, 12, "早﹥﹥﹥﹥﹥                    ﹥﹥﹥﹥﹥﹥早");
	globalScreen->GetScreen()->ScreenPrint(0, 13, "早﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥早");
	globalScreen->GetScreen()->ScreenPrint(0, 14, "早﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥早");
	globalScreen->GetScreen()->ScreenPrint(0, 15, "早﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥早");
	globalScreen->GetScreen()->ScreenPrint(0, 16, "早﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥早");
	globalScreen->GetScreen()->ScreenPrint(0, 17, "早﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥早");
	globalScreen->GetScreen()->ScreenPrint(0, 18, "早﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥早");
	globalScreen->GetScreen()->ScreenPrint(0, 19, "早﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥早");
	globalScreen->GetScreen()->ScreenPrint(0, 20, "早﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥早");
	globalScreen->GetScreen()->ScreenPrint(0, 21, "早﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥早");
	globalScreen->GetScreen()->ScreenPrint(0, 22, "早﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥早");
	globalScreen->GetScreen()->ScreenPrint(0, 23, "曲收收收收收收收收收收收收收收收收收收收收收旭");
}

void FootballManager::BackScreen()
{
	char string[100];

	globalScreen->GetScreen()->ScreenPrint(0, 0, "旨收收收收收收收收收收收收收收收收收收收收收旬");
	globalScreen->GetScreen()->ScreenPrint(0, 1, "早                                          早");
	globalScreen->GetScreen()->ScreenPrint(0, 2, "早                                          早");
	globalScreen->GetScreen()->ScreenPrint(0, 3, "早                                          早");
	sprintf_s(string, "早                                          早蝶纔檜雖: %d", g_nStage + 1);
	globalScreen->GetScreen()->ScreenPrint(0, 4, string);
	globalScreen->GetScreen()->ScreenPrint(0, 5, "早                                          早");
	sprintf_s(string, "曳收收收收收收收收收收收收收收收收收收收收收朽薯и 衛除: %d", fStageInfo[g_nStage]->GetLimitTime() / 1000);
	globalScreen->GetScreen()->ScreenPrint(0, 6, string);
	globalScreen->GetScreen()->ScreenPrint(0, 7, "早                                          早");
	sprintf_s(string, "早                                          早⑷營 衛除: %d", (clock() - g_GameStartTime) / 1000);
	globalScreen->GetScreen()->ScreenPrint(0, 8, string);
	globalScreen->GetScreen()->ScreenPrint(0, 9, "早                                          早");
	sprintf_s(string, "早                                          早跡ル 埤檣: %d ", fStageInfo[g_nStage]->GetGoalBall());
	globalScreen->GetScreen()->ScreenPrint(0, 10, string);
	globalScreen->GetScreen()->ScreenPrint(0, 11, "早                                          早");
	sprintf_s(string, "早                                          早埤檣 奢 偃熱: %d ", g_nBallCount);
	globalScreen->GetScreen()->ScreenPrint(0, 12, string);

	globalScreen->GetScreen()->ScreenPrint(0, 13, "早                                          早");
	sprintf_s(string, "早                                          早");
	globalScreen->GetScreen()->ScreenPrint(0, 14, string);
	globalScreen->GetScreen()->ScreenPrint(0, 15, "早                                          早");
	sprintf_s(string, "早                                          早");
	globalScreen->GetScreen()->ScreenPrint(0, 16, string);
	globalScreen->GetScreen()->ScreenPrint(0, 17, "早                                          早");
	globalScreen->GetScreen()->ScreenPrint(0, 18, "早                                          早");
	globalScreen->GetScreen()->ScreenPrint(0, 19, "早                                          早");
	globalScreen->GetScreen()->ScreenPrint(0, 20, "早                                          早");
	globalScreen->GetScreen()->ScreenPrint(0, 21, "早                                          早");
	globalScreen->GetScreen()->ScreenPrint(0, 22, "早                                          早");
	globalScreen->GetScreen()->ScreenPrint(0, 23, "曲收收收收收收收收收收收收收收收收收收收收收旭");
}

void FootballManager::GoalMessage(int nX, int nY)
{
	globalScreen->GetScreen()->ScreenPrint(nX, nY, "≧ )) 埤檣 (( ≠");
	globalScreen->GetScreen()->ScreenPrint(nX, nY + 1, "′(^^')/ ′(\"*')/");
	globalScreen->GetScreen()->ScreenPrint(nX, nY + 2, "   ﹥       ﹥");
	globalScreen->GetScreen()->ScreenPrint(nX, nY + 3, "  戎忖    忙戌");
}

void FootballManager::SuccessScreen()
{
	globalScreen->GetScreen()->ScreenPrint(0, 0, "旨收收收收收收收收收收收收收收收收收收收收收旬");
	globalScreen->GetScreen()->ScreenPrint(0, 1, "早                                          早");
	globalScreen->GetScreen()->ScreenPrint(0, 2, "早                                          早");
	globalScreen->GetScreen()->ScreenPrint(0, 3, "早                                          早");
	globalScreen->GetScreen()->ScreenPrint(0, 4, "早                                          早");
	globalScreen->GetScreen()->ScreenPrint(0, 5, "早                                          早");
	globalScreen->GetScreen()->ScreenPrint(0, 6, "早                ////′′                  早");
	globalScreen->GetScreen()->ScreenPrint(0, 7, "早               q ∥  ∥ p                 早");
	globalScreen->GetScreen()->ScreenPrint(0, 8, "早               (戌式式戎)                 早");
	globalScreen->GetScreen()->ScreenPrint(0, 9, "早             Ｏ 嘐暮 撩奢 Ｎ              早");
	globalScreen->GetScreen()->ScreenPrint(0, 10, "早                                          早");
	globalScreen->GetScreen()->ScreenPrint(0, 11, "早                                          早");
	globalScreen->GetScreen()->ScreenPrint(0, 12, "早                                          早");
	globalScreen->GetScreen()->ScreenPrint(0, 13, "早                                          早");
	globalScreen->GetScreen()->ScreenPrint(0, 14, "早                                          早");
	globalScreen->GetScreen()->ScreenPrint(0, 15, "早                                          早");
	globalScreen->GetScreen()->ScreenPrint(0, 16, "早                                          早");
	globalScreen->GetScreen()->ScreenPrint(0, 17, "早                                          早");
	globalScreen->GetScreen()->ScreenPrint(0, 18, "早                                          早");
	globalScreen->GetScreen()->ScreenPrint(0, 19, "早                                          早");
	globalScreen->GetScreen()->ScreenPrint(0, 20, "早                                          早");
	globalScreen->GetScreen()->ScreenPrint(0, 21, "早                                          早");
	globalScreen->GetScreen()->ScreenPrint(0, 22, "早                                          早");
	globalScreen->GetScreen()->ScreenPrint(0, 23, "曲收收收收收收收收收收收收收收收收收收收收收旭");
}

void FootballManager::FailureScreen()
{
	globalScreen->GetScreen()->ScreenPrint(0, 0, "旨收收收收收收收收收收收收收收收收收收收收收旬");
	globalScreen->GetScreen()->ScreenPrint(0, 1, "早                                          早");
	globalScreen->GetScreen()->ScreenPrint(0, 2, "早                                          早");
	globalScreen->GetScreen()->ScreenPrint(0, 3, "早                                          早");
	globalScreen->GetScreen()->ScreenPrint(0, 4, "早                                          早");
	globalScreen->GetScreen()->ScreenPrint(0, 5, "早                                          早");
	globalScreen->GetScreen()->ScreenPrint(0, 6, "早                                          早");
	globalScreen->GetScreen()->ScreenPrint(0, 7, "早                                          早");
	globalScreen->GetScreen()->ScreenPrint(0, 8, "早                                          早");
	globalScreen->GetScreen()->ScreenPrint(0, 9, "早                                          早");
	globalScreen->GetScreen()->ScreenPrint(0, 10, "早                                          早");
	globalScreen->GetScreen()->ScreenPrint(0, 11, "早                    嘐暮 褒ぬ !!!!        早");
	globalScreen->GetScreen()->ScreenPrint(0, 12, "早                                          早");
	globalScreen->GetScreen()->ScreenPrint(0, 13, "早                                          早");
	globalScreen->GetScreen()->ScreenPrint(0, 14, "早                 ≒有收旬                 早");
	globalScreen->GetScreen()->ScreenPrint(0, 15, "早                   旭  曲                 早");
	globalScreen->GetScreen()->ScreenPrint(0, 16, "早                  ﹥﹥﹥﹥                早");
	globalScreen->GetScreen()->ScreenPrint(0, 17, "早                                          早");
	globalScreen->GetScreen()->ScreenPrint(0, 18, "早        棻衛 ж衛啊蝗棲梱? (y/n)          早");
	globalScreen->GetScreen()->ScreenPrint(0, 19, "早                                          早");
	globalScreen->GetScreen()->ScreenPrint(0, 20, "早                                          早");
	globalScreen->GetScreen()->ScreenPrint(0, 21, "早                                          早");
	globalScreen->GetScreen()->ScreenPrint(0, 22, "曲收收收收收收收收收收收收收收收收收收收收收旭");
}

void FootballManager::ResultScreen()
{
	char string[100];
	globalScreen->GetScreen()->ScreenPrint(0, 0, "旨收收收收收收收收收收收收收收收收收收收收收旬");
	globalScreen->GetScreen()->ScreenPrint(0, 1, "早                                          早");
	globalScreen->GetScreen()->ScreenPrint(0, 2, "早                                          早");
	globalScreen->GetScreen()->ScreenPrint(0, 3, "早             ﹤收收收﹤                   早");
	globalScreen->GetScreen()->ScreenPrint(0, 4, "早                                          早");
	globalScreen->GetScreen()->ScreenPrint(0, 5, "早                                          早");
	globalScreen->GetScreen()->ScreenPrint(0, 6, "早                                          早");
	globalScreen->GetScreen()->ScreenPrint(0, 7, "早                                          早");
	sprintf_s(string, "早      撩奢и 蝶纔檜雖 :  %2d               早", g_nStage + 1);
	globalScreen->GetScreen()->ScreenPrint(0, 8, string);
	globalScreen->GetScreen()->ScreenPrint(0, 9, "早                                          早");
	globalScreen->GetScreen()->ScreenPrint(0, 10, "早                                          早");
	globalScreen->GetScreen()->ScreenPrint(0, 11, "早   ___〤〤〤___                           早");
	globalScreen->GetScreen()->ScreenPrint(0, 12, "早     (*^  ^*)                             早");
	globalScreen->GetScreen()->ScreenPrint(0, 13, "早 =====∞==∞=====                         早");
	globalScreen->GetScreen()->ScreenPrint(0, 14, "早                                          早");
	globalScreen->GetScreen()->ScreenPrint(0, 15, "早                                          早");
	globalScreen->GetScreen()->ScreenPrint(0, 16, "早                                          早");
	globalScreen->GetScreen()->ScreenPrint(0, 17, "早                                          早");
	globalScreen->GetScreen()->ScreenPrint(0, 18, "早                      曲≒旭              早");
	globalScreen->GetScreen()->ScreenPrint(0, 19, "早                                          早");
	globalScreen->GetScreen()->ScreenPrint(0, 20, "早                                          早");
	globalScreen->GetScreen()->ScreenPrint(0, 21, "早                                          早");
	globalScreen->GetScreen()->ScreenPrint(0, 22, "曲收收收收收收收收收收收收收收收收收收收收收旭");
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
			if (fPlayer->nMoveX > 2) // 豭薹 醱給 唳啗 謝ル 羹觼
			{
				fPlayer->nMoveX--;
				nRemain = g_nLength - fPlayer->nCenterX + 1; // 瞪羹 望檜 - ( 醞褕 謝ル + 1 )擎 陴擎 望檜
															  // Note: 2鏽歲噶 檜翕ж晦 嬪и 睡碟 ( つ檜 勘耀 唳辦 ) 
				if (fPlayer->nMoveX - fPlayer->nCenterX < 2 || fPlayer->nMoveX + nRemain > 43)
					fPlayer->nMoveX--;

				fPlayer->SetnX(fPlayer->nMoveX - fPlayer->nCenterX);
			}
			break;
		case 'l':
			if (fPlayer->nMoveX + 1 < 43) // 螃艇薹 醱給 唳啗 謝ル 羹觼
			{
				fPlayer->nMoveX++;
				nRemain = g_nLength - fPlayer->nCenterX + 1; // 瞪羹 望檜 - ( 醞褕 謝ル + 1 )擎 陴擎 望檜
															  // Note: 2鏽歲噶 檜翕ж晦 嬪и 睡碟 ( つ檜 勘耀 唳辦 )
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
				//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[5], 0, &g_Channel[5]); // 螂 翕濛 模葬 轎溘
			}
			break;

		case 'y':
		case 'Y':
			if (g_GameState == FAILED)
			{
				Init();
				g_GameState = READY;
				//FMOD_Channel_Stop( g_Channel[2] );  // 嘐暮 褒ぬ 餌遴萄 轎溘 醞雖 
				//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[3], 0, &g_Channel[3]);
			}
			break;
		case 'n':
		case 'N':
			if (g_GameState == FAILED)
			{
				g_GameState = RESULT;
				//FMOD_Channel_Stop( g_Channel[2] );  // 嘐暮 褒ぬ 餌遴萄 轎溘 醞雖							
			}
			break;

		case ' ':
			if (g_GameState == INIT && g_nStage == 0)
			{
				g_GameState = READY;
				//FMOD_Channel_Stop( g_Channel[0] ); // 寡唳擠 醞雖
				//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[3], 0, &g_Channel[3]); // ready 餌遴萄
				g_UpdateOldTime = clock();  // ready蒂 橾薑衛除 雖樓п 輿晦 嬪п 							
			}
			break;
		}
	}

	return true;
}

void FootballManager::Update()
{
	clock_t CurTime = clock();
	int nLength = fGoalpost->GetnLength() * 2 + 1; // Note: 寡翮曖 譆渠 望檜

	switch (g_GameState)
	{
	case READY:
		if (CurTime - g_UpdateOldTime > 2000)  // 2蟾
		{
			g_GameState = RUNNING;
			g_GameStartTime = CurTime;

			//FMOD_Channel_Stop( g_Channel[3] );  // ready 餌遴萄 醞雖
			//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[1], 0, &g_Channel[1]); // running 寡唳擠
		}
		break;
	case RUNNING:
		if (CurTime - g_GameStartTime > g_LimitTime) // Note: 薯и 衛除
		{
			g_GameState = STOP;
			return;
		}
		else {
			// Note: 埤渠
			if (CurTime - fGoalpost->OldTime > fGoalpost->MoveTime)
			{
				fGoalpost->OldTime = CurTime;
				if (fGoalpost->nMoveX + fGoalpost->GetnDist() >= 2 && ((fGoalpost->GetnLineX(nLength - 1) + 3) + fGoalpost->GetnDist()) <= 43)
				{
					fGoalpost->nMoveX += fGoalpost->GetnDist();
					fGoalpost->SetnLineX();
				}
				else {
					fGoalpost->SetnDist(fGoalpost->GetnDist() * -1); // -1 檜 寞щ擊 夥紱橫 邀.
				}
			}

			if (fBall->GetIsReady() == false) // 檜翕 醞橾 陽 
			{	// 檜翕 衛除 除問縑 曖и 檜翕
				if ((CurTime - fBall->OldTime) > fBall->MoveTime)
				{
					if (fBall->nMoveY - 1 > 0)
					{
						fBall->nMoveY--;
						fBall->OldTime = CurTime; // 棻擠 檜翕 衛陝婁 綠掖ж晦 嬪п ⑷營 衛除擊 檜瞪 衛除 滲熱縑 盪濰

												   // 埤渠 塭檣 醱給
						if (fBall->nMoveX >= fGoalpost->GetnLineX(0) && fBall->nMoveX + 1 <= fGoalpost->GetnLineX(nLength - 1) + 1)
						{
							if (fBall->nMoveY <= fGoalpost->nMoveY)
							{   // 奢 蟾晦��
								fBall->SetIsReady(1);
								fBall->nMoveX = fPlayer->nMoveX;
								fBall->nMoveY = fPlayer->nMoveY - 1;
								g_nBallCount++;  // 埤檣и 奢曖 偃熱										

								if (g_nBallCount == g_nGoalBallCount) // 奢婁 跡ル 奢婁曖 偃熱陛 偽戲賊 SUCCESS
								{
									g_GameState = STOP;
									g_nGoal = 1;
									return;
								}

								// �膩� 轎溘
								if (g_nIsGoal == 0)
								{
									g_nIsGoal = 1;
									fEffect->SetStartTime(CurTime);
								}

								// 埤檣 餌遴萄 轎溘
								//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[6], 0, &g_Channel[6]); // 埤檣 餌遴萄 諦辦~
							}
							// 埤渠 醱給 
						}
						else if ((fBall->nMoveX >= fGoalpost->GetnLineX(0) - 2 && fBall->nMoveX <= fGoalpost->GetnLineX(0) - 1) ||
							(fBall->nMoveX + 1 >= fGoalpost->GetnLineX(0) - 2 && fBall->nMoveX + 1 <= fGoalpost->GetnLineX(0) - 1) ||
							(fBall->nMoveX >= fGoalpost->GetnLineX(nLength - 1) + 2 && fBall->nMoveX <= fGoalpost->GetnLineX(nLength - 1) + 3) ||
							(fBall->nMoveX + 1 >= fGoalpost->GetnLineX(nLength - 1) + 2 && fBall->nMoveX + 1 <= fGoalpost->GetnLineX(nLength - 1) + 3))
						{
							if (fBall->nMoveY <= fGoalpost->nMoveY)
							{   // 奢 蟾晦��
								fBall->SetIsReady(1);
								fBall->nMoveX = fPlayer->nMoveX;
								fBall->nMoveY = fPlayer->nMoveY - 1;
							}
						}
					}
					else { // 奢 蟾晦��
						fBall->SetIsReady(1);
						fBall->nMoveX = fPlayer->nMoveX;
						fBall->nMoveY = fPlayer->nMoveY - 1;
					}
				}
			}
			else {
				fBall->nMoveX = fPlayer->nMoveX;
			}

			// �膩� 
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
			//FMOD_Channel_Stop( g_Channel[1] );  // running 餌遴萄 醞雖
			//FMOD_Channel_Stop( g_Channel[1] );  // running 餌遴萄 醞雖

			//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[4], 0, &g_Channel[4]); // 嘐暮 撩奢 餌遴萄
		}
		else {
			g_GameState = FAILED;
			//FMOD_Channel_Stop( g_Channel[1] );  // running 餌遴萄 醞雖
			//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[2], 0, &g_Channel[2]); // 嘐暮 褒ぬ 餌遴萄
		}
		break;
	case SUCCESS:
		if (CurTime - g_UpdateOldTime > 3000)
		{
			g_UpdateOldTime = CurTime;
			++g_nStage;
			Init();
			g_GameState = READY;
			//FMOD_Channel_Stop( g_Channel[4] );  // 嘐暮 撩奢 餌遴萄 轎溘 醞雖					
			//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[3], 0, &g_Channel[3]); //READY 餌遴萄 
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
		globalScreen->GetScreen()->ScreenPrint(fGoalpost->nMoveX, fGoalpost->nMoveY, "﹤");
		nLength = fGoalpost->GetnLength() * 2 + 1;

		for (i = 0; i < nLength; i++)
			globalScreen->GetScreen()->ScreenPrint(fGoalpost->GetnLineX(i), fGoalpost->nMoveY, "收");

		globalScreen->GetScreen()->ScreenPrint(fGoalpost->GetnLineX(nLength - 1) + 2, fGoalpost->nMoveY, "﹤");

		// Note: �膩� 轎溘  	
		if (g_nIsGoal == 1)
		{
			GoalMessage(10, 10);
		}

		// Note: 2 鏽歲噶 贗葬ё 
		if (fPlayer->GetnX() < 2)  //  豭薹 贗葬ё 籀葬
			globalScreen->GetScreen()->ScreenPrint(2, fPlayer->nMoveY, &g_strPlayer[(fPlayer->GetnX() - 2)*-1]);	 // 謝ル蒂 寡翮 檣策蝶 
		else if (fPlayer->nMoveX + (g_nLength - fPlayer->nCenterX + 1) > 43) // 螃艇薹 贗葬ё 籀葬
		{
			strncat_s(string, g_strPlayer, g_nLength - ((fPlayer->nMoveX + fPlayer->nCenterX + 1) - 43));
			globalScreen->GetScreen()->ScreenPrint(fPlayer->GetnX(), fPlayer->nMoveY, string);
		}
		else { // 1 鏽歲噶 檜翕
			globalScreen->GetScreen()->ScreenPrint(fPlayer->GetnX(), fPlayer->nMoveY, g_strPlayer);
		}

		globalScreen->GetScreen()->ScreenPrint(fBall->nMoveX, fBall->nMoveY, "Ⅸ");
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

	// Note: 溶渦葭 部 
	globalScreen->GetScreen()->ScreenFlipping();
}
