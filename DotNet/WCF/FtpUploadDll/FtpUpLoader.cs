using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.IO;
using System.Net;

namespace FtpUploadDll
{
    public delegate void UploadEvent(FtpUploadEvent uploadEvent,object param);

    public class FtpUpLoader
    {
        public event UploadEvent UploadCompleted = null;
        public event UploadEvent UploadError = null;
        public event UploadEvent UploadGuage = null;
        private NetworkCredential _networkCredential = null;

        public FtpUpLoader()
        {
            _networkCredential = new NetworkCredential("anonymous", "anonymous@founder.com");
        }

        public FtpUpLoader(string userName, string passWord)
        {
            _networkCredential = new NetworkCredential(userName, passWord);
        }

        public bool Upload(string address, string fileName)
        {
            string parentPath = address.Substring(0, address.LastIndexOf("/"));
            if (!MakeDir(parentPath))
            {
                if (UploadError != null)
                {
                    UploadError(FtpUploadEvent.Error, "Could not access to ftp server.");
                }
                return false;
            }
            ManualResetEvent waitObject;
            Uri target = new Uri(address);
            FtpState state = new FtpState();
            FtpWebRequest request = (FtpWebRequest)WebRequest.Create(target);
            request.Method = WebRequestMethods.Ftp.UploadFile;

            request.Credentials = _networkCredential;

            state.Request = request;
            state.FileName = fileName;
            waitObject = state.OperationComplete;

            request.BeginGetRequestStream(
                new AsyncCallback(EndGetStreamCallback),
                state
            );
            return true;
        }

        private bool MakeDir(string target)
        {
            try
            {
                if (IsDirExist(target))
                {
                    return true;
                }
                else
                {
                    Uri uri = new Uri(target);
                    if (uri.AbsolutePath == "/")
                    {
                        return false;
                    }
                }
                string parentPath = target.Substring(0, target.LastIndexOf("/"));
                if (!IsDirExist(parentPath))
                {
                    if (!MakeDir(parentPath))
                    {
                        return false;
                    }
                }
                FtpWebRequest reqFTP = (FtpWebRequest)FtpWebRequest.Create(target);
                reqFTP.Credentials = _networkCredential;
                reqFTP.Method = WebRequestMethods.Ftp.MakeDirectory;
                FtpWebResponse response = (FtpWebResponse)reqFTP.GetResponse();
                response.Close();
                return true;
            }
            catch (System.Exception)
            {
                return false;
            }
        }

        private bool IsDirExist(string dir)
        {
            try
            {
                FtpWebRequest reqFTP = (FtpWebRequest)FtpWebRequest.Create(dir);
                reqFTP.Credentials = _networkCredential;
                reqFTP.Method = WebRequestMethods.Ftp.ListDirectory;
                FtpWebResponse response = (FtpWebResponse)reqFTP.GetResponse();
                response.Close();
                return true;
            }
            catch (System.Exception)
            {
                return false;
            }
        }

        private void EndGetStreamCallback(IAsyncResult ar)
        {
            FtpState state = (FtpState)ar.AsyncState;

            Stream requestStream = null;
            try
            {
                requestStream = state.Request.EndGetRequestStream(ar);
                const int bufferLength = 2048;
                byte[] buffer = new byte[bufferLength];
                int count = 0;
                int readBytes = 0;
                FileStream stream = File.OpenRead(state.FileName);
                DateTime lastEvent = DateTime.Now;
                long fileSize = stream.Length;
                do
                {
                    readBytes = stream.Read(buffer, 0, bufferLength);
                    requestStream.Write(buffer, 0, readBytes);
                    count += readBytes;
                    if (UploadGuage != null && DateTime.Now.Ticks - lastEvent.Ticks > 10000000)
                    {
                        lastEvent = DateTime.Now;
                        UploadGuage(FtpUploadEvent.Guage, System.Convert.ToDouble(count) / fileSize + "   " + state.Request.RequestUri.AbsoluteUri);
                    }
                }
                while (readBytes != 0);

                if (UploadGuage != null)
                {
                    UploadGuage(FtpUploadEvent.Guage, System.Convert.ToDouble(1));
                }
                requestStream.Close();
                state.Request.BeginGetResponse(
                    new AsyncCallback(EndGetResponseCallback),
                    state
                );
            }
            catch (Exception e)
            {
                if (UploadError != null)
                {
                    UploadError(FtpUploadEvent.Error, "Could not get the request stream.");
                }
                state.OperationException = e;
                state.OperationComplete.Set();
                return;
            }

        }

        private void EndGetResponseCallback(IAsyncResult ar)
        {
            FtpState state = (FtpState)ar.AsyncState;
            FtpWebResponse response = null;
            try
            {
                response = (FtpWebResponse)state.Request.EndGetResponse(ar);
                response.Close();
                state.StatusDescription = response.StatusDescription;
                if (UploadCompleted != null)
                {
                    UploadCompleted(FtpUploadEvent.Completed, state.StatusDescription);
                }
                state.OperationComplete.Set();
            }
            catch (Exception e)
            {
                if (UploadError != null)
                {
                    UploadError(FtpUploadEvent.Error, "Error getting response.");
                }
                state.OperationException = e;
                state.OperationComplete.Set();
            }
        }
    }
}
