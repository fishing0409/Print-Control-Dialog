
// PrnCntDlg.h: 헤더 파일
//

#pragma once


// CPrnCntDlg 대화 상자
class CPrnCntDlg : public CDialogEx
{
// 생성입니다.
public:
	CPrnCntDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PRNCNT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();

	BOOL CPrnCntDlg::SetPrinterStatus(LPTSTR pPrinterName, DWORD dwStatus);
	BOOL CPrnCntDlg::SetPrintList();
	int CPrnCntDlg::GetPrinterJobList(LPTSTR pPrinterName);
	BOOL CPrnCntDlg::SetDataLog(LPTSTR wszLog, BOOL bReset = TRUE);
	int CPrnCntDlg::SetPrinterJobList(LPTSTR pPrinterName, DWORD JobId, DWORD Command);

	CComboBox m_comboPrnList;
	afx_msg void OnBnClickedButton3();
	CListBox m_listboxDataLog;
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
};
