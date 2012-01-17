using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Autofac;


///示例见，Autofac是一个依赖注入容器，简单使用说明见
/// http://code.google.com/p/autofac/wiki/ComponentCreation
///

namespace AutoFacDemo
{
    interface IPerson
    {
        void Say();
    }

    public class Chinese : IPerson
    {

        public void Say()
        {
            Console.WriteLine("I'm chinese!");
        }
    }

    class Program
    {
        static void Main(string[] args)
        {
            var builder = new ContainerBuilder();
            builder.RegisterType<Chinese>().As<IPerson>();
            //builder.RegisterType<NHPersonRepository>().As<IFindPerson, IRepository<Person>>();
            var container = builder.Build();
            var onePerson = container.Resolve<IPerson>();
            onePerson.Say();
        }
    }
}
