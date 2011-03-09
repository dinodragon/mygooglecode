========================================================================
    活动模板库 : ATLQuickStart 项目概述
========================================================================

应用程序向导已为您创建了此 ATLQuickStart 项目，作为编写可执行程序 (EXE) 的起点。

本文件概要介绍组成项目的每个文件的内容。

ATLQuickStart.vcproj
    这是使用应用程序向导生成的 VC++ 项目的主项目文件，
    其中包含生成该文件的 Visual C++ 的版本信息，以及有关使用应用程序向导选择的平台、配置和项目功能的信息。

ATLQuickStart.idl
    此文件包含项目中定义的类型库、接口和 co-class 的 IDL 定义。
    此文件将由 MIDL 编译器进行处理以生成：
        C++ 接口定义和 GUID 声明 (ATLQuickStart.h)
        GUID 定义                                (ATLQuickStart_i.c)
        类型库                                  (ATLQuickStart.tlb)
        封送处理代码                                 （ATLQuickStart_p.c 和 dlldata.c）

ATLQuickStart.h
    此文件包含 ATLQuickStart.idl 中定义的项目的 C++ 接口定义和 GUID 声明。它将在编译过程中由 MIDL 重新生成。

ATLQuickStart.cpp
    此文件包含对象映射和 WinMain 的实现。

ATLQuickStart.rc
    这是程序使用的所有 Microsoft Windows 资源的列表。


/////////////////////////////////////////////////////////////////////////////
其他标准文件：

StdAfx.h, StdAfx.cpp
    这些文件用于生成名为 ATLQuickStart.pch 的预编译头 (PCH) 文件和名为 StdAfx.obj 的预编译类型文件。

Resource.h
    这是用于定义资源 ID 的标准头文件。


/////////////////////////////////////////////////////////////////////////////