using System;
using System.Collections.Generic;
using System.Text;
using Office = Microsoft.Office.Core;
using System.Runtime.InteropServices;
using System.Windows.Forms;
using System.Drawing;

namespace WordAddIn
{
    [ComVisible(true)]
    public class Ribbon : Office.IRibbonExtensibility
    {

        public Office.IRibbonUI ribbonUI;

        public string GetCustomUI(string RibbonID)
        {
            return Properties.Resources.Ribbon;
        }

        //�ڴ˴����ص��������й���ӻص���������ϸ��Ϣ�����ڽ��������Դ��������ѡ�񡰹����� XML���Ȼ�� F1
        public void Ribbon_Load(Office.IRibbonUI ribbonUI)
        {
            this.ribbonUI = ribbonUI;
        }

        public stdole.IPictureDisp GetImage(string imageName)
        {
            return PictureConverter.ImageToPictureDisp(
                Properties.Resources.ResourceManager.GetObject(imageName) as Image);
        }


        internal class PictureConverter : AxHost
        {
            private PictureConverter() : base(String.Empty) { }

            static public stdole.IPictureDisp ImageToPictureDisp(Image image)
            {
                return (stdole.IPictureDisp)GetIPictureDispFromPicture(image);
            }

            static public stdole.IPictureDisp IconToPictureDisp(Icon icon)
            {
                return ImageToPictureDisp(icon.ToBitmap());
            }

            static public Image PictureDispToImage(stdole.IPictureDisp picture)
            {
                return GetPictureFromIPicture(picture);
            }
        }



        public void Login_Click(Office.IRibbonControl control)
        {
            if (control.Id == "Launcher1")
            {

            }
        }

    }


}
