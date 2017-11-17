
// CsToolDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CsTool.h"
#include "CsToolDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

UINT SendLivePackageThread(LPVOID * aPram);            //发送心跳包线程
UINT ConnectControlThread(LPVOID * aPram);             //连接控制器线程

// CAboutDlg dialog used for App About
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCsToolDlg dialog
bool CCsToolDlg::CStringToChar(CString pstr,char * ch,int len)                          
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

CCsToolDlg::CCsToolDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCsToolDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCsToolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_ConTypeCtl);
	DDX_Control(pDX, IDC_LIST2, m_NodeListCtl);
	DDX_Control(pDX, IDC_LIST3, m_MsgListCtl);
	DDX_Control(pDX, IDC_EDIT1, m_RateCtl);
	DDX_Control(pDX, IDC_EDIT2, m_ChangeCntCtl);
	DDX_Control(pDX, IDC_BUTTON3, m_ConDisconBtn);
	DDX_Control(pDX, IDC_BUTTON1, m_AddNodeBtn);
	DDX_Control(pDX, IDC_BUTTON2, m_DeleteNodeBtn);
	DDX_Control(pDX, IDC_BUTTON6, m_StartAndStopBtn);
	DDX_Control(pDX, IDC_BUTTON4, m_BatchAddBtn);
	DDX_Control(pDX, IDC_BUTTON9, m_ClearAllNodeBtn);
}

BEGIN_MESSAGE_MAP(CCsToolDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_MESSAGE(WM_NEWNODE_MSG, &CCsToolDlg::OnNewNodeSignalFunction)           //自定义
	ON_MESSAGE(WM_BATCHADDNODE_MSG,&CCsToolDlg::OnBatchAddNodeSignalFunction)
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CCsToolDlg::OnAddNodeBtnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CCsToolDlg::OnDeleteNodeBtnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON7, &CCsToolDlg::OnHelpBtnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON3, &CCsToolDlg::OnConAndDisConBtnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON5, &CCsToolDlg::OnOkBtnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON8, &CCsToolDlg::OnClearBtnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON6, &CCsToolDlg::OnStartAndStopBtnClickedButton6)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON4, &CCsToolDlg::OnAddBatchBtnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON9, &CCsToolDlg::OnClearAllNodeBtnClickedButton9)
END_MESSAGE_MAP()


// CCsToolDlg message handlers

BOOL CCsToolDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	m_ConTypeCtl.AddString(_T("         ICAN"));
	m_ConTypeCtl.AddString(_T("        XDCNET"));
	m_ConTypeCtl.SetCurSel(0);
	m_RateCtl.SetWindowText(_T("10"));
	rateval=10;
	m_ChangeCntCtl.SetWindowText(_T("0"));
	changecnt=0;                                                       //切换计数清零
	connectflag=false;                                                 //连接标记
	runflag=true;                                                      //断开标记
	ConType=false;                                                     //默认为ican
	startflag=false;

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCsToolDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCsToolDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCsToolDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



BOOL CCsToolDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	if (pMsg->message == WM_KEYDOWN)  
	{  
		switch(pMsg->wParam)  
		{  
		case VK_ESCAPE:           //Esc按键事件  
			return true;  
		case VK_RETURN:           //Enter按键事件 
			
			return true;
		case VK_F1:               //开启帮助信息
			return true;
		default:  
			;  
		}  
	}  
	return CDialogEx::PreTranslateMessage(pMsg);

}


void CCsToolDlg::OnAddNodeBtnClickedButton1()
{
	// TODO: Add your control notification handler code here
	m_ConTypeCtl.EnableWindow(false);
	w_NodeEnterDlg.DoModal();
}


void CCsToolDlg::OnDeleteNodeBtnClickedButton2()
{
	// TODO: Add your control notification handler code here
	unsigned int curnode=this->m_NodeListCtl.GetCurSel();
	if(curnode==-1)
	{
		this->MessageBox(_T("请先在右边选中要删除的节点."));
		return ;
	}
	//弹出一个确认窗口
	if(::MessageBox(NULL, _T("选中的节点将会被删除."),_T("提 示"), MB_YESNO) != IDYES)
	{
		return ;
	}
	this->m_NodeListCtl.DeleteString(curnode);
}


