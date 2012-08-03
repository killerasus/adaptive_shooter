-- Demo scene description file

--[[ 
 scene table = { 1 or more waves }
 wave table = { 1 or more enemies }
 enemy table = { sprite resource, start x, start y, speed x, speed y, behavior }
]]--

--[[
Behaviors:
0 - Static
1 - Shoot
2 - Go down
4 - Go horizontal
8 - Go sinusoid down
--]]

scene = {
	-- Wave 1
	{	{"sprites/enemy2", 0, 40, 100, 200, 2},
		{"sprites/enemy2", 40, 80, 100, 200, 2},
		{"sprites/enemy2", 80, 120, 100, 200, 2}
	},
	-- Wave 2
	{	{"sprites/enemy1", 40, 40, 100, 200, 3},
		{"sprites/enemy1", 80, 80, 100, 200, 3},
		{"sprites/enemy1", 120, 120, 100, 200, 3}
	},
	-- Wave 3
	{
		{"sprites/enemy1", 40, 40, 100, 200, 7},
		{"sprites/enemy1", 80, 80, 100, 200, 7},
		{"sprites/enemy1", 120, 120, 100, 200, 7}
	}
}