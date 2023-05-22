// StrringFormat.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <string>
#include <any>
#include <vector>

std::string format = "qwert%dqwert%drree%fyy%d";
typedef std::vector<std::any> PARAM_LIST;


/// <summary>
/// 格式化输入字符串  
/// </summary>
/// <param name="input">输入字符串</param>
/// <param name="format">字符串格式</param>
/// <param name="param">格式化后的参数</param>
/// <returns>是否正常格式化</returns>
bool StringFormatInput(const std::string& input,const std::string& format , PARAM_LIST* param) {
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

int main()
{
	PARAM_LIST param;
	bool ret = StringFormatInput("qwert1231qwert4321rree145.678yy-987", format, &param);

	for(int i =0;i< param.size();i++){
		if (param[i].type() == typeid(int)) {
			std::cout << " param[" << i << "] = " << std::any_cast<int>(param[i]) << std::endl;
		}
		else if (param[i].type() == typeid(float)) {
			std::cout << " param[" << i << "] = " << std::any_cast<float>(param[i]) << std::endl;
		}
		
	}
    std::cout << "Hello World!\n";
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
