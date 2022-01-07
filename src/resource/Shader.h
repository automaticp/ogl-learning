#pragma once
#include <string>
#include <fstream>
#include <iterator>
#include <stdexcept>
#include <concepts>
#include <memory>
#include <iostream>
#include <utility>
#include <glad/glad.h>
#include "TypeAliases.h"
#include "IResource.h"


class ShaderAllocator : public IResource {
protected:
	explicit ShaderAllocator(GLenum type) noexcept {
		id_ = glCreateShader(type);
#ifndef NDEBUG
		std::cerr << "\nShaderAllocator("
		          << ((type == GL_FRAGMENT_SHADER) ? "GL_FRAGMENT_SHADER" : "")
		          << ((type == GL_VERTEX_SHADER) ? "GL_VERTEX_SHADER" : "") << ")";
#endif
	}
public:
	virtual ~ShaderAllocator() override {
#ifndef NDEBUG
		std::cerr << "\n~ShaderAllocator()";
#endif
		glDeleteShader(id_);
	}
};


class Shader : public IResource {
private:
	std::string filename_;
	GLenum type_;

	void acquireResource() noexcept { id_ = glCreateShader(type_); }
	void releaseResource() noexcept { glDeleteShader(id_); }

public:
	Shader(GLenum type, std::string filename);

	virtual ~Shader() override { releaseResource(); }

	GLenum getType() const noexcept { return type_; }
	const std::string& getFilename() const noexcept { return filename_; }
	std::string getSource() const { return getShaderFileSource(filename_); }

	static std::string getShaderFileSource(const std::string& filename);

	std::string getCompileInfo() const;

	void compile() const;
};




class FragmentShader : public Shader {
public:
	explicit FragmentShader(std::string filename) :
			Shader(GL_FRAGMENT_SHADER, std::move(filename)) {}
};


class VertexShader : public Shader {
public:
	explicit VertexShader(std::string filename) :
			Shader(GL_VERTEX_SHADER, std::move(filename)) {}
};




inline Shader::Shader(GLenum type, std::string filename) :
		type_{ type }, filename_{ std::move(filename) } {

	// check shader type to be a valid enum
	if ( (type_ != GL_VERTEX_SHADER) && (type_ != GL_FRAGMENT_SHADER) ) {
		throw std::invalid_argument("invalid_argument: invalid shader type");
	}

	// create shader id and compile from file
	acquireResource();
	try { compile(); }
	catch (const std::runtime_error& e) {
		std::cerr << e.what();
		releaseResource();
		throw;
	}
	catch (...) {
		releaseResource();
		throw;
	}

}

inline void Shader::compile() const {
	const std::string shaderSourceString{ getSource() };
	const GLchar* shaderSource{ shaderSourceString.c_str() };
	glShaderSource(id_, 1, &shaderSource, nullptr);
	glCompileShader(id_);

	// check for succesful compilation
	GLint success;
	glGetShaderiv(id_, GL_COMPILE_STATUS, &success);
	if ( !success ) {
		std::string compileInfo{ getCompileInfo() };
		throw std::runtime_error(std::string("runtime_error: shader compilation failed") + compileInfo);
	}
}

inline std::string Shader::getShaderFileSource(const std::string& filename) {

	static const std::string shaderDir{ "resources/shaders/" };

	std::ifstream file{ shaderDir + filename };
	std::string outString{ std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>() };
	return outString;
}

inline std::string Shader::getCompileInfo() const {
	std::string output{};
	GLint shaderType, success, sourceLength;
	glGetShaderiv(id_, GL_SHADER_TYPE, &shaderType);
	glGetShaderiv(id_, GL_COMPILE_STATUS, &success);
	glGetShaderiv(id_, GL_SHADER_SOURCE_LENGTH, &sourceLength);

	std::string shaderTypeName{};
	if ( shaderType == GL_VERTEX_SHADER ) { shaderTypeName = "Vertex"; }
	else if ( shaderType == GL_FRAGMENT_SHADER ) { shaderTypeName = "Fragment"; }
	else { shaderTypeName = "???"; }

	output += "\nShader Id: " + std::to_string(id_);
	output += "\nShader Type: " + shaderTypeName;
	output += "\nCompilation Status: " + ((success == GL_TRUE) ? std::string("Success") : std::string("Failure"));
	output += "\nSource File: " + filename_;
	output += "\nSource Length: " + std::to_string(sourceLength);
	if ( success != GL_TRUE ) {
		GLint infoLength;
		glGetShaderiv(id_, GL_INFO_LOG_LENGTH, &infoLength);
		auto infoLog{ std::make_unique<GLchar[]>(infoLength) };
		glGetShaderInfoLog(id_, infoLength, nullptr, infoLog.get());
		output += "\nInfo Length: " + std::to_string(infoLength);
		output += "\nInfo Message:< " + std::string(infoLog.get());
		output += " >";
	}
	output += '\n';
	return output;
}

