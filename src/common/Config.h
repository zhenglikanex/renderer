#ifndef CONFIG_H_
#define CONFIG_H_

#include <string>
#include <unordered_map>

namespace aurora
{
	class Config
	{
	public:
		bool Load(const std::string& name);

		int32_t GetInt(const std::string& name);
		bool GetBool(const std::string& name);
		const std::string& GetString(const std::string& name);
	private:
		std::unordered_map<std::string, std::string> params_;
	};
}

#endif
