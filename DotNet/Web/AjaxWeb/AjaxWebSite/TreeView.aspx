<%@ Page Language="C#" AutoEventWireup="true" CodeFile="TreeView.aspx.cs" Inherits="TreeView" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title></title>
</head>
<body>
    <form id="form1" runat="server">
    <div >
        <asp:ScriptManager ID="ScriptManager1" runat="server">
        </asp:ScriptManager>
        <br />
        更新区域包含了Div，更新时会导致重绘，滚动条会回去。<asp:UpdatePanel ID="UpdatePanel1" runat="server" 
            UpdateMode="Conditional">
            <ContentTemplate>
                <%--div在部分更新里面的时候就会被刷新，滚动条就会回去--%>
                <div style="border-style: solid; width: 500px; height: 500px; overflow: auto;">
                    <asp:Label ID="Label1" runat="server" Text="Label"></asp:Label>
                    <asp:TreeView ID="treeView" runat="server" OnSelectedNodeChanged="treeView_SelectedNodeChanged">
                        <SelectedNodeStyle Font-Bold="True" BackColor="#CCFF33" />
                    </asp:TreeView>
                </div>
            </ContentTemplate>
        </asp:UpdatePanel>
    </div>
    </form>
</body>
</html>
