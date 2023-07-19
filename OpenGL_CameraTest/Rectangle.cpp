#include "Rectangle.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>
#include <learnopengl/filesystem.h>
#include <learnopengl/camera.h>
namespace AjiaoGL
{



    static glm::vec3 cubePositions[] = {
         glm::vec3(0.0f,  0.0f,  0.0f),
         glm::vec3(2.0f,  5.0f, -15.0f),
         glm::vec3(-1.5f, -2.2f, -2.5f),
         glm::vec3(-3.8f, -2.0f, -12.3f),
         glm::vec3(2.4f, -0.4f, -3.5f),
         glm::vec3(-1.7f,  3.0f, -7.5f),
         glm::vec3(1.3f, -2.0f, -2.5f),
         glm::vec3(1.5f,  2.0f, -2.5f),
         glm::vec3(1.5f,  0.2f, -1.5f),
         glm::vec3(-1.3f,  1.0f, -1.5f)
    };

    glm::mat3 faceMatrix(glm::vec4 camera_in_world, glm::mat4 model)
    {
        glm::mat4 inverse_model = glm::inverse(model);

        glm::vec4 camera_position_in_world = camera_in_world;
        glm::vec4 camera_position_in_object = inverse_model * camera_position_in_world;
        glm::vec3 zp = glm::vec3(camera_position_in_object.x, camera_position_in_object.y, camera_position_in_object.z);
       
        glm::vec3 xp = glm::cross(zp, glm::vec3(0.0f, 1.0f, 0.0f));
        glm::vec3 yp = glm::cross(zp, xp);

        glm::vec3 nx = glm::normalize(xp);
        glm::vec3 ny = glm::normalize(yp);
        glm::vec3 nz = glm::normalize(zp);

        glm::mat3x3 x;
        x[0] = nx;
        x[1] = ny;
        x[2] = nz;
         
        return x;
    }
    glm::mat3 faceMatrix2(glm::vec4 front)
    { 
        glm::vec3 zp = glm::vec3(front.x, front.y, front.z); 
        glm::vec3 xp = glm::cross(zp, glm::vec3(0.0f, 1.0f, 0.0f));
        glm::vec3 yp = glm::cross(zp, xp);

        glm::vec3 nx = glm::normalize(xp);
        glm::vec3 ny = glm::normalize(yp);
        glm::vec3 nz = glm::normalize(zp);

        glm::mat3x3 x;
        x[0] = nx;
        x[1] = ny;
        x[2] = nz;

        return x;
    }


	Rectangle::Rectangle():m_shader("7.4.camera.vs", "7.4.camera.fs"), m_shader4FaceToCamera("rectangle.vs", "rectangle.fs")
	{
		_init();
	}

    Rectangle::~Rectangle()
    {
    }

    
 
	void Rectangle::_init()
	{
        m_bFaceToCamera = true;
        // build and compile our shader zprogram
      // ------------------------------------
        Shader ourShader("rectangle.vs", "rectangle.fs");

        // set up vertex data (and buffer(s)) and configure vertex attributes
        // ------------------------------------------------------------------
        float vertices[] = {
            -0.5f, -0.5f, 0.0f,  0.0f, 0.0f,
             0.5f, -0.5f, 0.0f,  1.0f, 0.0f,
             0.5f,  0.5f, 0.0f,  1.0f, 1.0f,
             0.5f,  0.5f, 0.0f,  1.0f, 1.0f,
            -0.5f,  0.5f, 0.0f,  0.0f, 1.0f,
            -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 
        };
        // world space positions of our cubes

        unsigned int VBO, VAO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        // texture coord attribute
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);


        // load and create a texture 
        // -------------------------
        unsigned int texture1, texture2;
        // texture 1
        // ---------
        glGenTextures(1, &texture1);
        glBindTexture(GL_TEXTURE_2D, texture1);
        // set the texture wrapping parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // load image, create texture and generate mipmaps
        int width, height, nrChannels;
        stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
        unsigned char* data = stbi_load(FileSystem::getPath("resources/textures/container.jpg").c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
        }
        stbi_image_free(data);
        // texture 2
        // ---------
        glGenTextures(1, &texture2);
        glBindTexture(GL_TEXTURE_2D, texture2);
        // set the texture wrapping parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // load image, create texture and generate mipmaps
        data = stbi_load(FileSystem::getPath("resources/textures/awesomeface.png").c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            // note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
        }
        stbi_image_free(data);

        m_id_vertex_arrays_object = VAO;
        m_id_vertex_data_buffer = VBO;
        m_id_texure01 = texture1;
        m_id_texure02 = texture2;
        glBindVertexArray(0);


	}

  
    void Rectangle::prepare()
    {
        m_shader.use();
        m_shader.setInt("texture1", 0);
        m_shader.setInt("texture2", 1);

        m_shader4FaceToCamera.use();
        m_shader4FaceToCamera.setInt("texture1", 0);
        m_shader4FaceToCamera.setInt("texture2", 1);

    }
  
    void Rectangle::render(glm::vec3 position, glm::vec3 rotate, glm::vec3 scale, Camera camera, float screen_width, float screen_height)
    {
  

         // bind textures on corresponding texture units


     
      
          
        // pass projection matrix to shader (note that in this case it could change every frame)
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)screen_width / (float)screen_height, 0.1f, 100.0f);
        // camera/view transformation
        glm::mat4 view = camera.GetViewMatrix();
        


        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_id_texure01);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, m_id_texure02);
         
        // activate shader
        m_shader.use(); 
        m_shader.setMat4("projection", projection);
        m_shader.setMat4("view", view);


        // render boxes
        glBindVertexArray(m_id_vertex_arrays_object);

        for (unsigned int i = 0; i < 10; i++)
        {
            // calculate the model matrix for each object and pass it to shader before drawing
            glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
            model = glm::translate(model, cubePositions[i] + glm::vec3(2.0f, 0.0f, 0.0f));
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            m_shader.setMat4("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }






        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_id_texure01);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, m_id_texure02);

        // activate shader
        m_shader4FaceToCamera.use();

        // pass projection matrix to shader (note that in this case it could change every frame)
        m_shader4FaceToCamera.setMat4("projection", projection);

        // camera/view transformation
        m_shader4FaceToCamera.setMat4("view", view);

        if (m_bFaceToCamera)
        {
            for (unsigned int i = 0; i < 10; i++)
            {
                // calculate the model matrix for each object and pass it to shader before drawing
                glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
                model = glm::translate(model, cubePositions[i]);

               // glm::mat3 fm = faceMatrix(glm::vec4(camera.Position, 1.0f), model);
                glm::mat3 fm = faceMatrix2(glm::vec4(camera.Front,1.0f));
                m_shader4FaceToCamera.setMat4("model", model);
                m_shader4FaceToCamera.setMat3("faceMatrix", fm);
                
                glDrawArrays(GL_TRIANGLES, 0, 36);
            }
        }
        else
        {
            for (unsigned int i = 0; i < 10; i++)
            {
                // calculate the model matrix for each object and pass it to shader before drawing
                glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
                model = glm::translate(model, cubePositions[i]);
                glm::mat3 fm = glm::mat3(1.0f);
                m_shader4FaceToCamera.setMat3("faceMatrix", fm);
                m_shader4FaceToCamera.setMat4("model", model);
                glDrawArrays(GL_TRIANGLES, 0, 36);
            }

        }

 

	}

}
