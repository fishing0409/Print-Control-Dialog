
// PrnCntDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "PrnCnt.h"
#include "PrnCntDlg.h"
#include "afxdialogex.h"
#include "Winspool.h"
#include "stdio.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CPrnCntDlg 대화 상자



CPrnCntDlg::CPrnCntDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PRNCNT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPrnCntDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_comboPrnList);
	DDX_Control(pDX, IDC_LIST1, m_listboxDataLog);
}

BEGIN_MESSAGE_MAP(CPrnCntDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CPrnCntDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CPrnCntDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CPrnCntDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CPrnCntDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CPrnCntDlg::OnBnClickedButton5)
END_MESSAGE_MAP()


// CPrnCntDlg 메시지 처리기

BOOL CPrnCntDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	SetPrintList();

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CPrnCntDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CPrnCntDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CPrnCntDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CPrnCntDlg::OnBnClickedButton1()
{
	WCHAR wszPrintName[MAX_PATH] = { 0 };
	m_comboPrnList.GetLBText(m_comboPrnList.GetCurSel(), wszPrintName);
	if (wcslen(wszPrintName) > 0 && SetPrinterStatus(wszPrintName, PRINTER_STATUS_BUSY))
	{
		WCHAR wszDataLog[MAX_PATH] = { 0 };
		swprintf_s(wszDataLog, MAX_PATH, L"Print Name = %s [On-Line]", wszPrintName);
		SetDataLog(wszDataLog);
	}
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CPrnCntDlg::OnBnClickedButton2()
{
	WCHAR wszPrintName[MAX_PATH] = { 0 };
	m_comboPrnList.GetLBText(m_comboPrnList.GetCurSel(), wszPrintName);
	if (wcslen(wszPrintName) > 0 && SetPrinterStatus(wszPrintName, PRINTER_STATUS_OFFLINE))
	{
		WCHAR wszDataLog[MAX_PATH] = { 0 };
		swprintf_s(wszDataLog, MAX_PATH, L"Print Name = %s [Off-Line]", wszPrintName);
		SetDataLog(wszDataLog);
	}

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CPrnCntDlg::OnBnClickedButton3()
{
	WCHAR wszPrintName[MAX_PATH] = { 0 };
	m_comboPrnList.GetLBText(m_comboPrnList.GetCurSel(), wszPrintName);
	if (wcslen(wszPrintName) > 0)
		GetPrinterJobList(wszPrintName);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CPrnCntDlg::OnBnClickedButton4()
{
	WCHAR wszPrintName[MAX_PATH] = { 0 };
	m_comboPrnList.GetLBText(m_comboPrnList.GetCurSel(), wszPrintName);
	if (wcslen(wszPrintName) > 0 )
	{
		WCHAR wszJob[MAX_PATH] = { 0 };
		m_listboxDataLog.GetText(m_listboxDataLog.GetCurSel(), wszJob);

		if (wcslen(wszJob) > 0)
		{
			WCHAR split_type[] = L"|";
			WCHAR* p_next_token = NULL;
			WCHAR* p_token = _tcstok_s(wszJob, split_type, &p_next_token);

			if (p_token != NULL)
			{
				DWORD dwJob = static_cast<DWORD>(wcstod(p_token, L'\0'));
				SetPrinterJobList(wszPrintName, dwJob, JOB_CONTROL_PAUSE);
			}
		}
		else
		{
			SetPrinterJobList(wszPrintName, NULL, JOB_CONTROL_PAUSE);
		}
	}
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CPrnCntDlg::OnBnClickedButton5()
{
	WCHAR wszPrintName[MAX_PATH] = { 0 };
	m_comboPrnList.GetLBText(m_comboPrnList.GetCurSel(), wszPrintName);
	if (wcslen(wszPrintName) > 0)
	{
		WCHAR wszJob[MAX_PATH] = { 0 };
		m_listboxDataLog.GetText(m_listboxDataLog.GetCurSel(), wszJob);

		if (wcslen(wszJob) > 0)
		{
			WCHAR split_type[] = L"|";
			WCHAR* p_next_token = NULL;
			WCHAR* p_token = _tcstok_s(wszJob, split_type, &p_next_token);

			if (p_token != NULL)
			{
				DWORD dwJob = static_cast<DWORD>(wcstod(p_token, L'\0'));
				SetPrinterJobList(wszPrintName, dwJob, JOB_CONTROL_RESUME);
			}
		}
		else
		{
			SetPrinterJobList(wszPrintName, NULL, JOB_CONTROL_RESUME);
		}
	}
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

BOOL CPrnCntDlg::SetDataLog(LPTSTR wszLog, BOOL bReset)
{
	if(bReset)
		m_listboxDataLog.ResetContent();
	if(wcslen(wszLog) > 0)
		m_listboxDataLog.AddString(wszLog);
	return TRUE;
}

BOOL CPrnCntDlg::SetPrintList()
{
	PRINTER_INFO_4* pi;
	DWORD cbNeed, cbReturn;

	EnumPrinters(PRINTER_ENUM_LOCAL, NULL, 4, NULL, 0, &cbNeed, &cbReturn);
	pi = (PRINTER_INFO_4*)malloc(cbNeed);
	EnumPrinters(PRINTER_ENUM_LOCAL, NULL, 4, (PBYTE)pi, cbNeed, &cbNeed, &cbReturn);
	for (UINT i = 0; i < cbReturn; i++)
	{
		m_comboPrnList.AddString(pi[i].pPrinterName);
	}
	m_comboPrnList.SetCurSel(0);

	return TRUE;
}
BOOL CPrnCntDlg::SetPrinterStatus(LPTSTR pPrinterName, DWORD dwStatus)
{
	HANDLE hPrinter = NULL;
	DWORD dwNeeded = 0;
	PRINTER_INFO_6* pi = NULL;
	DEVMODE* pDevMode = NULL;
	PRINTER_DEFAULTS pd;
	BOOL bFlag;

	// Open printer handle (on Windows NT, you need full-access because you
	// will eventually use SetPrinter)...
	ZeroMemory(&pd, sizeof(pd));
	pd.DesiredAccess = PRINTER_ALL_ACCESS;
	bFlag = OpenPrinter(pPrinterName, &hPrinter, &pd);
	if (!bFlag || (hPrinter == NULL))
		return FALSE;

	// The first GetPrinter tells you how big the buffer should be in 
	// order to hold all of PRINTER_INFO_2. Note that this should fail with 
	// ERROR_INSUFFICIENT_BUFFER.  If GetPrinter fails for any other reason 
	// or dwNeeded isn't set for some reason, then there is a problem...
	SetLastError(0);
	bFlag = GetPrinter(hPrinter, 6, 0, 0, &dwNeeded);
	if ((!bFlag) && (GetLastError() != ERROR_INSUFFICIENT_BUFFER) ||
		(dwNeeded == 0))
	{
		ClosePrinter(hPrinter);
		return FALSE;
	}

	// Allocate enough space for PRINTER_INFO_2...
	pi = (PRINTER_INFO_6*)GlobalAlloc(GPTR, dwNeeded);
	if (pi == NULL)
	{
		ClosePrinter(hPrinter);
		return FALSE;
	}

	// The second GetPrinter fills in all the current settings, so all you
	// need to do is modify what you're interested in...
	bFlag = GetPrinter(hPrinter, 6, (LPBYTE)pi, dwNeeded, &dwNeeded);
	if (!bFlag)
	{
		GlobalFree(pi);
		ClosePrinter(hPrinter);
		return FALSE;
	}

	if(dwStatus != NULL)
		pi->dwStatus = dwStatus;
	//pi->dwStatus = PRINTER_STATUS_OFFLINE;
	//pi->dwStatus = PRINTER_STATUS_PAUSED;
	//pi->dwStatus = PRINTER_STATUS_BUSY;
	// Update printer information...
	bFlag = SetPrinter(hPrinter, 6, (LPBYTE)pi, 0);
	if (!bFlag)
		// The driver doesn't support, or it is unable to make the change...
	{
		GlobalFree(pi);
		ClosePrinter(hPrinter);
		if (pDevMode)
			GlobalFree(pDevMode);
		return FALSE;
	}

	// Tell other apps that there was a change...
	SendMessageTimeout(HWND_BROADCAST, WM_DEVMODECHANGE, 0L,
		(LPARAM)(LPCSTR)pPrinterName,
		SMTO_NORMAL, 1000, NULL);

	// Clean up...
	if (pi)
		GlobalFree(pi);
	if (hPrinter)
		ClosePrinter(hPrinter);
	if (pDevMode)
		GlobalFree(pDevMode);

	return TRUE;
}

int CPrnCntDlg::GetPrinterJobList(LPTSTR pPrinterName)
{
	SetDataLog(L"", TRUE);
	HANDLE      hPrinter;
	DWORD       dwNeeded, dwReturned, i;
	JOB_INFO_2* pJobInfo;
	DWORD       Fail = -1;
	DWORD       TotalPages = 0;

	if (!OpenPrinter(pPrinterName, &hPrinter, NULL))
	{
		SetDataLog(L"GetPrinterJobList() - OpenPrinter Fail");
		return Fail;
	}

	if (!EnumJobs(hPrinter, 0, 0xFFFFFFFF, 2, NULL, 0, &dwNeeded,
		&dwReturned))
	{
		if (GetLastError() != ERROR_INSUFFICIENT_BUFFER)
		{
			ClosePrinter(hPrinter);
			SetDataLog(L"GetPrinterJobList() - ERROR_INSUFFICIENT_BUFFER");
		}
	}
	if ((pJobInfo = (JOB_INFO_2*)malloc(dwNeeded)) == NULL)
	{
		ClosePrinter(hPrinter);
	}

	// Call EnumJobs() again and let it fill out our structures
	if (!EnumJobs(hPrinter, 0, 0xFFFFFFFF, 2, (LPBYTE)pJobInfo,
		dwNeeded, &dwNeeded, &dwReturned))
	{
		ClosePrinter(hPrinter);
		free(pJobInfo);
	}

	ClosePrinter(hPrinter);

	if (dwReturned == 0)
	{
		SetDataLog(L"EnumJob[N]- No Jobs In Queue");
	}
	else
	{
		TotalPages = 0;
		for (i = 0; i < dwReturned; i++)
		{
			WCHAR wszDataLog[MAX_PATH] = { 0 };
			swprintf_s(wszDataLog, MAX_PATH, L"%d| EnumJob[%d]- JobId[%d] Doc[%s] CPage[%d] TPage[%d]"
				,pJobInfo[i].JobId, (i+1), pJobInfo[i].JobId, pJobInfo[i].pDocument, pJobInfo[i].PagesPrinted, pJobInfo[i].TotalPages);
			SetDataLog(wszDataLog, FALSE);
			TotalPages = TotalPages + pJobInfo[i].TotalPages;
		}
	}
	free(pJobInfo);

	return 1;
}

int CPrnCntDlg::SetPrinterJobList(LPTSTR pPrinterName, DWORD JobId,DWORD Command)
{
	HANDLE      hPrinter;
	DWORD       dwNeeded, dwReturned, i;
	JOB_INFO_2* pJobInfo;
	DWORD       Fail = -1;
	DWORD       TotalPages = 0;

	if (!OpenPrinter(pPrinterName, &hPrinter, NULL))
	{
		SetDataLog(L"GetPrinterJobList() - OpenPrinter Fail");
		return Fail;
	}

	// First you call EnumJobs() to find out how much memory you need
	if (!EnumJobs(hPrinter, 0, 0xFFFFFFFF, 2, NULL, 0, &dwNeeded,
		&dwReturned))
	{
		// It should have failed, but if it failed for any reason other
		// than "not enough memory", you should bail out
		if (GetLastError() != ERROR_INSUFFICIENT_BUFFER)
		{
			ClosePrinter(hPrinter);
			SetDataLog(L"GetPrinterJobList() - ERROR_INSUFFICIENT_BUFFER");
		}
	}
	// Allocate enough memory for the JOB_INFO_2 structures plus
	// the extra data - dwNeeded from the previous call tells you
	// the total size needed
	if ((pJobInfo = (JOB_INFO_2*)malloc(dwNeeded)) == NULL)
	{
		ClosePrinter(hPrinter);
	}

	// Call EnumJobs() again and let it fill out our structures
	if (!EnumJobs(hPrinter, 0, 0xFFFFFFFF, 2, (LPBYTE)pJobInfo,
		dwNeeded, &dwNeeded, &dwReturned))
	{
		ClosePrinter(hPrinter);
		free(pJobInfo);
	}

	if (dwReturned == 0)
	{
		SetDataLog(L"EnumJob[N]- No Jobs In Queue");
	}
	else
	{
		for (i = 0; i < dwReturned; i++)
		{
			if(JobId == pJobInfo[i].JobId)
				SetJob(hPrinter, pJobInfo[i].JobId,0, NULL, Command);
			else if(JobId == NULL)
				SetJob(hPrinter, pJobInfo[i].JobId,0, NULL, Command);
		}
	}

	// You're done with the printer handle, close it
	ClosePrinter(hPrinter);
	// Clean up
	free(pJobInfo);

	return 1;
}
