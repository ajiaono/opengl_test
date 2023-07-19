#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <learnopengl/filesystem.h>
#include <learnopengl/shader_m.h>
#include <learnopengl/camera.h>

using namespace std;
using namespace glm;

int main()
{

    glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
   
    glm::vec4 position = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);


    model = glm::translate(model, glm::vec3(2.0f,0.0f,0.0f)); 
     
    model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));

    model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
    
    glm::vec4 offset = model * position;
    
    std::cout << offset.x <<","<< offset.y << "," << offset.z << "," <<  offset.w ;
  
    std::cout << std::endl;
  
    glm::vec4  position2 = offset;

    std::cout << position2.x << "," << position2.y << "," << position2.z << "," << position2.w;
    std::cout << std::endl;

    glm::mat4 model2 = glm::mat4(1.0f);

     
    model2 = glm::scale(model2, glm::vec3(0.5f, 0.5f, 0.5f)); 
    model2 = glm::rotate(model2, glm::radians(-90.0f), glm::vec3(0.0f, 0.0f, 1.0f));  
    model2 = glm::translate(model2, glm::vec3(-2.0f, 0.0f, 0.0f));
 
    glm::vec4  offset2 = model2 * position2; 
    std::cout << offset2.x << "," << offset2.y << "," << offset2.z << "," << offset2.w;
       
    std::cout << std::endl;
     
    glm::mat4 inverse_model = glm::inverse(model);
 
    glm::vec4  offset3 = inverse_model * position2;
   
    std::cout << offset3.x << "," << offset3.y << "," << offset3.z << "," << offset3.w;
    std::cout << std::endl;
     




    glm::vec4 camera_position_in_world = glm::vec4(6.0f,5.0f,5.0f,1.0f); 
    glm::vec4 camera_position_in_object = inverse_model * camera_position_in_world; 
    vec3 zp = vec3(camera_position_in_object.x, camera_position_in_object.y, camera_position_in_object.z); 
    vec3 xp = cross(zp, vec3(0.0f, 1.0f, 0.0f)); 
    vec3 yp = cross(zp, xp); 
    
    vec3 nx = normalize(xp);
    vec3 ny = normalize(yp);
    vec3 nz = normalize(zp);

    vec3 rect_lt = vec3(-1.0f,1.0f,0.0f);
    rect_lt = rect_lt.x * nx + rect_lt.y * ny + rect_lt.z * nz;

    std::cout << rect_lt.x << "," << rect_lt.y << "," << rect_lt.z;



    

    



	return 0;
}