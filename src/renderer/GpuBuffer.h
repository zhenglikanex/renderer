#ifndef GPUBUFFER_H_
#define GPUBUFFER_H_

#include <string>

#include "AuroraDef.h"
#include "noncopyable.h"
#include "glSupport.h"

namespace aurora
{
	// 用来封装OpenGL的一些Buffer操作
	class GpuBuffer : public Noncopyable
	{
	public:
		class Mapper
		{
		public:
			Mapper(const GpuBufferPtr& buffer, GLintptr offset, GLsizeiptr size, GLenum access)
				: buffer_(buffer)
				, offset_(offset)
				, size_(size)
				, access_(access)
				, data_(nullptr)
				, cur_size_(0)
			{
				//buffer_->Bind();
				//CHECK_GL_ERROR(data_ = glMapBufferRange(buffer_->target(), offset_, size_, access_));
				data_ = buffer_->MapBuffer(offset_,size,access_);

				if ((access_ & GL_MAP_READ_BIT) != 0)
				{
					cur_size_ = size_;
				}
			}
			~Mapper()
			{
				//buffer_->Bind();
				//CHECK_GL_ERROR(glUnmapBuffer(buffer_->target()));
				buffer_->UnMapBuffer();
			}

			void FlushRangeBuffer(GLintptr offset, GLsizeiptr size)
			{
				//buffer_->Bind();
				//CHECK_GL_ERROR(glFlushMappedBufferRange(buffer_->target(), offset, size));
				buffer_->FlushMappedRangeBuffer(offset, size);
			}

			GLsizeiptr size() { return size_; }

			template<typename T>
			T* Pointer()
			{
				return (T*)data_;
			}

			template<typename T>
			Mapper& operator<<(const T& data)
			{
				Write(&data, sizeof(T));
				return *this;
			}

			template<>
			Mapper& operator<<(const std::string& data)
			{
				GLsizeiptr size = strlen(data.c_str()) * sizeof(char);
				Write(data.c_str(), size);
				return *this;
			}

			void Write(const void* data,GLsizeiptr size)
			{
				AURORA_ASSERT(cur_size_ + size <= size_ && "Gpu Mapper Memeory Write Out Of Range");

				memcpy((uint8_t*)data_ + cur_size_, data, size);
				cur_size_ += size;
				
			}

			template<typename T>
			Mapper& operator>>(T& data)
			{
				Read(&data, sizeof(T));
			}

			void Read(void* data, GLsizeiptr size)
			{
				AURORA_ASSERT(seek_ + size <= size_ && "Gpu Mapper Memeory Read Out Of Range");
				memcpy(data,(uint8_t*)data_ + seek_, size);
				seek_ += size;
			}
		private:
			GpuBufferPtr buffer_;
			GLintptr offset_;
			GLsizeiptr size_;
			GLenum access_;
			void* data_;
			GLsizeiptr cur_size_;
			GLsizeiptr seek_;
		};

		GpuBuffer(GLenum target,GLsizeiptr size,GLenum usage,const void* data = nullptr);
		~GpuBuffer();

		void Bind();
		void UnBind();
		
		void Resize(GLsizeiptr size);

		void ReadBuffer(GLintptr offset, GLsizeiptr size,void* data);
		void WriteBuffer(GLintptr offset,GLsizeiptr size,const void* data);

		void DiscardBuffer(GLintptr offset = 0, GLsizeiptr size = 0);

		GLuint id() const { return id_; }
		GLenum target() const { return target_; }
		GLsizeiptr size() const { return size_; }
	private:
		void* MapBuffer(GLintptr offset, GLsizeiptr size, GLenum access);
		bool UnMapBuffer();

		void FlushMappedRangeBuffer(GLintptr offset, GLsizeiptr size);

		RenderSystemPtr renderer_;

		GLuint id_;
		GLenum target_;
		GLsizeiptr size_;
		GLenum usage_;
	};
}

#endif
