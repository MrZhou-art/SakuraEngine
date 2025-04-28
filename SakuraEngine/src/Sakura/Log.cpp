#include "Log.h"
#include <spdlog/sinks/stdout_color_sinks.h>//��־��ɫ

namespace Sakura
{
	//��̬��Ա�����������ʼ��
	std::shared_ptr<spdlog::logger> Log::mCoreLogger = nullptr;
	std::shared_ptr<spdlog::logger> Log::mClientLogger = nullptr;

	void Log::initLog()//��ʼ����־
	{
		//������־�����ʽ(��ʼ��ɫ��Χ,ʱ��,��¼��������,Ҫ��¼��ʵ���ı�,������ɫ��Χ)
		spdlog::set_pattern("%^[%T] %n %v%$");

		//���ÿ������û���־��¼��
		mCoreLogger = spdlog::stdout_color_mt("SAKURA");
		mCoreLogger->set_level(spdlog::level::trace);

		mClientLogger = spdlog::stdout_color_mt("CLINT");
		mClientLogger->set_level(spdlog::level::trace);
	}
}