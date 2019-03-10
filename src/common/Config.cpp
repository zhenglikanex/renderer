#include "Config.h"

#include "Aurora.h"

#include <fstream>
#include <sstream>
#include <string>

#include "FileHelper.h"
#include "FileIdentifer.h"
#include "StringUtil.h"

namespace aurora
{
	bool Config::Load(const std::string& name)
	{
		auto identifer = FileHelper::GetInstance()->OpenFileIdentifer(name);
		if (!identifer)
		{
			return false;
		}

		std::string line;
		std::vector<std::string> tokens;
		while (getline(*identifer.istream(), line))
		{
			auto size = line.size();
			if (size > 0 && line[0] != '#')
			{
				StringUtil::RemoveCh(line, ' ');

				size = line.size();
				if (size < 3)
				{
					return false;
				}

				tokens = StringUtil::split(line, '=');
				if (tokens.size() < 2)
				{
					return false;
				}
				
				params_.emplace(tokens[0], tokens[1]);
			}
		}

		return true;
	}

	int32_t Config::GetInt(const std::string& name)
	{
		AURORA_ASSERT(params_.find(name) != params_.end());

		auto iter = params_.find(name);
		return std::stoi(iter->second);
	}

	bool Config::GetBool(const std::string& name)
	{
		AURORA_ASSERT(params_.find(name) != params_.end());
		
		auto iter = params_.find(name);
		if (iter->second == "false")
		{
			return false;
		}
		else if (iter->second == "true")
		{
			return true;
		}

		return false;
	}

	const std::string& Config::GetString(const std::string& name)
	{
		AURORA_ASSERT(params_.find(name) != params_.end());
		
		return params_.find(name)->second;
	}
}