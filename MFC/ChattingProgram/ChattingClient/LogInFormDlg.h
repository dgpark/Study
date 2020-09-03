#pragma once


// LogInForm 대화 상자

class LogInForm : public CDialogEx
{
	DECLARE_DYNAMIC(LogInForm)

public:
	LogInForm(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~LogInForm();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LogInForm };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedLoginBtn();
};
