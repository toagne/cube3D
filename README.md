# Cube3D
Transform a simple 2D map into an interactive 3D environment using raycasting, the same core technique behind pioneering games like Wolfenstein 3D. Cube3D demonstrates foundational graphics programming, efficient event handling, and basic texture mapping.

## Key Features
- Raycasting cast rays from the player’s viewpoint to determine wall intersections on a 2D grid. Each calculation converts two-dimensional map data into a three-dimensional perspective.
- Texture are applied to each wall face (north, south, east, west) for visual detail. Floor and ceiling coloring options are also supported.
- Responsive player navigation with adjustable movement and rotation speeds. Smooth transitions and collision detection ensure a consistent experience.
- Configurable levels in plain-text .cub files. The parser reads map layouts, texture paths, and color values, allowing rapid iteration without recompilation.
- Simple 2D sprites—such as items or decorative objects—overlaid within the 3D world.

## Architecture Overview
- Initialization
     - Parse the .cub file: load map dimensions, texture file paths, and color codes for floor and ceiling.
- Main Loop
     - Event Handling: Capture keyboard input for movement and rotation.
     - Raycasting: For each column on screen, send a ray, calculate distance to wall, select texture slice.
     - Rendering: Draw floor, wall slice, and ceiling for every frame.
- Cleanup
     - Release allocated memory and close the window on exit.

<img width="500" alt="Screenshot 2025-06-09 alle 10 29 08" src="https://github.com/user-attachments/assets/a837a69c-f580-4cdf-9711-6802935f5037" />

<img width="500" alt="Screenshot 2025-06-09 alle 10 30 12" src="https://github.com/user-attachments/assets/f3270582-5001-4a0d-b13c-2fda340cc136" />


