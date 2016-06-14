#include "Football_FootballManager.h"

FootballManager::FootballManager() 
{
	char playerform[] = "¦±¦¬¡Ü¦¬¦°";

	fStageInfo[0] = new StageInfo(3, 1000 * 20, 1, 20, 3, 300, 1);
	fStageInfo[1] = new StageInfo(10, 1000 * 30, 2, 20, 5, 300, 1);

	fPlayer = new Player(4, 0, 20, 22);
	fPlayer->SetnX(fPlayer->nMoveX - fPlayer->nCenterX);
	
	g_nStage = 0;
	g_strPlayer = new char[sizeof(playerform)];
	for (int i = 0; i < sizeof(playerform); i++)
		g_strPlayer[i] = playerform[i];

	g_LimitTime = fStageInfo[g_nStage]->GetLimitTime();  // Á¦ÇÑ ½Ã°£ ¼³Á¤
	g_nGoalBallCount = fStageInfo[g_nStage]->GetGoalBall(); // ¸ñÇ¥ °ñÀÎ °³¼ö

	g_nLength = strlen(g_strPlayer);

	//°øÀÇ ÃÊ±âÈ­
	fBall = new Ball(true, fPlayer->nMoveX, fPlayer->nMoveY -1, 100);
	
	//°ñ´ë ÃÊ±âÈ­
	fGoalpost = new Goalpost(fStageInfo[g_nStage]->GetGoalDaeX(), fStageInfo[g_nStage]->GetGoalDaeY(), 
		fStageInfo[g_nStage]->GetGoalDaeLength(), fStageInfo[g_nStage]->GetnDist(), 
		fStageInfo[g_nStage]->GetMoveTime(), clock());

	//È¿°ú
	fEffect = new Effect();
	fEffect->SetStartTime(2000); // 2ÃÊ ¼³Á¤
	g_nGoal = 0; //½ºÅ×ÀÌÁö ¿Ï·á º¯¼ö
	g_UpdateOldTime = clock();
	g_nBallCount = 0; // °ñÀÎÇÑ °øÀÇ °³¼ö

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

	g_LimitTime = fStageInfo[g_nStage]->GetLimitTime();  // Á¦ÇÑ ½Ã°£ ¼³Á¤
	g_nGoalBallCount = fStageInfo[g_nStage]->GetGoalBall(); // ¸ñÇ¥ °ñÀÎ °³¼ö

	fBall->SetIsReady(true);
	fBall->nMoveX = fPlayer->nMoveX;
	fBall->nMoveY = fPlayer->nMoveY -1;
	fBall->MoveTime = 100;

	fGoalpost->Init(fStageInfo[g_nStage]->GetGoalDaeX(), fStageInfo[g_nStage]->GetGoalDaeY(),
		fStageInfo[g_nStage]->GetGoalDaeLength(), fStageInfo[g_nStage]->GetnDist(),
		fStageInfo[g_nStage]->GetMoveTime(), clock());

	//È¿°ú
	fEffect->SetStartTime(2000); // 2ÃÊ ¼³Á¤
	g_nGoal = 0; //½ºÅ×ÀÌÁö ¿Ï·á º¯¼ö
	g_UpdateOldTime = clock();
	g_nBallCount = 0; // °ñÀÎÇÑ °øÀÇ °³¼ö
}

