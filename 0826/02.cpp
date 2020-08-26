/*
	api 
		1) winmain
		2) �޽���ó���Լ�
*/

#include <Windows.h>

// �Լ� ���� : �޽��� ó���Լ� ����
LRESULT CALLBACK WndMsgProc(HWND, UINT, WPARAM, LPARAM);

// WINMAIN�Լ�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance
	, LPSTR lpszCmdLine, int nCmdShow) {
	HWND hwnd;
	MSG  msg;
	WNDCLASS wc;

	// 1. ������ Ŭ������ ����
	// ����ü   --> ����ü�̸�.�������
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndMsgProc;   // �޽��� ó���Լ� ���
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL , IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = TEXT("FIRST API");

	// 2. ������ Ŭ������ ������Ʈ���� ���
	RegisterClass(&wc);

	// 3. �޸𸮿� ����
	hwnd = CreateWindow(TEXT("FIRST API")
		, TEXT("FIRST API START")
		, WS_EX_OVERLAPPEDWINDOW
		, CW_USEDEFAULT   // X��ǥ)
		, CW_USEDEFAULT   // Y��ǥ
		, CW_USEDEFAULT   // ������ ��
		, CW_USEDEFAULT   // ������ ����
		, NULL				// �θ� ������ �ڵ�
		, NULL				// �޴� Ȥ�� �ڽ� ������ �ĺ���
		, hInstance
		, NULL				// createstruct ����ü�� ���� ���޵Ǵ� ��
	);

	// �޸𸮿� create�Ǿ����� Ȯ��
	if (!hwnd)	// ������ ���� ����
	{
		return FALSE;
	}

	// 4. ȭ�鿡 �޸𸮿� ������ �����츦 ȭ�� �����ֱ�
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	// 5. �޽��� ���� -> �޽��� ť�κ��� �޽����� �о �����ؼ� �޽��� ó���Լ��� ����
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}


// �Լ� ���� : �޽���ó���Լ� ����
LRESULT CALLBACK WndMsgProc(HWND hwnd, UINT uMsg
						, WPARAM wParam, LPARAM lParam) {
	PAINTSTRUCT ps;
	HDC hdc;
	switch (uMsg) {
	case WM_LBUTTONDOWN:
		MessageBox(hwnd, TEXT("������ API"), TEXT("���� ���� API")
			, MB_ICONEXCLAMATION);
		break;
	case WM_PAINT:  // Ŭ���̾� ������ ��°��õ� ����
		// �׸��� ���� ��� ���
		hdc = BeginPaint(hwnd, &ps);
		TextOut(hdc, 10, 10, TEXT("�������� ���� API")
			, strlen("�������� ���� API"));
		EndPaint(hwnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);  //WM_QUIT �޽����� �߻����� �޽��� ������ �ߴ�
		break;
	default:   // ó������ �ʴ� �޽���
		return DefWindowProc(hwnd, uMsg, wParam, lParam);

	}
	return 0;
}