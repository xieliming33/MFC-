#pragma once
#define WM_NEWNODE_MSG WM_USER+100                           //自定义消息
// NodeEnterDlg dialog

class NodeEnterDlg : public CDialogEx
{
	DECLARE_DYNAMIC(NodeEnterDlg)

public:
	NodeEnterDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~NodeEnterDlg();
	bool CStringToChar(CString,char* ,int);                 //CString 转 Char *
// Dialog Data
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	CEdit m_NewNodeCtl;
};
