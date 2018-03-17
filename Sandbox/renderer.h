#pragma once

struct Entity;

class Camera;
class ShaderProgram;

class Renderer final
{
public:
	Renderer(const ShaderProgram& program, const Camera& camera);
	void Draw(const Entity& entity);

private:
	const ShaderProgram& m_program;
	const Camera& m_camera;
};
