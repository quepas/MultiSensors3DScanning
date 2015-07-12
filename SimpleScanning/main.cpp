#include <iostream>
#include <RecFusion.h>
#include <SFML/Graphics.hpp>

using RecFusion::ColorImage;
using RecFusion::DepthImage;
using RecFusion::Sensor;
using RecFusion::Mesh;
using RecFusion::Reconstruction;
using RecFusion::ReconstructionParams;

int main() {
  sf::RenderWindow window(sf::VideoMode(640, 480), "Scanners 3d");
  sf::CircleShape shape(100.0f);
  shape.setFillColor(sf::Color::Green);
  Sensor* sensor = new Sensor();

  // open sesnors
  try {
  if (sensor->deviceCount() == 0 || !sensor->open(0)) {
    std::cout << "Couldn't open device." << std::endl;
    return 1;
  }
  std::cout << "Num. of devices found: " << sensor->deviceCount() << std::endl;
  } catch(...)
  {
    std::cout << "Sorry no devices." << std::endl;
  }

  int width = sensor->width();
  int height = sensor->height();

  while(window.isOpen()) {
    sf::Event event;
    while(window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
      {
        window.close();
      }
    }
    window.clear();
    ColorImage imgColor(width, height);
    DepthImage imgDepth(width, height);
    sensor->readImage(imgDepth, imgColor);
    //std::cout << (int)imgColor.data()[width*height/2] << std::endl;
    sf::Image img;
    //img.create(640, 480, (sf::Uint8*)imgColor.data());
    /*for (int i = 0; i < width; ++i)
    {
      for (int j = 0; j < height; ++j)
      {
        img.setPixel(i, j, sf::Color((int) imgColor.data()[i*j]));
      }
    }*/
    img.loadFromMemory(imgDepth.data(), 1000);
    sf::Texture tex;
    tex.create(640, 480);
    tex.update(img);
    sf::Sprite spr(tex);
    window.draw(spr);
    window.display();
  }
  // reconstruction
  /*ReconstructionParams recParams;
  recParams.setImageSize(width, height);
  recParams.setIntrinsics(sensor->depthIntrinsics());
  Reconstruction* reconstruction = new Reconstruction(recParams);
  // buffers
  ColorImage imgColor(width, height);
  DepthImage imgDepth(width, height);
  getchar();
  std::cout << "Starting reconstruction ..." << std::endl;

  int frame = 0;
  int maxFrames = 100;
  while (frame < maxFrames)
  {
    bool ok = sensor->readImage(imgDepth, imgColor);
    if (!ok) continue;

    ok = reconstruction->addFrame(0, imgDepth, imgColor);
    if (!ok) break;
    ++frame;
    std::cout << "Processed frame " << frame << std::endl;
  }

  if (reconstruction) {
    // Get reconstructed mesh
    Mesh m;
    if (reconstruction->getMesh(&m)) m.save("mesh.ply",Mesh::PLY);
    RecFusion::MeshViewer meshViewer;
    meshViewer.showMesh(&m);
  }
  delete reconstruction;
  delete sensor;*/
}
