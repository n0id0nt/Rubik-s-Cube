#include "MovePanel.h"

void MovePanel::Render()
{
	StartPanelRender();

	ImGui::InputText("Moves", (char*)moves.c_str(), moves.size());

	if (ImGui::Button("Make move"))
	{
		moves.clear();
	}

	EndPanelRender();
}
