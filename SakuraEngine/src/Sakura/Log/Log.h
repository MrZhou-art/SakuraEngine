#pragma once

#include "Sakura/core.h"
#include <spdlog/spdlog.h>// spdlog ��
#include <spdlog/fmt/ostr.h>//�����������

namespace Sakura
{
	class SAKURA_API Log
	{
	public:
		static void initLog();//��ʼ����־

		inline static std::shared_ptr<spdlog::logger>& getCoreLogger() { return mCoreLogger; }//��ȡ������־��¼��
		inline static std::shared_ptr<spdlog::logger>& getClientLogger() { return mClientLogger; }//��ȡ�û���־��¼��

	private:
		// ��¼��
		static std::shared_ptr<spdlog::logger> mCoreLogger;
		static std::shared_ptr<spdlog::logger> mClientLogger;
	};
}


//�궨����־����
/*
*	SAKURA_CORE_ERROR	�����ƣ���Ϊ��־���õļ�д��
*	(...)				�ɱ�����б����������������Ĳ�����
*	::					ȫ�������ռ�ǰ׺��ȷ���ҵ���ȷ�� Sakura �����ռ䡣(��ʽ����ȫ��������,Ƕ�������ռ��ͬ���ֲ�ʵ��)
*	Sakura::Log			��־ϵͳ����������ռ䡣
*	getCoreLogger()		��̬���������غ�����־���Ĺ���ָ�루ͨ���� spdlog::logger����
*	->error(...)		������־���� error ��������¼���󼶱����־��
*	__VA_ARGS__			Ԥ������������ʶ�����������д���Ŀɱ����
*/
//������
#define SAKURA_CORE_TRACE(...)		::Sakura::Log::getCoreLogger()->trace(__VA_ARGS__)
#define SAKURA_CORE_INFO(...)		::Sakura::Log::getCoreLogger()->info(__VA_ARGS__)
#define SAKURA_CORE_WARN(...)		::Sakura::Log::getCoreLogger()->warn(__VA_ARGS__)
#define SAKURA_CORE_ERROR(...)		::Sakura::Log::getCoreLogger()->error(__VA_ARGS__)
#define SAKURA_CORE_CRITICAL(...)	::Sakura::Log::getCoreLogger()->critical(__VA_ARGS__)
//�û���
#define SAKURA_TRACE(...)			::Sakura::Log::getClientLogger()->trace(__VA_ARGS__)
#define SAKURA_INFO(...)			::Sakura::Log::getClientLogger()->info(__VA_ARGS__)
#define SAKURA_WARN(...)			::Sakura::Log::getClientLogger()->warn(__VA_ARGS__)
#define SAKURA_ERROR(...)			::Sakura::Log::getClientLogger()->error(__VA_ARGS__)
#define SAKURA_CRITICAL(...)		::Sakura::Log::getClientLogger()->critical(__VA_ARGS__)