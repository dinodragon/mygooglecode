using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.Text;
using System.IO;

namespace WcfFileTransferService
{

    ///**/
    ///// <summary>
    ///// 消息契约（定义与 SOAP 消息相对应的强类型类）
    ///// </summary>
    //[MessageContract]
    //public class FileWrapper
    //{
    //    /**/
    //    /// <summary>
    //    /// 指定数据成员为 SOAP 消息头
    //    /// </summary>
    //    [MessageHeader]
    //    public string FilePath;

    //    /**/
    //    /// <summary>
    //    /// 指定将成员序列化为 SOAP 正文中的元素
    //    /// </summary>
    //    [MessageBodyMember]
    //    public Stream FileData;
    //}



    // NOTE: If you change the interface name "IService1" here, you must also update the reference to "IService1" in App.config.
    [ServiceContract]
    public interface IFileTransfer
    {
        [OperationContract]
        string GetData(int value);

        [OperationContract]
        void UploadFile(Stream fileWrapper);

        [OperationContract]
        CompositeType GetDataUsingDataContract(CompositeType composite);

        // TODO: Add your service operations here
    }

    // Use a data contract as illustrated in the sample below to add composite types to service operations
    [DataContract]
    public class CompositeType
    {
        bool boolValue = true;
        string stringValue = "Hello ";

        [DataMember]
        public bool BoolValue
        {
            get { return boolValue; }
            set { boolValue = value; }
        }

        [DataMember]
        public string StringValue
        {
            get { return stringValue; }
            set { stringValue = value; }
        }
    }
}
