#pragma once
#define WM_BATCHADDNODE_MSG WM_USER+101                           //��������Զ�����Ϣ

// BatchAddDlg dialog

class BatchAddDlg : public CDialogEx
{
	DECLARE_DYNAMIC(BatchAddDlg)

public:
	BatchAddDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~BatchAddDlg();
	bool CStringToChar(CString,char* ,int);                 //CString ת Char *
	bool isValidFunction(char * ch,int len);
// Dialog Data
	enum { IDD = IDD_DIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_NodeListCtl;
	afx_msg void OnOkBtnClickedButton1();
};