void FootballManager::InitScreen()
{
	globalScreen->GetScreen()->ScreenPrint(0, 0, "¦®¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¯");
	globalScreen->GetScreen()->ScreenPrint(0, 1, "¦­                                          ¦­");
	globalScreen->GetScreen()->ScreenPrint(0, 2, "¦­             ¡à¦¬¦¬¦¬¡à                   ¦­");
	globalScreen->GetScreen()->ScreenPrint(0, 3, "¦­                                          ¦­");
	globalScreen->GetScreen()->ScreenPrint(0, 4, "¦­                        ///.   ½¸~~~      ¦­");
	globalScreen->GetScreen()->ScreenPrint(0, 5, "¦­                       (^.^)              ¦­");
	globalScreen->GetScreen()->ScreenPrint(0, 6, "¦­                      ¦±¦´ ¦²¦¯           ¦­");
	globalScreen->GetScreen()->ScreenPrint(0, 7, "¦­                         ¦®¦°             ¦­");
	globalScreen->GetScreen()->ScreenPrint(0, 8, "¦­                     ¢Á  ¦°¡¬             ¦­");
	globalScreen->GetScreen()->ScreenPrint(0, 9, "¦­                                          ¦­");
	globalScreen->GetScreen()->ScreenPrint(0, 10, "¦­                                          ¦­");
	globalScreen->GetScreen()->ScreenPrint(0, 11, "¦­       ½¸ °ñÀÎ °ÔÀÓ  Go! Go!              ¦­");
	globalScreen->GetScreen()->ScreenPrint(0, 12, "¦­                                          ¦­");
	globalScreen->GetScreen()->ScreenPrint(0, 13, "¦­                                          ¦­");
	globalScreen->GetScreen()->ScreenPrint(0, 14, "¦­       j :¿ÞÂÊ l : ¿À¸¥ÂÊ k :½¸           ¦­");
	globalScreen->GetScreen()->ScreenPrint(0, 15, "¦­                                          ¦­");
	globalScreen->GetScreen()->ScreenPrint(0, 16, "¦­                                          ¦­");
	globalScreen->GetScreen()->ScreenPrint(0, 17, "¦­                                          ¦­");
	globalScreen->GetScreen()->ScreenPrint(0, 18, "¦­        ¦±¡Ü¦°  space Å°¸¦ ´­·¯ÁÖ¼¼¿ä     ¦­");
	globalScreen->GetScreen()->ScreenPrint(0, 19, "¦­                                          ¦­");
	globalScreen->GetScreen()->ScreenPrint(0, 20, "¦­                                          ¦­");
	globalScreen->GetScreen()->ScreenPrint(0, 21, "¦­                                          ¦­");
	globalScreen->GetScreen()->ScreenPrint(0, 22, "¦±¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦°");
}

void FootballManager::ReadyScreen()
{
	char string[100];

	globalScreen->GetScreen()->ScreenPrint(0, 0, "¦®¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¯");
	globalScreen->GetScreen()->ScreenPrint(0, 1, "¦­¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¦­");
	globalScreen->GetScreen()->ScreenPrint(0, 2, "¦­¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¦­");
	globalScreen->GetScreen()->ScreenPrint(0, 3, "¦­¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¦­");
	globalScreen->GetScreen()->ScreenPrint(0, 4, "¦­¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¦­");
	globalScreen->GetScreen()->ScreenPrint(0, 5, "¦­¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¦­");
	globalScreen->GetScreen()->ScreenPrint(0, 6, "¦­¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¦­");
	globalScreen->GetScreen()->ScreenPrint(0, 7, "¦­¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¦­");
	globalScreen->GetScreen()->ScreenPrint(0, 8, "¦­¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¦­");
	globalScreen->GetScreen()->ScreenPrint(0, 9, "¦­¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¦­");
	globalScreen->GetScreen()->ScreenPrint(0, 10, "¦­¡á¡á¡á¡á¡á                    ¡á¡á¡á¡á¡á¡á¦­");
	sprintf_s(string, "¦­¡á¡á¡á¡á¡á     %d   ½ºÅ×ÀÌÁö   ¡á¡á¡á¡á¡á¡á¦­", g_nStage + 1);
	globalScreen->GetScreen()->ScreenPrint(0, 11, string);
	globalScreen->GetScreen()->ScreenPrint(0, 12, "¦­¡á¡á¡á¡á¡á                    ¡á¡á¡á¡á¡á¡á¦­");
	globalScreen->GetScreen()->ScreenPrint(0, 13, "¦­¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¦­");
	globalScreen->GetScreen()->ScreenPrint(0, 14, "¦­¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¦­");
	globalScreen->GetScreen()->ScreenPrint(0, 15, "¦­¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¦­");
	globalScreen->GetScreen()->ScreenPrint(0, 16, "¦­¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¦­");
	globalScreen->GetScreen()->ScreenPrint(0, 17, "¦­¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¦­");
	globalScreen->GetScreen()->ScreenPrint(0, 18, "¦­¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¦­");
	globalScreen->GetScreen()->ScreenPrint(0, 19, "¦­¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¦­");
	globalScreen->GetScreen()->ScreenPrint(0, 20, "¦­¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¦­");
	globalScreen->GetScreen()->ScreenPrint(0, 21, "¦­¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¦­");
	globalScreen->GetScreen()->ScreenPrint(0, 22, "¦­¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¦­");
	globalScreen->GetScreen()->ScreenPrint(0, 23, "¦±¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦°");
}

