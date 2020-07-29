#include "main.h"

//存储为json格式字符串流
string writeFileJson(int equipment_id,int status,double electricity)
{
	//创立json根节点
	Json::Value root;

	//获取系统本地时间
	char time_buf[32] = { 0 };
	time_t now_time = time(NULL);
	struct tm  *t = localtime(&now_time);
	//把time需要的对应格式转化到time_buf中
	sprintf(time_buf,"%04d-%02d-%02d %02d:%02d:%02d", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);

	//根节点属性，即为显示的数据
	root["equipment"] = Json::Value(equipment_id);
	root["time"] = Json::Value(time_buf);
	root["status"] = Json::Value(status);
	root["electricity"] = Json::Value(electricity);

	//直接输出
	//cout << "FastWriter:" << endl;
	Json::FastWriter fw;
	//cout << fw.write(root);
	//json快速格式（整行显示）直接转化为 string类型，存到buf中
	string buf = fw.write(root);
	//cout << buf << endl;


	//json分行有格式的显示转换为string 格式，存到ret中
	//string ret = root.toStyledString();

	//template<typename ty>
	//inline void load_from_buff(ty & val, char* buff, size_t len = -1)
	//{
	//	reader rd(buff, len);
	//	json_impl<ty>::read(rd, val);
	//}

	//子节点
	//Json::Value partner;

	//子节点属性
	//partner["partner name"] = Json::Value("joe");
	//partner["partner age"] = Json::Value(22);
	//partner["partner_sex_is_male"] = Json::Value(true);

	//子节点挂载到根节点上
	//root["partner"] = Json::Value(partner);

	//数组形式
	//root["achievement"].append("ach1");
	//root["achievement"].append("ach2");
	//root["achievement"].append("ach3");

	//缩进输出
	//cout << "StyledWriter:" << endl;
	//Json::StyledWriter sw;
	//cout << sw.write(root) << endl << endl;

	//输出到文件中
	//ofstream os;
	//os.open("demo.log");
	//os << fw.write(root);
	//os.close();

	return buf;
}





