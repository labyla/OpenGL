#include <glad/glad.h>

class VertexBuffer {
public: 
	unsigned int m_ID;

public: 
	VertexBuffer(unsigned int a_Size, const void* a_Data);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;
};