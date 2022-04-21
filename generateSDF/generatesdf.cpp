#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
using namespace std;
int main()
{
	ofstream is("model2.txt");
	float rad = 0.001, length=1;
	int kol = length / (2 * rad);
	//начало
	is << "<?xml version='1.0'?>\n<sdf version = '1.7'>\n<model name = 'my_rope'>\n";
	//добавление шаров
	for (int i = 0; i < kol; i++)
	{
		is << "<model name='ball_bearing_"<< i<<"'>";
		is << "\n<link name='link'>\n";
		is << "<pose>" << 0 <<" "<< 0 << " " << 0.003 << " " << 0 << " " << -0 << " " << 0 << "</pose>\n<inertial>\n<mass>0.0011</mass>\n<inertia>\n<ixx>3.96e-09</ixx>\n<ixy>0</ixy>\n<ixz>0</ixz>\n";
		is << "<iyy>3.96e-09</iyy>\n<iyz>0</iyz>\n<izz>3.96e-09</izz>\n</inertia>\n</inertial>\n";
		is << "<collision name='collision'>\n<geometry>\n<sphere>\n<radius>" << rad << "</radius>\n</sphere>\n</geometry>\n<surface>\n<contact>\n";
		is << "<poissons_ratio>0.305</poissons_ratio>\n<elastic_modulus>2e+11</elastic_modulus>\n<ode>\n<kp>100000</kp>\n<kd>100</kd>\n<max_vel>100</max_vel>\n";
		is << "<min_depth>0.001</min_depth>\n</ode>\n</contact>\n<friction>\n<torsional>\n<coefficient>1</coefficient>\n";
		is << "<use_patch_radius>0</use_patch_radius>\n<surface_radius>0.01</surface_radius>\n</torsional>\n</friction>\n</surface>\n</collision>\n";
		is << "<visual name='visual'>\n<geometry>\n<sphere>\n<radius>" << rad << "</radius>\n</sphere>\n</geometry>\n<material>\n<script>\n<uri>file://media/materials/scripts/gazebo.material</uri>\n";
		is << "<name>Gazebo/Grey</name>\n</script>\n</material>\n</visual>\n<velocity_decay>\n<linear>0</linear>\n<angular>0.005</angular>\n</velocity_decay>\n</link>\n";
		is << "<pose>" << 0 << " " << 0 << " " << i*2*rad << " " << 0 << " " << -0 << " " << 0 << "</pose>\n</model>\n";
	}
	//добавление соединений
	for (int i = 0; i < kol - 1; i++)
	{
		is << "<joint name='link_JOINT_" << i + 1 << "' type='ball'\n>";
		is << "<parent>ball_bearing_" << i << "::link</parent>\n";
		is << "<child>ball_bearing_" << i + 1 << "::link</child>\n";
		is << "<pose>" << 0 << " " << 0 << " " << 0 << " " << 0 << " " << -0 << " " << 0 << " " << "</pose>\n";
		is << "<physics>\n<ode>\n<limit>\n<cfm>0</cfm>\n<erp>0.2</erp>\n</limit>\n<suspension>\n<cfm>0</cfm>\n<erp>0.2</erp>\n</suspension>\n</ode>\n";
		is << "</physics>\n</joint>\n";
	}
	//конец
	is << "<static>0</static>\n<allow_auto_disable>1</allow_auto_disable>\n</model>\n</sdf>";

	is.close(); // закрываем файл

	return 0;
}
