// HelpManual.cpp : implementation file
//

#include "stdafx.h"
#include "CsTool.h"
#include "HelpManual.h"
#include "afxdialogex.h"


// HelpManual dialog

IMPLEMENT_DYNAMIC(HelpManual, CDialogEx)

HelpManual::HelpManual(CWnd* pParent /*=NULL*/)
	: CDialogEx(HelpManual::IDD, pParent)
{

}

HelpManual::~HelpManual()
{
}

void HelpManual::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_helplistcnt);
}


BEGIN_MESSAGE_MAP(HelpManual, CDialogEx)
END_MESSAGE_MAP()


// HelpManual message handlers


BOOL HelpManual::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	m_helplistcnt.AddString(_T("1.开发时间：2017.11.17 开发者：谢立明 "));
	m_helplistcnt.AddString(_T(""));
	m_helplistcnt.AddString(_T("2.先选择好控制器类型，接着添加节点号； "));
	m_helplistcnt.AddString(_T(""));
	m_helplistcnt.AddString(_T("3.点击连接按钮连接控制器，然后开始就行； "));
	m_helplistcnt.AddString(_T(""));
	m_helplistcnt.AddString(_T("4.节点添加上限为50 个，频率设置必须大于10s； "));
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
