#pragma once

#define DllExport   __declspec( dllexport )

#include <vector>
namespace AI_TicTacToe
{
#define FIELD_SIDE (3)
#define AI_MARK	(2)
#define PLAYER_MARK	(1)
	using Field = std::vector<std::vector<int> >;

	namespace AI_Helper
	{
		DllExport bool IsCellInbound(int x, int y);
	}

	//AI --- will put an array with '2', when player will use '1'
	class DllExport AI
	{
	public:
		explicit AI(Field &field);
		virtual ~AI() = default;
		virtual void MakeATurn() = 0;

	protected:
		Field &_field; //3x3 array
		int _turns_num = 0; //for now if it`s first turn (and for statistics)
		int _last_mark_x = 0; //last mark is needed for AI to know were to continue 
		int _last_mark_y = 0;

		bool TryToPutMark(int x, int y);

		virtual bool TryToWin();
		virtual bool TryToObstructOpponent();
		virtual void MakeMyMark() = 0;
		virtual void MakeFirstMark() = 0;

	};
}
