#include "Dudagi_GameManager.h"


GameManager::GameManager()
{
	m_tStage = 3; // 스테이지 개수

	//스테이지 초기화
	m_nStage = 0;

	//객체 생성
	m_Stage = new Stage[m_tStage];
	m_Mangchi = new Mangchi;
	m_Dudagi = new Dudagi[9];

	m_GameStartTime = clock();

	m_nGameState = INIT;

	//stage 초기화
	m_Stage[0].Init(2, 1000 * 10, 6000, 4000);
	m_Stage[1].Init(5, 1000 * 10, 2000, 2000);
	m_Stage[2].Init(50, 1000 * 120, 1000, 1000);
}


GameManager::~GameManager()
{

}


void GameManager::Init()
{
	if (m_nStage == -1)
	{
		m_nStage = 0;
	}

	m_nDudagiCount = 0;
	m_nTotalGrade = 0;

	globalScreen->GetScreen()->ScreenInit();

	//망치 초기화
	m_Mangchi->Init(m_GameStartTime);

	//두더지 초기화
	for (int i = 0; i < 9; i++) { 
		m_Dudagi[i].Init(m_Stage, i);
	}
}

void GameManager::Update()
{
	m_isMangchiAtt = false;

	InputKey();

	clock_t CurTime = clock();

	switch (m_nGameState)
	{
	case READY:
		if (CurTime - m_UpdateOldTime > 2000)  // 2초
		{
			m_nGameState = RUNNING;
			m_GameStartTime = CurTime;
		}
		break;
	case RUNNING:
		if ((CurTime - m_GameStartTime) > m_Stage[m_nStage].GetLimitTime())
		{
			m_nGameState = STOP;
			return;
		}
		else {
			// 두더지 업데이트	
			for (int i = 0; i < 9; i++)
			{
				m_Dudagi[i].Update(CurTime, m_Stage[m_nStage]);
			}

			// 망치 업데이트 
			if(m_isMangchiAtt)
				m_Mangchi->Update(nKey);
			
			if (m_Mangchi->GetAttack())
			{
				// 충돌 테스트 망치는 오직 하나의 두더지만 잡을 수 있기에 하나만 잡았으면 충돌 체크를 빠져 나온다.
				for (int i = 0; i < 9; i++)
				{
					if (m_Dudagi[i].IsDudagiDown(m_Mangchi->GetIndex())) {
						m_nDudagiCount++;
						m_nGrade += 10;
						break;
					}
				}

				// Note: 망치의 상태를 변경해주는 부분 망치로 쳤을 때에 일정한 시간 동안 머물도록 하기 위한 부분
				m_Mangchi->Delay(CurTime);
			}

			m_RemainTime = (m_Stage[m_nStage].GetLimitTime() - (CurTime - m_GameStartTime)) / 1000; // 게임 진행 남은 시간
		}
		break;
	case STOP:
		// 성공이냐 실패를 판단해주어서 출력을 해주는 부분이 와야 한다.
		if (m_Stage[m_nStage].IsSuccess(m_nDudagiCount))
		{
			m_UpdateOldTime = CurTime;
			m_nGameState = SUCCESS;
			m_nTotalGrade += m_nGrade;
		}
		else {
			m_nGameState = FAILED;
		}
		break;
	case SUCCESS:
		if (CurTime - m_UpdateOldTime > 3000)
		{
			m_UpdateOldTime = CurTime;
			m_nGrade = 0;
			++m_nStage;
			Init();
			m_nGameState = READY;
		}
		break;
	}
}