void CCsToolDlg::OnHelpBtnClickedButton7()
{
	// TODO: Add your control notification handler code here
	w_HelpManualDlg.DoModal();
}

void CCsToolDlg::OnConAndDisConBtnClickedButton3()
{
	// TODO: Add your control notification handler code here
	if(!this->m_NodeListCtl.GetCount())
	{
		this->MessageBox(_T("没有可用的节点号."));
		return ;
	}
	if(!connectflag)
	{
		m_AddNodeBtn.EnableWindow(false);
		m_BatchAddBtn.EnableWindow(false);
		m_DeleteNodeBtn.EnableWindow(false);
		m_ClearAllNodeBtn.EnableWindow(false);
		ConType=this->m_ConTypeCtl.GetCurSel();
		unsigned int _count=this->m_NodeListCtl.GetCount();
		for(unsigned int i=0;i<_count;++i)
		{
			CString tmp;
			this->m_NodeListCtl.GetText(i,tmp);
			char ch[32]={0};
			memset(ch,0,sizeof(ch));
			this->CStringToChar(tmp,ch,sizeof(ch));
			unsigned int _node=atoi(ch);
			ParamData Pdata;
			Pdata.dlg=this;
			Pdata._node=&_node;
			//建立线程依次连接控制器
			AfxBeginThread((AFX_THREADPROC)ConnectControlThread,&Pdata);
			Sleep(3);                                                   //这个延时很重要的保证数据正确性
		}
		connectflag=true;
		this->m_ConDisconBtn.SetWindowText(_T("断     开"));
	}
	else                                                                //断开进行资源清理工作
	{
		runflag=false;
		connectflag=false;
		m_ClearAllNodeBtn.EnableWindow(true);
		m_ConTypeCtl.EnableWindow(true);
		m_AddNodeBtn.EnableWindow(true); 
		m_BatchAddBtn.EnableWindow(true);
		m_DeleteNodeBtn.EnableWindow(true);
		this->m_ConDisconBtn.SetWindowText(_T("连     接"));
	}
}
UINT ConnectControlThread(LPVOID * aPram)                               //连接控制器线程
{
	ParamData Pdata=*(ParamData*)aPram;
	CCsToolDlg* dlg=Pdata.dlg;
	unsigned int node=*(Pdata._node);
	char cip[32]={0};
	memset(cip,0,sizeof(cip));
	sprintf(cip,"222.222.221.%d",node);
	unsigned int port = 0;
	if(!dlg->ConType)                   //ican 
		port=ICANPORT+node;
	else                               //xdc
		port=XDCPORT+node;
	/******************************************************/
	XCU xcuobj;
	xcuobj.sendflag=true;
	xcuobj.m_Addr.sin_family=AF_INET;
	xcuobj.m_Addr.sin_port=htons(port);
	xcuobj.m_Addr.sin_addr.S_un.S_addr=inet_addr(cip);
	//接下来就是登录连接控制器了
	int res=xcuobj.Link();
	if(res==0)
	{
		CString msg;
		msg.Format(_T("连接控制器：%s 失败."),CStringW(cip));
		dlg->m_MsgListCtl.AddString(msg);
		return -1;
	}
	CString msg;
	msg.Format(_T("连接控制器：%s 成功."),CStringW(cip));
	dlg->m_MsgListCtl.AddString(msg);
	//登录控制器
	if(xcuobj.Login()==0)
	{
		CString msg;
		msg.Format(_T("登录控制器：%s 失败."),CStringW(cip));
		dlg->m_MsgListCtl.AddString(msg);
		return -1;
	}
	msg.Format(_T("登录控制器：%s 成功."),CStringW(cip));
	dlg->m_MsgListCtl.AddString(msg);
	//建立心跳线程一直发送心跳包
	ParamLiveData Pldata;
	Pldata.dlg=dlg;
	Pldata.xcuobj=&xcuobj;
	AfxBeginThread((AFX_THREADPROC)SendLivePackageThread,&Pldata);
	//
	bool tmp_flag=false;
	while(dlg->runflag)                                             //循环进行切换操作
	{
		if(dlg->startflag&&xcuobj.sendflag)
		{
			++dlg->changecnt;
			CString cntctr;
			cntctr.Format(_T("%d"),dlg->changecnt);
			dlg->m_ChangeCntCtl.SetWindowText(cntctr);
			if(!tmp_flag)
			{
				if(dlg->m_MsgListCtl.GetCount()>100)                    //只保留100条日志记录
				{
					dlg->m_MsgListCtl.ResetContent();
				}
				if(xcuobj.XcuOperate(8))
				{
					CString msg;
					msg.Format(_T("%s to Main Ok."),CStringW(cip));
					dlg->m_MsgListCtl.AddString(msg);
				}
				else
				{
					CString msg;
					msg.Format(_T("%s to Main Failed."),CStringW(cip));
					dlg->m_MsgListCtl.AddString(msg);
				}
				tmp_flag=true;
			}
			else
			{
				if(dlg->m_MsgListCtl.GetCount()>100)                    //只保留100条日志记录
				{
					dlg->m_MsgListCtl.ResetContent();
				}
				if(xcuobj.XcuOperate(7))
				{
					CString msg;
					msg.Format(_T("%s to Trace Ok."),CStringW(cip));
					dlg->m_MsgListCtl.AddString(msg);
				}
				else
				{
					CString msg;
					msg.Format(_T("%s to Trace Failed."),CStringW(cip));
					dlg->m_MsgListCtl.AddString(msg);
				}
				tmp_flag=false;
			}
			Sleep(dlg->rateval*1000);
			if(dlg->m_MsgListCtl.GetCount()>100)
				dlg->m_MsgListCtl.ResetContent();
		}
		else
		{
			Sleep(2000);
		}
	}
	CString msgctr;
	msgctr.Format(_T("%s 连接线程成功退出."),CStringW(cip));
	dlg->m_MsgListCtl.AddString(msgctr);
	return 0;
}
UINT SendLivePackageThread(LPVOID * aPram)
{
	ParamLiveData pd=*(ParamLiveData*)aPram;
	CCsToolDlg*  dlg=pd.dlg;
	XCU xcuobj      =*(XCU*)pd.xcuobj;
	unsigned int disconnum=0;
	while(dlg->runflag)                                             //循环进行切换操作
	{
		if(xcuobj.XcuGetStatus()==3)
		{
			++disconnum;
			if(disconnum>5)
			{
				xcuobj.sendflag=false;
				//重连控制器
				xcuobj.CloseLink();
				if(xcuobj.Link()!=0)
				{
					if(xcuobj.Login()!=0)
					{
						disconnum=0;
						xcuobj.sendflag=true;
					}
				}
			}
			dlg->m_MsgListCtl.AddString(_T("Keep Alive XcuGetStatus Failed."));
		}
		else
		{
			dlg->m_MsgListCtl.AddString(_T("Keep Alive XcuGetStatus OK."));
		}

		Sleep(8000);
	}
	return 0;
}

