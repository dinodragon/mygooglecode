using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Web.Services.Protocols;
using System.Web.Services;

namespace WebService_Client
{
    [WebServiceBinding(Name = "TestWebServiceSoap", Namespace = "http://tempuri.org/")]
    public class WebServiceClient : SoapHttpClientProtocol
    {
        public WebServiceClient(string url)
        {
            base.Url = url;
        }

        [SoapDocumentMethod("http://tempuri.org/HelloWorld",
            RequestNamespace = "http://tempuri.org/",
            ResponseNamespace = "http://tempuri.org/",
            Use = System.Web.Services.Description.SoapBindingUse.Default,
            ParameterStyle = System.Web.Services.Protocols.SoapParameterStyle.Default)]
        public string HelloWorld() //请注意这里实现的方法的参数，参数类型以及返回类型都需要和Web服务里的方法是一模一样，否则将报找不到该Web服务的错误
        {
            return (string)base.Invoke("HelloWorld", new object[] { })[0];
        }
    }
}
