#include <fstream>
#include <iostream>

#include "FileParser.h"

#include "../Graphics/Colour.h"

#include "../Maths/Vector2.h"

void FileParser::AddCommand(const Command& command)
{
	m_commands.push_back(command);
}

bool FileParser::LoadFile(const std::string& path)
{
	std::ifstream in;
	in.open(path);
	std::string line = "";

	if (!in.is_open)
	{
		std::cout << "Could not open the file: " << path << std::endl;
		return false;
	}

	while (!in.eof) //end of file
	{
		std::getline(in, line); //get next line in file

		size_t postion = std::string::npos; //end of line (no position)
		
		if ((postion = line.find(":")) != std::string::npos) //find next ':'
		{
			size_t curserpos = line.find_first_of(" ", postion); //look for space at, or right after, current line position

			if (curserpos == std::string::npos)
				curserpos = line.length(); //position is at end of line
			else
				curserpos -= 1;

			std::string commandStr = line.substr(postion + 1, curserpos); //doesn't return ':'
			curserpos += 1;

			for (size_t i = 0; i < m_commands.size(); ++i)
			{
				if (commandStr == m_commands[i].commandString) //if there is a command
				{
					ParseParams params;

					switch (m_commands[i].commandType)
					{
					case E_ONE_LINE:
						params.cursorpos = curserpos;
						params.lineNum = 0;
						params.line = line;
						m_commands[i].parse(params);
						break;

					case E_MULTI_LINE:
						std::string numLines = line.substr(curserpos + 1);
						int totalLines = std::stoi(numLines);
						int lineNum = 0;

						while (lineNum < totalLines)
						{
							std::getline(in, line);

							if (line.empty())
							{
								continue;
							}
							else
							{
								params.cursorpos = curserpos;
								params.lineNum = lineNum;
								params.line = line;
								m_commands[i].parse(params);
								++lineNum;
							}
						}
					}
				}
			}
		}
	}

	return true;
}

Colour FileParser::ReadColour(const ParseParams& params)
{
	size_t next = params.line.find_first_of(" ", params.cursorpos + 1);

	int red = std::stoi(params.line.substr(params.cursorpos, next - params.cursorpos));

	size_t last = next;
	next = params.line.find_first_of(" ", last + 1);

	int green = std::stoi(params.line.substr(last + 1, next - last));

	next = params.line.find_first_of(" ", last + 1);

	int blue = std::stoi(params.line.substr(last + 1, next - last));
	int alpha = std::stoi(params.line.substr(next + 1));

	return Colour(red, green, blue, alpha);
}

Vector2 FileParser::ReadSize(const ParseParams& params)
{
	size_t next = params.line.find_first_of(" ", params.cursorpos + 1);

	int width = std::stoi(params.line.substr(params.cursorpos, next - params.cursorpos));

	size_t last = next;
	next = params.line.find_first_of(" ", last + 1);

	int height = std::stoi(params.line.substr(last + 1, next - last));

	return Vector2(width, height);
}

int FileParser::ReadInteger(const ParseParams& params)
{
	std::string integer = params.line.substr(params.cursorpos + 1);
	return std::stoi(integer);
}

char FileParser::ReadCharacter(const ParseParams& params)
{
	return params.line.substr(params.cursorpos + 1)[0];
}

std::string FileParser::ReadString(const ParseParams& params)
{
	return params.line.substr(params.cursorpos + 1);
}