void FootballManager::BackScreen()
{
	char string[100];

	globalScreen->GetScreen()->ScreenPrint(0, 0, "¦®¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¯");
	globalScreen->GetScreen()->ScreenPrint(0, 1, "¦­                                          ¦­");
	globalScreen->GetScreen()->ScreenPrint(0, 2, "¦­                                          ¦­");
	globalScreen->GetScreen()->ScreenPrint(0, 3, "¦­                                          ¦­");
	sprintf_s(string, "¦­                                          ¦­½ºÅ×ÀÌÁö: %d", g_nStage + 1);
	globalScreen->GetScreen()->ScreenPrint(0, 4, string);
	globalScreen->GetScreen()->ScreenPrint(0, 5, "¦­                                          ¦­");
	sprintf_s(string, "¦²¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦´Á¦ÇÑ ½Ã°£: %d", fStageInfo[g_nStage]->GetLimitTime() / 1000);
	globalScreen->GetScreen()->ScreenPrint(0, 6, string);
	globalScreen->GetScreen()->ScreenPrint(0, 7, "¦­                                          ¦­");
	sprintf_s(string, "¦­                                          ¦­ÇöÀç ½Ã°£: %d", (clock() - g_GameStartTime) / 1000);
	globalScreen->GetScreen()->ScreenPrint(0, 8, string);
	globalScreen->GetScreen()->ScreenPrint(0, 9, "¦­                                          ¦­");
	sprintf_s(string, "¦­                                          ¦­¸ñÇ¥ °ñÀÎ: %d ", fStageInfo[g_nStage]->GetGoalBall());
	globalScreen->GetScreen()->ScreenPrint(0, 10, string);
	globalScreen->GetScreen()->ScreenPrint(0, 11, "¦­                                          ¦­");
	sprintf_s(string, "¦­                                          ¦­°ñÀÎ °ø °³¼ö: %d ", g_nBallCount);
	globalScreen->GetScreen()->ScreenPrint(0, 12, string);

	globalScreen->GetScreen()->ScreenPrint(0, 13, "¦­                                          ¦­");
	sprintf_s(string, "¦­                                          ¦­");
	globalScreen->GetScreen()->ScreenPrint(0, 14, string);
	globalScreen->GetScreen()->ScreenPrint(0, 15, "¦­                                          ¦­");
	sprintf_s(string, "¦­                                          ¦­");
	globalScreen->GetScreen()->ScreenPrint(0, 16, string);
	globalScreen->GetScreen()->ScreenPrint(0, 17, "¦­                                          ¦­");
	globalScreen->GetScreen()->ScreenPrint(0, 18, "¦­                                          ¦­");
	globalScreen->GetScreen()->ScreenPrint(0, 19, "¦­                                          ¦­");
	globalScreen->GetScreen()->ScreenPrint(0, 20, "¦­                                          ¦­");
	globalScreen->GetScreen()->ScreenPrint(0, 21, "¦­                                          ¦­");
	globalScreen->GetScreen()->ScreenPrint(0, 22, "¦­                                          ¦­");
	globalScreen->GetScreen()->ScreenPrint(0, 23, "¦±¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦°");
}

