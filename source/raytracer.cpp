#include <thread>
#include <renderer.hpp>
#include <fensterchen.hpp>
#include <scene.hpp>

int main(int argc, char* argv[])
{
  unsigned const width = 600;
  unsigned const height = 600;
  std::string const OPfilename = "./checkerboard.ppm";
  std::string const IPfilename = "./SCENE.sdf";

  Scene bigPicture;
  bigPicture.loadscene(IPfilename);

  Renderer app(bigPicture, width, height, OPfilename);

  std::thread thr([&app]() { app.render(); });

  Window win(glm::ivec2(width,height));

  while (!win.shouldClose()) {
    if (win.isKeyPressed(GLFW_KEY_ESCAPE)) {
      win.stop();
    }

    glDrawPixels( width, height, GL_RGB, GL_FLOAT
                , app.colorbuffer().data());

    win.update();
  }

  thr.join();

  return 0;
}
