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
	m_helplistcnt.AddString(_T("1.����ʱ�䣺2017.11.17 �����ߣ�л���� "));
	m_helplistcnt.AddString(_T(""));
	m_helplistcnt.AddString(_T("2.��ѡ��ÿ��������ͣ�������ӽڵ�ţ� "));
	m_helplistcnt.AddString(_T(""));
	m_helplistcnt.AddString(_T("3.������Ӱ�ť���ӿ�������Ȼ��ʼ���У� "));
	m_helplistcnt.AddString(_T(""));
	m_helplistcnt.AddString(_T("4.�ڵ��������Ϊ50 ����Ƶ�����ñ������10s�� "));
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
