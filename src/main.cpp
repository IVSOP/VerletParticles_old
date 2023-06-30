#include <iostream>
#include "Renderer.h"
#include "GLErrors.h"

// void saveFrame() {
// 	char filename[] = "frame.tga";
// 	int* buffer = new int[ 1000 * 1000 * 3 ];
// 					 // width, height
// 	glReadPixels( 0, 0, 1000, 1000, GL_BGR, GL_UNSIGNED_BYTE, buffer );

// 	FILE   *out = fopen(filename, "w");
// 	short  TGAhead[] = {0, 2, 0, 0, 0, 0, 1000, 1000, 24};
// 	fwrite(&TGAhead, sizeof(TGAhead), 1, out);
// 	fwrite(buffer, 3 * 1000 * 1000, 1, out);
// 	fclose(out);
// }

int main() {
	// int width, height;
	// glfwGetWindowSize(window, &width, &height);
#define CHECK_ALL_CELL_COLLISIONS // if you desable this, it is much faster but at a risk on jankyness
	GridSandbox sandbox(5000, 1000, 1000); // why tf can I change this and not window pixels and it just works???????? i dont even know anymore, it works too well its just inconsistent

	Renderer renderer(1000, 1000, &sandbox);
	// renderer.addSandbox(&sandbox);

	// center point and particle radius, if they decide to use it
	// spawnerInfo info1(pVec2(500, 500), GRID_PARTICLE_SIZE, nullptr);
	// spawnerInfo info2(pVec2(500, 500), GRID_PARTICLE_SIZE, nullptr);
	spawnerInfo info3(pVec2(GRID_PARTICLE_SIZE, 1000 - GRID_PARTICLE_SIZE), GRID_PARTICLE_SIZE, nullptr, pVec2(325000.0, 0));
	spawnerInfo info4(pVec2(GRID_PARTICLE_SIZE, 1000 - (GRID_PARTICLE_SIZE * 3)), GRID_PARTICLE_SIZE, nullptr, pVec2(320000.0, 0));
	spawnerInfo info5(pVec2(GRID_PARTICLE_SIZE, 1000 - (GRID_PARTICLE_SIZE * 5)), GRID_PARTICLE_SIZE, nullptr, pVec2(315000.0, 0));
	spawnerInfo info6(pVec2(1000 - GRID_PARTICLE_SIZE, 1000 - GRID_PARTICLE_SIZE), GRID_PARTICLE_SIZE, nullptr, pVec2(- 325000.0, 0));

	// Spawner spawner1(0, 2200, centerSpawnerFixedSize, &info2);
	// sandbox.addSpawner(spawner1);

	// Spawner spawner2(0, 2200, inCircle, &info2);
	// sandbox.addSpawner(spawner2);
	
	// Spawner spawner3(0, 2200, inCircleReverse, &info2);
	// sandbox.addSpawner(spawner3);


	Spawner spawner4(0, 2100, fixedSpawner, &info3);
	sandbox.addSpawner(spawner4);
	Spawner spawner5(50, 1750, fixedSpawner, &info4);
	sandbox.addSpawner(spawner5);
	Spawner spawner6(100, 1750, fixedSpawner, &info5);
	sandbox.addSpawner(spawner6);
	Spawner spawner7(1750, 2100, fixedSpawner, &info6);
	sandbox.addSpawner(spawner7);


	// run simulation once
	int i;
	std::cout << "Running simulation for 2100 ticks" << std::endl;
	for (i = 0; i < 2100; i++) {
		renderer.tick();
		renderer.renderSandboxWithoutTick();
		if (i % 100 == 0) {
			printf("tick #%d\n", i);
		}
	}

	// get colors according to particle position
	std::cout << "Calculating colors from this position" << std::endl;
	GLfloat * color_feed = sandbox.getParticleColorsFromImage("res/radiation_symbol.png");

	std::cout << "Finished, clearing and starting visual simulation" << std::endl;

	sandbox.clear();

	// info2.color_feed = color_feed;
	info3.color_feed = color_feed;
	info4.color_feed = color_feed;
	info5.color_feed = color_feed;
	info6.color_feed = color_feed;



	renderer.mainLoop();



	free(color_feed);

	return 0;
}
