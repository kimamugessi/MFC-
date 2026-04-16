
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
	, m_strResult(_T(""))	//결과창 변수
	, m_strInfo(_T(""))	//안내창 변수
	, m_bIsCalculated(FALSE)	//계산되었나 부울
	,m_nOpenParen(0)	//괄호
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_RESULT, m_strResult);
	DDX_Control(pDX, IDC_EDIT_RESULT, m_editResult);
	DDX_Text(pDX, IDC_EDIT_INFO, m_strInfo);
	DDX_Control(pDX, IDC_LIST_History, m_listHistory);
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
	ON_BN_CLICKED(IDC_RESET, &CMFCApplication2Dlg::OnBnClickedReset)
	ON_BN_CLICKED(IDC_SQUARE, &CMFCApplication2Dlg::OnBnClickedSquare)
	ON_BN_CLICKED(IDC_LPAR, &CMFCApplication2Dlg::OnBnClickedLpar)
	ON_BN_CLICKED(IDC_RPAR, &CMFCApplication2Dlg::OnBnClickedRpar)
	ON_LBN_SELCHANGE(IDC_LIST_History, &CMFCApplication2Dlg::OnLbnSelchangeListHistory)
	ON_BN_CLICKED(IDC_BUTTON_HisClear, &CMFCApplication2Dlg::OnBnClickedButtonHisClear)
	ON_BN_CLICKED(IDC_BUTTON_HisSave, &CMFCApplication2Dlg::OnBnClickedButtonHisSave)
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

	m_fontResult.CreateFont(	//결과창 글씨 
		28,           
		0, 0, 0,
		FW_BOLD,      
		FALSE, FALSE, FALSE,
		DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH,
		_T("Microsoft Sans Serif") 
	);
	m_editResult.SetFont(&m_fontResult);

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	m_bIsCalculated=FALSE;
	m_nOpenParen = 0;
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
//======연산자 우선 순위 반환 함수======
int GetPrecedence(TCHAR op) {
	if (op == _T('+') || op == _T('-')) return 1;
	else if (op == _T('*') || op == _T('/')) return 2;
	return 0;
}

//======연산 수행 함수======
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

