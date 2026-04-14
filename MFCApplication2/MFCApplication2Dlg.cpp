
// MFCApplication2Dlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MFCApplication2.h"
#include "MFCApplication2Dlg.h"
#include "afxdialogex.h"
#include <stack>
#include <cctype>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

int GetPrecedence(TCHAR op) {
	if (op == _T('+') || op == _T('-')) return 1;
	else if (op == _T('*') || op == _T('/')) return 2;
	return 0;
}
double ApplyOp(double a, double b, TCHAR op) {
	switch (op) {
		case _T('+'): return a + b;
		case _T('-'): return a - b;
		case _T('*'): return a * b;
		case _T('/'): 
			if (b == 0) return 0;
		return a / b;
	}
	return 0;
}

double CalculateExpression(CString strExpr) {
	std::stack<double> values;
	std::stack<TCHAR> ops;

	int len = strExpr.GetLength();

	for (int i = 0; i < len; i++) {
		TCHAR c = strExpr[i];
		if (isxdigit(c) || c == _T('.')) {
			CString strNum = _T("");
			while (i < len && (_istdigit(strExpr[i]) || strExpr[i] == _T('.'))) {
				strNum += strExpr[i];
				i++;
			}
			values.push(_ttof(strNum));
			i--;
		}

		else if (c == _T('+') || c == _T('-') || c == _T('*') || c == _T('/')) {
			while (!ops.empty() && GetPrecedence(ops.top()) >= GetPrecedence(c)) {
				double val2 = values.top(); values.pop();
				double val1 = values.top(); values.pop();
				TCHAR op = ops.top(); ops.pop();
				values.push(ApplyOp(val1, val2, op));
			}
			ops.push(c);
		}
	}

	while (!ops.empty())
	{
		double val2 = values.top(); values.pop();
		double val1 = values.top(); values.pop();
		TCHAR op = ops.top(); ops.pop();
		values.push(ApplyOp(val1, val2, op));
	}

	return values.empty() ? 0.0 : values.top();
}

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
public:
	afx_msg void OnBnClicked1();
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


// CMFCApplication2Dlg 대화 상자



CMFCApplication2Dlg::CMFCApplication2Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION2_DIALOG, pParent)
	, m_strResult(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_RESULT, m_strResult);
}

BEGIN_MESSAGE_MAP(CMFCApplication2Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_1, &CMFCApplication2Dlg::OnBnClicked1)
	ON_BN_CLICKED(IDRESULT, &CMFCApplication2Dlg::OnBnClickedResult)
	ON_BN_CLICKED(IDC_2, &CMFCApplication2Dlg::OnBnClicked2)
	ON_BN_CLICKED(IDC_3, &CMFCApplication2Dlg::OnBnClicked3)
	ON_BN_CLICKED(IDC_4, &CMFCApplication2Dlg::OnBnClicked4)
	ON_BN_CLICKED(IDC_5, &CMFCApplication2Dlg::OnBnClicked5)
	ON_BN_CLICKED(IDC_6, &CMFCApplication2Dlg::OnBnClicked6)
	ON_BN_CLICKED(IDC_7, &CMFCApplication2Dlg::OnBnClicked7)
	ON_BN_CLICKED(IDC_8, &CMFCApplication2Dlg::OnBnClicked8)
	ON_BN_CLICKED(IDC_9, &CMFCApplication2Dlg::OnBnClicked9)
	ON_BN_CLICKED(IDC_0, &CMFCApplication2Dlg::OnBnClicked0)
	ON_BN_CLICKED(IDC_DIV, &CMFCApplication2Dlg::OnBnClickedDiv)
	ON_BN_CLICKED(IDC_MUL, &CMFCApplication2Dlg::OnBnClickedMul)
	ON_BN_CLICKED(IDC_SUB, &CMFCApplication2Dlg::OnBnClickedSub)
	ON_BN_CLICKED(IDC_ADD, &CMFCApplication2Dlg::OnBnClickedAdd)
	ON_BN_CLICKED(IDC_DAT, &CMFCApplication2Dlg::OnBnClickedDat)
	ON_BN_CLICKED(IDCANCEL, &CMFCApplication2Dlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_DEL, &CMFCApplication2Dlg::OnBnClickedDel)
	ON_EN_CHANGE(IDC_EDIT_RESULT, &CMFCApplication2Dlg::OnEnChangeEditResult)
	ON_BN_CLICKED(IDC_RESET, &CMFCApplication2Dlg::OnBnClickedReset)
	ON_BN_CLICKED(IDC_SQUARE, &CMFCApplication2Dlg::OnBnClickedSquare)
END_MESSAGE_MAP()


// CMFCApplication2Dlg 메시지 처리기

