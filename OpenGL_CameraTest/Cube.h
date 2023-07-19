#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <learnopengl/shader_m.h>
#include <learnopengl/camera.h>

namespace AjiaoGL
{
	class Cube
	{
	private:
		Shader   m_shader;
		unsigned m_id_vertex_arrays_object;
		unsigned m_id_vertex_data_buffer;
		unsigned m_id_vertex_index_buffer;
		unsigned m_id_texure01;
		unsigned m_id_texure02;

	private:
		void _init(); 
	public:
		Cube(); 
		~Cube();
	public:
		void prepare();

		void render(glm::vec3 position, glm::vec3 rotate, glm::vec3 scale, Camera c,float screen_width,float screen_height);

		void renderFaceToCamera(glm::vec3 position, glm::vec3 scale, Camera c);

 


	};

}


