﻿<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="WebForm1.aspx.cs" Inherits="WebApp.WebForm1" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title></title>
</head>
<body>
    <form id="form1" runat="server">
    <div>
        现在时间：<asp:Label ID="Label1" runat="server" Text="Label"></asp:Label><br />
        <asp:Button ID="Button1" runat="server" Text="更新时间" onclick="Button1_Click" />
    </div>
    </form>
</body>
</html>
