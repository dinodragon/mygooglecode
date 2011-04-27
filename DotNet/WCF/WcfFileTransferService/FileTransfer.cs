using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.Text;
using System.IO;

namespace WcfFileTransferService
{
    public class FileTransfer : IFileTransfer
    {
        public string GetData(int value)
        {
            return string.Format("You entered: {0}", value);
        }

        public CompositeType GetDataUsingDataContract(CompositeType composite)
        {
            if (composite.BoolValue)
            {
                composite.StringValue += "Suffix";
            }
            return composite;
        }

        public void UploadFile(Stream fileWrapper)
        {
            var sourceStream = fileWrapper;

            var targetStream = new FileStream(@"D:\" + Guid.NewGuid().ToString(),
                FileMode.Create,
                FileAccess.Write,
                FileShare.None);

            var buffer = new byte[4096];
            var count = 0;

            while ((count = sourceStream.Read(buffer, 0, buffer.Length)) > 0)
            {
                targetStream.Write(buffer, 0, count);
            }

            targetStream.Close();
            sourceStream.Close();
        }
    }
}
