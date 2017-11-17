
// CsToolDlg.h : header file
//

#pragma once
#include "XCU.h"
#include "HelpManual.h"
#include "NodeEnterDlg.h"
#include "BatchAddDlg.h"
//ʵ���Ͽ��Ż���Ҫ����һ���ڵ��
#define ICANPORT    5000
#define XDCPORT     4000

// CCsToolDlg dialog
class CCsToolDlg : public CDialogEx
{
	// Construction
public:
	CCsToolDlg(CWnd* pParent = NULL);	                    // standard constructor
	bool CStringToChar(CString,char* ,int);                 //CString ת Char *
	// Dialog Data
	enum { IDD = IDD_CSTOOL_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	   // DDX/DDV support


	// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnClose();
	afx_msg void OnOkBtnClickedButton5();
	afx_msg void OnClearBtnClickedButton8();
	afx_msg void OnStartAndStopBtnClickedButton6();
	afx_msg void OnAddNodeBtnClickedButton1();
	afx_msg void OnDeleteNodeBtnClickedButton2();
	afx_msg void OnHelpBtnClickedButton7();
	afx_msg void OnConAndDisConBtnClickedButton3();
	afx_msg LRESULT OnNewNodeSignalFunction(WPARAM,LPARAM);          //�Զ�����Ϣ������
	afx_msg LRESULT OnBatchAddNodeSignalFunction(WPARAM,LPARAM);
	/****************************************************************/
	CEdit m_RateCtl;                                                //Ƶ�ʿؼ�
	unsigned int rateval;                                           //Ƶ��
	CComboBox m_ConTypeCtl;                                         //����������ѡ��ؼ�
	CListBox m_NodeListCtl;                                         //�ڵ��б�
	CEdit m_ChangeCntCtl;                                           //�л������ؼ�
	unsigned int changecnt;                                         //�л�����
	CButton m_ClearAllNodeBtn;                                      //������нڵ㰴ť
	CListBox m_MsgListCtl;                                          //��־��Ϣ�ؼ�
	CButton m_ConDisconBtn;                                         //���Ӱ�ť
	CButton m_AddNodeBtn;                                           //��ӽڵ㰴ť
	CButton m_BatchAddBtn;                                          //������Ӱ�ť
	CButton m_DeleteNodeBtn;                                        //ɾ���ڵ㰴ť
	BatchAddDlg   w_BacthAddDlg;
	NodeEnterDlg  w_NodeEnterDlg;
	HelpManual    w_HelpManualDlg;
	/****************************************************************/
	bool runflag;                                                   //���߳����б��
	bool ConType;                                                   //����������
	bool connectflag;                                               //���ӱ�� Ĭ����false ICAN
	bool startflag;                                                 //��ʼ���
	CButton m_StartAndStopBtn;
	afx_msg void OnAddBatchBtnClickedButton4();
	afx_msg void OnClearAllNodeBtnClickedButton9();
};

typedef struct ParamData
{
	CCsToolDlg* dlg;
	unsigned int * _node;
};
typedef struct ParamLiveData
{
	CCsToolDlg* dlg;
	XCU    * xcuobj;
};