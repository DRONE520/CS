mkdir -p ~/cop/cs/workspace/src
cd ~/cop/cs/workspace/src
catkin_init_workspace
catkin_create_pkg lab1
cd lab1
sudo rm CMakeLists.txt package.xml
cd ~/cop/cs/Rope
cp CMakeLists.txt ../workspace/src/lab1/
cp generatesdf.cpp ../workspace/src/lab1/
cp newRope.cpp ../workspace/src/lab1/
cp rope.h ../workspace/src/lab1/
cp package.xml ../workspace/src/lab1/
cd ~/cop/cs/workspace/src/lab1
cmake .
make
cd devel/lib/lab1/
./lab1
