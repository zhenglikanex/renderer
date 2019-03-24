#ifndef GPUBUFFER_H_
#define GPUBUFFER_H_

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
			{
				buffer_->Bind();
				CHECK_GL_ERROR(data_ = glMapBufferRange(buffer_->target(), offset_, size_, access_));
			}
			~Mapper()
			{
				buffer_->Bind();
				glUnmapBuffer(buffer_->target());
			}

			void FlushRangeBuffer(GLintptr offset, GLsizeiptr size)
			{
				buffer_->Bind();
				CHECK_GL_ERROR(glFlushMappedBufferRange(buffer_->target(), offset, size));
			}

			void* get() { return data_; }

		private:
			GpuBufferPtr buffer_;
			GLintptr offset_;
			GLsizeiptr size_;
			GLenum access_;
			void* data_;
		};

		GpuBuffer(GLenum target,GLsizeiptr size,GLenum usage,const void* data = nullptr);
		~GpuBuffer();

		void Bind();
		void UnBind();
		
		void Resize(GLsizeiptr size);

		void ReadBuffer(GLintptr offset, GLsizeiptr size,void* data);
		void WriteBuffer(GLintptr offset,GLsizeiptr size,const void* data);

		void DiscardBuffer(GLintptr offset = 0, GLsizeiptr size = 0);

		void* MapBuffer(GLintptr offset,GLsizeiptr size,GLenum access);
		bool UnMapBuffer();

		void FlushMappedRangeBuffer(GLintptr offset, GLsizeiptr size);

		GLuint id() const { return id_; }
		GLenum target() const { return target_; }
		GLsizeiptr size() const { return size_; }
	private:
		RenderSystemPtr renderer_;

		GLuint id_;
		GLenum target_;
		GLsizeiptr size_;
		GLenum usage_;
	};
}

#endif
