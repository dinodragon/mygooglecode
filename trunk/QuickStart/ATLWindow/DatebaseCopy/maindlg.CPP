#include "StdAfx.h"
#include "MainDlg.h"
#include "DataCopyer.h"
#include "tinyxml/tinyxml.h"

LRESULT CMainDlg::OnBnClickedOk(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: Add your control notification handler code here
	SaveSetting();
	UpdateData(TRUE);
	//MessageBox(m_sServer);
	CDataCopyer::GetInstance()->SetSource(m_sServer,m_sUser,m_sPwd,m_sDb,m_sLocalpath,m_sNetpath);
	CDataCopyer::GetInstance()->SetDestination(m_dServer,m_dUser,m_dPwd,m_dDb,m_dLocalpath,m_dNetpath);
	//CDataCopyer::GetInstance()->Backup();
	//CDataCopyer::GetInstance()->CopyFile();
	//CDataCopyer::GetInstance()->Restore();
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
		//TiXmlAttribute a_sServer("Server","a");
		//TiXmlAttribute a_sUser("User",m_sUser);
		//TiXmlAttribute a_sPassword("Password",m_sPwd);
		//TiXmlAttribute a_sDatabase("Database",m_sDb);
		//TiXmlAttribute a_sLocalPath("LocalPath",m_sLocalpath);
		//TiXmlAttribute a_sNetPath("NetPath",m_sNetpath);

		//TiXmlAttribute a_dServer("Server",m_dServer);
		//TiXmlAttribute a_dUser("User",m_dUser);
		//TiXmlAttribute a_dPassword("Password",m_dPwd);
		//TiXmlAttribute a_dDatabase("Database",m_dDb);
		//TiXmlAttribute a_dLocalPath("LocalPath",m_dLocalpath);
		//TiXmlAttribute a_dNetPath("NetPath",m_dNetpath);
		source.SetAttribute("Server","a");
		//source.InsertEndChild(a_sUser);
		//source.InsertEndChild(a_sPassword);
		//source.InsertEndChild(a_sDatabase);
		//source.InsertEndChild(a_sLocalPath);
		//source.InsertEndChild(a_sNetPath);

		//des.InsertEndChild(a_dServer);
		//des.InsertEndChild(a_dUser);
		//des.InsertEndChild(a_dPassword);
		//des.InsertEndChild(a_dDatabase);
		//des.InsertEndChild(a_dLocalPath);
		//des.InsertEndChild(a_dNetPath);

		rootElem.InsertEndChild(source);
		rootElem.InsertEndChild(des);
		xmlDoc.InsertEndChild(rootElem);


		xmlDoc.SaveFile();
	}
	catch (...)
	{
	}
	return FALSE;
}

