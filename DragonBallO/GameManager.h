#pragma once

class GameManager {
public:
		bool Init();
		bool Cleanup();
		bool Render();
		void Update();
};