/*
	api
		1) winmain
		2) 메시지처리함수
*/

#include <Windows.h>

// 함수 선언 : 메시지 처리함수 선언
LRESULT CALLBACK WndMsgProc(HWND, UINT, WPARAM, LPARAM);

// WINMAIN함수
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance
	, LPSTR lpszCmdLine, int nCmdShow) {
	HWND hwnd;
	MSG  msg;
	WNDCLASS wc;


	static LPCTSTR szAppName = "EasyText";		// 윈도우 클래스 이름
	static LPCTSTR szTitleName = "Hello API";	// 타이틀 바에 출력될 문자열

	// 1. 윈도우 클래스를 설정
	// 구조체   --> 구조체이름.멤버변수
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndMsgProc;   // 메시지 처리함수 등록
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = szAppName;

	// 2. 윈도우 클래스를 레지스트리에 등록
	RegisterClass(&wc);

	// 3. 메모리에 생성
	hwnd = CreateWindow(szAppName
		, szTitleName
		, WS_EX_OVERLAPPEDWINDOW
		, CW_USEDEFAULT   // X좌표)
		, CW_USEDEFAULT   // Y좌표
		, CW_USEDEFAULT   // 윈도우 폭
		, CW_USEDEFAULT   // 윈도우 높이
		, NULL				// 부모 윈도우 핸들
		, NULL				// 메뉴 혹은 자식 윈도우 식별자
		, hInstance
		, NULL				// createstruct 구조체를 통해 전달되는 값
	);

	// 메모리에 create되었는지 확인
	if (!hwnd)	// 윈도우 생성 실패
	{
		return FALSE;
	}

	// 4. 화면에 메모리에 생성된 윈도우를 화면 보여주기
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	// 5. 메시지 루프 -> 메시지 큐로부터 메시지를 읽어서 번역해서 메시지 처리함수로 전달
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}


// 함수 정의 : 메시지처리함수 정의
LRESULT CALLBACK WndMsgProc(HWND hwnd, UINT uMsg
	, WPARAM wParam, LPARAM lParam) {
	PAINTSTRUCT ps;
	HDC hdc;
	RECT rect;		// 사각형 LEFT RIGH, TOP, BOTTOM
	POINT MousePoint;	// point구조체 x, y

	switch (uMsg) {
	case WM_CREATE:  // 윈도우가 시작될때
		MessageBox(hwnd, TEXT("WM_CREATE"), TEXT("윈도우가 시작할때")
			, MB_ICONEXCLAMATION);
		break;
	case WM_LBUTTONDOWN:
		// WM_PAINT 이외서 HDC를 얻는 방법은 GetDC
		hdc = GetDC(hwnd);
		// 클라이언트 영역에 중앙을 계산하는 함수
		GetClientRect(hwnd, &rect);
		DrawText(hdc, "TEST API", strlen("TEST API")
			, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		ReleaseDC(hwnd, hdc);
		break;
	case WM_PAINT:  // 클라이언 영역에 출력관련된 역할
		// 그리기 도구 얻는 방법
		hdc = BeginPaint(hwnd, &ps);
		TextOut(hdc, 10, 10, TEXT("내손으로 만든 API")
			, strlen("내손으로 만든 API"));
		EndPaint(hwnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);  //WM_QUIT 메시지를 발생시켜 메시지 루프를 중단
		break;
	default:   // 처리하지 않는 메시지
		return DefWindowProc(hwnd, uMsg, wParam, lParam);

	}
	return 0;
}