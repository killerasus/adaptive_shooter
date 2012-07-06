#include <ClanLib/core.h>
#include <ClanLib/display.h>
#include <ClanLib/gl1.h>
#include <ClanLib/application.h>

#include <iostream>
#include <string>

class DisplayProgram
{
public:
	static void printUsage()
	{
		std::cout << "Outliner: (c) Bruno Baere Pederassi Lomba de Araujo\tUses ClanLib\n";
		std::cout << "Usage:\n\toutliner filename\n\nfilename\tFile to be outlined.\n\nReturn: filename.out\n";
	}

	static int main(const std::vector<CL_String> &args){

#if _DEBUG
		CL_ConsoleWindow console("Debug Console", 80, 160);
		CL_Console::write_line("Arguments: %1", args.size());

		std::cout << "Arguments: " + args.size();

		for( unsigned int i = 0; i < args.size(); i++ )
		{
			CL_Console::write( "[%1] = %2\t", i, args[i] );
		}

		CL_Console::write_line("");
#endif

		if(args.size() <= 1)
		{
			printUsage();
			return 0;
		}

		CL_SetupCore setup_core;
		CL_SetupDisplay setup_display;
		CL_SetupGL1 setup_gl1;
		CL_ResourceManager manager("../../../../data/resources.xml");

		try
		{
			CL_String filename("starfox50.png");

			CL_CollisionOutline outline("C:\\Users\\Bruno\\Documents\\Mestrado\\2011.2\\Dissertacao\\Jogo\\build\\Win32\\Release\\Outliner\\starfox50.png", 128, accuracy_high, true);
			
			//outline.load( filename.c_str() );

			//outline.load("C:\\Users\\Bruno\\Documents\\Mestrado\\2011.2\\Dissertacao\\Jogo\\build\\Win32\\Release\\Outliner\\starfox50.png");

			//CL_CollisionOutline generated( filename );

			outline.save( "C:\\Users\\Bruno\\Documents\\Mestrado\\2011.2\\Dissertacao\\Jogo\\build\\Win32\\Release\\Outliner\\starfox50.out" );
		}
		catch (CL_Exception &exception)
		{
			CL_ConsoleWindow console("Console", 80, 160);
			CL_Console::write("Exception caught: " + exception.get_message_and_stack_trace());
			console.display_close_message();
			return -1;
		}
		return 0;
	}
};

// Create global application object, you MUST include this line or the application start-up will fail to locate your application object.
CL_ClanApplication app(&DisplayProgram::main);