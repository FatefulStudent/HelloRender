echo "creating dir build"
mkdir build

echo "glfw dependencies https://www.glfw.org/docs/latest/compile.html"
sudo apt install xorg-dev

echo "glew dependencies. see https://github.com/nigels-com/glew"
sudo apt-get install build-essential libxmu-dev libxi-dev libgl-dev libglfw3-dev libgl1-mesa-dev libglu1-mesa-dev