LRESULT CCsToolDlg::OnNewNodeSignalFunction(WPARAM wParam,LPARAM LParam)       
{
	//遍历一遍节点列表
	unsigned int _node=atoi((char*)LParam);
	CString _nodectr;
	_nodectr.Format(_T("%d"),_node);
	unsigned int _count=this->m_NodeListCtl.GetCount();
	if( _count > 49 )
	{
		this->MessageBox(_T("节点数目已达上限50个."));
		return 0;
	}
	for(unsigned int i=0;i<_count;++i)
	{
		CString tmp;
		this->m_NodeListCtl.GetText(i,tmp);
		if(_nodectr==tmp)
		{
			this->MessageBox(_T("添加的节点已经存在."));
			return 0;
		}
		char ch[32]={0};
		memset(ch,0,sizeof(ch));
		this->CStringToChar(tmp,ch,sizeof(ch));
		unsigned int tmpnode=atoi(ch);

		if(!this->ConType)                   //ican 
		{
			if(_node>tmpnode&&(_node-100)==tmpnode)
			{
				this->MessageBox(_T("主副控节点只需要添加一个就行."));
				return 0;
			}
			else if(_node<tmpnode&&(_node+100)==tmpnode)
			{
				this->MessageBox(_T("主副控节点只需要添加一个就行."));
				return 0;
			}
		}
		else                               //xdc
		{
			if(_node>tmpnode&&(_node-20)==tmpnode)
			{
				this->MessageBox(_T("主副控节点只需要添加一个就行."));
				return 0;
			}
			else if(_node<tmpnode&&(_node+20)==tmpnode)
			{
				this->MessageBox(_T("主副控节点只需要添加一个就行."));
				return 0;
			}
		}
	}
	CString str;
	str.Format(_T("%s"),CStringW((char*)LParam));
	this->m_NodeListCtl.AddString(str);
	this->UpdateData(false);
	return 1;
}
LRESULT CCsToolDlg::OnBatchAddNodeSignalFunction(WPARAM wParam,LPARAM LParam)         //批量添加
{
	char* ch=(char*)LParam;
	char* oldch=ch;
	unsigned int oldindex=0;
	unsigned int index=0;
	unsigned int cnt=0;
	while(*ch != '#')
	{
		++index;
		if(*ch==',')
		{
			char ptr[32]={0};
			memset(ptr,0,32);
			memcpy(ptr,oldch,index-oldindex-1);
			CString str;
			str.Format(_T("%s"),CStringW(ptr));
			this->m_NodeListCtl.AddString(str);


			oldindex=index;
			oldch=ch+1;
		}
		++ch;
		if(cnt++>150)
			break;
	}
	*ch='\0';
	CString str;
	str.Format(_T("%s"),CStringW(oldch));
	this->m_NodeListCtl.AddString(str);
	return 1;
}
void CCsToolDlg::OnOkBtnClickedButton5()
{
	// TODO: Add your control notification handler code here
	CString tmp;
	this->m_RateCtl.GetWindowText(tmp);
	char ch[128]={0};
	memset(ch,0,sizeof(ch));
	if(this->CStringToChar(tmp,ch,sizeof(ch)))
	{
		unsigned int _val=atoi(ch);
		if(_val>=10)
		{
			this->rateval=_val;
			CString msg;
			msg.Format(_T("提示：频率设置为 %d 成功."),this->rateval);
			this->m_MsgListCtl.AddString(msg);
		}
		else
		{
			this->MessageBox(_T("频率设置必须大于10s."));
			CString oldctr;
			oldctr.Format(_T("%d"),this->rateval);
			this->m_RateCtl.SetWindowText(oldctr);
		}
	}
	else
	{
		this->MessageBox(_T("频率设置失败."));
	}
	this->UpdateData(false);
}


