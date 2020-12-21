#include "stdafx.h"

CWinThread*	g_pThread = NULL; // 작업 스레드 제어하기 위해 글로벌 변수로 선언

// 스레드가 종료되지 않은 상황에서 응용 프로그램이 먼저 종료될 경우 문제가 될 수 있다.
// ::TerminateThread() API 함수를 이용하여 스레드를 강제종료 시키면서 스레드를 관리하면서
// 사용했던 메모리는 해제되지 못하고 낭비된다.
// => 응용 프로그램이 종되료는 시점을 스레드가 감지하여 스스로 종료되도록 코드를 작성한다.
CEvent		g_ExitEvent;

CWinThread* g_pUIThread = NULL; // 사용자 인터페이스 스레드를 제어하기 위해 전역 변수로 선언