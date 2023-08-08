# Qt Plugins Framework

Qt 插件框架，使用Qt的Plugins功能，一个Qt的Plugin在本框架中为一个PluginsPackage，其中可包含任意数量的Plugin。

## PluginsManager

PluginsManager本身也是一个Qt的Plugin，负责扫描PluginsPackage、创建和销毁Plugin以及Plugin之间的消息传递。

## PluginsPackage

每一个PluginsPackage，需要继承IPluginsPackage接口并注册为Qt Plugin的接口类，该接口负责对外提供每个Plugin的ID以及创建函数（工厂模式）

## Plugin

每个Plugin应该继承IPlugin，并在OnMessage中响应需要关注的消息，使用Message发送消息（消息订阅模式），同时每个Plugin应说明为普通插件还是单例插件。

为解耦，每个Plugin还应抽象出其接口类，以方便在其他插件中只添加头文件即可编译及调用。
