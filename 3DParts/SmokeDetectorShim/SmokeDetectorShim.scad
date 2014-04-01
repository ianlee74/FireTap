outer_dia = 140.5;
inner_dia = 93.0;
center_dia = inner_dia/2 + (outer_dia-inner_dia)/4;

height = 10.0;

screw_dia = 4.0;

fudge = 0.1;

module smokeDetectorShim()
{
	union()
	{
		difference()
		{
			cylinder(h=height, r=outer_dia/2, center=true, $fn=200);
#			cylinder(h=height+fudge*2, r=inner_dia/2, center=true, $fn=200);
			
			for(i=[0:20:360])
			{
				translate([center_dia*sin(i), center_dia*cos(i)])
#					cylinder(h=height+fudge*2, r=8, center = true);
			}
		}

		screwBlock();

		mirror([0, 1, 0])
			screwBlock();
	}
}

module screwBlock()
{
	difference()
	{
		translate([0, inner_dia/2 - 11.5 + fudge])
#			cube([35.0, 23.0, height], center=true);
			
		translate([0, inner_dia/2 - 14.5 - screw_dia/2])
			cylinder(h=height+fudge*2, r=screw_dia/2, center=true, $fn=100);
	}
}

smokeDetectorShim();