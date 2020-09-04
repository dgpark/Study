#pragma once


// LogInForm 대화 상자

class LogInFormDlg : public CDialogEx
{
	DECLARE_DYNAMIC(LogInFormDlg)

public:
	LogInFormDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~LogInFormDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LOGINFORM_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedLoginBtn();
	afx_msg void OnBnClickedRegisterBtn();
};
