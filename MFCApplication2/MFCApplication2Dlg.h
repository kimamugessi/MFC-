
// MFCApplication2Dlg.h: 헤더 파일
//

#pragma once

// CMFCApplication2Dlg 대화 상자
class CMFCApplication2Dlg : public CDialogEx
{
// 생성입니다.
public:
	CMFCApplication2Dlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.
	~CMFCApplication2Dlg();
// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION2_DIALOG };
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
	afx_msg void OnBnClicked1();
	CString m_strResult;
	BOOL m_bIsCalculated;
	afx_msg void OnBnClickedResult();

	void AppendString(CString strInput);
	afx_msg void OnBnClicked2();
	afx_msg void OnBnClicked3();
	afx_msg void OnBnClicked4();
	afx_msg void OnBnClicked5();
	afx_msg void OnBnClicked6();
	afx_msg void OnBnClicked7();
	afx_msg void OnBnClicked8();
	afx_msg void OnBnClicked9();
	afx_msg void OnBnClicked0();
	afx_msg void OnBnClickedDiv();
	afx_msg void OnBnClickedMul();
	afx_msg void OnBnClickedSub();
	afx_msg void OnBnClickedAdd();
	afx_msg void OnBnClickedDat();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedDel();
	afx_msg void OnBnClickedReset();
	afx_msg void OnBnClickedSquare();
	BOOL PreTranslateMessage(MSG* pMsg);
	CEdit m_editResult;
	afx_msg void OnBnClickedLpar();
	afx_msg void OnBnClickedRpar();
	int m_nOpenParen;
	// CEdit m_strInfo;// CEdit m_strInfo;
//	CString m_strInFo;
	CString m_strInfo;
	CListBox m_listHistory;
	afx_msg void OnLbnSelchangeListHistory();
	afx_msg void OnBnClickedButtonHisClear();

	CFont m_fontResult; //결과창에 폰트 설정

	afx_msg void OnBnClickedButtonHisSave();
	afx_msg void OnBnClickedButtonHisread();
};