void FootballManager::GoalMessage(int nX, int nY)
{
	globalScreen->GetScreen()->ScreenPrint(nX, nY, "¡Ù )) °ñÀÎ (( ¡Ú");
	globalScreen->GetScreen()->ScreenPrint(nX, nY + 1, "¡¬(^^')/ ¡¬(\"*')/");
	globalScreen->GetScreen()->ScreenPrint(nX, nY + 2, "   ¡á       ¡á");
	globalScreen->GetScreen()->ScreenPrint(nX, nY + 3, "  ¦¥¦¤    ¦£¦¦");
}

void FootballManager::SuccessScreen()
{
	globalScreen->GetScreen()->ScreenPrint(0, 0, "¦®¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¯");
	globalScreen->GetScreen()->ScreenPrint(0, 1, "¦­                                          ¦­");
	globalScreen->GetScreen()->ScreenPrint(0, 2, "¦­                                          ¦­");
	globalScreen->GetScreen()->ScreenPrint(0, 3, "¦­                                          ¦­");
	globalScreen->GetScreen()->ScreenPrint(0, 4, "¦­                                          ¦­");
	globalScreen->GetScreen()->ScreenPrint(0, 5, "¦­                                          ¦­");
	globalScreen->GetScreen()->ScreenPrint(0, 6, "¦­                ////¡¬¡¬                  ¦­");
	globalScreen->GetScreen()->ScreenPrint(0, 7, "¦­               q ¡ü  ¡ü p                 ¦­");
	globalScreen->GetScreen()->ScreenPrint(0, 8, "¦­               (¦¦¦¡¦¡¦¥)                 ¦­");
	globalScreen->GetScreen()->ScreenPrint(0, 9, "¦­             ¢Ý ¹Ì¼Ç ¼º°ø ¢Ü              ¦­");
	globalScreen->GetScreen()->ScreenPrint(0, 10, "¦­                                          ¦­");
	globalScreen->GetScreen()->ScreenPrint(0, 11, "¦­                                          ¦­");
	globalScreen->GetScreen()->ScreenPrint(0, 12, "¦­                                          ¦­");
	globalScreen->GetScreen()->ScreenPrint(0, 13, "¦­                                          ¦­");
	globalScreen->GetScreen()->ScreenPrint(0, 14, "¦­                                          ¦­");
	globalScreen->GetScreen()->ScreenPrint(0, 15, "¦­                                          ¦­");
	globalScreen->GetScreen()->ScreenPrint(0, 16, "¦­                                          ¦­");
	globalScreen->GetScreen()->ScreenPrint(0, 17, "¦­                                          ¦­");
	globalScreen->GetScreen()->ScreenPrint(0, 18, "¦­                                          ¦­");
	globalScreen->GetScreen()->ScreenPrint(0, 19, "¦­                                          ¦­");
	globalScreen->GetScreen()->ScreenPrint(0, 20, "¦­                                          ¦­");
	globalScreen->GetScreen()->ScreenPrint(0, 21, "¦­                                          ¦­");
	globalScreen->GetScreen()->ScreenPrint(0, 22, "¦­                                          ¦­");
	globalScreen->GetScreen()->ScreenPrint(0, 23, "¦±¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦°");
}

