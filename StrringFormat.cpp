// StrringFormat.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <string>
#include <any>
#include <vector>

std::string format = "qwert%dqwert%drree%fyy%d";
typedef std::vector<std::any> PARAM_LIST;

#define PARAM_IN 
#define PARAM_OUT 

/// <summary>
/// 格式化输入字符串  
/// </summary>
/// <param name="input">输入字符串</param>
/// <param name="format">字符串格式</param>
/// <param name="param">格式化后的参数</param>
/// <returns>是否正常格式化</returns>
bool StringFormatInput(PARAM_IN const std::string& input, PARAM_IN const std::string& format ,PARAM_OUT PARAM_LIST* param) {
	 bool error = false;
	 int input_index = 0;
	 int format_index = 0;
	 while (input_index < input.size() && format_index < format.size())
	 {
		 if (input.at(input_index) == format.at(format_index)) {
			//< 字符匹配
			 format_index++;
			input_index++;
		 }
		 else if(format.at(format_index) == '%') {
			 if (format.at(format_index+1) == 'd') {
				//< 此刻开始 整数
				 int i = 0;
				 int symbol = 1;
				 int ret = 0;
				 while (true)
				 {
					 if (input.at(input_index+i) >= '0' && input.at(input_index + i) <= '9') {
						 i++;
					 }
					 else if ((i == 0) && ((input.at(input_index) == '+') || (input.at(input_index) == '-'))) {
						//< 符号位
						 i++;
					 }
					 else {
						 //< 不是数字 退出
						 break;
					 }
					 if((input_index+i)>= input.size()){
						 break;
					 }
				 }
				 char num[128] = { 0 };
				 memcpy(num, &(input.c_str()[input_index]), i);
				 ret = atoi(num);
				 param->push_back(std::make_any<int>(ret));

				 format_index +=2;
				 input_index += i;
			 }
			 else if (format.at(format_index + 1) == 'f') {
				 //< 此刻开始 整数
				 int i = 0;
				 int symbol = 1;
				 float ret = 0;
				 while (true)
				 {
					 if ((input.at(input_index + i) >= '0' && input.at(input_index + i) <= '9')|| (input.at(input_index + i) == '.')) {
						 i++;
					 }
					 else if ((i == 0) && ((input.at(input_index) == '+') || (input.at(input_index) == '-'))) {
						 //< 符号位
						 i++;
					 }
					 else {
						 //< 不是数字 退出
						 break;
					 }
					 if ((input_index + i) >= input.size()) {
						 break;
					 }
				 }
				 char num[128] = { 0 };
				 memcpy(num, &(input.c_str()[input_index]), i);
				 ret = atof(num);
				 param->push_back(std::make_any<float>(ret));

				 format_index += 2;
				 input_index += i;
			 }
			 else
			 {
				 error = true;
				 break;
			 }
		 }
		 else
		 {
			 error = true;
			 break;
		 }
	 }
	 if (error || (input_index != input.size() || format_index != format.size())){
		 param->clear();
		 return false;
	 }
	 return true;
}

/// <summary>
/// 格式化输出字符串
/// </summary>
/// <param name="format"></param>
/// <param name="param"></param>
/// <returns></returns>
bool StringFormatOutput(PARAM_OUT std::string& output, PARAM_IN const std::string& format, PARAM_IN const PARAM_LIST& param) {
	int index = 0;	//< format 的当前索引
	int param_index = 0; //< param 的当前索引
	bool error = false;
	while (index < format.size() && param_index < param.size()) {
		if (format.at(index) != '%') {
			output += format.at(index);
			index++;
			continue;
		}
		index++;
		if (format.at(index) == 'd') {
			if (param[param_index].type() != typeid(int)) {
				return false;
			}
			output += std::to_string(std::any_cast<int>(param.at(param_index)));
		}
		else if (format.at(index) == 'f') {
			if (param[param_index].type() != typeid(float)) {
				return false;
			}
			output += std::to_string(std::any_cast<float>(param.at(param_index)));
		}
		else {
			return false;
		}
		index++;
		param_index++;
	}
	if (param_index != param.size() || index != format.size()) {
		return false;
	}
	return true;
}

int main()
{
	PARAM_LIST param;
	std::string input = "qwert1231qwert4321rree145.678yy-987";
	bool ret = StringFormatInput(input, format, &param);

	for(int i =0;i< param.size();i++){
		if (param[i].type() == typeid(int)) {
			std::cout << " param[" << i << "] = " << std::any_cast<int>(param[i]) << std::endl;
		}
		else if (param[i].type() == typeid(float)) {
			std::cout << " param[" << i << "] = " << std::any_cast<float>(param[i]) << std::endl;
		}
	}
	std::string output;
	StringFormatOutput(output, format, param);

    std::cout << output <<std::endl;
	std::cout << input << std::endl;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
