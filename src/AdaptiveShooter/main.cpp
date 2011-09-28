#include <ClanLib/core.h>
#include <ClanLib/display.h>
#include <ClanLib/gl.h>
#include <ClanLib/application.h>

class DisplayProgram
{
public:
	static int main(const std::vector<CL_String> &args)
	{
		CL_SetupCore setup_core;
		CL_SetupDisplay setup_display;
		CL_SetupGL setup_gl;

		try
		{
			CL_DisplayWindow window("Hello World", 640, 480);

			CL_GraphicContext gc = window.get_gc();
			CL_InputDevice keyboard = window.get_ic().get_keyboard();
			CL_Font font(gc, "Tahoma", 30);

			while (!keyboard.get_keycode(CL_KEY_ESCAPE))
			{
				gc.clear(CL_Colorf::cadetblue);

				CL_Draw::line(gc, 0, 110, 640, 110, CL_Colorf::yellow);
				font.draw_text(gc, 100, 100, "Hello World!", CL_Colorf::lightseagreen);

				// Make the stuff visible:
				window.flip();

				// Read messages from the windowing system message queue, if any are available:
				CL_KeepAlive::process();

				// Avoid using 100% CPU in the loop:
				CL_System::sleep(10);
			}
		}
		catch(CL_Exception &exception)
		{
			// Create a console window for text-output if not available
			CL_ConsoleWindow console("Console", 80, 160);
			CL_Console::write_line("Exception caught: " + exception.get_message_and_stack_trace());
			console.display_close_message();

			return -1;
		}

		return 0;
	}
};

// Create global application object, you MUST include this line or the application start-up will fail to locate your application object.
CL_ClanApplication app(&DisplayProgram::main);