void FootballManager::FailureScreen()
{
	globalScreen->GetScreen()->ScreenPrint(0, 0, "¦®¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¯");
	globalScreen->GetScreen()->ScreenPrint(0, 1, "¦­                                          ¦­");
	globalScreen->GetScreen()->ScreenPrint(0, 2, "¦­                                          ¦­");
	globalScreen->GetScreen()->ScreenPrint(0, 3, "¦­                                          ¦­");
	globalScreen->GetScreen()->ScreenPrint(0, 4, "¦­                                          ¦­");
	globalScreen->GetScreen()->ScreenPrint(0, 5, "¦­                                          ¦­");
	globalScreen->GetScreen()->ScreenPrint(0, 6, "¦­                                          ¦­");
	globalScreen->GetScreen()->ScreenPrint(0, 7, "¦­                                          ¦­");
	globalScreen->GetScreen()->ScreenPrint(0, 8, "¦­                                          ¦­");
	globalScreen->GetScreen()->ScreenPrint(0, 9, "¦­                                          ¦­");
	globalScreen->GetScreen()->ScreenPrint(0, 10, "¦­                                          ¦­");
	globalScreen->GetScreen()->ScreenPrint(0, 11, "¦­                    ¹Ì¼Ç ½ÇÆÐ !!!!        ¦­");
	globalScreen->GetScreen()->ScreenPrint(0, 12, "¦­                                          ¦­");
	globalScreen->GetScreen()->ScreenPrint(0, 13, "¦­                                          ¦­");
	globalScreen->GetScreen()->ScreenPrint(0, 14, "¦­                 ¡Ü¦³¦¬¦¯                 ¦­");
	globalScreen->GetScreen()->ScreenPrint(0, 15, "¦­                   ¦°  ¦±                 ¦­");
	globalScreen->GetScreen()->ScreenPrint(0, 16, "¦­                  ¡á¡á¡á¡á                ¦­");
	globalScreen->GetScreen()->ScreenPrint(0, 17, "¦­                                          ¦­");
	globalScreen->GetScreen()->ScreenPrint(0, 18, "¦­        ´Ù½Ã ÇÏ½Ã°Ú½À´Ï±î? (y/n)          ¦­");
	globalScreen->GetScreen()->ScreenPrint(0, 19, "¦­                                          ¦­");
	globalScreen->GetScreen()->ScreenPrint(0, 20, "¦­                                          ¦­");
	globalScreen->GetScreen()->ScreenPrint(0, 21, "¦­                                          ¦­");
	globalScreen->GetScreen()->ScreenPrint(0, 22, "¦±¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦°");
}

