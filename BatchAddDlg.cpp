// BatchAddDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CsTool.h"
#include "BatchAddDlg.h"
#include "afxdialogex.h"


// BatchAddDlg dialog

IMPLEMENT_DYNAMIC(BatchAddDlg, CDialogEx)

	BatchAddDlg::BatchAddDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(BatchAddDlg::IDD, pParent)
{

}

BatchAddDlg::~BatchAddDlg()
{
}
bool BatchAddDlg::CStringToChar(CString pstr,char * ch,int len)                          
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
void BatchAddDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_NodeListCtl);
}


BEGIN_MESSAGE_MAP(BatchAddDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &BatchAddDlg::OnOkBtnClickedButton1)
END_MESSAGE_MAP()


// BatchAddDlg message handlers
bool BatchAddDlg::isValidFunction(char * ch,int len)
{
	char oldchar='\0';
	for(int i=0;i<len;++i)
	{
		char tmp=*(ch+i);
		if(i!=(len-1)&&(tmp<48||tmp>57)&&(tmp!=','&&tmp!='#'))
		{
			this->MessageBox(_T("����Ľڵ��ʽ�����в��ϸ��ַ�."));
			return false;
		}
		if(i==0&&(tmp<48||tmp>57))
		{
			this->MessageBox(_T("����Ľڵ��ʽ�����׸����ű���Ϊ����."));
			return false;
		}
		if(oldchar==','&&(tmp<48||tmp>57))
		{
			this->MessageBox(_T("����Ľڵ��ʽ�����������ķ���."));
			return false;
		}
		if(i==(len-1)&&tmp!='#')                                    //û������#
		{
			this->MessageBox(_T("����Ľڵ��ʽ����ĩβû��#����."));
			return false;
		}
		oldchar=tmp;
	}
	return true;
}
void BatchAddDlg::OnOkBtnClickedButton1()
{
	// TODO: Add your control notification handler code here
	CString cstr;
	m_NodeListCtl.GetWindowText(cstr);
	if(cstr==_T(""))
	{
		this->MessageBox(_T("����Ľڵ㲻��Ϊ��."));
		return ;
	}
	char ch[1024]={0};
	memset(ch,0,sizeof(ch));
	if(CStringToChar(cstr,ch,sizeof(ch)))
	{
		if(!isValidFunction(ch,strlen(ch)))
		{
			return ;
		}
		HWND hWnd=::FindWindow(NULL,_T("CsTool"));
		if(hWnd)
		{
			CString param;
			param.Format(_T("%s"),CStringW(ch));
			::SendMessage(hWnd,WM_BATCHADDNODE_MSG,TRUE,(LPARAM)ch);
			this->PostMessage(WM_CLOSE);
		}
		else
		{
			this->MessageBox(_T("����½ڵ�ʧ��."));
		}
	}
	else
	{
		this->MessageBox(_T("�ڵ���������."));
	}
}
