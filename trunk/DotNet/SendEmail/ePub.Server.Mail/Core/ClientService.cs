using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using System.ServiceModel;
using System.ServiceModel.Channels;

namespace ePub.Server.Mail.Core
{
    public class ClientServices
    {
        public static T GetService<T>(string endpointConfigurationName)
        {
            ChannelFactory<T> channelFactory = new ChannelFactory<T>(endpointConfigurationName);
            T channel = channelFactory.CreateChannel();

            return channel;
        }
    }
}
