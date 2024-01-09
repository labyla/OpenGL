#include <glad/glad.h>

#include "../VertexBufferClass/VertexBufferClass.h"
#include "../VertexBufferLayoutClass/VertexBufferLayoutClass.h"

class VertexArray {
public:
	unsigned int m_ID;

public:
	VertexArray();
	~VertexArray();

	void Bind() const;
	void Unbind() const;

	void AddVertexBuffer(const VertexBuffer& a_VertexBuffer, const VertexBufferLayout& a_VertexBufferLayout);
};