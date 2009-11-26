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

        //在此创建回调方法。有关添加回调方法的详细信息，请在解决方案资源管理器中选择“功能区 XML”项，然后按 F1
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
