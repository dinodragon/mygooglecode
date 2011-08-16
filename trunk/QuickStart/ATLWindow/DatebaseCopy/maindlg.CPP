#include "StdAfx.h"
#include "MainDlg.h"
#include "DataCopyer.h"
#include "tinyxml/tinyxml.h"

extern CAppModule _Module; 

LRESULT CMainDlg::OnBnClickedOk(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: Add your control notification handler code here

	CString s;
	s.LoadString(IDR_HTML1);
	HINSTANCE i = _Module.m_hInstResource;
	//HRSRC hRes = ::FindResourceEx(NULL, RT_STRING, MAKEINTRESOURCE((ID_FILE_OPEN>>4) + 1), 0);
	//HRSRC hRes = ::FindResource(NULL,MAKEINTRESOURCE((IDR_HTML1>>4) + 1),RT_RCDATA);
	/*TCHAR buf[200];
	LoadString(NULL,ID_FILE_OPEN,buf,200);*/
	HRSRC hRes = FindResource(i,MAKEINTRESOURCE(IDR_HTML1),RT_HTML); 
	if (hRes == NULL)
	{
		DWORD err = ::GetLastError();
		return TRUE;
	}
	HRSRC hResLoad = (HRSRC)LoadResource(NULL, hRes);
	if (hResLoad == NULL)
		return TRUE;
	LPVOID lpResLock = LockResource(hResLoad);
	CString strRes;
	strRes.Format(_T("%s"), lpResLock);
	MessageBox(RT_RCDATA);


	//UpdateData(TRUE);
	//SaveSetting();
	////MessageBox(m_sServer);
	//CDataCopyer::GetInstance()->SetSource(m_sServer,m_sUser,m_sPwd,m_sDb,m_sLocalpath,m_sNetpath);
	//CDataCopyer::GetInstance()->SetDestination(m_dServer,m_dUser,m_dPwd,m_dDb,m_dLocalpath,m_dNetpath);
	//BOOL result = CDataCopyer::GetInstance()->Backup();
	//if (!result)
	//{
	//	MessageBox(_T("备份数据库失败！"));
	//	return 0;
	//}
	//result = CDataCopyer::GetInstance()->CopyFile();
	//if (!result)
	//{
	//	MessageBox(_T("拷贝文件失败！"));
	//	return 0;
	//}
	//result = CDataCopyer::GetInstance()->Restore();
	//if (!result)
	//{
	//	MessageBox(_T("还原数据库失败！"));
	//	return 0;
	//}
	return 0;
}



BOOL CMainDlg::SaveSetting()
{
	try
	{
		TiXmlDocument xmlDoc("config.xml"); // 建立一个XML文件
		TiXmlDeclaration Declaration( "1.0","UTF-8", "yes" ); // 声明XML的属性
		xmlDoc.InsertEndChild(Declaration ); // 写入基本的XML头结构

		TiXmlElement rootElem("Setting");
		TiXmlElement source("Source");
		TiXmlElement des("Destination");
		source.SetAttribute("Server",CW2A(m_sServer));
		source.SetAttribute("User",CW2A(m_sUser));
		source.SetAttribute("Password",CW2A(m_sPwd));
		source.SetAttribute("Database",CW2A(m_sDb));
		source.SetAttribute("LocalPath",CW2A(m_sLocalpath));
		source.SetAttribute("NetPath",CW2A(m_sNetpath));

		des.SetAttribute("Server",CW2A(m_dServer));
		des.SetAttribute("User",CW2A(m_dUser));
		des.SetAttribute("Password",CW2A(m_dPwd));
		des.SetAttribute("Database",CW2A(m_dDb));
		des.SetAttribute("LocalPath",CW2A(m_dLocalpath));
		des.SetAttribute("NetPath",CW2A(m_dNetpath));

		rootElem.InsertEndChild(source);
		rootElem.InsertEndChild(des);
		xmlDoc.InsertEndChild(rootElem);

		xmlDoc.SaveFile();
	}
	catch (...)
	{
		return FALSE;
	}
	return TRUE;
}

BOOL CMainDlg::LoadSetting()
{
	try
	{
		TiXmlDocument xmlDoc("config.xml");
		xmlDoc.LoadFile();
		TiXmlElement * pRootElem = xmlDoc.RootElement();
		if(!pRootElem)
			return FALSE;
		TiXmlElement * pSource = pRootElem->FirstChildElement("Source");
		m_sServer = pSource->Attribute("Server");
		m_sUser = pSource->Attribute("User");
		m_sPwd = pSource->Attribute("Password");
		m_sDb = pSource->Attribute("Database");
		m_sLocalpath = pSource->Attribute("LocalPath");
		m_sNetpath = pSource->Attribute("NetPath");

		TiXmlElement * pDes = pRootElem->FirstChildElement("Destination");
		m_dServer = pDes->Attribute("Server");
		m_dUser = pDes->Attribute("User");
		m_dPwd = pDes->Attribute("Password");
		m_dDb = pDes->Attribute("Database");
		m_dLocalpath = pDes->Attribute("LocalPath");
		m_dNetpath = pDes->Attribute("NetPath");
	}
	catch (...)
	{
		assert(false);
		return FALSE;
	}
	return TRUE;
}
