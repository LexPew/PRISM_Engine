#include <PRISM/Engine/Light.h>
#include <PRISM/Renderer/Renderer.h>

void Light::Start()
{
    lightId = Renderer::Get().RequestLightId();
    //For now just set enabled
    //TODO: Add functionality later
    Renderer::Get().SetLightEnabled(lightId, true);
}
void Light::Update(float deltaTime) 
{
    //Get Renderer, send light data
    //Eventually add if statement so it doesnt update unless movement detected or values edited
    Renderer::Get().SendLightDetails(lightId, transform.position, intensity);
}
