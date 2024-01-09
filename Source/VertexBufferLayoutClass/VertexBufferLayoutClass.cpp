#include "VertexBufferLayoutClass.h"

unsigned int VertexBufferLayoutElement::GetTypeSize(unsigned int a_Type) {
	switch (a_Type) {
		case GL_FLOAT:
			return 4;
		case GL_UNSIGNED_INT:
			return 4;
		case GL_UNSIGNED_BYTE:
			return 1;
	}
}


const std::vector<VertexBufferLayoutElement>* VertexBufferLayout::GetElements() const {
	return &m_Elements;
}

unsigned int VertexBufferLayout::GetStride() const {
	return m_Stride;
}

template <typename T>
void VertexBufferLayout::PushElement(unsigned int a_Size, bool a_Normalized) {
	LOG("Invalid Element Type");
}

template <>
void VertexBufferLayout::PushElement<float>(unsigned int a_Size, bool a_Normalized) {
	m_Elements.push_back({ a_Size, GL_FLOAT, a_Normalized });
	m_Stride += a_Size * VertexBufferLayoutElement::GetTypeSize(GL_FLOAT);
}

template <>
void VertexBufferLayout::PushElement<unsigned int>(unsigned int a_Size, bool a_Normalized) {
	m_Elements.push_back({ a_Size, GL_UNSIGNED_INT, a_Normalized });
	m_Stride += a_Size * VertexBufferLayoutElement::GetTypeSize(GL_UNSIGNED_INT);
}

template <>
void VertexBufferLayout::PushElement<unsigned char>(unsigned int a_Size, bool a_Normalized) {
	m_Elements.push_back({ a_Size, GL_UNSIGNED_BYTE, a_Normalized });
	m_Stride += a_Size * VertexBufferLayoutElement::GetTypeSize(GL_UNSIGNED_BYTE);
}