void GameManager::Render()
{
	char string[100];
	globalScreen->GetScreen()->ScreenClear();

	switch (m_nGameState)
	{
	case INIT:
		if (m_nStage == 0)
			InitScreen();		//stage		
		break;

	case READY:
		ReadyScreen();	//stage
		sprintf_s(string, 100, "%d", m_nStage + 1);
		globalScreen->GetScreen()->ScreenPrint(16, 11, string);
		break;

	case RUNNING:
		RunningScreen();//stage

		sprintf_s(string, 100, "목표 두더지 : %d  잡은 두더지 : %d", m_Stage[m_nStage].GetnCatchDudagi() , m_nDudagiCount);
		globalScreen->GetScreen()->ScreenPrint(2, 1, string);
		sprintf_s(string, 100, "스테이지 : %d 점수 : %d 남은 시간 : %d ", m_nStage + 1, m_nGrade, m_RemainTime);
		globalScreen->GetScreen()->ScreenPrint(2, 2, string);

		//dudagi
		for (int i = 0; i < 9; i++)
		{
			m_Dudagi[i].Render();
		}

		//Mangchi
		m_Mangchi->Render(m_Dudagi[m_Mangchi->GetIndex()].GetnX(), m_Dudagi[m_Mangchi->GetIndex()].GetnY());
		break;

	case SUCCESS:
		SuccessScreen();	//stage
		sprintf_s(string, 100, "%d", m_nStage + 1);
		globalScreen->GetScreen()->ScreenPrint(20, 11, string);
		sprintf_s(string, 100, "%d", m_nDudagiCount);
		globalScreen->GetScreen()->ScreenPrint(21, 17, string);
		sprintf_s(string, 100, "%d", m_nTotalGrade);
		globalScreen->GetScreen()->ScreenPrint(14, 19, string);
		break;

	case FAILED:				//stage
		FailureScreen();
		sprintf_s(string, 100, "%d", m_nStage + 1);
		globalScreen->GetScreen()->ScreenPrint(16, 11, string);
		break;

	case RESULT://stage
		ResultScreen();
		sprintf_s(string, 100, "%d", m_nTotalGrade);
		globalScreen->GetScreen()->ScreenPrint(25, 11, string);
		break;
	}
	globalScreen->GetScreen()->ScreenFlipping();
}

void GameManager::InputKey()
{
	if (_kbhit()) {
		if (m_nGameState == RESULT)
			return;

		nKey = NULL;
		nKey = _getch();
		switch (nKey)
		{
		case ' ':
			if (m_nGameState == INIT && m_nStage == 0)
			{
				m_nGameState = READY;
				m_UpdateOldTime = clock();  // ready를 일정시간 지속해 주기 위해 							
			}
			break;
		case '1':  // 망치 키 입력 1 ~ 9까지
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			if (m_Mangchi->GetAttack() == 0 && m_nGameState == RUNNING)
			{
				m_isMangchiAtt = true;
			}
			break;

		case 'y':
		case 'Y':
			if (m_nGameState == FAILED)
			{
				Init();
				m_nGameState = READY;
				//FMOD_Channel_Stop( m_Channel[1] );  // 미션 실패 사운드 출력 중지 
				//FMOD_System_PlaySound( m_System, FMOD_CHANNEL_FREE, m_Sound[2], 0, &m_Channel[2]); // READY 사운드 출력
				m_nGrade = 0;
				m_UpdateOldTime = clock();
			}
			break;
		case 'n':
		case 'N':
			if (m_nGameState == FAILED)
			{
				m_nGameState = RESULT;
				//FMOD_Channel_Stop( m_Channel[1] );  // 미션 실패 사운드 출력 중지							
			}
			break;
		}
	}
}


