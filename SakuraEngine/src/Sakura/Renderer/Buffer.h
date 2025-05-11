#pragma once

namespace Sakura
{
	enum class ShaderDataType : uint8_t	//枚举类型 
	{
		None = 0,
		Float, Float2, Float3, Float4,
		Mat3 ,Mat4,
		Int, Int2, Int3, Int4,
		Bool
	};

	static uint32_t ShaderDataTypeSize(ShaderDataType type)// 计算不同类型的大小
	{
		switch (type)
		{
			case ShaderDataType::None:		return 0;
			case ShaderDataType::Float:		return 4;
			case ShaderDataType::Float2:	return 4 * 2;
			case ShaderDataType::Float3:	return 4 * 3;
			case ShaderDataType::Float4:	return 4 * 4;
			case ShaderDataType::Mat3:		return 4 * 3 * 3;
			case ShaderDataType::Mat4:		return 4 * 4 * 4;
			case ShaderDataType::Int:		return 4;
			case ShaderDataType::Int2:		return 4 * 2;
			case ShaderDataType::Int3:		return 4 * 3;
			case ShaderDataType::Int4:		return 4 * 4;
			case ShaderDataType::Bool:		return 1;
			default:
				SAKURA_CORE_ASSERT(false, "Unknow Shader Data Type!");
				return 0;
		}
	}

	struct BufferElement // 顶点缓冲元素
	{
		std::string Name;
		ShaderDataType Type;
		uint32_t Offset;
		uint32_t Size;
		bool Normalized;

		BufferElement():
			Type(ShaderDataType::None),
			Name(""),
			Size(ShaderDataTypeSize(ShaderDataType::None)),
			Offset(0),
			Normalized(false){}		//默认构造函数(用于 vector 容器拷贝 initialize_list 容器)

		BufferElement(			//有参构造函数(用于创建单个缓冲元素)
			ShaderDataType type, 
			const std::string& name,
			bool normalized = false) 
			:
			Type(type), Name(name),
			Size(ShaderDataTypeSize(type)), 
			Offset(0), 
			Normalized(normalized){}

		uint32_t GetComponentCount() const // 获取类型对应的组成数
		{
			switch (Type)
			{
				case ShaderDataType::None:		return 0;
				case ShaderDataType::Float:		return 1;
				case ShaderDataType::Float2:	return 2;
				case ShaderDataType::Float3:	return 3;
				case ShaderDataType::Float4:	return 4;
				case ShaderDataType::Mat3:		return 3 * 3;
				case ShaderDataType::Mat4:		return 4 * 4;
				case ShaderDataType::Int:		return 1;
				case ShaderDataType::Int2:		return 2;
				case ShaderDataType::Int3:		return 3;
				case ShaderDataType::Int4:		return 4;
				default:
					SAKURA_CORE_ASSERT(false, "Unknow Shader Data Type!");
					return 0;
			}
		}
	};

	class BufferLayout // 顶点缓冲布局
	{
	public:
		BufferLayout() :m_Stride(0){}

		BufferLayout(const std::initializer_list<BufferElement>& bufferLayerout)
			: m_BufferElements(bufferLayerout) // 使用 initializer_list 接受初始化列表 {}
		{
			/*
			* std::initializer_list 是轻量级的只读视图，适合临时数据传递和初始化。
			* std::vector 是功能完整的动态容器，适合需要长期存储或修改数据的场景。
			*/
			CalculateOffsetAndStride();
		}

		inline const uint32_t GetStride() const { return m_Stride; }// 获取步幅
		inline const std::vector<BufferElement> GetElements() const { return m_BufferElements; }// 获取缓冲布局

		inline std::vector<BufferElement>::iterator begin() { return m_BufferElements.begin(); }
		inline std::vector<BufferElement>::iterator end()	{ return m_BufferElements.end(); }	
		inline std::vector<BufferElement>::const_iterator begin() const { return m_BufferElements.begin(); }
		inline std::vector<BufferElement>::const_iterator end()   const { return m_BufferElements.end(); }
	private:
		void CalculateOffsetAndStride() // 计算不同缓冲区的偏移和步幅
		{
			uint32_t offset = 0;
			m_Stride = 0;
			
			for (auto& layout : m_BufferElements) 
			{
				layout.Offset = offset;
				offset += layout.Size;
				m_Stride += layout.Size;
			}
		}
	private:
		std::vector<BufferElement> m_BufferElements;	// 顶点缓冲区
		uint32_t m_Stride;								// 步幅
	};

	class VertexBuffer // VBO
	{
	public:
		VertexBuffer() {}
		virtual ~VertexBuffer() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		//缓冲布局
		virtual void SetLayout(const BufferLayout& bufferLayout) = 0;
		virtual const BufferLayout& GetLayout() const = 0;
	public:
		static VertexBuffer* Create(float* data, uint32_t size);
	};

	class IndexBuffer // EBO (IBO)
	{
	public:
		IndexBuffer() {}
		virtual ~IndexBuffer() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		//索引总数
		virtual uint32_t GetCount() const = 0;
	public:
		static IndexBuffer* Create(uint32_t* indices, uint32_t count);
	};
}