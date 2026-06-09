#include <string>
#include <fstream>
#include <sstream>

struct ShaderSources {
	std::string VertexShader;
	std::string FragmentShader;
};

class Shader {
public:
	ShaderSources m_ShaderSources;
	unsigned int m_ShaderProgram;
	std::string m_ErrorInfo;

public:
	Shader(const std::string& a_FilePath);
	
	unsigned int CreateShaderProgram();
	void UseProgram();

	~Shader();

private:
	unsigned int CreateShader(unsigned int a_Type, const std::string& a_ShaderSource);
	bool CompileShader(unsigned int a_Shader);
};