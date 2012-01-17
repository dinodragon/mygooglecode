using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Xml;
using Verlinea.ComboBoxTree;

namespace DynamicUI
{
    public partial class Form1 : Form
    {
        private XmlDocument _doc = new XmlDocument();
        private List<Control> controlList = new List<Control>();
        static int yIndex = 0;

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            _doc.Load(@"动态面板.xml");
            XmlNodeList name = _doc.SelectNodes("/Root/Type");
            List<ListItem> list = new List<ListItem>();
            foreach (XmlNode item in name)
            {
                ListItem li = new ListItem(item.Attributes["ID"].Value, item.Attributes["Name"].Value);
                list.Add(li);
            }
            typeComboBox.DataSource = list;
        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            tableLayoutPanel1.Controls.Clear();
            controlList.Clear();
            yIndex = 0;
            string type = typeComboBox.SelectedValue.ToString();
            XmlNode node = _doc.SelectSingleNode(String.Format("/Root/Type[@Name=\"{0}\"]", type));
            XmlNodeList condition = node.SelectNodes("Condition");
            foreach (XmlNode item in condition)
            {
                BuildUI(item);
            }
        }

        private void BuildUI(XmlNode conditionNode)
        {
            Label lable = new Label();
            lable.AutoSize = true;
            lable.Anchor = AnchorStyles.Bottom | AnchorStyles.Left | AnchorStyles.Right | AnchorStyles.Top;
            lable.TextAlign = ContentAlignment.MiddleCenter;
            switch (conditionNode.Attributes["Type"].Value.ToLower())
            {
                case "select":
                    {
                        lable.Text = conditionNode.Attributes["Name"].Value;
                        tableLayoutPanel1.Controls.Add(lable, 0, yIndex);
                        ComboBox comboBox = new ComboBox();
                        comboBox.DropDownStyle = ComboBoxStyle.DropDownList;
                        XmlNodeList name = conditionNode.SelectNodes("Item");
                        List<ListItem> list = new List<ListItem>();
                        foreach (XmlNode item in name)
                        {
                            ListItem li = new ListItem(item.Attributes["Key"].Value, item.Attributes["Value"].Value);
                            list.Add(li);
                        }
                        comboBox.DataSource = list;
                        comboBox.Tag = lable.Text;
                        tableLayoutPanel1.Controls.Add(comboBox, 1, yIndex++);
                        controlList.Add(comboBox);
                    }
                    break;
                case "input":
                    {
                        lable.Text = conditionNode.Attributes["Name"].Value;
                        tableLayoutPanel1.Controls.Add(lable, 0, yIndex);
                        TextBox textBox = new TextBox();
                        textBox.Tag = lable.Text;
                        tableLayoutPanel1.Controls.Add(textBox, 1, yIndex++);
                        controlList.Add(textBox);
                    }
                    break;
                case "tree":
                    {
                        lable.Text = conditionNode.Attributes["Name"].Value;
                        tableLayoutPanel1.Controls.Add(lable, 0, yIndex);
                        ComboBoxTree comboBoxTree = new ComboBoxTree();
                        comboBoxTree.Tag = lable.Text;
                        comboBoxTree.BranchSeparator = "-";
                        XmlNodeList nodes = conditionNode.SelectNodes("Item");
                        TreeNode treeNode = new TreeNode();
                        BuileTreeNode(treeNode.Nodes, nodes);
                        foreach (TreeNode item in treeNode.Nodes)
                        {
                            comboBoxTree.Nodes.Add(item);
                        }
                        tableLayoutPanel1.Controls.Add(comboBoxTree, 1, yIndex++);
                        controlList.Add(comboBoxTree);
                    }
                    break;
            }
        }

        private void BuileTreeNode(TreeNodeCollection treeNodeCol, XmlNodeList nodes)
        {
            foreach (XmlNode item in nodes)
            {
                TreeNode treeNodeItem = new TreeNode();
                treeNodeItem.Name = item.Attributes["Key"].Value;
                treeNodeItem.Text = item.Attributes["Value"].Value;
                treeNodeCol.Add(treeNodeItem);
                if (item.ChildNodes.Count > 0)
                {
                    BuileTreeNode(treeNodeItem.Nodes, item.ChildNodes);
                }
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            BuildSearch();
        }

        private string BuildSearch()
        {
            ListItem type = typeComboBox.SelectedItem as ListItem;
            XmlNode typeNode = _doc.SelectSingleNode(String.Format("/Root/Type[@Name=\"{0}\" and @ID=\"{1}\"]", type.Value, type.Key));
            XmlDocument doc = new XmlDocument();
            doc.AppendChild(doc.CreateXmlDeclaration("1.0", "UTF-8", ""));
            XmlElement rootElement = doc.CreateElement("Root");
            XmlElement typeElement = doc.CreateElement("Type");
            XmlAttribute attrib = doc.CreateAttribute("Name");
            attrib.Value = type.Value;
            typeElement.Attributes.Append(attrib);
            attrib = doc.CreateAttribute("ID");
            attrib.Value = type.Key;
            typeElement.Attributes.Append(attrib);

            foreach (Control item in controlList)
            {
                string xpath = String.Format("Condition[@Name=\"{0}\"]", item.Tag);
                XmlNode conditionNode = typeNode.SelectSingleNode(xpath);
                XmlElement conditionElement = doc.CreateElement("Condition");
                XmlAttribute attribTemp = doc.CreateAttribute("Name");
                attribTemp.Value = conditionNode.Attributes["Name"].Value;
                conditionElement.Attributes.Append(attribTemp);
                attribTemp = doc.CreateAttribute("Type");
                attribTemp.Value = conditionNode.Attributes["Type"].Value;
                conditionElement.Attributes.Append(attribTemp);
                attribTemp = doc.CreateAttribute("FieldName");
                attribTemp.Value = conditionNode.Attributes["FieldName"].Value;
                conditionElement.Attributes.Append(attribTemp);
                attribTemp = doc.CreateAttribute("CatTypeId");
                attribTemp.Value = conditionNode.Attributes["CatTypeId"].Value;
                conditionElement.Attributes.Append(attribTemp);
                attribTemp = doc.CreateAttribute("FieldValue");

                switch (item.GetType().Name.ToLower())
                {
                    case "combobox":
                        {
                            ComboBox cb = item as ComboBox;
                            ListItem li = cb.SelectedItem as ListItem;
                            attribTemp.Value = li.Key;
                        }
                        break;
                    case "textbox":
                        {
                            TextBox tb = item as TextBox;
                            attribTemp.Value = tb.Text;
                        }
                        break;
                    case "comboboxtree":
                        {
                            ComboBoxTree cbt = item as ComboBoxTree;
                            attribTemp.Value = cbt.SelectItemName;
                        }
                        break;
                }
                conditionElement.Attributes.Append(attribTemp);
                typeElement.AppendChild(conditionElement);
            }
            XmlElement elementTemp = doc.CreateElement("PageNo");
            elementTemp.InnerText = "1";
            typeElement.AppendChild(elementTemp);
            elementTemp = doc.CreateElement("PageSize");
            elementTemp.InnerText = "20";
            typeElement.AppendChild(elementTemp);
            rootElement.AppendChild(typeElement);
            doc.AppendChild(rootElement);
            return doc.InnerXml;
        }
    }
}
