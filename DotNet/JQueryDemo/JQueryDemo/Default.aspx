<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="Default.aspx.cs" Inherits="JQueryDemo._Default" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml" >
<head runat="server">
    <title></title>
    <script type="text/javascript" src="Scripts/jquery-1.4.1.js"></script>

    <script type="text/javascript">
        $(document).ready(function() {$("#r2").show();});
    </script>
    
    
</head>
<body>
    <form id="form1" runat="server">
    <div>
    <p id='p1'>If you click on me, I will disappear.</p>
    <h1 id='text1'>文本1</h1>
    <h1 id='text2'>文本2</h1>
    
    <table style="width: 100%;" border="2">
    <tr>
        <td>
            &nbsp;
        </td>
        <td>
            &nbsp;
        </td>
        <td>
            &nbsp;
        </td>
    </tr>
    <tr id="r2" style="visibility: hidden">
        <td>
            &nbsp;
        </td>
        <td>
            &nbsp;
        </td>
        <td>
            &nbsp;
        </td>
    </tr>
    <tr>
        <td>
            &nbsp;
        </td>
        <td>
            &nbsp;
        </td>
        <td>
            &nbsp;
        </td>
    </tr>
</table>
    
    </div>
    </form>
</body>

</html>
