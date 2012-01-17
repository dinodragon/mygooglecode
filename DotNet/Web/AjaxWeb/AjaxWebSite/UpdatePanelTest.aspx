<%@ Page Language="C#" AutoEventWireup="true" CodeFile="UpdatePanelTest.aspx.cs" Inherits="UpdatePanelTest" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title>UpdatePanel嵌套</title>
    <style type="text/css">
        body
        {
            Font-size: 9pt;
            Color: #333333;
            Scrollbar-face-color: #EEEEEE;
            Scrollbar-shadow-color: #CCCCCC;
            Scrollbar-3dlight-color: #CCCCCC;
            Scrollbar-darkshadow-color: #CCCCCC;
            Scrollbar-arrow-color: #999999;
        }       
        h1
        {
        	margin: 0; 
        	padding: 0; 
        	font-size: 1em;
        }
        .styleDiv
	    {
		    width: 700px;
		    height: 100%;		   
		    border:1px solid #92B0DD;
		    background-color: #FFFFFf;
		    margin: 1em 10em 1em !important; 
		    padding: 0px; 
		    margin-bottom: 10px;
		    padding-bottom:10px;
	    }
	    .styleDiv h1
	    {
	    	
		  line-height: 26px; border: 1px solid; 
		  background: #DDDCE4; 
		  background-repeat: repeat-x; 
		  background-position: 0 0; 
		  border-color: #FBFBF9 #FBFBF9 #CCCCD4 #FBFBF9; 
		  padding-left: 1em; 
		  margin-bottom: 1em; 
	    }

        fieldset {
            padding:10px;
            margin:10px;
            color:#333; 
            border:#06c dashed 1px;
        } 
        legend {
            color:#06c;
            font-weight:800; 
            background:#fff;
        } 
    </style>
</head>
<body>
    <form id="form1" runat="server">
    <asp:ScriptManager ID="ScriptManager1" runat="server">
    </asp:ScriptManager>
    <div>
        <asp:Label ID="Label1" runat="server" Height="300px" Text="Label的作用是为了显示局部更新时，并没有影响到定位"></asp:Label>
        <div class="styleDiv">
            <h1>UpdatePanel嵌套</h1>
            <div>
                <fieldset>
                    <legend>最外层DateTime：<%= DateTime.Now %></legend>
                    <div>
                        <asp:UpdatePanel ID="UpdatePanel1" runat="server" UpdateMode="Conditional">
                            <ContentTemplate>
                                <fieldset>
                                    <legend>UpdatePanel1 DateTime：<%= DateTime.Now %></legend>
                                    <div style="background-color:#E8E8E8">
                                        <asp:UpdatePanel ID="UpdatePanel2" runat="server" UpdateMode="Conditional">
                                            <ContentTemplate>
                                                <fieldset>
                                                    <legend>UpdatePanel2 DateTime：<%= DateTime.Now %></legend>
                                                    <div>
                                                        <div style="border:1px red solid;">
                                                            <asp:Button ID="btnAll" runat="server" Text="更新整个页面" onclick="btnAll_Click" />
                                                            <div>为了更新整个页面，UpdatePanel1的UpdateMode属性必须设置为：“Conditional”<br />
                                                                 并且必须使用“&lt;asp:PostBackTrigger ControlID="btnAll" / &gt;”
                                                            </div>
                                                        </div><br />
                                                        <div style="border:1px red solid;">
                                                            <asp:Button ID="btnUpdate" runat="server" Text="更新UpdatePanel1、2、3" onclick="btnUpdate_Click" /> 
                                                            <div>更新UpdatePanel1时会影响到UpdatePanel2、UpdatePanel3。所以UpdatePanel1更新时，它里面的都会更新。<br />
                                                                UpdatePanel1的UpdateMode属性必须设置为：“Conditional”<br />
                                                                并且必须使用“&lt;asp:AsyncPostBackTrigger ControlID="btnUpdate" EventName="click" / &gt;”
                                                            </div>
                                                        </div>
                                                            <br />
                                                         <div style="border:1px red solid;">
                                                            <asp:Button ID="btnSubmit" runat="server" Text="只更新UpdatePanel2" onclick="btnSubmit_Click" />                                                                                                             
                                                            <div>为了使UpdatePanel2中的更新不影响UpdatePanel1、UpdatePanel3，UpdatePanel1、UpdatePanel3的UpdateMode属性必须设置为：“Conditional”</div>
                                                         </div>
                                                     </div>
                                                </fieldset>                                           
                                            </ContentTemplate>
                                            <Triggers>
                                                <asp:AsyncPostBackTrigger ControlID="btnUp" EventName="click" />
                                            </Triggers>                                           
                                        </asp:UpdatePanel>
                                    </div>
                                    <div>
                                        <asp:UpdatePanel ID="UpdatePanel3" runat="server" UpdateMode="Conditional">
                                            <ContentTemplate>
                                                <fieldset>
                                                    <legend>UpdatePanel3 DateTime：<%= DateTime.Now %></legend>
                                                    <div>
                                                        <asp:Button ID="btnUpdate3" runat="server" Text="只更新UpdatePanel3" />                                                        
                                                    </div>
                                                    <div>
                                                        <asp:Button ID="btnUp" runat="server" Text="更新UpdatePanel2、UpdatePanel3" />
                                                    </div>
                                                </fieldset>
                                            </ContentTemplate>
                                        </asp:UpdatePanel>
                                    </div>                                    
                                </fieldset>                                
                            </ContentTemplate>    
                            <Triggers>
                                <asp:AsyncPostBackTrigger ControlID="btnUpdate" EventName="click" />
                                <asp:PostBackTrigger ControlID="btnAll" />
                            </Triggers>                        
                        </asp:UpdatePanel>                        
                    </div>                    
                </fieldset>                
            </div>
        </div>
    </div>
    </form>
</body>
</html>
