
module halfHydrant()
{
	color("red")
	union()
	{
		translate([-2.8, 20, 0])
		import("fire_hydrant.stl");

		translate([-25, 0, -1])
		cube([50, 20, 80]);
	}
}

//halfHydrant();

import("fire_hydrant.stl");
