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
		GpuBuffer(GLenum target,GLsizeiptr size,GLenum usage,const void* data = nullptr);
		~GpuBuffer();

		void Bind();
		void UnBind();
		
		void ReadBuffer(GLintptr offset, GLsizeiptr size,void* data);
		void WirteBuffer(GLintptr offset,GLsizeiptr size,const void* data);

		void DiscardBuffer(GLintptr offset = 0, GLsizeiptr size = 0);

		void* MapBuffer(GLintptr offset,GLsizeiptr size,GLenum access);
		bool UnMapBuffer();

		void FlushMappedRangeBuffer(GLintptr offset, GLsizeiptr size);

		GLuint id() const { return id_; }
		GLsizeiptr size() const { return target_; }
	private:
		RenderSystemPtr renderer_;

		GLuint id_;
		GLenum target_;
		GLsizeiptr size_;
		GLenum usage_;
	};
}

#endif
