#pragma once

#include <string>
#include <memory>

#include "Singleton.h"

namespace aurora
{
	class ProfilerPattern
	{
	public:
		virtual void OnRun(uint32_t layer, const std::string& info) = 0;
	private:
	};

	class StreamProfilerPattern : public ProfilerPattern
	{
	public:
		void OnRun(uint32_t layer, const std::string& info) override;
	private:

	};

	class DrawProfilerPattern : public ProfilerPattern
	{
	public:
		void OnRun(uint32_t layer, const std::string& info) override;
	private:
	};

	class Profiler : public Singleton<Profiler>
	{
	public:
		Profiler();

		void OnRun();

		void set_pattern(std::unique_ptr<ProfilerPattern> pattern) { pattern_ = std::move(pattern); }
		const std::unique_ptr<ProfilerPattern>& pattern() const { return pattern_; }
	private:
		std::unique_ptr<ProfilerPattern> pattern_;
		std::unique_ptr<ProfilerNode> root_;
	};

	class ProfilerNode
	{
	public:
		ProfilerNode(const std::string& name);
		ProfilerNode(const std::string& name, const std::string& parent_name);
		ProfilerNode(const std::string& name, const std::unique_ptr<ProfilerNode>& parent);

		virtual ~ProfilerNode() = 0;
		
		void AddChild(std::shared_ptr<ProfilerNode> child);
		const std::shared_ptr<ProfilerNode> GetChildByName() const;

		virtual void OnRun(const std::unique_ptr<ProfilerPattern>& pattern) = 0;

		const std::string& name() const { return name_; }
		uint32_t layer() const { return layer_; }
	private:
		std::string name_;
		uint32_t layer_;
		std::shared_ptr<ProfilerNode> children_;
	};

	class TimeProfilerNode : public ProfilerNode
	{
	public:
		class Timer
		{
		public:
			Timer(const std::shared_ptr<ProfilerNode> owner);
			~Timer();
		private:
			std::shared_ptr<ProfilerNode> owner_;
		};

	public:
		TimeProfilerNode(const std::string& name);
		TimeProfilerNode(const std::string& name, const std::string& parent_name);
		TimeProfilerNode(const std::string& name, const std::unique_ptr<ProfilerNode>& parent);

		void OnRun(const std::unique_ptr<ProfilerPattern>& pattern) override;
	private:

	};

	class CountProfilerNode : public ProfilerNode
	{
	public:
		class Counter
		{
		public:
		private:
		};

	public:
		CountProfilerNode(const std::string& name);
		CountProfilerNode(const std::string& name, const std::string& parent_name);
		CountProfilerNode(const std::string& name, const std::unique_ptr<ProfilerNode>& parent);

		void OnRun(const std::unique_ptr<ProfilerPattern>& pattern) override;
	private:
	};
}