void GameManager::InitScreen()
{
	globalScreen->GetScreen()->ScreenPrint(0, 0, "┏━━━━━━━━━━━━━━━━━━━━┓");
	globalScreen->GetScreen()->ScreenPrint(0, 1, "┃                                        ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 2, "┃                                        ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 3, "┃                                        ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 4, "┃                                        ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 5, "┃                                        ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 6, "┃                                        ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 7, "┃                                        ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 8, "┃             ////////                   ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 9, "┃             ┃＼ /┃ ＼│/             ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 10, "┃             ┃··┃┏┳┳┓           ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 11, "┃             ┗┓┏┛┗┓┏┛           ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 12, "┃                                        ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 13, "┃                                        ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 14, "┃                                        ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 15, "┃             두더지 잡기 게임           ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 16, "┃                                        ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 17, "┃          space 키를 눌러주세요         ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 18, "┃                                        ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 19, "┃                                        ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 20, "┃                                        ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 21, "┃                                        ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 22, "┃                                        ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 23, "┗━━━━━━━━━━━━━━━━━━━━┛");
}

void GameManager::ReadyScreen()
{
	globalScreen->GetScreen()->ScreenPrint(0, 0, "┏━━━━━━━━━━━━━━━━━━━━┓");
	globalScreen->GetScreen()->ScreenPrint(0, 1, "┃■■■■■■■■■■■■■■■■■■■■┃");
	globalScreen->GetScreen()->ScreenPrint(0, 2, "┃■■■■■■■■■■■■■■■■■■■■┃");
	globalScreen->GetScreen()->ScreenPrint(0, 3, "┃■■■■■■■■■■■■■■■■■■■■┃");
	globalScreen->GetScreen()->ScreenPrint(0, 4, "┃■■■■■■■■■■■■■■■■■■■■┃");
	globalScreen->GetScreen()->ScreenPrint(0, 5, "┃■■■■■■■■■■■■■■■■■■■■┃");
	globalScreen->GetScreen()->ScreenPrint(0, 6, "┃■■■■■■■■■■■■■■■■■■■■┃");
	globalScreen->GetScreen()->ScreenPrint(0, 7, "┃■■■■■■■■■■■■■■■■■■■■┃");
	globalScreen->GetScreen()->ScreenPrint(0, 8, "┃■■■■■■■■■■■■■■■■■■■■┃");
	globalScreen->GetScreen()->ScreenPrint(0, 9, "┃■■■■■■■■■■■■■■■■■■■■┃");
	globalScreen->GetScreen()->ScreenPrint(0, 10, "┃■■■■■                    ■■■■■┃");
	globalScreen->GetScreen()->ScreenPrint(0, 11, "┃■■■■■        스테이지    ■■■■■┃");
	globalScreen->GetScreen()->ScreenPrint(0, 12, "┃■■■■■                    ■■■■■┃");
	globalScreen->GetScreen()->ScreenPrint(0, 13, "┃■■■■■■■■■■■■■■■■■■■■┃");
	globalScreen->GetScreen()->ScreenPrint(0, 14, "┃■■■■■■■■■■■■■■■■■■■■┃");
	globalScreen->GetScreen()->ScreenPrint(0, 15, "┃■■■■■■■■■■■■■■■■■■■■┃");
	globalScreen->GetScreen()->ScreenPrint(0, 16, "┃■■■■■■■■■■■■■■■■■■■■┃");
	globalScreen->GetScreen()->ScreenPrint(0, 17, "┃■■■■■■■■■■■■■■■■■■■■┃");
	globalScreen->GetScreen()->ScreenPrint(0, 18, "┃■■■■■■■■■■■■■■■■■■■■┃");
	globalScreen->GetScreen()->ScreenPrint(0, 19, "┃■■■■■■■■■■■■■■■■■■■■┃");
	globalScreen->GetScreen()->ScreenPrint(0, 20, "┃■■■■■■■■■■■■■■■■■■■■┃");
	globalScreen->GetScreen()->ScreenPrint(0, 21, "┃■■■■■■■■■■■■■■■■■■■■┃");
	globalScreen->GetScreen()->ScreenPrint(0, 22, "┃■■■■■■■■■■■■■■■■■■■■┃");
	globalScreen->GetScreen()->ScreenPrint(0, 23, "┗━━━━━━━━━━━━━━━━━━━━┛");
}

void GameManager::SuccessScreen()
{
	globalScreen->GetScreen()->ScreenPrint(0, 0, "┏━━━━━━━━━━━━━━━━━━━━┓");
	globalScreen->GetScreen()->ScreenPrint(0, 1, "┃                                        ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 2, "┃                                        ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 3, "┃                                        ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 4, "┃             // / // ＼＼＼             ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 5, "┃             │/＼    /＼│♬           ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 6, "┃             │≡  ▽  ≡│○           ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 7, "┃              ＼_________///            ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 8, "┃                                        ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 9, "┃                                        ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 10, "┃                                        ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 11, "┃                       스테이지         ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 12, "┃                                        ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 13, "┃                   미션 성공 !!!!       ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 14, "┃                                        ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 15, "┃                                        ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 16, "┃                                        ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 17, "┃     잡은 두더지 :                      ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 18, "┃                                        ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 19, "┃     총점 :                             ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 20, "┃                                        ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 21, "┃                                        ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 22, "┃                                        ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 23, "┗━━━━━━━━━━━━━━━━━━━━┛");
}

void GameManager::RunningScreen()
{
	globalScreen->GetScreen()->ScreenPrint(0, 0, "┏━━━━━━━━━━━━━━━━━━━━┓");
	globalScreen->GetScreen()->ScreenPrint(0, 1, "┃                                        ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 2, "┃                                        ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 3, "┃                                        ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 4, "┃                                        ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 5, "┃                                        ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 6, "┃                                        ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 7, "┃                                        ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 8, "┃                                        ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 9, "┃                                        ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 10, "┃                                        ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 11, "┃                                        ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 12, "┃                                        ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 13, "┃                                        ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 14, "┃                                        ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 15, "┃                                        ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 16, "┃                                        ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 17, "┃                                        ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 18, "┃                                        ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 19, "┃                            ○    ●    ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 20, "┃                          ┏■┛┏□┛  ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 21, "┃                            ┛┓  ┛┓  ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 22, "┃                                        ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 23, "┗━━━━━━━━━━━━━━━━━━━━┛");
}

void GameManager::FailureScreen()
{
	globalScreen->GetScreen()->ScreenPrint(0, 0, "┏━━━━━━━━━━━━━━━━━━━━┓");
	globalScreen->GetScreen()->ScreenPrint(0, 1, "┃                                        ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 2, "┃                                        ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 3, "┃                                        ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 4, "┃                                        ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 5, "┃                                        ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 6, "┃             ┎-━━-┒                 ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 7, "┃             d ご,.ご b                 ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 8, "┃             ┃┭─┮┃                 ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 9, "┃             ┖┦│┞┚                 ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 10, "┃               ┕┷┙                   ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 11, "┃                    스테이지            ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 12, "┃                                        ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 13, "┃            미션 실패 !!!!              ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 14, "┃                                        ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 15, "┃                                        ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 16, "┃                                        ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 17, "┃      다시 하시겠습니까? ( y/n )        ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 18, "┃                                        ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 19, "┃                                        ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 20, "┃                                        ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 21, "┃                                        ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 22, "┃                                        ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 23, "┗━━━━━━━━━━━━━━━━━━━━┛");
}

void GameManager::ResultScreen()
{
	globalScreen->GetScreen()->ScreenPrint(0, 0, "┏━━━━━━━━━━━━━━━━━━━━┓");
	globalScreen->GetScreen()->ScreenPrint(0, 1, "┃                                        ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 2, "┃                                        ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 3, "┃                                        ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 4, "┃                                        ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 5, "┃                                        ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 6, "┃                                        ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 7, "┃  (((    두더지 잡기 게임 Score  ))))   ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 8, "┃                                        ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 9, "┃                                        ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 10, "┃                                        ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 11, "┃           총 점수  :                   ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 12, "┃                                        ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 13, "┃                                        ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 14, "┃                                        ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 15, "┃                                        ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 16, "┃                                        ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 17, "┃                                        ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 18, "┃                                        ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 19, "┃                                        ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 20, "┃                                        ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 21, "┃                                        ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 22, "┃                                        ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 23, "┗━━━━━━━━━━━━━━━━━━━━┛");
}