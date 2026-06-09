#include <glad.h>

#include "vertex_buffer_class.h"
#include "vertex_buffer_layout_class.h"

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