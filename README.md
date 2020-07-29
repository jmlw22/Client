# Client
从电流计量模块（传感器）监测设备的client；modbus协议格式：通过传感器----ATC-1000（把RS-485的modbus-RTU数据转换成RJ45的Internet的TCP数据报文）--Internet。
client远程获取传感器的数据，之后进行处理，最终socket形式把数据给java后台中。

有Windows平台的vs2019开发，以及centOS 7  的Linux下运行的client代码。
