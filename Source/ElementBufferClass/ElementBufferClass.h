#include <glad/glad.h>

class ElementBuffer {
public:
	unsigned int m_ID;

public:
	ElementBuffer(unsigned int a_Size, const void* a_Data);
	~ElementBuffer();

	void Bind() const;
	void Unbind() const;
};