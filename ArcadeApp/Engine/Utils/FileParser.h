#pragma once

#include <functional>
#include <stdint.h>
#include <string>
#include <vector>

class Colour;
class Vector2;

enum E_COMMAND_TYPE
{
	E_ONE_LINE, 
	E_MULTI_LINE
};

struct ParseParams
{
	std::string line;
	size_t cursorpos;
	uint32_t lineNum;
};

using Parse = std::function<void(const ParseParams& params)>;

struct Command
{
	E_COMMAND_TYPE commandType = E_ONE_LINE;
	std::string commandString = "";
	Parse parse = nullptr;
};

class FileParser
{
public:
	void AddCommand(const Command& command);
	bool LoadFile(const std::string& path);

	/*---------------------------------
		Helper Functions
	----------------------------------*/

	static Colour ReadColour(const ParseParams& params);
	static Vector2 ReadSize(const ParseParams& params);
	static int ReadInteger(const ParseParams& params);
	static char ReadCharacter(const ParseParams& params);
	static std::string ReadString(const ParseParams& params);

private:
	std::vector<Command> m_commands;
};
