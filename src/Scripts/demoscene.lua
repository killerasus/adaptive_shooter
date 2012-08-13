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


local enemy1Width = 57
local enemy1Height = 26
local enemy2Width = 27
local enemy2Height = 26

local speedX = 100
local speedY = 50
local sidestep = 24
local incrementX = enemy2Width + 20
local incrementY = -enemy2Height - 20
local startY = -40

local startXPart1 = 258
local startXPart2 = 40
local startXPart3 = 479

local startXWave3Part1 = 235 - enemy1Width
local startXWave3Part2 = 640 - 235
local sidestepWave2 = enemy1Width - 10

scene = {
	-- Wave 1
	{
		-- Part 1
		{"sprites/enemy2", startXPart1, startY, 0, speedY, Behavior.GoDown},
		{"sprites/enemy2", startXPart1 + incrementX, startY, 0, speedY, Behavior.GoDown},
		{"sprites/enemy2", startXPart1 + 2*incrementX, startY, 0, speedY, Behavior.GoDown},
		{"sprites/enemy2", startXPart1 + sidestep, startY + incrementY, 0, speedY, Behavior.GoDown},
		{"sprites/enemy2", startXPart1 + sidestep + incrementX, startY + incrementY, 0, speedY, Behavior.GoDown},
		{"sprites/enemy2", startXPart1 + 2*sidestep, startY + 2*incrementY, 0, speedY, Behavior.GoDown},

		-- Part 2
		{"sprites/enemy2", startXPart2, 4*startY, 0, speedY, Behavior.GoDown},
		{"sprites/enemy2", startXPart2 + incrementX, 4*startY, 0, speedY, Behavior.GoDown},
		{"sprites/enemy2", startXPart2 + 2*incrementX, 4*startY, 0, speedY, Behavior.GoDown},
		{"sprites/enemy2", startXPart2 + sidestep, 4*startY + incrementY, 0, speedY, Behavior.GoDown},
		{"sprites/enemy2", startXPart2 + sidestep + incrementX, 4*startY + incrementY, 0, speedY, Behavior.GoDown},
		{"sprites/enemy2", startXPart2 + 2*sidestep, 4*startY + 2*incrementY, 0, speedY, Behavior.GoDown},

		--Part 3
		{"sprites/enemy2", startXPart3, 8.5*startY, 0, speedY, Behavior.GoDown},
		{"sprites/enemy2", startXPart3 + incrementX, 8.5*startY, 0, speedY, Behavior.GoDown},
		{"sprites/enemy2", startXPart3 + 2*incrementX, 8.5*startY, 0, speedY, Behavior.GoDown},
		{"sprites/enemy2", startXPart3 + sidestep, 8.5*startY + incrementY, 0, speedY, Behavior.GoDown},
		{"sprites/enemy2", startXPart3 + sidestep + incrementX, 8.5*startY + incrementY, 0, speedY, Behavior.GoDown},
		{"sprites/enemy2", startXPart3 + 2*sidestep, 8.5*startY + 2*incrementY, 0, speedY, Behavior.GoDown}
	},
	-- Wave 2
	{
		-- Part 1
		{"sprites/enemy2", startXPart1, startY, 0, speedY, Behavior.GoDown + Behavior.Shoot},
		{"sprites/enemy2", startXPart1 + incrementX, startY, 0, speedY, Behavior.GoDown},
		{"sprites/enemy2", startXPart1 + 2*incrementX, startY, 0, speedY, Behavior.GoDown + Behavior.Shoot},
		{"sprites/enemy2", startXPart1 + sidestep, startY + incrementY, 0, speedY, Behavior.GoDown},
		{"sprites/enemy2", startXPart1 + sidestep + incrementX, startY + incrementY, 0, speedY, Behavior.GoDown},
		{"sprites/enemy2", startXPart1 + 2*sidestep, startY + 2*incrementY, 0, speedY, Behavior.GoDown + Behavior.Shoot},

		-- Part 2
		{"sprites/enemy2", startXPart2, 4*startY, 0, speedY, Behavior.GoDown + Behavior.Shoot},
		{"sprites/enemy2", startXPart2 + incrementX, 4*startY, 0, speedY, Behavior.GoDown},
		{"sprites/enemy2", startXPart2 + 2*incrementX, 4*startY, 0, speedY, Behavior.GoDown + Behavior.Shoot},
		{"sprites/enemy2", startXPart2 + sidestep, 4*startY + incrementY, 0, speedY, Behavior.GoDown},
		{"sprites/enemy2", startXPart2 + sidestep + incrementX, 4*startY + incrementY, 0, speedY, Behavior.GoDown},
		{"sprites/enemy2", startXPart2 + 2*sidestep, 4*startY + 2*incrementY, 0, speedY, Behavior.GoDown + Behavior.Shoot},

		-- Part 3
		{"sprites/enemy2", startXPart3, 8*startY, 0, speedY, Behavior.GoDown + Behavior.Shoot},
		{"sprites/enemy2", startXPart3 + incrementX, 8*startY, 0, speedY, Behavior.GoDown},
		{"sprites/enemy2", startXPart3 + 2*incrementX, 8*startY, 0, speedY, Behavior.GoDown + Behavior.Shoot},
		{"sprites/enemy2", startXPart3 + sidestep, 8*startY + incrementY, 0, speedY, Behavior.GoDown},
		{"sprites/enemy2", startXPart3 + sidestep + incrementX, 8*startY + incrementY, 0, speedY, Behavior.GoDown},
		{"sprites/enemy2", startXPart3 + 2*sidestep, 8*startY + 2*incrementY, 0, speedY, Behavior.GoDown + Behavior.Shoot}
	},
	-- Wave 3
	{
		-- Part 1
		{"sprites/enemy1", startXWave3Part1, startY, speedX, speedY, Behavior.GoDown + Behavior.GoHorizontal},
		{"sprites/enemy1", startXWave3Part1 - sidestepWave2, startY + incrementY, speedX, speedY, Behavior.GoDown + Behavior.GoHorizontal},
		{"sprites/enemy1", startXWave3Part1 - 2*sidestepWave2, startY + 2*incrementY, speedX, speedY, Behavior.GoDown + Behavior.GoHorizontal},
		{"sprites/enemy1", startXWave3Part1 - 3*sidestepWave2, startY + 3*incrementY, speedX, speedY, Behavior.GoDown + Behavior.GoHorizontal},
		{"sprites/enemy1", startXWave3Part1 - 4*sidestepWave2, startY + 4*incrementY, speedX, speedY, Behavior.GoDown + Behavior.GoHorizontal},

		-- Part 2
		{"sprites/enemy1", startXWave3Part2, 5*startY, speedX, speedY, Behavior.GoDown + Behavior.GoHorizontal + Behavior.Shoot},
		{"sprites/enemy1", startXWave3Part2 + sidestepWave2, 5*startY + incrementY, speedX, speedY, Behavior.GoDown + Behavior.GoHorizontal + Behavior.Shoot},
		{"sprites/enemy1", startXWave3Part2 + 2*sidestepWave2, 5*startY + 2*incrementY, speedX, speedY, Behavior.GoDown + Behavior.GoHorizontal + Behavior.Shoot},
		{"sprites/enemy1", startXWave3Part2 + 3*sidestepWave2, 5*startY + 3*incrementY, speedX, speedY, Behavior.GoDown + Behavior.GoHorizontal + Behavior.Shoot},
		{"sprites/enemy1", startXWave3Part2 + 4*sidestepWave2, 5*startY + 4*incrementY, speedX, speedY, Behavior.GoDown + Behavior.GoHorizontal + Behavior.Shoot}
	},
	-- Wave 4
	{
	-- Part 1
		{"sprites/enemy1", startXWave3Part1, startY, speedX, speedY, Behavior.GoDown + Behavior.GoHorizontal + Behavior.Shoot},
		{"sprites/enemy1", startXWave3Part1 - sidestepWave2, startY + incrementY, speedX, speedY, Behavior.GoDown + Behavior.GoHorizontal + Behavior.Shoot},
		{"sprites/enemy1", startXWave3Part1 - 2*sidestepWave2, startY + 2*incrementY, speedX, speedY, Behavior.GoDown + Behavior.GoHorizontal + Behavior.Shoot},
		{"sprites/enemy1", startXWave3Part1 - 3*sidestepWave2, startY + 3*incrementY, speedX, speedY, Behavior.GoDown + Behavior.GoHorizontal + Behavior.Shoot},
		{"sprites/enemy1", startXWave3Part1 - 4*sidestepWave2, startY + 4*incrementY, speedX, speedY, Behavior.GoDown + Behavior.GoHorizontal + Behavior.Shoot},

		-- Part 2
		{"sprites/enemy1", startXWave3Part2, 5*startY, speedX, speedY, Behavior.GoDown + Behavior.GoHorizontal + Behavior.Shoot},
		{"sprites/enemy1", startXWave3Part2 + sidestepWave2, 5*startY + incrementY, speedX, speedY, Behavior.GoDown + Behavior.GoHorizontal + Behavior.Shoot},
		{"sprites/enemy1", startXWave3Part2 + 2*sidestepWave2, 5*startY + 2*incrementY, speedX, speedY, Behavior.GoDown + Behavior.GoHorizontal + Behavior.Shoot},
		{"sprites/enemy1", startXWave3Part2 + 3*sidestepWave2, 5*startY + 3*incrementY, speedX, speedY, Behavior.GoDown + Behavior.GoHorizontal + Behavior.Shoot},
		{"sprites/enemy1", startXWave3Part2 + 4*sidestepWave2, 5*startY + 4*incrementY, speedX, speedY, Behavior.GoDown + Behavior.GoHorizontal + Behavior.Shoot},

		-- Part 3
		{"sprites/enemy1", startXWave3Part1, 10*startY, speedX, speedY, Behavior.GoDown + Behavior.GoHorizontal + Behavior.Shoot},
		{"sprites/enemy1", startXWave3Part1 - sidestepWave2, 10*startY + incrementY, speedX, speedY, Behavior.GoDown + Behavior.GoHorizontal + Behavior.Shoot},
		{"sprites/enemy1", startXWave3Part1 - 2*sidestepWave2, 10*startY + 2*incrementY, speedX, speedY, Behavior.GoDown + Behavior.GoHorizontal + Behavior.Shoot},
		{"sprites/enemy1", startXWave3Part2, 10*startY, speedX, speedY, Behavior.GoDown + Behavior.GoHorizontal + Behavior.Shoot},
		{"sprites/enemy1", startXWave3Part2 + sidestepWave2, 10*startY + incrementY, speedX, speedY, Behavior.GoDown + Behavior.GoHorizontal + Behavior.Shoot},
		{"sprites/enemy1", startXWave3Part2 + 2*sidestepWave2, 10*startY + 2*incrementY, speedX, speedY, Behavior.GoDown + Behavior.GoHorizontal + Behavior.Shoot}
	},
	-- Wave 5
	{
		-- Part 1
		{"sprites/enemy2", startXPart1, startY, 0, speedY, Behavior.GoDown + Behavior.Shoot},
		{"sprites/enemy2", startXPart1 + incrementX, startY, 0, speedY, Behavior.GoDown},
		{"sprites/enemy2", startXPart1 + 2*incrementX, startY, 0, speedY, Behavior.GoDown + Behavior.Shoot},
		{"sprites/enemy2", startXPart1 + sidestep, startY + incrementY, 0, speedY, Behavior.GoDown},
		{"sprites/enemy2", startXPart1 + sidestep + incrementX, startY + incrementY, 0, speedY, Behavior.GoDown},

		-- Part 2
		{"sprites/enemy2", startXPart2, 4*startY, 0, speedY, Behavior.GoDown + Behavior.Shoot},
		{"sprites/enemy2", startXPart2 + incrementX, 4*startY, 0, speedY, Behavior.GoDown},
		{"sprites/enemy2", startXPart2 + 2*incrementX, 4*startY, 0, speedY, Behavior.GoDown + Behavior.Shoot},
		{"sprites/enemy2", startXPart2 + sidestep, 4*startY + incrementY, 0, speedY, Behavior.GoDown},
		{"sprites/enemy2", startXPart2 + sidestep + incrementX, 4*startY + incrementY, 0, speedY, Behavior.GoDown},

		-- Part 3
		{"sprites/enemy2", startXPart3, 8*startY, 0, speedY, Behavior.GoDown + Behavior.Shoot},
		{"sprites/enemy2", startXPart3 + incrementX, 8*startY, 0, speedY, Behavior.GoDown},
		{"sprites/enemy2", startXPart3 + 2*incrementX, 8*startY, 0, speedY, Behavior.GoDown + Behavior.Shoot},
		{"sprites/enemy2", startXPart3 + sidestep, 8*startY + incrementY, 0, speedY, Behavior.GoDown},
		{"sprites/enemy2", startXPart3 + sidestep + incrementX, 8*startY + incrementY, 0, speedY, Behavior.GoDown}
	},
	-- Wave 6
	{
		{"sprites/enemy1", 40, 40, 300, 75, Behavior.GoDown + Behavior.GoHorizontal + Behavior.GoSinusoidDown + Behavior.Shoot},
		{"sprites/enemy1", 80, 80, 300, 75, Behavior.GoDown + Behavior.GoHorizontal + Behavior.GoSinusoidDown + Behavior.Shoot},
		{"sprites/enemy1", 120, 120, 300, 75, Behavior.GoDown + Behavior.GoHorizontal + Behavior.GoSinusoidDown + Behavior.Shoot}
	}
}
