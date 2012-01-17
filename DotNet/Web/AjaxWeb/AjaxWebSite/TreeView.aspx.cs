using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Xml;

public partial class TreeView : System.Web.UI.Page
{
    protected void Page_Load(object sender, EventArgs e)
    {
        if (!IsPostBack)
        {
            XmlDocument doc = new XmlDocument();
            doc.Load(Server.MapPath("XmlFile.xml"));
            treeView.Nodes.Clear();
            treeView.Nodes.Add(new TreeNode("Root"));
            TreeNode tNode = treeView.Nodes[0];
            AddTreeNode(doc.DocumentElement, tNode);
            treeView.ExpandAll();
        }
    }

    private void AddTreeNode(XmlNode xmlNode, TreeNode treeNode)
    {
        int i = 0;
        if (xmlNode.HasChildNodes)
        {
            foreach (XmlNode ChildNode in xmlNode.ChildNodes)
            {
                string strTreeNodeName = ChildNode.Attributes["Text"].Value;
                if (ChildNode as XmlElement == null)
                {
                    continue;
                }
                if (ChildNode.FirstChild as XmlText != null)
                {
                    strTreeNodeName += ":";
                    strTreeNodeName += ChildNode.FirstChild.InnerText;
                }
                treeNode.ChildNodes.Add(new TreeNode(strTreeNodeName,i.ToString()));
                AddTreeNode(ChildNode, treeNode.ChildNodes[i++]);
            }
        }
    }
    protected void treeView_SelectedNodeChanged(object sender, EventArgs e)
    {
        Label1.Text = treeView.SelectedNode.ValuePath;
    }
}
