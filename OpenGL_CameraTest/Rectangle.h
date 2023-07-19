#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <learnopengl/shader_m.h>
#include <learnopengl/camera.h>
namespace AjiaoGL
{
	class Rectangle
	{
	private:
		Shader   m_shader;
		Shader   m_shader4FaceToCamera;
		unsigned m_id_vertex_arrays_object;
		unsigned m_id_vertex_data_buffer;
		unsigned m_id_vertex_index_buffer;
		unsigned m_id_texure01;
		unsigned m_id_texure02;
		bool     m_bFaceToCamera;

	private:
		void _init(); 
	public:
		Rectangle();
		~Rectangle();

	public:
		void prepare();

		void render(glm::vec3 position,glm::vec3 rotate,glm::vec3 scale,Camera c,float screen_width,float screen_height);  

		inline void setIsFaceToCamera(bool b) { m_bFaceToCamera = b; }
	 
 
	}; 
}