//======입력된 문자열을 계산 하는 함수======
double CalculateExpression(CString strExpr) {

	std::stack<double> values;	//숫자 스택
	std::stack<TCHAR> ops;	//연산자 스텍

	int len = strExpr.GetLength();

	for (int i = 0; i < len; i++) {		//문자열의 길이만큼 반복
		TCHAR c = strExpr[i];
		if (isxdigit(c) || c == _T('.')) {	//16진수 또는 '.'일 때
			CString strNum = _T("");
			while (i < len && (_istdigit(strExpr[i]) || strExpr[i] == _T('.'))) { //조건에 맞으면 문자열에 더하기 반복
				strNum += strExpr[i];
				i++;
			}
			values.push(_ttof(strNum));	//_ttof() TCHAR to Float로 변환
			i--;
		}
		else if (c == _T('(')) ops.push(c);	//괄호일 때 
		else if (c == _T(')')) {
			while (!ops.empty() && ops.top() != _T('(')) {	//조건 1. 연산자 스택이 비어있지 않음 2. 맨 위가 '(' 가 아님
				if (values.size() < 2) return 0;	//?
				double val2 = values.top(); values.pop();
				double val1 = values.top(); values.pop();
				TCHAR op = ops.top(); ops.pop();
				values.push(ApplyOp(val1, val2, op));
			}
			if (!ops.empty()) ops.pop(); // '(' 제거
		}
		else if (c == _T('+') || c == _T('-') || c == _T('*') || c == _T('/')) {	//연산자일 때
			if ((c == _T('+') || c == _T('-')) && (i == 0 || strExpr[i - 1] == _T('('))) {	//조건 1. '+' 또는 '-' 2. i가 0 또는 마지막 문자가 '('
				values.push(0);
			}
			while (!ops.empty() && GetPrecedence(ops.top()) >= GetPrecedence(c)) {	//조건 1. 연산자 스택이 비어있지않음 2. 마지막 연산자가 현재 입력 연산자보다 우선순위가 커야함
				if (values.size() < 2) return 0;
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
		if (values.size() < 2) return 0;
		double val2 = values.top(); values.pop();
		double val1 = values.top(); values.pop();
		TCHAR op = ops.top(); ops.pop();
		values.push(ApplyOp(val1, val2, op));
	}

	return values.empty() ? 0 : values.top();	//값 스택이 비었냐? 참->0 거짓->마지막 값 반환
}

//======버튼 선택시 문자열 처리하는 함수=======
void CMFCApplication2Dlg::AppendString(CString strInput)	
{
	UpdateData(TRUE);
	m_strInfo = _T("");
	int len = m_strResult.GetLength();
	TCHAR lastChar = (len > 0) ? m_strResult[len - 1] : _T('\0');
	BOOL bIsLastOp = (lastChar == _T('+') || lastChar == _T('-') || lastChar == _T('*') || lastChar == _T('/'));

	BOOL bIsInputOp = (strInput == _T("+") || strInput == _T("-") || strInput == _T("*") || strInput == _T("/"));
	
	if (m_strResult.IsEmpty() && bIsInputOp) {
		m_strInfo = _T("맨앞에는 연산자가 올 수 없습니다.");
		UpdateData(FALSE);
		return;
	}

	if (bIsInputOp) {
		if (lastChar == _T('(') && (strInput == _T("*") || strInput == _T("/"))) {	//'('뒤에 바로 곱하기와 나누기를 쓸 수 없음
			m_strInfo = _T("'(' 뒤에는 '*'또는 '/'가 올 수 없습니다.");
			UpdateData(FALSE);
			return;
		}
	}
	// 소수점(.) 중복 입력 방지 
	if (strInput == _T("."))
	{
		int nLen = m_strResult.GetLength();
		BOOL bAlreadyHasDot = FALSE;

		// 문자열의 맨 뒤에서부터 앞으로 거꾸로 검사
		for (int i = nLen - 1; i >= 0; i--)
		{
			TCHAR c = m_strResult[i];

			// 사칙연산자를 만나면 그 앞은 '이전 숫자'이므로 탐색을 종료
			if (c == _T('+') || c == _T('-') || c == _T('*') || c == _T('/'))
				break;

			// 연산자를 만나기 전에 이미 점(.)이 발견되면 중복 상태
			if (c == _T('.'))
			{
				bAlreadyHasDot = TRUE;
				break;
			}
		}

		// 이미 점이 있다면 리턴
		if (bAlreadyHasDot)
		{
			m_strInfo = _T("소수점을 확인하세요.");
			UpdateData(FALSE);
			return;
		}
	}

	if (strInput == _T("(")) {	//'('앞에 숫자일 때 * 연산자 자동 삽입
		if (len > 0 && (_istdigit(lastChar) || lastChar == _T(')')))
			m_strResult += _T("*(");
		else m_strResult += _T("(");

		m_nOpenParen++;
		m_bIsCalculated = FALSE;
		UpdateData(FALSE);
		return;
	}

	if (strInput == _T(".")) {	//'.'앞에 연산자일 때 '0' 자동 삽입
		if (!_istdigit(lastChar))
			m_strResult += _T("0.");
		else m_strResult += _T(".");

		m_bIsCalculated = FALSE;
		UpdateData(FALSE);
		return;
	}


	if (strInput == _T(")")) {
		if (m_nOpenParen <= 0) {
			m_strInfo = _T("괄호를 확인하세요.");
			UpdateData(FALSE);
			return;	//'('없을 때 무시
		}

		if (lastChar == _T('(') || bIsLastOp) {
			m_strInfo = _T("불필요한 괄호 입니다.");
			UpdateData(FALSE);
			return;	//'('바로 뒤거나 연산자 뒤이면 무시
		}
		m_strResult += _T(')');
		m_nOpenParen--;
		m_bIsCalculated = FALSE;
		UpdateData(FALSE);
		return;
	}

	if (bIsLastOp && bIsInputOp)	//마지막과 현재 입력 글자 연산자인지
	{
		m_strResult = m_strResult.Left(len - 1);
		m_strResult += strInput;
	}
	else
	{
		if (m_bIsCalculated == TRUE)	//연산이 끝났을 때(숫자형식의 결과값)
		{
			if (bIsInputOp)	//연산자면 기존 결과에 더하기
				m_strResult += strInput;
			else	//아니면(즉, 숫자면 결과창 지우고 새로 작성)
				m_strResult = strInput;

			m_bIsCalculated = FALSE;	//처리가 끝났으므로 FALSE처리
		}
		else		
		{
			if (m_strResult == _T("0") && !bIsInputOp && strInput != _T("."))	//조건 1. 결과값이 초기값(0)  2. 현재 입력 글자가 연산자가 아니고, 입력 문자가 '.'이 아닐 시
				m_strResult = strInput;	//현재 입력 문자=결과 변수
			else
			{
				if(!bIsInputOp&&lastChar==_T(')')) m_strResult += _T("*");
				m_strResult += strInput;	//아니면 입력 문자를 결과 변수에 더하기 (배열 추가)
			}
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

//======'C'버튼 클릭======
void CMFCApplication2Dlg::OnBnClickedReset()	
{
	m_strResult = _T("");
	m_strInfo = _T("");
	m_nOpenParen = 0;
	
	UpdateData(FALSE);
}

//======'CE'버튼 클릭======
void CMFCApplication2Dlg::OnBnClickedDel()	
{
	m_strInfo = _T("");
	int len = m_strResult.GetLength();
	if (len > 0) {
		TCHAR lastChar = m_strResult[len - 1];

		if (lastChar == _T('(')) m_nOpenParen--;
		else if (lastChar == _T(')')) m_nOpenParen++;

		m_strResult = m_strResult.Left(len - 1);
		UpdateData(FALSE);
	}
}

//======'x^2'버튼 클릭======
void CMFCApplication2Dlg::OnBnClickedSquare()	
{
	UpdateData(TRUE);
	m_strInfo = _T("");

	if (m_strResult.IsEmpty())	return;

	int len = m_strResult.GetLength();
	TCHAR m_strLast = m_strResult[len - 1];

	if (m_nOpenParen != 0) {	//괄호가 남아있을 때
		m_strInfo = _T("괄호를 확인하세요.");
		UpdateData(FALSE);
		return;
	}

	if (m_strLast == _T('+') || m_strLast == _T('-') || m_strLast == _T('*') || m_strLast == _T('/')) {	//연산자로 끝날 때
		m_strInfo = _T("수식을 완성하세요.");
		UpdateData(FALSE);
		return;
	}
	
	CString m_strSaveResult = _T("(")+ m_strResult+_T(")")+_T("^2");	//계산식을 임시로 저장
	double dResult = CalculateExpression(m_strResult) * CalculateExpression(m_strResult);
	m_strResult.Format(_T("%g"), dResult);

	m_bIsCalculated = TRUE;

	CString strHistory;
	strHistory.Format(_T("%s = %s"), m_strSaveResult.GetString(), m_strResult.GetString());
	m_listHistory.AddString(strHistory);
	m_listHistory.SetCurSel(m_listHistory.GetCount() - 1);

	//문자열의 길이에 따라 가로 스크롤 자동 조절 
	CClientDC dc(this);	//가상의 도화지 같은..?
	CFont* pOldFont = dc.SelectObject(m_listHistory.GetFont());	//옛폰트
	CSize size = dc.GetTextExtent(strHistory); // 입력된 글자의 실제 픽셀 길이를 계산
	dc.SelectObject(pOldFont);

	if (size.cx + 20 > m_listHistory.GetHorizontalExtent()) {	//GetHorizontalExtent 최대길이 
		m_listHistory.SetHorizontalExtent(size.cx + 20);
	}

	UpdateData(FALSE);
}

//======'='버튼 클릭======
void CMFCApplication2Dlg::OnBnClickedResult()	
{
	UpdateData(TRUE);
	m_strInfo = _T("");

	if (m_strResult.IsEmpty()) return;

	int len = m_strResult.GetLength();
	TCHAR m_strLast = m_strResult[len - 1];

	if (m_bIsCalculated == TRUE)	return;

	if (m_strLast == _T('+') || m_strLast == _T('-') || m_strLast == _T('*') || m_strLast == _T('/')) {	//연산자로 끝날 때
		m_strInfo = _T("수식을 완성하세요.");
		UpdateData(FALSE);
		return;
	}

	if (m_nOpenParen != 0) {	//괄호가 남아있을 때
		m_strInfo=_T("괄호를 확인하세요.");
		UpdateData(FALSE);
		return;
	}
	else
		m_strInfo = _T("");
	CString m_strSaveResult = m_strResult;	//기록창에서 원래 수식을 임시로 저장
	double dResult = CalculateExpression(m_strResult);
	m_strResult.Format(_T("%g"), dResult);

	m_bIsCalculated = TRUE;

	CString strHistory;
	strHistory.Format(_T("%s = %s"), m_strSaveResult.GetString(), m_strResult.GetString());
	m_listHistory.AddString(strHistory);
	m_listHistory.SetCurSel(m_listHistory.GetCount() - 1);	//인덱스가 0부터 시작해서 -1을함

	CClientDC dc(this);
	CFont* pOldFont = dc.SelectObject(m_listHistory.GetFont());
	CSize size = dc.GetTextExtent(strHistory); // 입력된 글자의 실제 픽셀 길이를 계산
	dc.SelectObject(pOldFont);

	if (size.cx + 20 > m_listHistory.GetHorizontalExtent()) {
		m_listHistory.SetHorizontalExtent(size.cx + 20);
	}

	UpdateData(FALSE);
}

//키보드로 입력 가능하게 하는 함수
BOOL CMFCApplication2Dlg::PreTranslateMessage(MSG* pMsg)	
{
	if (pMsg->message == WM_CHAR)
	{
		TCHAR ch = (TCHAR)pMsg->wParam;

		// 숫자이거나 연산자, 소수점인 경우
		if ((ch >= _T('0') && ch <= _T('9')) ||
			ch == _T('+') || ch == _T('-') || ch == _T('*') || ch == _T('/') || ch == _T('.')||ch == _T('(')|| ch == _T(')'))
		{
			CString strInput;
			strInput.Format(_T("%c"), ch);
			AppendString(strInput);  

			return TRUE; // 입력을 가로챘으므로 윈도우에게 "처리 끝났다"고 알려줌
		}

		// '=' 키를 누르면 결과 계산
		if (ch == _T('='))
		{
			OnBnClickedResult();
			return TRUE;
		}
	}

	// 엔터(계산), 백스페이스(지우기), ESC(초기화)
	if (pMsg->message == WM_KEYDOWN)
	{
		switch (pMsg->wParam)
		{
		case VK_RETURN: // 엔터(Enter) 키
			OnBnClickedResult();
			return TRUE;

		case VK_BACK:   // 백스페이스(Backspace) 키
			OnBnClickedDel(); // 만들어두신 지우기 함수 호출
			return TRUE;

		case VK_ESCAPE: // ESC 키
			OnBnClickedCancel(); // 만들어두신 초기화 함수 호출
			return TRUE;
		case VK_DELETE:
			OnBnClickedReset();
			return TRUE;		
		}
	}

	//처리하지 않은 나머지 모든 키보드/마우스 입력은 원래대로 작동
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CMFCApplication2Dlg::OnBnClickedLpar()
{
	AppendString(_T("("));
}

void CMFCApplication2Dlg::OnBnClickedRpar()
{
	AppendString(_T(")"));
}

//기록창에 있는 목록 누를 때
void CMFCApplication2Dlg::OnLbnSelchangeListHistory()
{
	int nIndex = m_listHistory.GetCurSel();

	if (nIndex != LB_ERR) {
		CString strSelected;
		m_listHistory.GetText(nIndex, strSelected);

		int nPos = strSelected.Find(_T('='));
		if (nPos != -1) {
			m_strResult = strSelected.Mid(nPos + 1);
			m_strResult.Trim(); //양옆 띄어쓰기 지우기

			m_bIsCalculated = TRUE;
			UpdateData(FALSE);
		}
	}
}
 
//기록창의 클리어키 누를 때
void CMFCApplication2Dlg::OnBnClickedButtonHisClear()
{
	UpdateData(TRUE);
	m_listHistory.ResetContent();
	UpdateData(FALSE);
}

//폰트 소멸자
CMFCApplication2Dlg::~CMFCApplication2Dlg()	
{
	if (m_fontResult.GetSafeHandle())
		m_fontResult.DeleteObject();
}

//Save 버튼 누를 때
void CMFCApplication2Dlg::OnBnClickedButtonHisSave()
{
	if (m_listHistory.GetCount() == 0) {	//기록이 없을 때
		m_strInfo = (_T("기록이 없습니다."));
		UpdateData(FALSE);
		return;
	}
		CTime d = CTime::GetCurrentTime();

		CString strRootFloder = (_T("E:\\log"));	//고정 폴더
		CString strDataFloder = d.Format(_T("E:\\log\\%y%m%d"));	//새로 생성하는 폴더
		CString strPath = d.Format(_T("E:\\log\\%y%m%d\\%H.ini"));	//파일 저장 경로
		if (!PathFileExists(strRootFloder)) {	//폴더가 없으면 생성(메모리 값 보완용)
			::CreateDirectory(strRootFloder, NULL);
		}
		if (!PathFileExists(strDataFloder)) {	//폴더가 없으면 생성(메모리 값 보완용)
			::CreateDirectory(strDataFloder, NULL);		// :: 는 C++에서 전역 네임스페이스를 명시  사용 이유: 내가 만든게 아닌 윈도우가 제공하는 전용API에서 가져다 쓴 것을 의미
		}
		
		int listCount = m_listHistory.GetCount();
		CStdioFile file;
		if (file.Open(strPath, CFile::modeCreate | CFile::modeWrite | CFile::typeText)) {
			CString strLine;

			for (int i = 0; i < listCount; i++) {
				m_listHistory.GetText(i, strLine);
				strLine += _T("\n");
				file.WriteString(strLine);
			}
			file.Close();
		}
		m_strInfo.Format(_T("%s"), strPath.GetString());
		UpdateData(FALSE);
	
	
}
