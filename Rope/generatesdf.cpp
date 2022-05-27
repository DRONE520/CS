#include "rope.h"
int rope()
{
	ofstream is("model2.txt");
	float rad = 0.025, length=7;// Радиус шара, длина веревки.
	float x= 0.1, y = 0.1, z = 0.1;// Стороны кубика.
	int kol = length / (2 * rad);// Кол-во шаров.
	// Начало sdf файла.
	is << "<?xml version='1.0'?>\n<sdf version = '1.6'>\n<model name = 'my_rope'>\n";


	// Добавление крепления веревки. 
	is << "<model name='fastening'>\n<link name='link'>\n<inertial>\n<mass>1000</mass>\n<inertia>\n<ixx>0.166667</ixx>\n<ixy>0</ixy>\n<ixz>0</ixz>\n<iyy>0.166667</iyy>\n<iyz>0</iyz>\n<izz>0.166667</izz>\n";
	is << "</inertia>\n<pose>0 0 0 0 -0 0</pose>\n</inertial>\n<self_collide>0</self_collide>\n<enable_wind>0</enable_wind>\n<kinematic>0</kinematic>\n<pose>0 0 0 0 -0 0</pose>\n";
	is << "<gravity>1</gravity>\n<visual name='visual'>\n<geometry>\n<box>\n<size>"<< x <<" "<< y <<" "<< z <<"</size>\n</box>\n</geometry>\n<material>\n";
	is << "<shader type='pixel'>\n<normal_map>__default__</normal_map>\n</shader>\n<ambient>0.3 0.3 0.3 1</ambient>\n<diffuse>0.7 0.7 0.7 1</diffuse>\n<specular>0.01 0.01 0.01 1</specular>\n";
	is << "<emissive>0 0 0 1</emissive>\n</material>\n<pose>0 0 0 0 -0 0</pose>\n<transparency>0</transparency>\n<cast_shadows>1</cast_shadows>\n</visual>\n<collision name='collision'>\n<laser_retro>0</laser_retro>\n";
	is << "<max_contacts>10</max_contacts>\n<pose>0 0 0 0 -0 0</pose>\n<geometry>\n<box>\n<size>0.008427 0.007421 0.009779</size>\n</box>\n</geometry>\n<surface>\n<friction>\n<ode>\n<mu>1</mu>\n";
	is << "<mu2>1</mu2>\n<fdir1>0 0 0</fdir1>\n<slip1>0</slip1>\n<slip2>0</slip2>\n</ode>\n<torsional>\n<coefficient>1</coefficient>\n<patch_radius>0</patch_radius>\n<surface_radius>0</surface_radius>\n";
	is << "<use_patch_radius>1</use_patch_radius>\n<ode>\n<slip>0</slip>\n</ode>\n</torsional>\n</friction>\n<bounce>\n<restitution_coefficient>0</restitution_coefficient>\n<threshold>1e+06</threshold>\n";
	is << "</bounce>\n<contact>\n<collide_without_contact>0</collide_without_contact>\n<collide_without_contact_bitmask>1</collide_without_contact_bitmask>\n<collide_bitmask>1</collide_bitmask>\n";
	is << "<ode>\n<soft_cfm>0</soft_cfm>\n<soft_erp>0.2</soft_erp>\n<kp>1e+13</kp>\n<kd>1</kd>\n<max_vel>0.01</max_vel>\n<min_depth>0</min_depth>\n</ode><bullet>\n<split_impulse>1</split_impulse>\n";
	is << "<split_impulse_penetration_threshold>-0.01</split_impulse_penetration_threshold>\n<soft_cfm>0</soft_cfm>\n<soft_erp>0.2</soft_erp>\n<kp>1e+13</kp>\n<kd>1</kd>\n</bullet>\n";
	is << "</contact>\n</surface>\n</collision>\n</link>\n<static>0</static>\n<allow_auto_disable>1</allow_auto_disable>\n</model>\n";

	// Добавление шаров.
	for (int i = 0; i < kol; i++)
	{
		is << "<model name='ball_bearing_"<< i<<"'>";
		is << "\n<link name='link'>\n";
		is << "<pose>" << 0 <<" "<< 0 << " " << 0.003 << " " << 0 << " " << -0 << " " << 0 << "</pose>\n<inertial>\n<mass>0.0000000011</mass>\n<inertia>\n<ixx>3.96e-09</ixx>\n<ixy>0</ixy>\n<ixz>0</ixz>\n";
		is << "<iyy>3.96e-09</iyy>\n<iyz>0</iyz>\n<izz>3.96e-09</izz>\n</inertia>\n</inertial>\n";
		is << "<collision name='collision'>\n<geometry>\n<sphere>\n<radius>" << rad << "</radius>\n</sphere>\n</geometry>\n<surface>\n<contact>\n";
		is << "<poissons_ratio>0.305</poissons_ratio>\n<elastic_modulus>2e+11</elastic_modulus>\n<ode>\n<kp>100000</kp>\n<kd>100</kd>\n<max_vel>100</max_vel>\n";
		is << "<min_depth>0.001</min_depth>\n</ode>\n</contact>\n<friction>\n<torsional>\n<coefficient>1</coefficient>\n";
		is << "<use_patch_radius>0</use_patch_radius>\n<surface_radius>0.01</surface_radius>\n</torsional>\n</friction>\n</surface>\n</collision>\n";
		is << "<visual name='visual'>\n<geometry>\n<sphere>\n<radius>" << rad << "</radius>\n</sphere>\n</geometry>\n";
		is << "</visual>\n<velocity_decay>\n<linear>0</linear>\n<angular>0.005</angular>\n</velocity_decay>\n</link>\n";
		is << "<pose>" << 0 << " " << i*2*rad << " " << 0<< " " << 0 << " " << -0 << " " << 0 << "</pose>\n</model>\n";
	}
	// Добавление соединений между шарами.
	for (int i = 0; i < kol - 1; i++)
	{
		is << "<joint name='link_JOINT_" << i + 1 << "' type='ball'>\n";
		is << "<parent>ball_bearing_" << i << "::link</parent>\n";
		is << "<child>ball_bearing_" << i + 1 << "::link</child>\n";
		is << "</joint>\n";
	}

	// Добавление соединения между креплением и первым шаром.
	is << "<joint name='link_JOINT_" << kol<< "' type='ball'>\n";
	is << "<parent>fastening::link</parent>\n";
	is << "<child>ball_bearing_0::link</child>\n";
	is << "</joint>\n";

	// Конец.
	is << "<static>0</static>\n<allow_auto_disable>1</allow_auto_disable>\n</model>\n</sdf>";

	is.close(); // Закрываем файл.

	return 0;
}