void FootballManager::ResultScreen()
{
	char string[100];
	globalScreen->GetScreen()->ScreenPrint(0, 0, "¦®¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¯");
	globalScreen->GetScreen()->ScreenPrint(0, 1, "¦­                                          ¦­");
	globalScreen->GetScreen()->ScreenPrint(0, 2, "¦­                                          ¦­");
	globalScreen->GetScreen()->ScreenPrint(0, 3, "¦­             ¡à¦¬¦¬¦¬¡à                   ¦­");
	globalScreen->GetScreen()->ScreenPrint(0, 4, "¦­                                          ¦­");
	globalScreen->GetScreen()->ScreenPrint(0, 5, "¦­                                          ¦­");
	globalScreen->GetScreen()->ScreenPrint(0, 6, "¦­                                          ¦­");
	globalScreen->GetScreen()->ScreenPrint(0, 7, "¦­                                          ¦­");
	sprintf_s(string, "¦­      ¼º°øÇÑ ½ºÅ×ÀÌÁö :  %2d               ¦­", g_nStage + 1);
	globalScreen->GetScreen()->ScreenPrint(0, 8, string);
	globalScreen->GetScreen()->ScreenPrint(0, 9, "¦­                                          ¦­");
	globalScreen->GetScreen()->ScreenPrint(0, 10, "¦­                                          ¦­");
	globalScreen->GetScreen()->ScreenPrint(0, 11, "¦­   ___¢Æ¢Æ¢Æ___                           ¦­");
	globalScreen->GetScreen()->ScreenPrint(0, 12, "¦­     (*^  ^*)                             ¦­");
	globalScreen->GetScreen()->ScreenPrint(0, 13, "¦­ =====¡Û==¡Û=====                         ¦­");
	globalScreen->GetScreen()->ScreenPrint(0, 14, "¦­                                          ¦­");
	globalScreen->GetScreen()->ScreenPrint(0, 15, "¦­                                          ¦­");
	globalScreen->GetScreen()->ScreenPrint(0, 16, "¦­                                          ¦­");
	globalScreen->GetScreen()->ScreenPrint(0, 17, "¦­                                          ¦­");
	globalScreen->GetScreen()->ScreenPrint(0, 18, "¦­                      ¦±¡Ü¦°              ¦­");
	globalScreen->GetScreen()->ScreenPrint(0, 19, "¦­                                          ¦­");
	globalScreen->GetScreen()->ScreenPrint(0, 20, "¦­                                          ¦­");
	globalScreen->GetScreen()->ScreenPrint(0, 21, "¦­                                          ¦­");
	globalScreen->GetScreen()->ScreenPrint(0, 22, "¦±¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦°");
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
			if (fPlayer->nMoveX > 2) // ¿ÞÂÊ Ãæµ¹ °æ°è ÁÂÇ¥ Ã¼Å©
			{
				fPlayer->nMoveX--;
				nRemain = g_nLength - fPlayer->nCenterX + 1; // ÀüÃ¼ ±æÀÌ - ( Áß½É ÁÂÇ¥ + 1 )Àº ³²Àº ±æÀÌ
															  // Note: 2ÄÃ·³¾¿ ÀÌµ¿ÇÏ±â À§ÇÑ ºÎºÐ ( ÆÈÀÌ °ÉÄ£ °æ¿ì ) 
				if (fPlayer->nMoveX - fPlayer->nCenterX < 2 || fPlayer->nMoveX + nRemain > 43)
					fPlayer->nMoveX--;

				fPlayer->SetnX(fPlayer->nMoveX - fPlayer->nCenterX);
			}
			break;
		case 'l':
			if (fPlayer->nMoveX + 1 < 43) // ¿À¸¥ÂÊ Ãæµ¹ °æ°è ÁÂÇ¥ Ã¼Å©
			{
				fPlayer->nMoveX++;
				nRemain = g_nLength - fPlayer->nCenterX + 1; // ÀüÃ¼ ±æÀÌ - ( Áß½É ÁÂÇ¥ + 1 )Àº ³²Àº ±æÀÌ
															  // Note: 2ÄÃ·³¾¿ ÀÌµ¿ÇÏ±â À§ÇÑ ºÎºÐ ( ÆÈÀÌ °ÉÄ£ °æ¿ì )
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
				//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[5], 0, &g_Channel[5]); // ½¸ µ¿ÀÛ ¼Ò¸® Ãâ·Â
			}
			break;

		case 'y':
		case 'Y':
			if (g_GameState == FAILED)
			{
				Init();
				g_GameState = READY;
				//FMOD_Channel_Stop( g_Channel[2] );  // ¹Ì¼Ç ½ÇÆÐ »ç¿îµå Ãâ·Â ÁßÁö 
				//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[3], 0, &g_Channel[3]);
			}
			break;
		case 'n':
		case 'N':
			if (g_GameState == FAILED)
			{
				g_GameState = RESULT;
				//FMOD_Channel_Stop( g_Channel[2] );  // ¹Ì¼Ç ½ÇÆÐ »ç¿îµå Ãâ·Â ÁßÁö							
			}
			break;

		case ' ':
			if (g_GameState == INIT && g_nStage == 0)
			{
				g_GameState = READY;
				//FMOD_Channel_Stop( g_Channel[0] ); // ¹è°æÀ½ ÁßÁö
				//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[3], 0, &g_Channel[3]); // ready »ç¿îµå
				g_UpdateOldTime = clock();  // ready¸¦ ÀÏÁ¤½Ã°£ Áö¼ÓÇØ ÁÖ±â À§ÇØ 							
			}
			break;
		}
	}

	return true;
}

