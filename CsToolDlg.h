
// CsToolDlg.h : header file
//

#pragma once
#include "XCU.h"
#include "HelpManual.h"
#include "NodeEnterDlg.h"
#include "BatchAddDlg.h"
//实践断开号还需要加上一个节点号
#define ICANPORT    5000
#define XDCPORT     4000

// CCsToolDlg dialog
class CCsToolDlg : public CDialogEx
{
	// Construction
public:
	CCsToolDlg(CWnd* pParent = NULL);	                    // standard constructor
	bool CStringToChar(CString,char* ,int);                 //CString 转 Char *
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
	afx_msg LRESULT OnNewNodeSignalFunction(WPARAM,LPARAM);          //自定义消息处理函数
	afx_msg LRESULT OnBatchAddNodeSignalFunction(WPARAM,LPARAM);
	/****************************************************************/
	CEdit m_RateCtl;                                                //频率控件
	unsigned int rateval;                                           //频率
	CComboBox m_ConTypeCtl;                                         //控制器类型选择控件
	CListBox m_NodeListCtl;                                         //节点列表
	CEdit m_ChangeCntCtl;                                           //切换计数控件
	unsigned int changecnt;                                         //切换计数
	CButton m_ClearAllNodeBtn;                                      //清空所有节点按钮
	CListBox m_MsgListCtl;                                          //日志消息控件
	CButton m_ConDisconBtn;                                         //连接按钮
	CButton m_AddNodeBtn;                                           //添加节点按钮
	CButton m_BatchAddBtn;                                          //批量添加按钮
	CButton m_DeleteNodeBtn;                                        //删除节点按钮
	BatchAddDlg   w_BacthAddDlg;
	NodeEnterDlg  w_NodeEnterDlg;
	HelpManual    w_HelpManualDlg;
	/****************************************************************/
	bool runflag;                                                   //子线程运行标记
	bool ConType;                                                   //控制器类型
	bool connectflag;                                               //连接标记 默认是false ICAN
	bool startflag;                                                 //开始标记
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