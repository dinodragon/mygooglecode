<%@ Page Language="C#" AutoEventWireup="true"  CodeFile="Default.aspx.cs" Inherits="_Default" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">

    <script type="text/javascript" src="Scripts/jquery-1.3.2-vsdoc2.js"></script>

    <script type="text/javascript">
        $(document).ready(function() {
            $("#text1").click(function() {
                $(this).hide();
            });

            $("#P1").click(function() {
                $("#text1").show();
            });
        });
    </script>

    <title>jquery学习</title>
</head>
<body>
    <form id="form1" runat="server">
    <div>
        <p id="text1">
            If you click on me, I will disappear.</p>
        <p id="P1">
            If you click on me, text1 will disappear.</p>
        <asp:FileUpload ID="FileUpload1" runat="server" />
    </div>
    </form>
</body>
</html>