void CCsToolDlg::OnClearBtnClickedButton8()
{
	// TODO: Add your control notification handler code here
	m_ChangeCntCtl.SetWindowText(_T("0"));
	changecnt=0;
	this->UpdateData(false);
}


void CCsToolDlg::OnStartAndStopBtnClickedButton6()            //开始和暂停处理函数
{
	// TODO: Add your control notification handler code here
	if(!connectflag)
	{
		this->MessageBox(_T("请先连接所添加的控制器."));
		return ;
	}
	if(!startflag)
	{
		m_StartAndStopBtn.SetWindowText(_T("暂    停"));
		this->m_MsgListCtl.AddString(_T("======开始成功======."));
		startflag=true;
	}
	else
	{
		m_StartAndStopBtn.SetWindowText(_T("开    始"));
		this->m_MsgListCtl.AddString(_T("======暂停成功======."));
		startflag=false;
	}
}


void CCsToolDlg::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	CDialogEx::OnClose();
}


void CCsToolDlg::OnAddBatchBtnClickedButton4()                    //批量添加节点
{
	// TODO: Add your control notification handler code here
	m_ConTypeCtl.EnableWindow(false);
	w_BacthAddDlg.DoModal();
}


void CCsToolDlg::OnClearAllNodeBtnClickedButton9()             //清空所有节点
{
	// TODO: Add your control notification handler code here
	//弹出一个确认窗口
	if(::MessageBox(NULL, _T("所有节点将会被删除."),_T("提 示"), MB_YESNO) != IDYES)
	{
		return ;
	}
	this->m_NodeListCtl.ResetContent();
}
