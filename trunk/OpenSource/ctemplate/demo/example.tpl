<html>
<head>
<title> {{NAME}} </title>
</head>
{{!This is a example of template.}}
<body>
Hello {{NAME}},
You have just won ${{VALUE}}!
<table>
{{#IN_TABLE}}
<tr>
     <td> {{ITEM}} </td>
     <td> {{TAXED_VALUE}} </td>
</tr>
{{/IN_TABLE}}
</table>
{{>INCLUDED_TEMPLATE}}
</body>
</html>
<!--ctinclude.tpl-->
 <div>
{{INCLUDE_VAR}}
</div>