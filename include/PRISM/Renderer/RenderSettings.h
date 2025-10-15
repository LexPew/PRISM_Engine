#include <glm/vec4.hpp>
//TODO: Eventually move this to be a thing we can just apply to the renderer like post fx? potentially
namespace RenderSettings
{
    inline glm::vec4 clearColor{.42f, .47f, .53f, 1.0f};
    inline bool testDepth{true};
    
}