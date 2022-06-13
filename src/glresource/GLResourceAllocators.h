#pragma once
#include <glbinding/gl/gl.h>
#include <iostream>
#include "IGLResource.h"

using namespace gl;

class GLShaderAllocator : public IGLResource {
public:
	explicit GLShaderAllocator(GLenum type) noexcept {
		id_ = glCreateShader(type);
#ifndef NDEBUG
		std::cerr << "\n[id: " << id_ << "] "
		          << "GLShaderAllocator("
		          << ((type == GL_FRAGMENT_SHADER) ? "GL_FRAGMENT_SHADER" : "")
		          << ((type == GL_VERTEX_SHADER) ? "GL_VERTEX_SHADER" : "") << ")";
#endif
	}

private:
	virtual void release() noexcept override final {
#ifndef NDEBUG
		std::cerr << "\n[id: " << id_ << "] " << "GLShaderAllocator::release()";
#endif
		glDeleteShader(id_);
	}

public:
	virtual ~GLShaderAllocator() override { GLShaderAllocator::release(); }

	GLShaderAllocator(GLShaderAllocator&&) = default;
	GLShaderAllocator& operator=(GLShaderAllocator&&) = default;
};


class GLShaderProgramAllocator : public IGLResource {
public:
	GLShaderProgramAllocator() noexcept {
		id_ = glCreateProgram();
#ifndef NDEBUG
		std::cerr << "\n[id: " << id_ << "] "
		          << "GLShaderProgramAllocator()";
#endif
	}

private:
	virtual void release() noexcept override final {
#ifndef NDEBUG
		std::cerr << "\n[id: " << id_ << "] " << "GLShaderProgramAllocator::release()";
#endif
		glDeleteProgram(id_);
	}

public:
	virtual ~GLShaderProgramAllocator() override { GLShaderProgramAllocator::release(); }

	GLShaderProgramAllocator(GLShaderProgramAllocator&&) = default;
	GLShaderProgramAllocator& operator=(GLShaderProgramAllocator&&) = default;
};


class GLTextureAllocator : public IGLResource {
public:
	GLTextureAllocator() noexcept {
		glGenTextures(1, &id_);
#ifndef NDEBUG
		std::cerr << "\n[id: " << id_ << "] "
		          << "GLTextureAllocator()";
#endif
	}

private:
	virtual void release() noexcept override final {
#ifndef NDEBUG
		std::cerr << "\n[id: " << id_ << "] " << "GLTextureAllocator::release()";
#endif
		glDeleteTextures(1, &id_);
	}

public:
	virtual ~GLTextureAllocator() override { GLTextureAllocator::release(); }

	GLTextureAllocator(GLTextureAllocator&&) = default;
	GLTextureAllocator& operator=(GLTextureAllocator&&) = default;
};


class VAOAllocator : public IGLResource {
public:
	VAOAllocator() noexcept {
		glGenVertexArrays(1, &id_);
#ifndef NDEBUG
		std::cerr << "\n[id: " << id_ << "] "
		          << "VAOAllocator()";
#endif
	}

private:
	virtual void release() noexcept override final {
#ifndef NDEBUG
		std::cerr << "\n[id: " << id_ << "] " << "VAOAllocator::release()";
#endif
		glDeleteVertexArrays(1, &id_);
	}

public:
	virtual ~VAOAllocator() override { VAOAllocator::release(); }

	VAOAllocator(VAOAllocator&&) = default;
	VAOAllocator& operator=(VAOAllocator&&) = default;
};


class VBOAllocator : public IGLResource {
public:
	VBOAllocator() noexcept {
		glGenBuffers(1, &id_);
#ifndef NDEBUG
		std::cerr << "\n[id: " << id_ << "] "
		          << "VBOAllocator()";
#endif
	}

private:
	virtual void release() noexcept override final {
#ifndef NDEBUG
		std::cerr << "\n[id: " << id_ << "] " << "VBOAllocator::release()";
#endif
		glDeleteBuffers(1, &id_);
	}

public:
	virtual ~VBOAllocator() override { VBOAllocator::release(); }

	VBOAllocator(VBOAllocator&&) = default;
	VBOAllocator& operator=(VBOAllocator&&) = default;
};
