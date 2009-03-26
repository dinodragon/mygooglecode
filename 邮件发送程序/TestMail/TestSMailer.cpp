///////////////////////////////////////////////////////////////////
// This program is a demostration about how to use SMailer.
// Written by Morning, mailto:moyingzz@etang.com
//
// Date:2003-5
///////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <list>
#include <string>
#include <iostream>
#include "SMailer/SMailer.h"
#include "MUtils/WinSockHelper.h"

void main()
{
    MUtils::WinSockHelper wshelper;
	
    // make sure the file 'boot.ini' is in the root directory on driver C
    SMailer::TextPlainContent  content1("plain text content");
    SMailer::TextHtmlContent   content2("<a href='http://www.baidu.com'>click me</a>");
    //SMailer::AppOctStrmContent content3("c:\\boot.ini");
	
    SMailer::MailInfo info;
    info.setSenderName("Ñî·É");
    info.setSenderAddress("yangfei9592@163.com");
    info.addReceiver("·½Õý", "yangfei@founder.com");
    info.setPriority(SMailer::Priority::normal);
    info.setSubject("a test mail");
    info.addMimeContent(&content1);
    //info.addMimeContent(&content2);
    //info.addMimeContent(&content3);
	
    try
    {
        SMailer::MailSender sender("smtp.163.com", "yfsuoyou", "autoexec.bat");
        sender.setMail(&SMailer::MailWrapper(&info));
        sender.sendMail();
    }
    catch (SMailer::MailException& e)
    {
        std::cout << e.what() << std::endl;
    }
    catch (...)
    {
        std::cout << "Unkown error" << std::endl;
    }
}