#include "Camera.h"
#include "../Libs/Imgui/imgui.h"

namespace {
	static const VECTOR3 defPosition(2, 6, -10);
	static const VECTOR3 defLook(0, 2, 0);
}

Camera::Camera()
{
	position = defPosition;
	look = defLook;
}

Camera::~Camera()
{
}

void Camera::Update()
{
	ImGui::Begin("Camera");
	if (ImGui::TreeNode("Position")) {
		ImGui::InputFloat("X", &position.x);
		ImGui::InputFloat("Y", &position.y);
		ImGui::InputFloat("Z", &position.z);
		if (ImGui::Button("RESET")) {
			position = defPosition;
		}
		ImGui::TreePop();
	}
	if (ImGui::TreeNode("Look")) {
		ImGui::InputFloat("X", &look.x);
		ImGui::InputFloat("Y", &look.y);
		ImGui::InputFloat("Z", &look.z);
		if (ImGui::Button("RESET")) {
			look = defLook;
		}
		ImGui::TreePop();
	}
	ImGui::End();
}

void Camera::Draw()
{
	GameDevice()->m_vEyePt = position; // カメラ座標
	GameDevice()->m_vLookatPt = look; // 注視点
	GameDevice()->m_mView = XMMatrixLookAtLH(     // ビューマトリックス
		position, look, VECTOR3(0, 1, 0));
}
