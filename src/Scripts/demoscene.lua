-- Demo scene description file

--[[
Behaviors:
0 - Static
1 - Shoot
2 - Go down
4 - Go horizontal
8 - Go sinusoid down
--]]

Behavior = {
	Static = 0,
	Shoot = 1,
	GoDown = 2,
	GoHorizontal = 4,
	GoSinusoidDown = 8
}

--[[ 
 scene table = { 1 or more waves }
 wave table = { 1 or more enemies }
 enemy table = { sprite resource, start x, start y, speed x, speed y, behavior }
]]--

scene = {
	-- Wave 1
	{
		{"sprites/enemy2", 0, 40, 0, 75, Behavior.GoDown},
		{"sprites/enemy2", 40, 80, 0, 75, Behavior.GoDown},
		{"sprites/enemy2", 80, 120, 0, 75, Behavior.GoDown}
	},
	-- Wave 2
	{
		{"sprites/enemy1", 40, 40, 0, 75, Behavior.GoDown + Behavior.Shoot},
		{"sprites/enemy1", 80, 80, 0, 75, Behavior.GoDown + Behavior.Shoot},
		{"sprites/enemy1", 120, 120, 0, 75, Behavior.GoDown + Behavior.Shoot}
	},
	-- Wave 3
	{
		{"sprites/enemy1", 40, 40, 300, 75, Behavior.GoDown + Behavior.GoHorizontal + Behavior.Shoot},
		{"sprites/enemy1", 80, 80, 300, 75, Behavior.GoDown + Behavior.GoHorizontal + Behavior.Shoot},
		{"sprites/enemy1", 120, 120, 300, 75, Behavior.GoDown + Behavior.GoHorizontal + Behavior.Shoot}
	},
	-- Wave 4
	{
		{"sprites/enemy1", 40, 40, 300, 75, Behavior.GoDown + Behavior.GoHorizontal + Behavior.GoSinusoidDown + Behavior.Shoot},
		{"sprites/enemy1", 80, 80, 300, 75, Behavior.GoDown + Behavior.GoHorizontal + Behavior.GoSinusoidDown + Behavior.Shoot},
		{"sprites/enemy1", 120, 120, 300, 75, Behavior.GoDown + Behavior.GoHorizontal + Behavior.GoSinusoidDown + Behavior.Shoot}
	}
}
