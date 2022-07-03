#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include "../camera.h"


namespace UI {
  void Menu(bool& show_menu, bool& show_stats, Camera& camera, ImVec4& clear_color, float main_window_width, float main_window_height);
}