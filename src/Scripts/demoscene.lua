-- Demo scene description file

--[[ 
 scene table = { 1 or more waves }
 wave table = { 1 or more enemies }
 enemy table = { sprite resource, start x, start y, speed x, speed y, class }
]]--

scene = {
	-- Wave 1
	{	{"sprites/enemy2", 0, -40, 100, 200, "TestEnemy"},
		{"sprites/enemy2", 40, -40, 100, 200, "TestEnemy"},
		{"sprites/enemy2", 80, -40, 100, 200, "TestEnemy"}
	},
	-- Wave 2
	{	{"sprites/enemy1", 40, -40, 100, 200, "TestEnemy"},
		{"sprites/enemy1", 80, -80, 100, 200, "TestEnemy"},
		{"sprites/enemy1", 120, -40, 100, 200, "TestEnemy"}
	}
}