BOOL CMFCApplication2Dlg::OnInitDialog()
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
	m_bIsCalculated=FALSE;
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMFCApplication2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCApplication2Dlg::OnPaint()
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
HCURSOR CMFCApplication2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMFCApplication2Dlg::OnBnClickedResult()
{
	UpdateData(TRUE);
	int len = m_strResult.GetLength();
	TCHAR m_strLast= m_strResult[len-1];

	if (m_strResult.IsEmpty()) return;

	if (m_bIsCalculated == TRUE)	return;

	if (m_strLast == _T('+')|| m_strLast == _T('-')|| m_strLast == _T('*')|| m_strLast == _T('/')) return;
	double dResult = CalculateExpression(m_strResult);
	m_strResult.Format(_T("%g"), dResult);

	m_bIsCalculated = TRUE;

	UpdateData(FALSE);
}
void CMFCApplication2Dlg::AppendString(CString strInput)
{
	UpdateData(TRUE);

	BOOL bIsInputOp = (strInput == _T("+") || strInput == _T("-") || strInput == _T("*") || strInput == _T("/"));
	if (m_strResult == _T("") && m_bIsCalculated == FALSE && bIsInputOp)	return;
	int len = m_strResult.GetLength();
	BOOL bIsLastOp = FALSE;
	if (len > 0)
	{
		TCHAR lastChar = m_strResult[len - 1];
		if (lastChar == _T('+') || lastChar == _T('-') || lastChar == _T('*') || lastChar == _T('/'))
		{
			bIsLastOp = TRUE;
		}
	}

	if (bIsLastOp && bIsInputOp)
	{
		m_strResult = m_strResult.Left(len - 1);
		m_strResult += strInput;
	}
	else
	{
		if (m_bIsCalculated == TRUE)
		{
			if (bIsInputOp)
				m_strResult += strInput;
			else
				m_strResult = strInput;

			m_bIsCalculated = FALSE;
		}
		else
		{
			if (m_strResult == _T("0") && !bIsInputOp && strInput != _T("."))
				m_strResult = strInput;
			else
				m_strResult += strInput;
		}
	}

	UpdateData(FALSE);
}

void CMFCApplication2Dlg::OnBnClicked1()
{
	AppendString(_T("1"));
}

void CMFCApplication2Dlg::OnBnClicked2()
{
	AppendString(_T("2"));
}

void CMFCApplication2Dlg::OnBnClicked3()
{
	AppendString(_T("3"));
}

void CMFCApplication2Dlg::OnBnClicked4()
{
	AppendString(_T("4"));
}

void CMFCApplication2Dlg::OnBnClicked5()
{
	AppendString(_T("5"));
}

void CMFCApplication2Dlg::OnBnClicked6()
{
	AppendString(_T("6"));
}


void CMFCApplication2Dlg::OnBnClicked7()
{
	AppendString(_T("7"));
}

void CMFCApplication2Dlg::OnBnClicked8()
{
	AppendString(_T("8"));
}

void CMFCApplication2Dlg::OnBnClicked9()
{
	AppendString(_T("9"));
}

void CMFCApplication2Dlg::OnBnClicked0()
{
	AppendString(_T("0"));
}

void CMFCApplication2Dlg::OnBnClickedDiv()
{
	AppendString(_T("/"));
}

void CMFCApplication2Dlg::OnBnClickedMul()
{
	AppendString(_T("*"));
}

void CMFCApplication2Dlg::OnBnClickedSub()
{
	AppendString(_T("-"));
}

void CMFCApplication2Dlg::OnBnClickedAdd()
{
	AppendString(_T("+"));
}

void CMFCApplication2Dlg::OnBnClickedDat()
{
	AppendString(_T("."));
}

void CMFCApplication2Dlg::OnBnClickedCancel()
{
	OnOK();
}

void CMFCApplication2Dlg::OnEnChangeEditResult()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CMFCApplication2Dlg::OnBnClickedReset()
{
	m_strResult = _T("");
	UpdateData(FALSE);
}

void CMFCApplication2Dlg::OnBnClickedDel()
{
	int len = m_strResult.GetLength();
	if (len > 0) {
		m_strResult = m_strResult.Left(len - 1);
		UpdateData(FALSE);
	}
}

void CMFCApplication2Dlg::OnBnClickedSquare()
{
	UpdateData(TRUE);

	int len = m_strResult.GetLength();
	TCHAR m_strLast = m_strResult[len - 1];

	if (m_strResult.IsEmpty()) return;

	if (m_bIsCalculated == TRUE)	return;

	if (m_strLast == _T('+') || m_strLast == _T('-') || m_strLast == _T('*') || m_strLast == _T('/')) return;
	double dResult = CalculateExpression(m_strResult)* CalculateExpression(m_strResult);
	m_strResult.Format(_T("%g"), dResult);

	m_bIsCalculated = TRUE;

	UpdateData(FALSE);
}