void FootballManager::Update()
{
	clock_t CurTime = clock();
	int nLength = fGoalpost->GetnLength() * 2 + 1; // Note: ¹è¿­ÀÇ ÃÖ´ë ±æÀÌ

	switch (g_GameState)
	{
	case READY:
		if (CurTime - g_UpdateOldTime > 2000)  // 2ÃÊ
		{
			g_GameState = RUNNING;
			g_GameStartTime = CurTime;

			//FMOD_Channel_Stop( g_Channel[3] );  // ready »ç¿îµå ÁßÁö
			//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[1], 0, &g_Channel[1]); // running ¹è°æÀ½
		}
		break;
	case RUNNING:
		if (CurTime - g_GameStartTime > g_LimitTime) // Note: Á¦ÇÑ ½Ã°£
		{
			g_GameState = STOP;
			return;
		}
		else {
			// Note: °ñ´ë
			if (CurTime - fGoalpost->OldTime > fGoalpost->MoveTime)
			{
				fGoalpost->OldTime = CurTime;
				if (fGoalpost->nMoveX + fGoalpost->GetnDist() >= 2 && ((fGoalpost->GetnLineX(nLength - 1) + 3) + fGoalpost->GetnDist()) <= 43)
				{
					fGoalpost->nMoveX += fGoalpost->GetnDist();
					fGoalpost->SetnLineX();
				}
				else {
					fGoalpost->SetnDist(fGoalpost->GetnDist() * -1); // -1 ÀÌ ¹æÇâÀ» ¹Ù²Ù¾î ÁÜ.
				}
			}

			if (fBall->GetIsReady() == false) // ÀÌµ¿ ÁßÀÏ ¶§ 
			{	// ÀÌµ¿ ½Ã°£ °£°Ý¿¡ ÀÇÇÑ ÀÌµ¿
				if ((CurTime - fBall->OldTime) > fBall->MoveTime)
				{
					if (fBall->nMoveY - 1 > 0)
					{
						fBall->nMoveY--;
						fBall->OldTime = CurTime; // ´ÙÀ½ ÀÌµ¿ ½Ã°¢°ú ºñ±³ÇÏ±â À§ÇØ ÇöÀç ½Ã°£À» ÀÌÀü ½Ã°£ º¯¼ö¿¡ ÀúÀå

												   // °ñ´ë ¶óÀÎ Ãæµ¹
						if (fBall->nMoveX >= fGoalpost->GetnLineX(0) && fBall->nMoveX + 1 <= fGoalpost->GetnLineX(nLength - 1) + 1)
						{
							if (fBall->nMoveY <= fGoalpost->nMoveY)
							{   // °ø ÃÊ±âÈ­
								fBall->SetIsReady(1);
								fBall->nMoveX = fPlayer->nMoveX;
								fBall->nMoveY = fPlayer->nMoveY - 1;
								g_nBallCount++;  // °ñÀÎÇÑ °øÀÇ °³¼ö										

								if (g_nBallCount == g_nGoalBallCount) // °ø°ú ¸ñÇ¥ °ø°úÀÇ °³¼ö°¡ °°À¸¸é SUCCESS
								{
									g_GameState = STOP;
									g_nGoal = 1;
									return;
								}

								// È¿°ú Ãâ·Â
								if (g_nIsGoal == 0)
								{
									g_nIsGoal = 1;
									fEffect->SetStartTime(CurTime);
								}

								// °ñÀÎ »ç¿îµå Ãâ·Â
								//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[6], 0, &g_Channel[6]); // °ñÀÎ »ç¿îµå ¿Í¿ì~
							}
							// °ñ´ë Ãæµ¹ 
						}
						else if ((fBall->nMoveX >= fGoalpost->GetnLineX(0) - 2 && fBall->nMoveX <= fGoalpost->GetnLineX(0) - 1) ||
							(fBall->nMoveX + 1 >= fGoalpost->GetnLineX(0) - 2 && fBall->nMoveX + 1 <= fGoalpost->GetnLineX(0) - 1) ||
							(fBall->nMoveX >= fGoalpost->GetnLineX(nLength - 1) + 2 && fBall->nMoveX <= fGoalpost->GetnLineX(nLength - 1) + 3) ||
							(fBall->nMoveX + 1 >= fGoalpost->GetnLineX(nLength - 1) + 2 && fBall->nMoveX + 1 <= fGoalpost->GetnLineX(nLength - 1) + 3))
						{
							if (fBall->nMoveY <= fGoalpost->nMoveY)
							{   // °ø ÃÊ±âÈ­
								fBall->SetIsReady(1);
								fBall->nMoveX = fPlayer->nMoveX;
								fBall->nMoveY = fPlayer->nMoveY - 1;
							}
						}
					}
					else { // °ø ÃÊ±âÈ­
						fBall->SetIsReady(1);
						fBall->nMoveX = fPlayer->nMoveX;
						fBall->nMoveY = fPlayer->nMoveY - 1;
					}
				}
			}
			else {
				fBall->nMoveX = fPlayer->nMoveX;
			}

			// È¿°ú 
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
			//FMOD_Channel_Stop( g_Channel[1] );  // running »ç¿îµå ÁßÁö
			//FMOD_Channel_Stop( g_Channel[1] );  // running »ç¿îµå ÁßÁö

			//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[4], 0, &g_Channel[4]); // ¹Ì¼Ç ¼º°ø »ç¿îµå
		}
		else {
			g_GameState = FAILED;
			//FMOD_Channel_Stop( g_Channel[1] );  // running »ç¿îµå ÁßÁö
			//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[2], 0, &g_Channel[2]); // ¹Ì¼Ç ½ÇÆÐ »ç¿îµå
		}
		break;
	case SUCCESS:
		if (CurTime - g_UpdateOldTime > 3000)
		{
			g_UpdateOldTime = CurTime;
			++g_nStage;
			Init();
			g_GameState = READY;
			//FMOD_Channel_Stop( g_Channel[4] );  // ¹Ì¼Ç ¼º°ø »ç¿îµå Ãâ·Â ÁßÁö					
			//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[3], 0, &g_Channel[3]); //READY »ç¿îµå 
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
		globalScreen->GetScreen()->ScreenPrint(fGoalpost->nMoveX, fGoalpost->nMoveY, "¡à");
		nLength = fGoalpost->GetnLength() * 2 + 1;

		for (i = 0; i < nLength; i++)
			globalScreen->GetScreen()->ScreenPrint(fGoalpost->GetnLineX(i), fGoalpost->nMoveY, "¦¬");

		globalScreen->GetScreen()->ScreenPrint(fGoalpost->GetnLineX(nLength - 1) + 2, fGoalpost->nMoveY, "¡à");

		// Note: È¿°ú Ãâ·Â  	
		if (g_nIsGoal == 1)
		{
			GoalMessage(10, 10);
		}

		// Note: 2 ÄÃ·³¾¿ Å¬¸®ÇÎ 
		if (fPlayer->GetnX() < 2)  //  ¿ÞÂÊ Å¬¸®ÇÎ Ã³¸®
			globalScreen->GetScreen()->ScreenPrint(2, fPlayer->nMoveY, &g_strPlayer[(fPlayer->GetnX() - 2)*-1]);	 // ÁÂÇ¥¸¦ ¹è¿­ ÀÎµ¦½º 
		else if (fPlayer->nMoveX + (g_nLength - fPlayer->nCenterX + 1) > 43) // ¿À¸¥ÂÊ Å¬¸®ÇÎ Ã³¸®
		{
			strncat_s(string, g_strPlayer, g_nLength - ((fPlayer->nMoveX + fPlayer->nCenterX + 1) - 43));
			globalScreen->GetScreen()->ScreenPrint(fPlayer->GetnX(), fPlayer->nMoveY, string);
		}
		else { // 1 ÄÃ·³¾¿ ÀÌµ¿
			globalScreen->GetScreen()->ScreenPrint(fPlayer->GetnX(), fPlayer->nMoveY, g_strPlayer);
		}

		globalScreen->GetScreen()->ScreenPrint(fBall->nMoveX, fBall->nMoveY, "¢Á");
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

	// Note: ·»´õ¸µ ³¡ 
	globalScreen->GetScreen()->ScreenFlipping();
}
