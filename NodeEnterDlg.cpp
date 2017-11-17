// NodeEnterDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CsTool.h"
#include "NodeEnterDlg.h"
#include "afxdialogex.h"


// NodeEnterDlg dialog

IMPLEMENT_DYNAMIC(NodeEnterDlg, CDialogEx)

NodeEnterDlg::NodeEnterDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(NodeEnterDlg::IDD, pParent)
{

}

NodeEnterDlg::~NodeEnterDlg()
{
}
bool NodeEnterDlg::CStringToChar(CString pstr,char * ch,int len)                          
{
	if(pstr.GetLength()>len)    return false;
	int strlen=pstr.GetLength();
	int nbyte=WideCharToMultiByte(CP_ACP,0,pstr,strlen,NULL,0,NULL,NULL);
	char * VoicePath=new char[nbyte+1];
	memset(VoicePath,0,nbyte+1);
	WideCharToMultiByte(CP_OEMCP,0,pstr,strlen,VoicePath,nbyte,NULL,NULL);
	VoicePath[nbyte]=0;
	memcpy(ch,VoicePath,nbyte+1);
	delete []VoicePath;
	return true;
}
void NodeEnterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_NewNodeCtl);
}


BEGIN_MESSAGE_MAP(NodeEnterDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &NodeEnterDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// NodeEnterDlg message handlers


void NodeEnterDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	CString cstr;
	m_NewNodeCtl.GetWindowText(cstr);
	char ch[128]={0};
	memset(ch,0,sizeof(ch));
	if(CStringToChar(cstr,ch,sizeof(ch)))
	{
		unsigned int _node=atoi(ch);
		if(_node>0)
		{
			HWND hWnd=::FindWindow(NULL,_T("CsTool"));
			if(hWnd)
			{
				CString param;
				param.Format(_T("%s"),CStringW(ch));
				::SendMessage(hWnd,WM_NEWNODE_MSG,TRUE,(LPARAM)ch);
				this->PostMessage(WM_CLOSE);
			}
			else
			{
				this->MessageBox(_T("添加新节点失败."));
			}
		}
		else
		{
			this->MessageBox(_T("节点号输入错误."));
		}
	}
	else
	{	
		this->MessageBox(_T("添加新节点失败."));
	}
}
