using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Linq;

namespace Serialization
{
    public enum CheckOutState
    {
        CheckedIn = 0,
        CheckedOutTome = 1,
        CheckedOutByOthers = 2,
    };

    public class Document
    {
        private long _id = -1;
        private string _title = string.Empty;
        private CheckOutState _state = CheckOutState.CheckedIn;
        private string _status = string.Empty;
        private System.Guid _guid = System.Guid.Empty;
        private string _fullName = string.Empty;
        private string _frameName = string.Empty;
        private bool _haveXml = false;
        private long _styleId = -1;
        private System.Guid _pdfGuid = System.Guid.Empty;
        private System.Guid _xmlGuid = System.Guid.Empty;
        private string _desc = string.Empty;

        public Document()
        {

        }

        public Document(long id, string title, CheckOutState state, string status, System.Guid guid, string fullName, string frameName, bool haveXml, long styleId, System.Guid pdfGuid, System.Guid xmlGuid, string desc)
        {
            _id = id;
            _title = title;
            _state = state;
            _status = status;
            _guid = guid;
            _fullName = fullName;
            _frameName = frameName;
            _haveXml = haveXml;
            _styleId = styleId;
            _pdfGuid = pdfGuid;
            _xmlGuid = xmlGuid;
            _desc = desc;
        }

        public long Id { get { return _id; } set { _id = value; } }
        public string Title { get { return _title; } set { _title = value; } }
        public bool HaveXml { get { return _haveXml; } set { _haveXml = value; } }
        public string Status { get { return _status; } set { _status = value; } }
        public CheckOutState State { get { return _state; } set { _state = value; } }
        public System.Guid Guid { get { return _guid; } set { _guid = value; } }
        public string FullName { get { return _fullName; } set { _fullName = value; } }
        public string FrameName { get { return _frameName; } set { _frameName = value; } }
        public System.Guid PdfGuid { get { return _pdfGuid; } set { _pdfGuid = value; } }
        public System.Guid XmlGuid { get { return _xmlGuid; } set { _xmlGuid = value; } }
        public long StyleId { get { return _styleId; } set { _styleId = value; } }
        public string Desc { get { return _desc; } }

    }
}
