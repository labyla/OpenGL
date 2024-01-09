#include "VertexArrayClass.h"

VertexArray::VertexArray() {
	glGenVertexArrays(1, &m_ID);
}

VertexArray::~VertexArray() {
	glDeleteVertexArrays(1, &m_ID);
}

void VertexArray::Bind() const {
	glBindVertexArray(m_ID);
}

void VertexArray::Unbind() const {
	glBindVertexArray(0);
}

void VertexArray::AddVertexBuffer(const VertexBuffer& a_VertexBuffer, const VertexBufferLayout& a_VertexBufferLayout) {
	a_VertexBuffer.Bind();
	const std::vector<VertexBufferLayoutElement>* Elements = a_VertexBufferLayout.GetElements();
	int Offset = 0;

	for (unsigned int Index = 0; Index < Elements->size(); Index++) {
		glEnableVertexAttribArray(Index);
		glVertexAttribPointer(
			Index,
			Elements->at(Index).Size,
			Elements->at(Index).Type,
			Elements->at(Index).Normalized,
			a_VertexBufferLayout.GetStride(),
			(const void*)Offset
		);
		Offset += Elements->at(Index).Size * VertexBufferLayoutElement::GetTypeSize(Elements->at(Index).Type);
	}
}