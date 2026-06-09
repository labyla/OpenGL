#include <glad.h>
#include <vector>
#include <iostream>

#include "log.h"

struct VertexBufferLayoutElement {
	unsigned int Size;
	unsigned int Type;
	bool Normalized;

	static unsigned int GetTypeSize(unsigned int a_Type);
};

class VertexBufferLayout {
private:
	std::vector<VertexBufferLayoutElement> m_Elements;
	unsigned int m_Stride = 0;

public:
	const std::vector<VertexBufferLayoutElement>* GetElements() const;
	unsigned int GetStride() const;

	template <typename T>
	void PushElement(unsigned int a_Size, bool a_Normalized);
};

template <>
void VertexBufferLayout::PushElement<float>(unsigned int a_Size, bool a_Normalized);

template <>
void VertexBufferLayout::PushElement<unsigned int>(unsigned int a_Size, bool a_Normalized);

template <>
void VertexBufferLayout::PushElement<unsigned char>(unsigned int a_Size, bool a_Normalized);
