支持自注册的组件程序，向系统注册表注册自己。
该类组件需要实现下列方法
	DllRegisterServer 需要自己向注册表里写数据
	DllUnregisterServer
	DllGetClassObject

项目中需要提供类工厂