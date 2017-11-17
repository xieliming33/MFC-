#pragma once


// HelpManual dialog

class HelpManual : public CDialogEx
{
	DECLARE_DYNAMIC(HelpManual)

public:
	HelpManual(CWnd* pParent = NULL);   // standard constructor
	virtual ~HelpManual();

// Dialog Data
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CListBox m_helplistcnt;
	virtual BOOL OnInitDialog();
};
